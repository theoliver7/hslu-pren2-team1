import datetime

import cv2
import numpy as np


class PictogramDetector:
    interpreter = None
    input_details = None
    output_details = None
    floating_model = None
    height = 300
    width = 300
    labels = []
    min_conf_threshold = 0.5

    def __init__(self, tensor_config):
        self.interpreter = tensor_config.interpreter
        self.input_details = tensor_config.input_details
        self.output_details = tensor_config.output_details
        self.floating_model = tensor_config.floating_model
        self.height = tensor_config.height
        self.width = tensor_config.width
        self.labels = tensor_config.labels

    def analyze_picture(self, path):
        object_name = None

        print("Available labels: ")
        print(self.labels)

        input_mean = 127.5
        input_std = 127.5

        image = cv2.imread(path)
        image = cv2.flip(image, 0)
        image = cv2.flip(image, 1)

        image_center = image.shape[1] / 2
        print("center of the image: " + str(image_center))
        image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        imH, imW, _ = image.shape
        image_resized = cv2.resize(image_rgb, (self.width, self.height))
        input_data = np.expand_dims(image_resized, axis=0)

        # Normalize pixel values if using a floating model
        if self.floating_model:
            input_data = (np.float32(input_data) - input_mean) / input_std

        # Perform the actual detection by running the model with the image as input
        self.interpreter.set_tensor(self.input_details[0]['index'], input_data)
        self.interpreter.invoke()

        # Retrieve detection results
        # Bounding box coordinates of detected objects
        classes = self.interpreter.get_tensor(self.output_details[1]['index'])[0]  # Class index of detected objects
        scores = self.interpreter.get_tensor(self.output_details[2]['index'])[0]  # Confidence of detected objects

        old_score = 0
        tmp_name = self.labels[int(classes[0])]
        for i in range(len(scores)):
            if (scores[i] > self.min_conf_threshold) and (scores[i] <= 1.0):
                if scores[i] > old_score:
                    old_score = scores[i]
                    # Get Label
                    object_name = self.labels[int(classes[i])]
                    print(scores[i])
                    print(classes[i])
                    print("found better match:" + object_name)

        if object_name is None:
            object_name = tmp_name
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
            # Bounding box coordinates of detected objects
            boxes = self.interpreter.get_tensor(self.output_details[0]['index'])[0]
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
