from motors import StepperMotor
from sensors import Buttons
from mountain_climber import MountainClimber

# motor = StepperMotor()
# motor.go_to_degree(90)


climber = MountainClimber()

climber.wait_for_start()
print("we are on")

climber.search_identify_pictogram()
print("pictogram detected")


