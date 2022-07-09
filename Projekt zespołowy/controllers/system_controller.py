import platform
import ctypes
import pyautogui
from gesture_liblary.mouse_steering import GestureMouseSteering
import screen_brightness_control as sbc
from ctypes import cast, POINTER, wintypes as w
from comtypes import CLSCTX_ALL
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume


class SystemController:

    _scroll_speed = 200

    def __init__(self):
        self.operating_system_name = platform.system()
        self.camera=None
        self.mouse_steering = None
        self.sound_values = []
        self.read_sound_values_from_file()

    def read_sound_values_from_file(self):
        with open('./other/sound_level_values.txt','r') as f:
            self.sound_values = f.readlines()
        for a in range (len(self.sound_values)):
            b = self.sound_values[a]
            self.sound_values[a] = b[0:-2]
        self.sound_values = [float(x)  for x in self.sound_values]

    def set_reference(self,function_getter):
        self.function_getter=function_getter

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

    def volume_up(self):
        self.devices = AudioUtilities.GetSpeakers()
        self.interface = self.devices.Activate(IAudioEndpointVolume._iid_,
                                               CLSCTX_ALL, None)
        self.volume = cast(self.interface, POINTER(IAudioEndpointVolume))
        self.current_volume = self.volume.GetMasterVolumeLevel()
        for a in range (len(self.sound_values)):
            if self.current_volume <= self.sound_values[a]:
                if a < 50:
                    self.current_volume = self.sound_values[a+1]
                else:
                    self.current_volume = 0.0
                break
        if self.current_volume >0.0:
            self.current_volume = 0.0
        try:
            self.volume.SetMasterVolumeLevel(self.current_volume, None)
        except OSError:
            pass

    def volume_down(self):
        self.devices = AudioUtilities.GetSpeakers()
        self.interface = self.devices.Activate(IAudioEndpointVolume._iid_,
                                               CLSCTX_ALL, None)
        self.volume = cast(self.interface, POINTER(IAudioEndpointVolume))
        self.current_volume = self.volume.GetMasterVolumeLevel()
        for a in range (len(self.sound_values)):
            if self.current_volume <= self.sound_values[a]:
                if a > 0:
                    self.current_volume = self.sound_values[a - 1]
                else:
                    self.current_volume = -65.25
                break
        if self.current_volume < -65.25:
            self.current_volume = -65.25
        try:
            self.volume.SetMasterVolumeLevel(self.current_volume, None)
        except OSError:
            pass

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
        brightness = current_brightness[0] +5
        if brightness > 100:
            brightness = 100
        sbc.set_brightness(brightness)

    def brightness_down(self):
        current_brightness = sbc.get_brightness()
        brightness = current_brightness[0] -5
        if brightness < 0:
            brightness = 0
        sbc.set_brightness(brightness)

    def scroll_right(self):
        pyautogui.press('right')

    def scroll_left(self):
        pyautogui.press('left')

    def switch_window(self):
        pyautogui.keyDown('alt')
        pyautogui.press('tab')
        pyautogui.keyUp('alt')

    def mouse_start(self):
        self.mouse_steering.start_mouse_steering()
        self.function_getter.set_time_before()

    def stop_mouse(self):
        self.mouse_steering.stop_mouse_steering()

    def window_left(self):
        pyautogui.keyDown('win')
        pyautogui.press('left')
        pyautogui.keyUp('win')

    def window_right(self):
        pyautogui.keyDown('win')
        pyautogui.press('right')
        pyautogui.keyUp('win')

    def escape(self):
        pyautogui.press('esc')

    def set_controller_reference(self,cont):
        self.controller_reference=cont

    def do_nothing(self):
        pass

    def minimize_all_windows(self):
        pyautogui.keyDown('win')
        pyautogui.press('d')
        pyautogui.keyUp('win')

    def preview_of_opened_windows(self):
        pyautogui.keyDown('win')
        pyautogui.press('tab')
        pyautogui.keyUp('win')

    def open_action_center(self):
        pyautogui.keyDown('win')
        pyautogui.press('a')
        pyautogui.keyUp('win')

    def page_up(self):
        pyautogui.press('pageup')

    def page_down(self):
        pyautogui.press('pagedown')

    def space(self):
        pyautogui.press('space')

    def pause(self):
        pyautogui.press('pause')
