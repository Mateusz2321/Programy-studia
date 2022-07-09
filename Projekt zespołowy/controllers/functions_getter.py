import sys
sys.path.insert(0, "..")
from controllers import user_scripts
import time


class FunctionsGetter():

    def __init__(self, controller):
        self.time_before = time.time()
        self.u_scripts= user_scripts
        self.controller = controller
        self.controller.set_reference(self)
        self.u_dict = self.u_scripts.get_functions()
        self.dct={"minimize_window": self.controller.minimize_window ,
            "maximize_window": self.controller.maximize_window ,
            "close_window": self.controller.close_window ,
            "scroll_up": self.controller.scroll_up ,
            "scroll_down": self.controller.scroll_down ,
            "volume_up": self.controller.volume_up ,
            "volume_down": self.controller.volume_down ,
            "zoom_in": self.controller.zoom_in ,
            "zoom_out": self.controller.zoom_out ,
            "brightness_up": self.controller.brightness_up ,
            "brightness_down": self.controller.brightness_down ,
            "scroll_right": self.controller.scroll_right ,
            "scroll_left": self.controller.scroll_left ,
            "switch_window": self.controller.switch_window ,
            "mouse_start": self.controller.mouse_start,
            "window_left": self.controller.window_left,
            "window_right": self.controller.window_right,
            "escape": self.controller.escape,
            "do_nothing": self.controller.do_nothing,
            "minimize_all_windows": self.controller.minimize_all_windows,
            "preview_of_opened_windows": self.controller.preview_of_opened_windows,
            "open_action_center": self.controller.open_action_center,
            "page_up": self.controller.page_up,
            "page_down": self.controller.page_down,
            "space": self.controller.space,
            "pause": self.controller.pause
        }
        self.dct = {**self.dct, **self.u_dict}

    def set_mapping_reference(self,ref):
        self.map_ref = ref

    def set_time_before(self):
        self.map_ref.set_time_before()

    def call_function(self,name):
        for key in self.dct.keys():
            if name==key:
                func=self.dct.get(key)
                try:
                 func()
                except:
                    return False
                return True
        return False

    def get_all_functions_names(self):
        return self.dct.keys()


