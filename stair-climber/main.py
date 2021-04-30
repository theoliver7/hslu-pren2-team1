import object_centering
import object_detector
import tensor_setup
import video_stream

import object_detector_image
from motors import StepperMotor
from mountain_climber import MountainClimber


climber = MountainClimber()

# climber.wait_for_start()


tensorConfig = tensor_setup.TensorSetup()
# videoStream = videostream = video_stream.VideoStream(resolution=(imW, imH), framerate=30).start()
# objectCentering = object_centering.ObjectCentering(tensorConfig)
videoStream = video_stream.VideoStream(resolution=(1280, 720), framerate=30).start()

# objectCentering.detect_pictogram_video("taco", video_stream)

objectDetector = object_detector.ObjectDetector(tensorConfig)
detectedPictogram = objectDetector.analyzeVideo(videoStream, 5)
videoStream.stop()
print(detectedPictogram)

