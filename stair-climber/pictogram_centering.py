# Import packages
import cv2
import numpy as np

from mountain_climber import MountainClimber
from tensor_setup import TensorSetup


class PictogramCentering:

    def __init__(self, tensor_config: TensorSetup):
        # Define and parse input arguments
        # Default values are fine. Make sure detect.tflite & labelmap.txt are accessible
        self.interpreter = tensor_config.interpreter
        self.input_details = tensor_config.input_details
        self.output_details = tensor_config.output_details
        self.floating_model = tensor_config.floating_model
        self.height = tensor_config.height
        self.width = tensor_config.width
        self.labels = tensor_config.labels
        self.min_conf_threshold = 0.5

    def center_robot_on_pictogram(self, object_label, videostream, mountain_climber :MountainClimber):
        print(self.labels)

        input_mean = 127.5
        input_std = 127.5
        imH = 720
        imW = 1280
        # Initialize frame rate calculation
        frame_rate_calc = 1
        freq = cv2.getTickFrequency()

        # for frame1 in camera.capture_continuous(rawCapture, format="bgr",use_video_port=True):
        while True:

            # Start timer (for calculating frame rate)
            t1 = cv2.getTickCount()

            # Grab frame from video stream
            frame1 = videostream.read()

            # Acquire frame and resize to expected shape [1xHxWx3]
            frame = frame1.copy()
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            frame_resized = cv2.resize(frame_rgb, (self.width, self.height))
            input_data = np.expand_dims(frame_resized, axis=0)

            frame_center = frame.shape[1] / 2
            # print("center of frame: " + str(frame_center))

            # Normalize pixel values if using a floating model (i.e. if model is non-quantized)
            if self.floating_model:
                input_data = (np.float32(input_data) - input_mean) / input_std

            # Perform the actual detection by running the model with the image as input
            self.interpreter.set_tensor(self.input_details[0]['index'], input_data)
            self.interpreter.invoke()

            # Retrieve detection results
            boxes = self.interpreter.get_tensor(self.output_details[0]['index'])[
                0]  # Bounding box coordinates of detected objects
            classes = self.interpreter.get_tensor(self.output_details[1]['index'])[0]  # Class index of detected objects
            scores = self.interpreter.get_tensor(self.output_details[2]['index'])[0]  # Confidence of detected objects
            # num = interpreter.get_tensor(output_details[3]['index'])[0]  # Total number of detected objects (inaccurate
            # and not needed)

            # Loop over all detections and draw detection box if confidence is above minimum threshold
            for i in range(len(scores)):
                if ((scores[i] > self.min_conf_threshold) and (scores[i] <= 1.0)):
                    object_name = self.labels[
                        int(classes[i])]  # Look up object name from "labels" array using class index
                    # Get bounding box coordinates and draw box
                    # Interpreter can return coordinates that are outside of image dimensions, need to force them to be within image using max() and min()
                    ymin = int(max(1, (boxes[i][0] * imH)))
                    xmin = int(max(1, (boxes[i][1] * imW)))
                    ymax = int(min(imH, (boxes[i][2] * imH)))
                    xmax = int(min(imW, (boxes[i][3] * imW)))
                    if object_label == object_name:
                        print(xmin, xmax)
                        label_center = (xmax + xmin) / 2
                        print(label_center)
                        if label_center < frame_center:
                            print("move left")
                            mountain_climber.mid_motor.accelerate_forward(254)
                        elif label_center > frame_center:
                            print("move right")
                            mountain_climber.mid_motor.accelerate_backwards(254)
                        else:
                            print("haalt")
                            mountain_climber.mid_motor.accelerate_forward(0)
                            return

                    cv2.rectangle(frame, (xmin, ymin), (xmax, ymax), (10, 255, 0), 2)

                    # Draw label
                    label = '%s: %d%%' % (object_name, int(scores[i] * 100))  # Example: 'person: 72%'
                    labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.7, 2)  # Get font size
                    label_ymin = max(ymin, labelSize[1] + 10)  # Make sure not to draw label too close to top of window
                    cv2.rectangle(frame, (xmin, label_ymin - labelSize[1] - 10),
                                  (xmin + labelSize[0], label_ymin + baseLine - 10), (255, 255, 255),
                                  cv2.FILLED)  # Draw white box to put label text in
                    cv2.putText(frame, label, (xmin, label_ymin - 7), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0),
                                2)  # Draw label text

            # Draw framerate in corner of frame
            cv2.putText(frame, 'FPS: {0:.2f}'.format(frame_rate_calc), (30, 50), cv2.FONT_HERSHEY_SIMPLEX, 1,
                        (255, 255, 0),
                        2,
                        cv2.LINE_AA)

            # All the results have been drawn on the frame, so it's time to display it.
            cv2.imshow('Object detector', frame)

            # Calculate framerate
            t2 = cv2.getTickCount()
            time1 = (t2 - t1) / freq
            frame_rate_calc = 1 / time1

            # Press 'q' to quit
            if cv2.waitKey(1) == ord('q'):
                break

        # Clean up
        cv2.destroyAllWindows()
