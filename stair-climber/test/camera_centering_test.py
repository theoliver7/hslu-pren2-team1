import unittest

import object_detector_image


class CameraCentringTestCase(unittest.TestCase):
    def test_something(self):
        object_detector_image.detect_pictogram_image("test/images/paint_left.jpg", "paint")


if __name__ == '__main__':
    object_detector_image.detect_pictogram_image("test/images/paint_left.jpg", "paint")
    unittest.main()

object_detector_image.detect_pictogram_image("test/images/paint_left.jpg", "paint")
