# Import packages
import datetime

import cv2
import numpy as np
from time import sleep
from picamera import PiCamera


# Class for Object Detection.
from tensor_setup import TensorSetup


class ObjectDetector:
    interpreter = None
    input_details = None
    output_details = None
    floating_model = None
    height = 300
    width = 300
    labels = []
    min_conf_threshold = 0

    def __init__(self, tensor_config):
        # Define and parse input arguments
        # Default values are fine. Make sure detect.tflite & labelmap.txt are accessible
        self.interpreter = tensor_config.interpreter
        self.input_details = tensor_config.input_details
        self.output_details = tensor_config.output_details
        self.floating_model = tensor_config.floating_model
        self.height = tensor_config.height
        self.width = tensor_config.width
        self.labels = tensor_config.labels
        self.min_conf_threshold = tensor_config.min_conf_threshold

    def take_picture(self, path):
        camera = PiCamera()
        camera.resolution = (2592, 1944) #max resolution

        camera.start_preview()
        sleep(3) # wait 3 secs so camera can adjust to light
        camera.capture(path)
        camera.stop_preview()

    def analyze_picture (self, path):
        object_name = None

        MODEL_NAME = "tflite"
        GRAPH_NAME = "detect.tflite"
        LABELMAP_NAME = "labelmap.txt"
        min_conf_threshold = 0.5

        # Parse input image name and directory.
        IM_NAME = path

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

        print("Found the follwing labels: ")
        print(self.labels)

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
            oldScore = 0
            for i in range(len(scores)):
                if ((scores[i] > min_conf_threshold) and (scores[i] <= 1.0)):

                    # Draw label
                    object_name = labels[int(classes[i])]  # Look up object name from "labels" array using class index

                    print(object_name)
                    if scores[i] > oldScore:
                        oldScore = scores[i]
                        # Get Label
                        object_name = self.labels[int(classes[i])]  # Look up object name from "labels" array using class index
                        print(scores[i])
                        print(classes[i])
                        print(object_name)

            # All the results have been drawn on the image, now display the image
            cv2.imshow('Object detector', image)

            # Press any key to continue to next image, or press 'q' to quit
            if cv2.waitKey(0) == ord('q'):
                break

        # Clean up
        cv2.destroyAllWindows()
        return object_name
        
    # Analyze an available videoStream with the current model
    # videoStream - running stream from the VideoStream Class
    # ttl - Time to live, in seconds
    def analyze_video(self, videostream, ttl):
        print(self.labels)
        object_name = None
        # Function will run for ttl seconds
        addTime = datetime.timedelta(seconds=ttl)
        stop = datetime.datetime.now() + addTime

        # for frame1 in camera.capture_continuous(rawCapture, format="bgr",use_video_port=True):
        while datetime.datetime.now() < stop:
            # Grab frame from video stream
            frame1 = videostream.read()

            # Acquire frame and resize to expected shape [1xHxWx3]
            frame = frame1.copy()
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            frame_resized = cv2.resize(frame_rgb, (self.width, self.height))
            input_data = np.expand_dims(frame_resized, axis=0)

            # Normalize pixel values if using a floating model (i.e. if model is non-quantized)
            if self.floating_model:
                input_data = (np.float32(input_data) - 127.5) / 127.5

            # Perform the actual detection by running the model with the image as input
            self.interpreter.set_tensor(self.input_details[0]['index'], input_data)
            self.interpreter.invoke()

            # Retrieve detection results
            boxes = self.interpreter.get_tensor(self.output_details[0]['index'])[
                0]  # Bounding box coordinates of detected objects
            classes = self.interpreter.get_tensor(self.output_details[1]['index'])[0]  # Class index of detected objects
            scores = self.interpreter.get_tensor(self.output_details[2]['index'])[0]  # Confidence of detected objects

            # Loop over all detections and draw detection box if confidence is above minimum threshold

            oldScore = 0

            for i in range(len(scores)):
                if (scores[i] > self.min_conf_threshold) and (scores[i] <= 1.0):
                    object_debug = self.labels[int(classes[i])]
                    print(object_debug)
                    if scores[i] > oldScore:
                        oldScore = scores[i]
                        # Get Label
                        object_name = self.labels[
                            int(classes[i])]  # Look up object name from "labels" array using class index
                        print(scores[i])
                        print(classes[i])
                        print(object_name)
            # Quit Video
            if cv2.waitKey(1) == ord('q'):
                break

        # Clean up
        cv2.destroyAllWindows()

        return object_name
