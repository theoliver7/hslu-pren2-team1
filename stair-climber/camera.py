from time import sleep
from picamera import PiCamera
from picamera.array import PiRGBArray

class Camera:
    @staticmethod
    def take_picture_to_path(path):
        #investigate fov https://picamera.readthedocs.io/en/release-1.13/fov.html
        camera = PiCamera(sensor_mode=4,resolution='1920x1080')
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