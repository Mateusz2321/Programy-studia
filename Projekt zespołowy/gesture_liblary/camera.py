from keras.layers import Input
from keras.models import Model
from collections import deque
import numpy as np
import cv2
import time
import sys
sys.path.insert(0,"..")
from controllers.mapping import Mapping

from gesture_liblary.models import ModelType, ModelFactory

class Camera():
    def __init__(self, function_getter, sys_controller, camera_controller):
        self.recognize=True
        self.cam_controller=camera_controller
        self.gesture_map = Mapping(function_getter, sys_controller)
        self.initialize_recognition()
    def get_mapping(self):
        return self.gesture_map
    def stop_gesture_recognition(self):
        self.recognize=False
    def initialize_recognition(self):

        self.model = ModelFactory(rgbpath='trained_models/rgblstm.h5', trained=True).getModel(ModelType.RGB)

        self.model.summary()

        self.rgbinput = Input((150, 100, 3))

        self.x = self.model.layers[1].layer(self.rgbinput)
        for layer in self.model.layers[2:-3]:
            self.x = layer.layer(self.x)

        self.encoder = Model(inputs=self.rgbinput, outputs=self.x)
        self.encoder.summary()

        self.lstminput = Input((10, 1024))

        self.x = self.model.layers[-2](self.lstminput)
        self.x = self.model.layers[-1](self.x)

        self.lstm = Model(inputs=self.lstminput, outputs=self.x)
        self.lstm.summary()
        self.q = deque([np.zeros(1024) for i in range(10)])  # queue of extracted features , initialy filled with zeros

    def start_windows_gesture_library(self):
        self.recognize=True

        while True:
            if self.recognize is False:
                return
            ret, frame = self.cam_controller.get_camera_image()
            if ret is False:
                time.sleep(0.01)
                continue

            self.q.popleft()
            self.q.append(self.encoder.predict(np.array([cv2.resize(frame / 255., (100, 150))]))[0])
            our_values = self.lstm.predict(np.array([self.q]))

            position=0
            max_value = -10.0
            for i in range(len(our_values[0])):
                if our_values[0][i] > max_value:
                    max_value = our_values[0][i]
                    position = i
            if max_value > 0.9 and position == 1:
                self.gesture_map.gesture_action(1)
            elif max_value > 0.9 and position == 3:
                self.gesture_map.gesture_action(2)
            elif max_value > 0.9 and position == 4:
                self.gesture_map.gesture_action(3)
            elif max_value > 0.9 and position == 5:
                self.gesture_map.gesture_action(4)
            elif max_value > 0.70 and position == 6:
                self.gesture_map.gesture_action(5)
            elif max_value > 0.72 and position == 7:
                self.gesture_map.gesture_action(6)
            elif max_value > 0.54 and position == 8:
                self.gesture_map.gesture_action(7)
            elif max_value > 0.55 and position == 9:
                self.gesture_map.gesture_action(8)
            elif max_value > 0.9 and position == 10:
                self.gesture_map.gesture_action(9)
            elif max_value > 0.5 and position == 11:
                self.gesture_map.gesture_action(10)
            elif max_value > 0.5 and position == 12:
                self.gesture_map.gesture_action(11)
            elif max_value > 0.65 and position == 13:
                self.gesture_map.gesture_action(12)
            elif max_value > 0.65 and position == 14:
                self.gesture_map.gesture_action(13)
            elif max_value > 0.7 and position == 15:
                self.gesture_map.gesture_action(14)
            elif max_value > 0.9 and position == 16:
                self.gesture_map.gesture_action(15)
            elif max_value > 0.9 and position == 17:
                self.gesture_map.gesture_action(16)
            elif max_value > 0.90 and position == 18:
                self.gesture_map.gesture_action(17)
            elif max_value > 0.9 and position == 19:
                self.gesture_map.gesture_action(18)
            elif max_value > 0.9 and position == 20:
                self.gesture_map.gesture_action(19)
            elif max_value > 0.60 and position == 21:
                self.gesture_map.gesture_action(20)
            elif max_value > 0.60 and position == 22:
                self.gesture_map.gesture_action(21)
            elif max_value > 0.9 and position == 23:
                self.gesture_map.gesture_action(22)
            elif max_value > 0.9 and position == 24:
                self.gesture_map.gesture_action(23)
            elif max_value > 0.9 and position == 25:
                self.gesture_map.gesture_action(24)
            elif max_value > 0.9 and position == 26:
                self.gesture_map.gesture_action(25)
            time.sleep(0.0002)


if __name__ == '__main__':
    cam=Camera
    cam.start_windows_gesture_library(cam)