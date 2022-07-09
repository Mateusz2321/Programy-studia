#install ChromeDriver
#link: https://sites.google.com/chromium.org/driver/downloads?authuser=0


from selenium import webdriver

class ChromeController(object):
    PATH="C:\Program Files (x86)\ChromeDriver\chromedriver.exe"

    def init_window(self):
        self.driver = webdriver.Chrome(self.PATH)

    def open_yt(self):
        self.driver.get("https://www.youtube.com/")

    def close_current_tab(self):
        window_name=self.driver.window_handles[0]
        self.driver.switch_to.window(window_name=window_name)
        self.driver.close()

    def switch_tab(self):
        p = self.driver.current_window_handle
        chwd = self.driver.window_handles
        for w in chwd:
            if (w != p):
                self.driver.switch_to.window(w)

    def new_window(self):
        self.driver.execute_script('''window.open("http://google.pl","_blank");''')