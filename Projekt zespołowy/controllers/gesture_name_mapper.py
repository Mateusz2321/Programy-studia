

class NameMapper():

    def __init__(self):
        self.gesture_names = {1: "Drumming fingers",
                              2: "Pulling hand in",
                              3: "Pulling two fingers in",
                              4: "Pushing hand away",
                              5: "Pushing two fingers_away",
                              6: "Rolling hand backward",
                              7: "Rolling hand forward",
                              8: "Shaking hand",
                              9: "Sliding two fingers_down",
                              10: "Sliding two fingers_left",
                              11: "Sliding two fingers right",
                              12: "Sliding two fingers up",
                              13: "Stop sign",
                              14: "Swiping down",
                              15: "Swiping left",
                              16: "Swiping right",
                              17: "Swiping up",
                              18: "Thumb down",
                              19: "Thumb up",
                              20: "Turning hand clockwise",
                              21: "Turning hand counterclockwise",
                              22: "Zooming in with full hand",
                              23: "Zooming in with two fingers",
                              24: "Zooming out with full hand",
                              25: "Zooming out with two fingers"}

    def get_gesture_name(self, number):
            return self.gesture_names.get(number)

    def get_gesture_names(self):
            return self.gesture_names