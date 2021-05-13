import object_centering
import object_detector
import tensor_setup
import video_stream

import object_detector_image
from motors import StepperMotor
from mountain_climber import MountainClimber


climber = MountainClimber()

# Wait for start_button
climber.wait_for_start()
#Scan for pictogram
climber.search_identify_pictogram()
#Drive to stairs
climber.drive_to_stairs()
#Climb one stair
climber.climb_stairs()


