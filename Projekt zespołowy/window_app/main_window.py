
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtMultimediaWidgets import QVideoWidget
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
import cv2
import time
import sys
sys.path.insert(0,"..")
from controllers.controller import Controller
from controllers.gesture_name_mapper import NameMapper
from controllers.functions_getter import FunctionsGetter
from controllers.system_controller import SystemController

class Ui_MainWindow(object):
    def set_cameras_combo_box(self,lst):
        self.camerasComboBox.clear()
        for a in lst:
            self.camerasComboBox.addItem(str(a))
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(725, 571)
        self.name_mapper=NameMapper()
        self.sys_cont=SystemController()
        self.func_get=FunctionsGetter(self.sys_cont)
        self.cont=Controller(self.func_get,self.sys_cont,self)
        self.sys_cont.set_camera_reference(self.cont.get_camera_controller())
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout(self.centralwidget)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        self.tabWidget.setObjectName("tabWidget")
        self.gestureTab = QtWidgets.QWidget()
        self.gestureTab.setObjectName("gestureTab")
        self.gridLayout = QtWidgets.QGridLayout(self.gestureTab)
        self.gridLayout.setObjectName("gridLayout")


        self.mainTab = QtWidgets.QWidget()          ###########
        self.mainTab.setObjectName("mainTab")
        self.mainLayout = QtWidgets.QGridLayout(self.mainTab)
        self.mainLayout.setObjectName("mainLayout")
        self.start_button = QtWidgets.QPushButton(self.mainTab)
        self.start_button.setObjectName("start_button")
        self.mainLayout.addWidget(self.start_button,1,1,1,1)
        self.start_button.clicked.connect(lambda: self.cont.start_gesture_recognition())
        self.stop_button = QtWidgets.QPushButton(self.mainTab)
        self.stop_button.setObjectName("stop_button")
        self.stop_button.clicked.connect(lambda: self.cont.stop_gesture_recognition())
        self.mainLayout.addWidget(self.stop_button, 2, 1, 1, 1)
        self.applyButton_2 = QtWidgets.QPushButton(self.gestureTab)
        self.applyButton_2.setObjectName("applyButton_2")
        self.gridLayout.addWidget(self.applyButton_2, 3, 3, 1, 1)
        self.resetButton = QtWidgets.QPushButton(self.gestureTab)
        self.resetButton.setObjectName("resetButton")
        self.gridLayout.addWidget(self.resetButton, 3, 1, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 3, 2, 1, 1)
        self.cancelButton = QtWidgets.QPushButton(self.gestureTab)
        self.cancelButton.setObjectName("cancelButton")
        self.gridLayout.addWidget(self.cancelButton, 3, 0, 1, 1)
        self.scrollArea = QtWidgets.QScrollArea(self.gestureTab)
        self.scrollArea.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOn)
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents_2 = QtWidgets.QWidget()
        self.scrollAreaWidgetContents_2.setGeometry(QtCore.QRect(0, 0, 637, 411))
        self.scrollAreaWidgetContents_2.setObjectName("scrollAreaWidgetContents_2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.scrollAreaWidgetContents_2)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.widget = QtWidgets.QWidget(self.scrollAreaWidgetContents_2)
        self.widget.setObjectName("widget")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout(self.widget)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label = QtWidgets.QLabel(self.widget)
        self.label.setObjectName("label")
        self.horizontalLayout_4.addWidget(self.label)
        self.comboBox = QtWidgets.QComboBox(self.widget)
        self.comboBox.setObjectName("comboBox")
        for i in range(25):
            self.comboBox.addItem("")
        self.horizontalLayout_4.addWidget(self.comboBox)
        self.verticalLayout_2.addWidget(self.widget)
        self.widget_2 = QtWidgets.QWidget(self.scrollAreaWidgetContents_2)
        self.widget_2.setObjectName("widget_2")
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout(self.widget_2)
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.label_2 = QtWidgets.QLabel(self.widget_2)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_5.addWidget(self.label_2)
        self.comboBox_2 = QtWidgets.QComboBox(self.widget_2)
        self.comboBox_2.setObjectName("comboBox_2")
        for i in range(25):
            self.comboBox_2.addItem("")
        self.horizontalLayout_5.addWidget(self.comboBox_2)
        self.verticalLayout_2.addWidget(self.widget_2)
        self.widget_3 = QtWidgets.QWidget(self.scrollAreaWidgetContents_2)
        self.widget_3.setObjectName("widget_3")
        self.horizontalLayout_6 = QtWidgets.QHBoxLayout(self.widget_3)
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.label_3 = QtWidgets.QLabel(self.widget_3)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_6.addWidget(self.label_3)
        self.comboBox_3 = QtWidgets.QComboBox(self.widget_3)
        self.comboBox_3.setObjectName("comboBox_3")
        for i in range(25):
            self.comboBox_3.addItem("")
        self.horizontalLayout_6.addWidget(self.comboBox_3)
        self.verticalLayout_2.addWidget(self.widget_3)
        self.widget_4 = QtWidgets.QWidget(self.scrollAreaWidgetContents_2)
        self.widget_4.setObjectName("widget_4")
        self.horizontalLayout_7 = QtWidgets.QHBoxLayout(self.widget_4)
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.label_4 = QtWidgets.QLabel(self.widget_4)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_7.addWidget(self.label_4)
        self.comboBox_4 = QtWidgets.QComboBox(self.widget_4)
        self.comboBox_4.setObjectName("comboBox_4")
        for i in range(25):
            self.comboBox_4.addItem("")
        self.horizontalLayout_7.addWidget(self.comboBox_4)
        self.verticalLayout_2.addWidget(self.widget_4)
        self.widget_5 = QtWidgets.QWidget(self.scrollAreaWidgetContents_2)
        self.widget_5.setObjectName("widget_5")
        self.horizontalLayout_8 = QtWidgets.QHBoxLayout(self.widget_5)
        self.horizontalLayout_8.setObjectName("horizontalLayout_8")
        self.label_5 = QtWidgets.QLabel(self.widget_5)
        self.label_5.setObjectName("label_5")
        self.horizontalLayout_8.addWidget(self.label_5)
        self.comboBox_5 = QtWidgets.QComboBox(self.widget_5)
        self.comboBox_5.setObjectName("comboBox_5")
        for i in range(25):
            self.comboBox_5.addItem("")
        self.horizontalLayout_8.addWidget(self.comboBox_5)
        self.verticalLayout_2.addWidget(self.widget_5)
        self.widget_6 = QtWidgets.QWidget(self.scrollAreaWidgetContents_2)
        self.widget_6.setObjectName("widget_6")
        self.horizontalLayout_9 = QtWidgets.QHBoxLayout(self.widget_6)
        self.horizontalLayout_9.setObjectName("horizontalLayout_9")
        self.label_6 = QtWidgets.QLabel(self.widget_6)
        self.label_6.setObjectName("label_6")
        self.horizontalLayout_9.addWidget(self.label_6)
        self.comboBox_6 = QtWidgets.QComboBox(self.widget_6)
        self.comboBox_6.setObjectName("comboBox_6")
        for i in range(25):
            self.comboBox_6.addItem("")
        self.horizontalLayout_9.addWidget(self.comboBox_6)
        self.verticalLayout_2.addWidget(self.widget_6)
        self.scrollArea.setWidget(self.scrollAreaWidgetContents_2)
        self.gridLayout.addWidget(self.scrollArea, 2, 0, 1, 4)

        self.tabWidget.addTab(self.mainTab, "")
        self.tabWidget.addTab(self.gestureTab, "")
        self.cameraTab = QtWidgets.QWidget()
        self.cameraTab.setObjectName("cameraTab")

        self.VBL = QVBoxLayout(self.cameraTab)

        self.FeedLabel = QLabel()
        self.VBL.addWidget(self.FeedLabel)


        self.camerasComboBox = QtWidgets.QComboBox(self.cameraTab)


        self.VBL.addWidget(self.camerasComboBox)

        self.Worker1 = Worker1(self.cont)

        arr = self.cont.get_camera_controller().get_all_cameras()
        for i in arr:
            self.camerasComboBox.addItem(str(i))


        self.camerasComboBox.activated.connect(lambda:
            self.cont.get_camera_controller().set_used_camera_number(int(self.camerasComboBox.currentText())))

        self.Worker1.start()
        self.Worker1.ImageUpdate.connect(self.ImageUpdateSlot)
        # self.setLayout(self.VBL)

        # self.videoVidget = QVideoWidget(self.cameraTab)
        # self.videoVidget.setGeometry(QtCore.QRect(200, 70, 311, 141))
        # self.videoVidget.setLocale(QtCore.QLocale(QtCore.QLocale.Polish, QtCore.QLocale.Poland))
        # self.videoVidget.setObjectName("videoVidget")

        self.tabWidget.addTab(self.cameraTab, "")
        self.horizontalLayout_2.addWidget(self.tabWidget)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 725, 24))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Handy"))
        self.applyButton_2.setText(_translate("MainWindow", "Zastosuj"))
        self.resetButton.setText(_translate("MainWindow", "Reset"))
        self.cancelButton.setText(_translate("MainWindow", "Anuluj"))
        self.start_button.setText(_translate("MainWindow", "Start Handy"))
        self.stop_button.setText(_translate("MainWindow", "Stop Handy"))
        self.label.setText(_translate("MainWindow", "TextLabel"))
        self.label_2.setText(_translate("MainWindow", "TextLabel"))
        self.label_3.setText(_translate("MainWindow", "TextLabel"))
        self.label_4.setText(_translate("MainWindow", "TextLabel"))
        self.label_5.setText(_translate("MainWindow", "TextLabel"))
        self.label_6.setText(_translate("MainWindow", "TextLabel"))
        for i in range(25):
            self.comboBox.setItemText(i, _translate("MainWindow", self.name_mapper.get_gesture_name(i+1)))
            self.comboBox_2.setItemText(i, _translate("MainWindow", self.name_mapper.get_gesture_name(i + 1)))
            self.comboBox_3.setItemText(i, _translate("MainWindow", self.name_mapper.get_gesture_name(i + 1)))
            self.comboBox_4.setItemText(i, _translate("MainWindow", self.name_mapper.get_gesture_name(i + 1)))
            self.comboBox_5.setItemText(i, _translate("MainWindow", self.name_mapper.get_gesture_name(i + 1)))
            self.comboBox_6.setItemText(i, _translate("MainWindow", self.name_mapper.get_gesture_name(i + 1)))

        self.tabWidget.setTabText(self.tabWidget.indexOf(self.mainTab), _translate("MainWindow", "Start"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.gestureTab), _translate("MainWindow", "Gesty"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.cameraTab), _translate("MainWindow", "Kamera"))
        # if self.cameraTab.isActiveWindow():

    def ImageUpdateSlot(self, Image):
        self.FeedLabel.setPixmap(QPixmap.fromImage(Image))

    def CancelFeed(self):
        self.Worker1.stop()

class Worker1(QThread):
    def __init__(self,controller):
        super().__init__()
        self.controller=controller
    ImageUpdate = pyqtSignal(QImage)

    def run(self):
        self.ThreadActive = True
        self.camera=self.controller.get_camera_controller()

        while self.ThreadActive:
            ret, frame = self.camera.get_camera_image()
            if ret is True:
                Image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                FlippedImage = cv2.flip(Image, 1)
                ConvertToQtFormat = QImage(FlippedImage.data, FlippedImage.shape[1], FlippedImage.shape[0],
                                           QImage.Format_RGB888)
                Pic = ConvertToQtFormat.scaled(640, 480, Qt.KeepAspectRatio)
                self.ImageUpdate.emit(Pic)



    def stop(self):
        self.ThreadActive = False
        self.quit()


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
