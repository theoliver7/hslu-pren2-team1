from pynput import keyboard

from mountain_climber import MountainClimber

climber = MountainClimber()


def on_press(key):
    if key == keyboard.Key.esc:
        return False  # stop listener
    try:
        k = key.char  # single-char keys
    except:
        k = key.name  # other keys

    print('Key pressed: ' + k)
    # Mid Motor
    if k == "w":
        print("Mid Motor accelerate")
        climber.midMotor.accelerate()
    elif k == "s":
        print("Mid Motor Stop")
        climber.midMotor.stop()

    # OuterMotors
    elif k == "q":
        print("Outer Motor accelerate")
        climber.outerMotors.accelerate()
    elif k == "e":
        print("Outer Motor Stop")
        climber.outerMotors.stop()

    # Stepper
    elif k == "a":
        print("go to reference")
        climber.rotation.go_to_reference()
    elif k == "d":
        print("go to degree")
        climber.rotation.go_to_degree(90)

    # Lift Operation
    elif k == "up":
        print("Move Both Up")
        climber.lift.move_both_up()
    elif k == "down":
        print("Move Both Down")
        climber.lift.move_both_down()
    elif k == "left":
        print("Move Front down Back Up")
        climber.lift.move_frontDown_BackUp()
    elif k == "left":
        print("Move Front Up Back down")
        climber.lift.move_frontDown_BackUp()
    elif k == "i":
        print("Move Back UP")
        climber.lift.move_back_up()
    elif k == "k":
        print("Move Back Down")
        climber.lift.move_back_down()
    elif k == "o":
        print("Move Front UP")
        climber.lift.move_front_up()
    elif k == "l":
        print("Move Front down")
        climber.lift.move_front_up()


# climber.lift.move_front_up()

listener = keyboard.Listener(on_press=on_press)
listener.start()  # start to listen on a separate thread
listener.join()
