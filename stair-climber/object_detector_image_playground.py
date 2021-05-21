
# Import packages
import glob
import importlib.util
import os

import cv2
import numpy as np


def detect_pictogram_image(image):
    MODEL_NAME = "tflite"
    GRAPH_NAME = "model_optimize2_V4.tflite"
    LABELMAP_NAME = "labelmap_path.txt"
    min_conf_threshold = 0.1

    # Parse input image name and directory.
    IM_NAME = image

    # Import TensorFlow libraries
    # If tflite_runtime is installed, import interpreter from tflite_runtime, else import from regular tensorflow
    # If using Coral Edge TPU, import the load_delegate library
    pkg = importlib.util.find_spec('tflite_runtime')
    if pkg:
        print("hi")
        from tflite_runtime.interpreter import Interpreter

    else:
        from tensorflow.lite.python.interpreter import Interpreter

    # Get path to current working directory
    CWD_PATH = os.getcwd()

    PATH_TO_IMAGES = os.path.join(CWD_PATH, IM_NAME)
    images = glob.glob(PATH_TO_IMAGES)

    # Path to .tflite file, which contains the model that is used for object detection
    PATH_TO_CKPT = os.path.join(CWD_PATH, MODEL_NAME, GRAPH_NAME)

    # Path to label map file
    PATH_TO_LABELS = os.path.join(CWD_PATH, MODEL_NAME, LABELMAP_NAME)

    # Load the label map
    with open(PATH_TO_LABELS, 'r') as f:
        labels = [line.strip() for line in f.readlines()]

    # Have to do a weird fix for label map if using the COCO "starter model" from
    # https://www.tensorflow.org/lite/models/object_detection/overview
    # First label is '???', which has to be removed.
    if labels[0] == '???':
        del (labels[0])

    # Load the Tensorflow Lite model.
    # If using Edge TPU, use special load_delegate argument
    interpreter = Interpreter(model_path=PATH_TO_CKPT)

    interpreter.allocate_tensors()

    # Get model details
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()
    height = input_details[0]['shape'][1]
    width = input_details[0]['shape'][2]

    floating_model = (input_details[0]['dtype'] == np.float32)

    input_mean = 127.5
    input_std = 127.5
    bricks = list()
    steps = list()
    # Loop over every image and perform detection
    for image_path in images:

        # Load image and resize to expected shape [1xHxWx3]
        image = cv2.imread(image_path)
        image_center = image.shape[1] / 2
        print("center of the image: " + str(image_center))
        image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        imH, imW, _ = image.shape
        image_resized = cv2.resize(image_rgb, (width, height))
        input_data = np.expand_dims(image_resized, axis=0)

        # Normalize pixel values if using a floating model (i.e. if model is non-quantized)
        if floating_model:
            input_data = (np.float32(input_data) - input_mean) / input_std

        # Perform the actual detection by running the model with the image as input
        interpreter.set_tensor(input_details[0]['index'], input_data)
        interpreter.invoke()

        # Retrieve detection results
        boxes = interpreter.get_tensor(output_details[0]['index'])[0]  # Bounding box coordinates of detected objects
        classes = interpreter.get_tensor(output_details[1]['index'])[0]  # Class index of detected objects
        scores = interpreter.get_tensor(output_details[2]['index'])[0]  # Confidence of detected objects
        # num = interpreter.get_tensor(output_details[3]['index'])[0]  # Total number of detected objects (inaccurate and not needed)

        # Loop over all detections and draw detection box if confidence is above minimum threshold
        linksObe = (70, 210)
        rechtsUne = (500, 225)

        # cv2.rectangle(image, linksObe, rechtsUne, (200, 255, 200), 2)
        spacing = int((500 - 70) / 8)

        # cv2.rectangle(image, (105, 150), (480, 160), (200, 255, 200), 2)

        print(linksObe[0] + spacing)
        # cv2.rectangle(image, (linksObe[0] + spacing, linksObe[1]), (500, 225), (0, 0, 0), 2)


        steps.append((70, 210, 500, 225))
        # steps.append(((105, 150, 480, 160)))
        for i in range(len(scores)):
            if (scores[i] > min_conf_threshold) and (scores[i] <= 1.0):
                # Get bounding box coordinates and draw box
                # Interpreter can return coordinates that are outside of image dimensions, need to force them to be within image using max() and min()
                ymin = int(max(1, (boxes[i][0] * imH)))
                xmin = int(max(1, (boxes[i][1] * imW)))
                ymax = int(min(imH, (boxes[i][2] * imH)))
                xmax = int(min(imW, (boxes[i][3] * imW)))

                label_center = (xmax + xmin) / 2

                # print((xmin, ymin), (xmax, ymax))
                cv2.rectangle(image, (xmin, ymin), (xmax, ymax), (10, 255, 0), 2)

                # Draw label
                object_name = labels[int(classes[i])]
                if object_name == "brick":  # Look up object name from "labels" array using class index
                    bricks.append((xmin, ymin, xmax, ymax))
                elif object_name == "step":
                    steps.append((xmin, ymin, xmax, ymax))
                # label = '%s: %d%%' % (object_name, int(scores[i] * 100))  # Example: 'person: 72%'
                # labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.7, 2)  # Get font size
                # label_ymin = max(ymin, labelSize[1] + 10)  # Make sure not to draw label too close to top of window
                # cv2.rectangle(image, (xmin, label_ymin - labelSize[1] - 10),
                #               (xmin + labelSize[0], label_ymin + baseLine - 10), (255, 255, 255),
                #               cv2.FILLED)  # Draw white box to put label text in
                # cv2.putText(image, label, (xmin, label_ymin - 7), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0),
                #             2)  # Draw label text

        # ------ MAP bricks and steps to matrix
        # should be moved somewhere else
        bricks = np.array(bricks)
        steps = np.array(steps)

        stair_matrix = np.ones((7, 8))
        sorted_steps = steps[steps[:, 1].argsort()[::-1][:len(steps)]]
        sorted_bricks = bricks[bricks[:, 1].argsort()[::-1][:len(bricks)]]
        print(sorted_bricks)
        print(sorted_steps)
        print()

        for idx, step in enumerate(sorted_steps[:-1]):  # iterate all but last
            step_length = step[2] - step[0]
            raster_size = int(step_length / 8)
            print("step" + str(step))
            print("step lenght: " + str(step_length))
            print("raster size: " + str(raster_size))
            for brick in sorted_bricks:
                if step[1] + 5 > brick[3] > sorted_steps[idx + 1][1] + 5:  # 5 is a buffer is the stone is taller than next step
                    print("Brick: " + str(brick) + " is on " + str(idx + 1) + " step")
                    relativ_brick_pos1 = brick[0] - step[0]  # subtract the step start left
                    relativ_brick_pos2 = brick[2] - step[0]
                    first_field = int(relativ_brick_pos1 / raster_size)
                    second_field = int(relativ_brick_pos2 / raster_size)
                    # print(first_field)
                    # print(second_field)
                    for i in range(first_field, second_field + 1):
                        stair_matrix[5 - idx, i] = 0  # 7 floors - bottom and top floor = 5
                    print(stair_matrix)

        print("------------------------------")

        # All the results have been drawn on the image, now display the image
        cv2.imshow('Object detector', image)

        # Press any key to continue to next image, or press 'q' to quit
        if cv2.waitKey(0) == ord('q'):
            break


    # Clean up
    cv2.destroyAllWindows()
