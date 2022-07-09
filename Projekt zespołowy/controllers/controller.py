import sys
sys.path.insert(0, "..")
from gesture_liblary.camera import Camera
from controllers.camera_controller import CameraController
import threading


class Controller():

    def __init__(self, function_getter, sys_controller, win):
        self.win=win
        self.camera_controller = CameraController(win)
        self.system_controller= sys_controller
        self.camera = Camera(function_getter, sys_controller, self.camera_controller)
        self.started = False

    def get_camera(self):
        return self.camera

    def start_stop_gesture_recognition(self):
        if self.started is False:
            self.t = threading.Thread(name='daemon', target=self.camera.start_windows_gesture_library)
            self.t.start()
            self.win.set_button_to_stop_mode()
            self.started = True
        else:
            self.system_controller.stop_mouse()
            self.camera.stop_gesture_recognition()
            self.t.join()
            self.win.set_button_to_start_mode()
            self.started = False

    def start_gesture_recognition(self):
        if self.started is False:
            self.started = True
            self.t=threading.Thread(name='daemon',target=self.camera.start_windows_gesture_library)
            self.t.start()

    def stop_gesture_recognition(self):
        if self.started is True:
            self.system_controller.stop_mouse()
            self.camera.stop_gesture_recognition()
            self.t.join()
            self.started=False

    def get_camera_controller(self):
        return self.camera_controller