import cv2
from controllers.camera_checker import CameraChecker
from threading import Thread, Lock

class CameraController():
    def __init__(self,win):
        self.win=win
        self.camera_checker = CameraChecker()
        self.camera_list = self.camera_checker.list_ports()
        if len(self.camera_list) > 0:
            self.used_camera_number=self.camera_list[0]
            self.cap = cv2.VideoCapture(self.used_camera_number)
        else:
            self.used_camera_number = -1
            self.cap = None
        self.mutex = Lock()
    def release_camera(self):
        self.mutex.acquire()
        if self.used_camera_number > -1:
            self.used_camera_number = -1
            self.cap.release()
            self.cap = None
        self.mutex.release()
    def get_used_camera_number(self):
        return self.used_camera_number

    def get_camera_image(self):
        self.mutex.acquire()
        if self.used_camera_number > -1:
            ret, frame = self.cap.read()
        else:
            ret, frame = False, False
        self.mutex.release()
        if ret is False:
            self.set_used_camera_number(0)
            self.mutex.acquire()
            if self.used_camera_number > -1:
                ret, frame = self.cap.read()
            else:
                ret, frame = False, False
            self.mutex.release()
        return ret,frame
    def get_all_cameras(self):
        return self.camera_list
    def set_used_camera_number(self,number:int):
        self.mutex.acquire()
        self.camera_list = self.camera_checker.list_ports()
        contains=False
        for a in self.camera_list:
            if number == a:
                contains = True
                break
        self.win.set_cameras_combo_box(self.camera_list)
        if contains is True:
            self.used_camera_number=number
            self.cap.release()
            self.cap = cv2.VideoCapture(self.used_camera_number)
        self.mutex.release()
    def refresh_camera_list(self):
        self.mutex.acquire()
        self.camera_list = self.camera_checker.list_ports()
        if len(self.camera_list) > 0:
            self.used_camera_number = self.camera_list[0]
            self.cap = cv2.VideoCapture(self.used_camera_number)
        else:
            self.used_camera_number = -1
            self.cap = None
        self.win.set_cameras_combo_box(self.camera_list)

        self.mutex.release()
if __name__ == '__main__':
    ap=CameraController()



