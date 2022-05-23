import sys
from PyQt5 import QtWidgets
from window_app.main_window import Ui_MainWindow as win

def end_application():
    ui.close_application()

app = QtWidgets.QApplication(sys.argv)
app.setQuitOnLastWindowClosed(False)
app.lastWindowClosed.connect(end_application)
MainWindow = QtWidgets.QMainWindow()
ui = win()
ui.setupUi(MainWindow)
MainWindow.showNormal()

sys.exit(app.exec_())
