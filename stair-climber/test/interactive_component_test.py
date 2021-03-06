from time import sleep

from pynput import keyboard

from climber import Climber

climber = Climber()


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
        print("Mid Motor accelerate forward")
        climber.mid_motor.accelerate_forward(254)
    elif k == "s":
        print("Mid Motor Stop forward")
        climber.mid_motor.accelerate_forward(0)
    if k == "p":
        print("Mid Motor accelerate backwards")
        climber.mid_motor.accelerate_backwards(254)
    elif k == "l":
        print("Mid Motor Stop backwards")
        climber.mid_motor.accelerate_backwards(0)

    # OuterMotors
    elif k == "q":
        print("Outer Motor accelerate forward")
        climber.outer_motors.accelerate_forward(200)
    elif k == "e":
        print("Outer Motor Stop forward")
        climber.outer_motors.accelerate_forward(0)
    elif k == "r":
        print("Outer Motor accelerate backwards")
        climber.outer_motors.accelerate_backwards(200)
    elif k == "t":
        print("Outer Motor Stop backwards")
        climber.outer_motors.accelerate_backwards(0)

    # Stepper
    elif k == "a":
        print("go to reference in air")
        climber.rotation.go_to_reference_inair()
    elif k == "b":
        print("go to reference on ground")
        climber.rotation.go_to_degree_onground(340)
        climber.rotation.go_to_reference_onground()
    elif k == "d":
        print("go to degree in air")
        climber.rotation.go_to_degree_inair(50)
    elif k == "f":
        print("go to degree on ground")
        climber.rotation.go_to_degree_inair(90)
        sleep(2)
        climber.rotation.go_to_degree_inair(135)
        sleep(2)
        climber.rotation.go_to_degree_inair(45)
        sleep(2)
        climber.rotation.go_to_degree_inair(0)

    # Lift Operation
    elif k == "up":
        print("Enter Driving mode, middle up")
        climber.lift.driveMode_middleUp()
    elif k == "down":
        print("Enter Driving mode, middle Down")
        climber.lift.driveMode_middleDown()
    elif k == "left":
        print("Lower outer axes")
        climber.lift.lower_outer_axes()
    elif k == "right":
        print("Enter rotation mode")
        climber.lift.rotationMode()

    # Climb
    elif k == "o":
        print("Climb Stair")
        climber.lift.climb_stair()
    # LED
    elif k == "x":
        print("Set LED")
        climber.led.set_red(100)       
        climber.led.set_blue(100)
        climber.led.set_green(100)
    if k == "1":
        print("distance 1")
        print(climber.ultra_sonic.get_distance1())
    elif k == "2":
        print("distance 2")
        print(climber.ultra_sonic.get_distance2())
    # Other
    elif k == "y":
        quit()


# climber.lift.move_front_up()

listener = keyboard.Listener(on_press=on_press)
listener.start()  # start to listen on a separate thread
listener.join()
