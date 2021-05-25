# import object_centering
# import object_detector
# import tensor_setup
# import video_stream
#
# import object_detector_image_playground
# from motors import StepperMotor
import tensor_setup
from mountain_climber import MountainClimber

from object_detector import PictogramDetector
from path_finder import Pathfinder

climber = MountainClimber()
climber.plan_path()
climber.climb_stairs()


# Wait for start_button
# climber.wait_for_start()
# Scan for pictogram
# climber.search_identify_pictogram()
# #Drive to stairs
# climber.drive_to_stairs()
# Climb one stair
# climber.climb_stairs()
