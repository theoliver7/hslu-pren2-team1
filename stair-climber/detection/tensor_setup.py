import importlib.util
import os

import numpy as np


class TensorSetup:
    interpreter = None
    input_details = None
    output_details = None
    floating_model = None
    height = 300
    width = 300
    labels = []

    def __init__(self, graph_name, labelmap_name):
        folder = "tflite"

        pkg = importlib.util.find_spec('tflite_runtime')
        if pkg:
            from tflite_runtime.interpreter import Interpreter
        else:
            from tensorflow.lite.python.interpreter import Interpreter

        path = os.getcwd()

        path_to_checkpoint = os.path.join(path, folder, graph_name)

        path_to_labels = os.path.join(path, folder, labelmap_name)

        with open(path_to_labels, 'r') as f:
            self.labels = [line.strip() for line in f.readlines()]

        if self.labels[0] == '???':
            del (self.labels[0])

        self.interpreter = Interpreter(model_path=path_to_checkpoint)

        self.interpreter.allocate_tensors()

        self.input_details = self.interpreter.get_input_details()
        self.output_details = self.interpreter.get_output_details()
        self.height = self.input_details[0]['shape'][1]
        self.width = self.input_details[0]['shape'][2]

        self.floating_model = (self.input_details[0]['dtype'] == np.float32)
