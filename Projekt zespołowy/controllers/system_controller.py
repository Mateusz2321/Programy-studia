import platform
import ctypes
import pyautogui
from gesture_liblary.mouse_steering import GestureMouseSteering
try:
    import screen_brightness_control as sbc
except:
    pass
try:
    from ctypes import cast, POINTER, wintypes as w
    from comtypes import CLSCTX_ALL
except ImportError:
    pass
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume


class SystemController:
    # scroll
    _scroll_speed = 200

    # windows volume
    devices = AudioUtilities.GetSpeakers()
    interface = devices.Activate(IAudioEndpointVolume._iid_,
                                 CLSCTX_ALL, None)
    volume = cast(interface, POINTER(IAudioEndpointVolume))
    volume_change = 0.6525

    def __init__(self):
        self.operating_system_name = platform.system()
        self.current_volume = self.volume.GetMasterVolumeLevel()
        self.camera=None
        self.mouse_steering = None
    def set_camera_reference(self,camera):
        self.camera= camera
        self.mouse_steering = GestureMouseSteering(camera)
    def minimize_window(self):
        user32 = ctypes.WinDLL('user32')
        user32.GetForegroundWindow.argtypes = ()
        user32.GetForegroundWindow.restype = w.HWND
        user32.ShowWindow.argtypes = w.HWND, w.BOOL
        user32.ShowWindow.restype = w.BOOL
        SW_MINIMIZE = 6
        hWnd = user32.GetForegroundWindow()
        user32.ShowWindow(hWnd, SW_MINIMIZE)

    def maximize_window(self):
        user32 = ctypes.WinDLL('user32')
        user32.GetForegroundWindow.argtypes = ()
        user32.GetForegroundWindow.restype = w.HWND
        user32.ShowWindow.argtypes = w.HWND, w.BOOL
        user32.ShowWindow.restype = w.BOOL
        SW_MAXIMIZE = 3
        hWnd = user32.GetForegroundWindow()
        user32.ShowWindow(hWnd, SW_MAXIMIZE)

    def close_window(self):
        user32 = ctypes.WinDLL('user32')
        user32.GetForegroundWindow.argtypes = ()
        user32.GetForegroundWindow.restype = w.HWND
        user32.ShowWindow.argtypes = w.HWND, w.BOOL
        user32.ShowWindow.restype = w.BOOL
        hWnd = user32.GetForegroundWindow()
        user32.ShowWindow(hWnd, 0)

    @property
    def scroll_speed(self):
        return self._scroll_speed

    @scroll_speed.setter
    def scroll_speed(self, speed):
        self._scroll_speed = speed

    def scroll_up(self, speed=_scroll_speed):
        pyautogui.scroll(self.scroll_speed)

    def scroll_down(self, speed=_scroll_speed):
        pyautogui.scroll(-self.scroll_speed)

    def windows_volume_up(self):
        value = self.get_windows_volume() + self.volume_change
        if value > 0:
            value = 0
        self.current_volume = value
        self.volume.SetMasterVolumeLevel(self.current_volume, None)

    def windows_volume_down(self):
        value = self.get_windows_volume() - self.volume_change
        if value < -65.25:
            value = -65.25
        self.current_volume = value
        self.volume.SetMasterVolumeLevel(self.current_volume, None)

    def zoom_in(self):
        pyautogui.keyDown('ctrl')
        pyautogui.press('+')
        pyautogui.keyUp('ctrl')

    def zoom_out(self):
        pyautogui.keyDown('ctrl')
        pyautogui.press('-')
        pyautogui.keyUp('ctrl')

    def brightness_up(self):
        current_brightness = sbc.get_brightness()
        if current_brightness[0]<=90:
            sbc.set_brightness(current_brightness[0]+10)
        else:
            sbc.set_brightness(100)

    def brightness_down(self):
        current_brightness=sbc.get_brightness()
        if current_brightness[0]>= 10:
            sbc.set_brightness(current_brightness[0] - 10)
        else:
            sbc.set_brightness(0)

    def get_windows_volume(self):
        return self.current_volume

    def scroll_right(self):
        pyautogui.press('right')

    def scroll_left(self):
        pyautogui.press('left')

    def switch_window(self):
        pyautogui.keyDown('alt')
        pyautogui.press('tab')
        pyautogui.keyUp('alt')
    def mouse_start(self):
        print('mouse_start')
        self.mouse_steering.start_mouse_steering()
        print('mouse_stop')
    def stop_mouse(self):
        self.mouse_steering.stop_mouse_steering()