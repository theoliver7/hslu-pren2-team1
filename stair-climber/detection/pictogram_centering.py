# Import packages
import cv2
import numpy as np

# from mountain_climber import MountainClimber
from communication.motors import MidMotor
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

    def center_robot_on_pictogram(self, object_label, videostream, mid_motor: MidMotor):
        print(self.labels)

        input_mean = 127.5
        input_std = 127.5
        imH = 720
        imW = 1280

        frame_rate_calc = 1
        freq = cv2.getTickFrequency()

        driving = False
        while True:

            t1 = cv2.getTickCount()

            frame1 = videostream.read()

            frame = frame1.copy()
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            frame_resized = cv2.resize(frame_rgb, (self.width, self.height))
            input_data = np.expand_dims(frame_resized, axis=0)

            frame_center = frame.shape[1] / 2
            if self.floating_model:
                input_data = (np.float32(input_data) - input_mean) / input_std

            self.interpreter.set_tensor(self.input_details[0]['index'], input_data)
            self.interpreter.invoke()

            boxes = self.interpreter.get_tensor(self.output_details[0]['index'])[0]
            classes = self.interpreter.get_tensor(self.output_details[1]['index'])[0]
            scores = self.interpreter.get_tensor(self.output_details[2]['index'])[0]


            for i in range(len(scores)):
                if ((scores[i] > self.min_conf_threshold) and (scores[i] <= 1.0)):
                    object_name = self.labels[int(classes[i])]

                    ymin = int(max(1, (boxes[i][0] * imH)))
                    xmin = int(max(1, (boxes[i][1] * imW)))
                    ymax = int(min(imH, (boxes[i][2] * imH)))
                    xmax = int(min(imW, (boxes[i][3] * imW)))
                    if object_label == object_name:
                        label_center = (xmax + xmin) / 2
                        print(label_center)
                        print(frame_center)

                        if frame_center + 10 > label_center > frame_center - 10:
                            print("haalt")
                            mid_motor.accelerate_forward(0)
                            return
                        elif label_center < frame_center:
                            print("move left")
                            if not driving:
                                mid_motor.accelerate_forward(250)
                                driving = True
                        elif label_center > frame_center - 10:
                            print("move right")
                            if not driving:
                                mid_motor.accelerate_backwards(250)
                                driving = True

                    cv2.rectangle(frame, (xmin, ymin), (xmax, ymax), (10, 255, 0), 2)

                    # Draw label
                    label = '%s: %d%%' % (object_name, int(scores[i] * 100))
                    labelSize, baseLine = cv2.getTextSize(label, cv2.FONT_HERSHEY_SIMPLEX, 0.7, 2)
                    label_ymin = max(ymin, labelSize[1] + 10)
                    cv2.rectangle(frame, (xmin, label_ymin - labelSize[1] - 10),
                                  (xmin + labelSize[0], label_ymin + baseLine - 10), (255, 255, 255), cv2.FILLED)
                    cv2.putText(frame, label, (xmin, label_ymin - 7), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 0),                                2)

            cv2.putText(frame, 'FPS: {0:.2f}'.format(frame_rate_calc), (30, 50), cv2.FONT_HERSHEY_SIMPLEX, 1,
                        (255, 255, 0),
                        2,
                        cv2.LINE_AA)

            cv2.imshow('Object detector', frame)

            t2 = cv2.getTickCount()
            time1 = (t2 - t1) / freq
            frame_rate_calc = 1 / time1

            if cv2.waitKey(1) == ord('q'):
                break
        cv2.destroyAllWindows()
