from mountain_climber import MountainClimber

climber = MountainClimber()

# Wait for start_button
# climber.wait_for_start()
# Scan for pictogram
climber.search_identify_pictogram()
# Plan Path
climber.plan_path()
# Drive to stairs
climber.drive_to_stairs()
# Climb one stair
climber.climb_stairs()
# Center Robot and drive into flag
climber.drive_into_flag()
