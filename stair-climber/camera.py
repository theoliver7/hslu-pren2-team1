from time import sleep
from picamera import PiCamera
from picamera.array import PiRGBArray

class Camera:
    @staticmethod
    def take_picture_to_path(path):
        camera = PiCamera()
        camera.resolution = (1280, 720)  # max resolution
        try:
            camera.start_preview()
            sleep(3)  # wait 3 secs so camera can adjust to light
            camera.capture(path)
            camera.stop_preview()
        finally:
            camera.close()

    #pip install "picamera[array]"
    @staticmethod
    def take_picture_to_array():
        camera = PiCamera()
        camera.resolution = (1280, 720)
        rawCapture = PiRGBArray(camera)
        sleep(3)
        camera.capture(rawCapture, format="bgr")
        image = rawCapture.array
        return image