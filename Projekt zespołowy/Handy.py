import sys
from PyQt5 import QtWidgets
from window_app.main_window import Ui_main_window as win
from PyQt5.QtGui import QIcon

def end_application():
    ui.close_application()

app = QtWidgets.QApplication(sys.argv)
QtWidgets.QApplication.setWindowIcon(QIcon('logo.png'))
app.setQuitOnLastWindowClosed(False)
app.lastWindowClosed.connect(end_application)
MainWindow = QtWidgets.QMainWindow()
ui = win()
ui.setupUi(MainWindow)
MainWindow.showMaximized()
sys.exit(app.exec_())
