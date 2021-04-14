# Import packages
import os
import argparse
import cv2
import numpy as np
import sys
import time
import datetime
from threading import Thread
import importlib.util

# Class for Object Detection. 
class ObjectDetector: 
    interpreter = None
    input_details = None
    output_details = None
    floating_model = None
    height = 300
    width = 300

    def __init__(): 
        # Define and parse input arguments
        # Default values are fine. Make sure detect.tflite & labelmap.txt are accessible
        parser = argparse.ArgumentParser()
        parser.add_argument('--modeldir', help='Folder the .tflite file is located in',
                            required=True)
        parser.add_argument('--streamurl', help='The full URL of the video stream e.g. http://ipaddress:port/stream/video.mjpeg',
                            required=True)
        parser.add_argument('--graph', help='Name of the .tflite file, if different than detect.tflite',
                            default='detect.tflite')
        parser.add_argument('--labels', help='Name of the labelmap file, if different than labelmap.txt',
                            default='labelmap.txt')
        parser.add_argument('--threshold', help='Minimum confidence threshold for displaying detected objects',
                            default=0.5)
        parser.add_argument('--resolution', help='Desired webcam resolution in WxH. If the webcam does not support the resolution entered, errors may occur.',
                            default='1280x720')

        args = parser.parse_args()

        MODEL_NAME = args.modeldir
        STREAM_URL = args.streamurl
        GRAPH_NAME = args.graph
        LABELMAP_NAME = args.labels
        min_conf_threshold = float(args.threshold)
        resW, resH = args.resolution.split('x')
        imW, imH = int(resW), int(resH)

        # Import TensorFlow libraries
        # If tflite_runtime is installed, import interpreter from tflite_runtime, else import from regular tensorflow
        pkg = importlib.util.find_spec('tflite_runtime')
        if pkg:
            from tflite_runtime.interpreter import Interpreter
        else:
            from tensorflow.lite.python.interpreter import Interpreter  

        # Get path to current working directory
        CWD_PATH = os.getcwd()

        # Path to .tflite file, which contains the model that is used for object detection
        PATH_TO_CKPT = os.path.join(CWD_PATH,MODEL_NAME,GRAPH_NAME)

        # Path to label map file
        PATH_TO_LABELS = os.path.join(CWD_PATH,MODEL_NAME,LABELMAP_NAME)

        # Load the label map
        with open(PATH_TO_LABELS, 'r') as f:
            labels = [line.strip() for line in f.readlines()]

        # Have to do a weird fix for label map if using the COCO "starter model" from
        # https://www.tensorflow.org/lite/models/object_detection/overview
        # First label is '???', which has to be removed.
        if labels[0] == '???':
            del(labels[0])

        # Load the Tensorflow Lite model.
        interpreter = Interpreter(model_path=PATH_TO_CKPT)

        interpreter.allocate_tensors()

        # Get model details
        input_details = interpreter.get_input_details()
        output_details = interpreter.get_output_details()
        height = input_details[0]['shape'][1]
        width = input_details[0]['shape'][2]

        floating_model = (input_details[0]['dtype'] == np.float32)

    # Analyze an available videoStream with the current model
    # videoStream - running stream from the VideoStream Class
    # ttl - Time to live, in seconds
    def analyzeVideo(videostream, ttl)
        object_name = None
        # Function will run for ttl seconds
        addTime = datetime.timedelta(seconds=ttl)
        stop = datetime.datetime.now() + addTime

        #for frame1 in camera.capture_continuous(rawCapture, format="bgr",use_video_port=True):
        while datetime.datetime.now() < stop:
            # Grab frame from video stream
            frame1 = videostream.read()

            # Acquire frame and resize to expected shape [1xHxWx3]
            frame = frame1.copy()
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            frame_resized = cv2.resize(frame_rgb, (width, height))
            input_data = np.expand_dims(frame_resized, axis=0)

            # Normalize pixel values if using a floating model (i.e. if model is non-quantized)
            if floating_model:
                input_data = (np.float32(input_data) - 127.5) / 127.5

            # Perform the actual detection by running the model with the image as input
            interpreter.set_tensor(input_details[0]['index'],input_data)
            interpreter.invoke()

            # Retrieve detection results
            boxes = interpreter.get_tensor(output_details[0]['index'])[0] # Bounding box coordinates of detected objects
            classes = interpreter.get_tensor(output_details[1]['index'])[0] # Class index of detected objects
            scores = interpreter.get_tensor(output_details[2]['index'])[0] # Confidence of detected objects

            # Loop over all detections and draw detection box if confidence is above minimum threshold
            oldScore = 0
            for i in range(len(scores)):
                if ((scores[i] > min_conf_threshold) and (scores[i] <= 1.0)):
                    if(scores[i] > oldScore): 
                        oldScore = scores[i]
                        # Get Label
                        object_name = labels[int(classes[i])] # Look up object name from "labels" array using class index

            # Quit Video
            if cv2.waitKey(1) == ord('q'):
                break

        # Clean up
        cv2.destroyAllWindows()
        return object_name
