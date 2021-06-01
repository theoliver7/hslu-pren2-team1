# Import packages
import random

import cv2
import numpy as np
from pathfinding.core.diagonal_movement import DiagonalMovement
from pathfinding.core.grid import Grid
from pathfinding.finder.a_star import AStarFinder


class Pathfinder:
    interpreter = None
    input_details = None
    output_details = None
    floating_model = None
    height = 300
    width = 300
    labels = []
    min_conf_threshold = 0.01

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

    def transform_image_to_matrix(self, image_path):
        bricks, steps, image_center = self.__run_brick_step_detection(image_path)
        ##Initialize Matrix
        stair_matrix = np.ones((7, 8))

        if len(steps) == 0 or len(bricks) == 0:
            print("no steps or bricks found: exiting")
            return stair_matrix, 0

        sorted_bricks = bricks[bricks[:, 1].argsort()[::-1][:len(bricks)]]
        sorted_steps = self.__prepare_steps_for_mapping(steps)

        start_position = self.__determine_start_position(sorted_steps[0], image_center)
        print(sorted_bricks)
        print(sorted_steps)
        print()

        for idx, step in enumerate(sorted_steps[:-1]):  # iterate all but last
            step_length = step[2] - step[0]
            raster_size = int(step_length / 8)
            print("step" + str(step))
            to_remove = list()
            for idx2, brick in enumerate(sorted_bricks):
                middle_of_brick = int((brick[3] + brick[1]) / 2)
                print("middle of brick" + str(middle_of_brick))
                if (step[3] + 5) > middle_of_brick > (sorted_steps[idx + 1][3] - 5):
                    # 5 is a buffer is the stone is taller
                    print("Brick: " + str(brick) + " is on " + str(idx + 1) + " step")
                    # sorted_bricks.remove(brick)
                    to_remove.append(idx2)

                    # than next step
                    print("step lenght: " + str(step_length))
                    print("raster size: " + str(raster_size))
                    relativ_brick_pos1 = brick[0] - step[0]  # subtract the step start left
                    relativ_brick_pos2 = brick[2] - step[0]
                    first_field = int(relativ_brick_pos1 / raster_size)
                    second_field = int(relativ_brick_pos2 / raster_size)
                    # print(first_field)
                    # print(second_field)
                    for i in range(first_field, second_field + 1):
                        stair_matrix[5 - idx, i] = 0  # 7 floors - bottom and top floor = 5
                    print(stair_matrix)

                else:
                    print("checking next step")
                    break
            sorted_bricks = np.delete(sorted_bricks, to_remove, axis=0)
        print("------------------------------")

        return stair_matrix, start_position

    # Press any key to continue to next image, or press 'q' to quit
    def compute_path(self, matrix, start, end):
        grid = Grid(matrix=matrix)
        print(start, end)
        start = grid.node(start[0], start[1])
        end = grid.node(end[0], end[1])

        finder = AStarFinder(diagonal_movement=DiagonalMovement.never)
        path, runs = finder.find_path(start, end, grid)

        print('operations:', runs, 'path length:', len(path))
        print(grid.grid_str(path=path, start=start, end=end))
        print(path)
        return path

    def __prepare_steps_for_mapping(self, steps):
        sorted_steps = steps[steps[:, 1].argsort()[::-1][:len(steps)]]
        copy = list()
        for idx, step in enumerate(sorted_steps[:-1]):
            if step[1] < sorted_steps[idx + 1][3]:
                print("steps are in each other")
            else:
                copy.append(step)
        copy.append(sorted_steps[-1])

        return np.array(copy)

    def __determine_start_position(self, step, image_center):
        print("determining start position")
        step_length = step[2] - step[0]
        raster_size = int(step_length / 8)
        print("step lenght: " + str(step_length))
        print("raster size: " + str(raster_size))
        relativ_brick_pos1 = image_center - step[0]  # subtract the step start left
        first_field = int(relativ_brick_pos1 / raster_size)
        print("startposition is {0}".format(first_field))
        return first_field

    def __run_brick_step_detection(self, image_path):
        input_mean = 127.5
        input_std = 127.5
        bricks = list()
        steps = list()

        # Load image and resize to expected shape [1xHxWx3]
        image = cv2.imread(image_path)
        # Maybe flip while capturing
        image = cv2.flip(image, 0)
        image = cv2.flip(image, 1)
        image_center = image.shape[1] / 2
        print("center of the image: " + str(image_center))
        image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        imH, imW, _ = image.shape

        image_resized = cv2.resize(image_rgb, (self.width, self.height))
        input_data = np.expand_dims(image_resized, axis=0)

        # Normalize pixel values if using a floating model (i.e. if model is non-quantized)
        if self.floating_model:
            input_data = (np.float32(input_data) - input_mean) / input_std

        # Perform the actual detection by running the model with the image as input
        self.interpreter.set_tensor(self.input_details[0]['index'], input_data)
        self.interpreter.invoke()

        boxes = self.interpreter.get_tensor(self.output_details[0]['index'])[0]  # coordinates detected objects
        classes = self.interpreter.get_tensor(self.output_details[1]['index'])[0]  # index detected objects
        scores = self.interpreter.get_tensor(self.output_details[2]['index'])[0]  # Confidence detected objects

        for i in range(len(scores)):
            if scores[i] > self.min_conf_threshold:
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
                object_name = self.labels[int(classes[i])]
                if object_name == "brick":
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
        bricks = np.array(bricks)
        steps = np.array(steps)
        cv2.imwrite("test.jpg", image)
        return bricks, steps, image_center
