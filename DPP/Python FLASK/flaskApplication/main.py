
from PyQt5 import QtCore, QtGui, QtWidgets
import requests
import ast
import json
import easygui as e

from requests.exceptions import ConnectionError


class Ui_MainWindow(object):
    def __init__(self):
        self.stone = {}
        self.address = 'http://localhost:5000'
        self.req_answer = None
        try:
            self.req_answer = requests.get(self.address+'/add')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!",
                     "Error")
            quit()
        self.game_id = self.req_answer.text

    def choose_field(self,position:int):
        try:
            self.req_answer=requests.get(self.address+'/'+str(self.game_id)+'/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >=300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        game_status=eval(self.req_answer.text)
        self.req_answer = requests.get(self.address+'/'+str(self.game_id)+'/start_status')
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        start_status=eval (self.req_answer.text)
        self.req_answer = requests.get(self.address + '/'
                                       + str(self.game_id) + '/start_computer_status')
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        start_computer_status = eval (self.req_answer.text)
        if game_status is False:
            pos=self.get_label(position)
            color = pos.palette().button().color().name()
            if color=='#787878' or color=='#9b9b9b':
                stone_result = eval(requests.get(self.address + '/' + str(self.game_id) +
                                                 '/put_stone/white/'+str(position)+'/').text)
                if stone_result is True:
                    pos.setStyleSheet("border-radius: 20px;"
                                 "background-color: #ffffff")
            elif color=="#ffffff":
                stone_result = eval(requests.get(self.address + '/' + str(self.game_id) +
                                                 '/put_stone/black/' + str(position) + '/').text)
                if stone_result is True:
                    pos.setStyleSheet("border-radius: 20px;"
                                 "background-color: #000000")
            else:
                stone_result = eval(requests.get(self.address + '/' + str(self.game_id) +
                                                 '/put_stone/gray/' + str(position) + '/').text)
                if stone_result is True:
                    if position == 21 or position == 25 or position == 41\
                            or position == 57 or position == 61:
                        pos.setStyleSheet("border-radius: 20px;"
                                         "background-color: #787878")
                    else:
                        pos.setStyleSheet("border-radius: 20px;"
                                         "background-color: #9B9B9B")
        elif start_status is True :
            move_player=requests.get(self.address+'/'+str(self.game_id)+'/move').text
            stone_result = eval(requests.get(self.address + '/' + str(self.game_id) +
                                             '/put_stone/'+move_player+'/' + str(position) + '/').text)
            if stone_result is True:
                stone_layout = requests.get(self.address + '/' + str(self.game_id) + '/stone_layout').text
                layout_list = ast.literal_eval(stone_layout)
                layout_list = [n.strip() for n in layout_list]
                self.draw_stones(layout_list)
            if move_player=='black':
                move_player='white'
            else:
                move_player='black'
            self.label_83.setText(QtCore.QCoreApplication.translate
                                  ("MainWindow", move_player+ " move"))
            self.textEdit_2.clear()
            message = requests.get(self.address + '/' + str(self.game_id) + '/message').text
            self.textEdit_2.insertPlainText(message)
        elif start_computer_status is True:
            move_player=requests.get(self.address+'/'+
                                     str(self.game_id)+'/move').text
            stone_result = eval(requests.get(self.address + '/' + str(self.game_id) +
                                             '/put_stone/'+move_player+'/' + str(position) + '/').text)
            if stone_result is True:
                stone_layout = requests.get(self.address + '/' +
                                            str(self.game_id) + '/stone_layout').text
                layout_list = ast.literal_eval(stone_layout)
                layout_list = [n.strip() for n in layout_list]
                self.draw_stones(layout_list)
            self.label_83.setText(QtCore.QCoreApplication.translate
                                  ("MainWindow", move_player+ " move"))
            self.textEdit_2.clear()
            message = requests.get(self.address + '/' + str(self.game_id) + '/message').text
            self.textEdit_2.insertPlainText(message)

    def get_label(self,pos:int):
        for st in self.stone.keys():
            if self.stone.get(st)==pos:
                return st
        return None

    def start_game(self):
        try:
            self.req_answer = requests.get(self.address+'/'+str(self.game_id)+'/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        game_status=eval (self.req_answer.text)
        if game_status is True:
            self.textEdit_2.clear()
            self.textEdit_2.insertPlainText("You can not start new game during an ongoing game")
            return
        self.textEdit_2.clear()
        stone_layout=requests.get(self.address+'/'+str(self.game_id)+'/start_game').text
        layout_list=ast.literal_eval(stone_layout)
        layout_list= [n.strip() for n in layout_list]
        self.draw_stones(layout_list)
        move_player=requests.get(self.address+'/'+str(self.game_id)+'/move').text
        self.label_83.setText(QtCore.QCoreApplication.translate("MainWindow", move_player+" move"))

    def stop_game(self):
        try:
            self.req_answer = requests.get(self.address+'/'+str(self.game_id)+'/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        game_status=eval (self.req_answer.text)
        if game_status is False:
            self.textEdit_2.clear()
            self.textEdit_2.insertPlainText("You are not during any game!")
            return
        self.textEdit_2.clear()
        requests.get(self.address+'/'+str(self.game_id)+'/stop_game')
        self.textEdit_2.clear()
        white_result = requests.get(self.address + '/' + str(self.game_id) + '/white_result').text
        black_result = requests.get(self.address + '/' + str(self.game_id) + '/black_result').text
        self.textEdit_2.insertPlainText("White: "+white_result+"\n")
        self.textEdit_2.insertPlainText("Black: " + black_result)
        self.label_83.setText(QtCore.QCoreApplication.translate("MainWindow",""))

    def pass_game(self):
        self.textEdit_2.clear()
        try:
            self.req_answer = requests.get(self.address + '/' + str(self.game_id) + '/pass_game')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        pass_game = eval (self.req_answer.text)
        if pass_game is True:
            white_result = requests.get(self.address + '/' +
                                        str(self.game_id) + '/white_result').text
            black_result = requests.get(self.address + '/' +
                                        str(self.game_id) + '/black_result').text

            self.textEdit_2.insertPlainText("White: " + white_result+"\n")
            self.textEdit_2.insertPlainText("Black: " + black_result+"\n")
        message=requests.get(self.address+'/'+str(self.game_id)+'/message').text
        self.textEdit_2.insertPlainText(message)

    def resign(self):
        try:
            self.req_answer = requests.get(self.address+'/'+str(self.game_id)+'/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        game_status=eval (self.req_answer.text)
        if game_status is False:
            self.textEdit_2.clear()
            self.textEdit_2.insertPlainText("You are not during any game!")
            return
        requests.get(self.address+'/'+str(self.game_id)+'/stop_game')
        self.textEdit_2.clear()

        move_player = requests.get(self.address + '/' + str(self.game_id) + '/move').text
        self.textEdit_2.insertPlainText(move_player+ " lost!")
        self.label_83.setText(QtCore.QCoreApplication.translate("MainWindow", ""))

    def start_from_this_position(self):
        try:
            self.req_answer = requests.get(self.address+'/'+str(self.game_id)+'/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        game_status=eval (self.req_answer.text)
        if game_status is  True:
            self.textEdit_2.clear()
            self.textEdit_2.insertPlainText("You are during another game!")
            return
        temp_tab=[]
        for position in range(1,82):
            pos = self.get_label(position)
            color = pos.palette().button().color().name()
            if color == '#787878' or color == '#9b9b9b':
                temp_tab.append('gray')
            elif color == "#ffffff":
                temp_tab.append('white')
            else:
                temp_tab.append('black')
        layout = json.dumps(temp_tab)
        req=requests.post(self.address + '/' + str(self.game_id) +
                          '/start_position', json=layout)
        self.textEdit_2.clear()
        message = requests.get(self.address + '/' + str(self.game_id) +
                               '/message').text
        self.textEdit_2.insertPlainText(message)
        move_player = requests.get(self.address + '/' +
                                   str(self.game_id) + '/move').text
        self.label_83.setText(QtCore.QCoreApplication.translate("MainWindow", move_player + " move"))

    def play_against_computer(self):
        try:
            self.req_answer = requests.get(self.address + '/' + str(self.game_id) + '/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        game_status=eval (self.req_answer.text)
        if game_status is True:
            self.textEdit_2.clear()
            self.textEdit_2.insertPlainText("You can not start new game during an ongoing game")
            return
        self.textEdit_2.clear()
        stone_layout = requests.get(self.address + '/' + str(self.game_id) + '/start_computer').text
        layout_list = ast.literal_eval(stone_layout)
        layout_list = [n.strip() for n in layout_list]
        self.draw_stones(layout_list)
        move_player = requests.get(self.address + '/' + str(self.game_id) + '/move').text
        self.label_83.setText(QtCore.QCoreApplication.translate("MainWindow", move_player + " move"))

    def play_against_computer_from_this_position(self):
        try:
            self.req_answer = requests.get(self.address + '/' + str(self.game_id) + '/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\nServer answer was >= 300.")
            return
        game_status=eval (self.req_answer.text)
        if game_status is True:
            self.textEdit_2.clear()
            self.textEdit_2.insertPlainText("You are during another game!")
            return
        temp_tab = []
        for position in range(1, 82):
            pos = self.get_label(position)
            color = pos.palette().button().color().name()
            if color == '#787878' or color == '#9b9b9b':
                temp_tab.append('gray')
            elif color == "#ffffff":
                temp_tab.append('white')
            else:
                temp_tab.append('black')
        layout = json.dumps(temp_tab)
        req = requests.post(self.address + '/' + str(self.game_id) +
                            '/start_computer_position', json=layout)
        self.textEdit_2.clear()
        message = requests.get(self.address + '/' + str(self.game_id) + '/message').text
        self.textEdit_2.insertPlainText(message)
        move_player = requests.get(self.address + '/' + str(self.game_id) + '/move').text
        self.label_83.setText(QtCore.QCoreApplication.translate("MainWindow", move_player + " move"))

    def draw_stones(self,stones_list:list):
        x=None
        for st in self.stone.keys():
            x=self.stone.get(st)
            if stones_list[x-1]=='gray':
                if x==21 or x==25 or x==41 or x==57 or x==61:
                    st.setStyleSheet("border-radius: 20px;"
                                   "background-color: #787878")
                else:
                    st.setStyleSheet("border-radius: 20px;"
                             "background-color: #9B9B9B")
            elif stones_list[x-1]=='white':
                st.setStyleSheet("border-radius: 20px;"
                                 "background-color: #FFFFFF")
            else:
                st.setStyleSheet("border-radius: 20px;"
                                 "background-color: #000000")

    def clear_board(self):
        try:
            self.req_answer = requests.get(self.address + '/' +
                                       str(self.game_id) + '/status')
        except ConnectionError:
            e.msgbox("An error in connection with server has occured!", "Error")
            return
        if self.req_answer.status_code >= 300:
            self.textEdit.clear()
            self.textEdit.insertPlainText("Error in request occured!\n"
                                          "Server answer was >= 300.")
            return
        game_status= eval(self.req_answer.text)
        if game_status is True:
            self.textEdit_2.clear()
            self.textEdit_2.insertPlainText("You can not clear board during game")
        else:
            self.textEdit_2.clear()
            stone_layout = requests.get(self.address + '/' +
                                        str(self.game_id) + '/start_computer').text
            layout_list = ast.literal_eval(stone_layout)
            layout_list = [n.strip() for n in layout_list]
            self.draw_stones(layout_list)
    def on_close(self):
        try:
            requests.get(self.address + '/' + str(self.game_id) + '/delete')
        except:
            pass

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(799, 647)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.line = QtWidgets.QFrame(self.centralwidget)
        self.line.setGeometry(QtCore.QRect(40, 40, 491, 16))
        self.line.setFrameShape(QtWidgets.QFrame.HLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.line_2 = QtWidgets.QFrame(self.centralwidget)
        self.line_2.setGeometry(QtCore.QRect(40, 100, 491, 16))
        self.line_2.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_2.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_2.setObjectName("line_2")
        self.line_3 = QtWidgets.QFrame(self.centralwidget)
        self.line_3.setGeometry(QtCore.QRect(40, 160, 491, 16))
        self.line_3.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_3.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_3.setObjectName("line_3")
        self.line_4 = QtWidgets.QFrame(self.centralwidget)
        self.line_4.setGeometry(QtCore.QRect(20, 39, 41, 491))
        self.line_4.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_4.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_4.setObjectName("line_4")
        self.line_5 = QtWidgets.QFrame(self.centralwidget)
        self.line_5.setGeometry(QtCore.QRect(40, 220, 491, 16))
        self.line_5.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_5.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_5.setObjectName("line_5")
        self.line_6 = QtWidgets.QFrame(self.centralwidget)
        self.line_6.setGeometry(QtCore.QRect(40, 280, 491, 16))
        self.line_6.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_6.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_6.setObjectName("line_6")
        self.line_7 = QtWidgets.QFrame(self.centralwidget)
        self.line_7.setGeometry(QtCore.QRect(40, 340, 491, 16))
        self.line_7.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_7.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_7.setObjectName("line_7")
        self.line_8 = QtWidgets.QFrame(self.centralwidget)
        self.line_8.setGeometry(QtCore.QRect(40, 400, 491, 16))
        self.line_8.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_8.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_8.setObjectName("line_8")
        self.line_9 = QtWidgets.QFrame(self.centralwidget)
        self.line_9.setGeometry(QtCore.QRect(40, 460, 491, 20))
        self.line_9.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_9.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_9.setObjectName("line_9")
        self.line_10 = QtWidgets.QFrame(self.centralwidget)
        self.line_10.setGeometry(QtCore.QRect(40, 520, 491, 16))
        self.line_10.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_10.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_10.setObjectName("line_10")
        self.line_11 = QtWidgets.QFrame(self.centralwidget)
        self.line_11.setGeometry(QtCore.QRect(80, 40, 41, 491))
        self.line_11.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_11.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_11.setObjectName("line_11")
        self.line_12 = QtWidgets.QFrame(self.centralwidget)
        self.line_12.setGeometry(QtCore.QRect(140, 40, 41, 491))
        self.line_12.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_12.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_12.setObjectName("line_12")
        self.line_13 = QtWidgets.QFrame(self.centralwidget)
        self.line_13.setGeometry(QtCore.QRect(200, 40, 41, 491))
        self.line_13.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_13.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_13.setObjectName("line_13")
        self.line_14 = QtWidgets.QFrame(self.centralwidget)
        self.line_14.setGeometry(QtCore.QRect(260, 40, 41, 491))
        self.line_14.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_14.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_14.setObjectName("line_14")
        self.line_15 = QtWidgets.QFrame(self.centralwidget)
        self.line_15.setGeometry(QtCore.QRect(320, 40, 41, 491))
        self.line_15.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_15.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_15.setObjectName("line_15")
        self.line_16 = QtWidgets.QFrame(self.centralwidget)
        self.line_16.setGeometry(QtCore.QRect(380, 40, 41, 481))
        self.line_16.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_16.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_16.setObjectName("line_16")
        self.line_17 = QtWidgets.QFrame(self.centralwidget)
        self.line_17.setGeometry(QtCore.QRect(440, 40, 31, 491))
        self.line_17.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_17.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_17.setObjectName("line_17")
        self.line_18 = QtWidgets.QFrame(self.centralwidget)
        self.line_18.setGeometry(QtCore.QRect(500, 40, 31, 491))
        self.line_18.setFrameShape(QtWidgets.QFrame.VLine)
        self.line_18.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_18.setObjectName("line_18")

        self.label = QtWidgets.QPushButton(self.centralwidget)
        self.label.move(20,510)
        self.label.resize(40,40)
        self.label.setStyleSheet("border-radius: 20px;"
                                 "background-color: #9B9B9B")
        self.label.clicked.connect(lambda: self.choose_field(1))
        self.label_2 = QtWidgets.QPushButton(self.centralwidget)
        self.label_2.move(80, 510)
        self.label_2.resize(40, 40)
        self.label_2.setStyleSheet("border-radius: 20px;"
                                 "background-color: #9B9B9B")
        self.label_2.clicked.connect(lambda: self.choose_field(2))

        self.label_3 = QtWidgets.QPushButton(self.centralwidget)
        self.label_3.move(140, 510)
        self.label_3.resize(40, 40)
        self.label_3.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_3.clicked.connect(lambda: self.choose_field(3))
        self.label_4 = QtWidgets.QPushButton(self.centralwidget)
        self.label_4.move(200, 510)
        self.label_4.resize(40, 40)
        self.label_4.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_4.clicked.connect(lambda: self.choose_field(4))
        self.label_5 = QtWidgets.QPushButton(self.centralwidget)
        self.label_5.move(260, 510)
        self.label_5.resize(40, 40)
        self.label_5.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_5.clicked.connect(lambda: self.choose_field(5))
        self.label_6 = QtWidgets.QPushButton(self.centralwidget)
        self.label_6.move(320, 510)
        self.label_6.resize(40, 40)
        self.label_6.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_6.clicked.connect(lambda: self.choose_field(6))
        self.label_7 = QtWidgets.QPushButton(self.centralwidget)
        self.label_7.move(380, 510)
        self.label_7.resize(40, 40)
        self.label_7.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_7.clicked.connect(lambda: self.choose_field(7))
        self.label_8 = QtWidgets.QPushButton(self.centralwidget)
        self.label_8.move(440, 510)
        self.label_8.resize(40, 40)
        self.label_8.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_8.clicked.connect(lambda: self.choose_field(8))
        self.label_9 = QtWidgets.QPushButton(self.centralwidget)
        self.label_9.move(500, 510)
        self.label_9.resize(40, 40)
        self.label_9.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_9.clicked.connect(lambda: self.choose_field(9))
        self.label_10 = QtWidgets.QPushButton(self.centralwidget)
        self.label_10.move(20, 450)
        self.label_10.resize(40, 40)
        self.label_10.setStyleSheet("border-radius: 20px;"
                                 "background-color: #9B9B9B")

        self.label_10.clicked.connect(lambda: self.choose_field(10))

        self.label_11 = QtWidgets.QPushButton(self.centralwidget)
        self.label_11.move(80, 450)
        self.label_11.resize(40, 40)
        self.label_11.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_11.clicked.connect(lambda: self.choose_field(11))

        self.label_12 = QtWidgets.QPushButton(self.centralwidget)
        self.label_12.move(140, 450)
        self.label_12.resize(40, 40)
        self.label_12.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_12.clicked.connect(lambda: self.choose_field(12))
        self.label_13 = QtWidgets.QPushButton(self.centralwidget)
        self.label_13.move(200, 450)
        self.label_13.resize(40, 40)
        self.label_13.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_13.clicked.connect(lambda: self.choose_field(13))
        self.label_14 = QtWidgets.QPushButton(self.centralwidget)
        self.label_14.move(260, 450)
        self.label_14.resize(40, 40)
        self.label_14.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_14.clicked.connect(lambda: self.choose_field(14))
        self.label_15 = QtWidgets.QPushButton(self.centralwidget)
        self.label_15.move(320, 450)
        self.label_15.resize(40, 40)
        self.label_15.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_15.clicked.connect(lambda: self.choose_field(15))
        self.label_16 = QtWidgets.QPushButton(self.centralwidget)
        self.label_16.move(380, 450)
        self.label_16.resize(40, 40)
        self.label_16.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_16.clicked.connect(lambda: self.choose_field(16))
        self.label_17 = QtWidgets.QPushButton(self.centralwidget)
        self.label_17.move(440, 450)
        self.label_17.resize(40, 40)
        self.label_17.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_17.clicked.connect(lambda: self.choose_field(17))
        self.label_18 = QtWidgets.QPushButton(self.centralwidget)
        self.label_18.move(500, 450)
        self.label_18.resize(40, 40)
        self.label_18.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")
        self.label_18.clicked.connect(lambda: self.choose_field(18))
        self.label_19 = QtWidgets.QPushButton(self.centralwidget)
        self.label_19.move(20, 390)
        self.label_19.resize(40, 40)
        self.label_19.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")

        self.label_19.clicked.connect(lambda: self.choose_field(19))

        self.label_20 = QtWidgets.QPushButton(self.centralwidget)
        self.label_20.move(80, 390)
        self.label_20.resize(40, 40)
        self.label_20.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_20.clicked.connect(lambda: self.choose_field(20))

        self.label_21 = QtWidgets.QPushButton(self.centralwidget)
        self.label_21.move(140, 390)
        self.label_21.resize(40, 40)
        self.label_21.setStyleSheet("border-radius: 20px;"
                                    "background-color: #787878")
        self.label_21.clicked.connect(lambda: self.choose_field(21))
        self.label_22 = QtWidgets.QPushButton(self.centralwidget)
        self.label_22.move(200, 390)
        self.label_22.resize(40, 40)
        self.label_22.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_22.clicked.connect(lambda: self.choose_field(22))
        self.label_23 = QtWidgets.QPushButton(self.centralwidget)
        self.label_23.move(260, 390)
        self.label_23.resize(40, 40)
        self.label_23.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_23.clicked.connect(lambda: self.choose_field(23))
        self.label_24 = QtWidgets.QPushButton(self.centralwidget)
        self.label_24.move(320, 390)
        self.label_24.resize(40, 40)
        self.label_24.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_24.clicked.connect(lambda: self.choose_field(24))
        self.label_25 = QtWidgets.QPushButton(self.centralwidget)
        self.label_25.move(380, 390)
        self.label_25.resize(40, 40)
        self.label_25.setStyleSheet("border-radius: 20px;"
                                    "background-color: #787878")
        self.label_25.clicked.connect(lambda: self.choose_field(25))
        self.label_26 = QtWidgets.QPushButton(self.centralwidget)
        self.label_26.move(440, 390)
        self.label_26.resize(40, 40)
        self.label_26.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_26.clicked.connect(lambda: self.choose_field(26))
        self.label_27 = QtWidgets.QPushButton(self.centralwidget)
        self.label_27.move(500, 390)
        self.label_27.resize(40, 40)
        self.label_27.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_27.clicked.connect(lambda: self.choose_field(27))
        self.label_28 = QtWidgets.QPushButton(self.centralwidget)
        self.label_28.move(20, 330)
        self.label_28.resize(40, 40)
        self.label_28.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")

        self.label_28.clicked.connect(lambda: self.choose_field(28))

        self.label_29 = QtWidgets.QPushButton(self.centralwidget)
        self.label_29.move(80, 330)
        self.label_29.resize(40, 40)
        self.label_29.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_29.clicked.connect(lambda: self.choose_field(29))

        self.label_30 = QtWidgets.QPushButton(self.centralwidget)
        self.label_30.move(140, 330)
        self.label_30.resize(40, 40)
        self.label_30.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_30.clicked.connect(lambda: self.choose_field(30))
        self.label_31 = QtWidgets.QPushButton(self.centralwidget)
        self.label_31.move(200, 330)
        self.label_31.resize(40, 40)
        self.label_31.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_31.clicked.connect(lambda: self.choose_field(31))
        self.label_32 = QtWidgets.QPushButton(self.centralwidget)
        self.label_32.move(260, 330)
        self.label_32.resize(40, 40)
        self.label_32.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_32.clicked.connect(lambda: self.choose_field(32))
        self.label_33 = QtWidgets.QPushButton(self.centralwidget)
        self.label_33.move(320, 330)
        self.label_33.resize(40, 40)
        self.label_33.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_33.clicked.connect(lambda: self.choose_field(33))
        self.label_34 = QtWidgets.QPushButton(self.centralwidget)
        self.label_34.move(380, 330)
        self.label_34.resize(40, 40)
        self.label_34.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_34.clicked.connect(lambda: self.choose_field(34))
        self.label_35 = QtWidgets.QPushButton(self.centralwidget)
        self.label_35.move(440, 330)
        self.label_35.resize(40, 40)
        self.label_35.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_35.clicked.connect(lambda: self.choose_field(35))
        self.label_36 = QtWidgets.QPushButton(self.centralwidget)
        self.label_36.move(500, 330)
        self.label_36.resize(40, 40)
        self.label_36.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_36.clicked.connect(lambda: self.choose_field(36))
        self.label_37 = QtWidgets.QPushButton(self.centralwidget)
        self.label_37.move(20, 270)
        self.label_37.resize(40, 40)
        self.label_37.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")

        self.label_37.clicked.connect(lambda: self.choose_field(37))

        self.label_38 = QtWidgets.QPushButton(self.centralwidget)
        self.label_38.move(80, 270)
        self.label_38.resize(40, 40)
        self.label_38.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_38.clicked.connect(lambda: self.choose_field(38))

        self.label_39 = QtWidgets.QPushButton(self.centralwidget)
        self.label_39.move(140, 270)
        self.label_39.resize(40, 40)
        self.label_39.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_39.clicked.connect(lambda: self.choose_field(39))
        self.label_40 = QtWidgets.QPushButton(self.centralwidget)
        self.label_40.move(200, 270)
        self.label_40.resize(40, 40)
        self.label_40.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_40.clicked.connect(lambda: self.choose_field(40))
        self.label_41 = QtWidgets.QPushButton(self.centralwidget)
        self.label_41.move(260, 270)
        self.label_41.resize(40, 40)
        self.label_41.setStyleSheet("border-radius: 20px;"
                                    "background-color: #787878")
        self.label_41.clicked.connect(lambda: self.choose_field(41))
        self.label_42 = QtWidgets.QPushButton(self.centralwidget)
        self.label_42.move(320, 270)
        self.label_42.resize(40, 40)
        self.label_42.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_42.clicked.connect(lambda: self.choose_field(42))
        self.label_43 = QtWidgets.QPushButton(self.centralwidget)
        self.label_43.move(380, 270)
        self.label_43.resize(40, 40)
        self.label_43.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_43.clicked.connect(lambda: self.choose_field(43))
        self.label_44 = QtWidgets.QPushButton(self.centralwidget)
        self.label_44.move(440, 270)
        self.label_44.resize(40, 40)
        self.label_44.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_44.clicked.connect(lambda: self.choose_field(44))
        self.label_45 = QtWidgets.QPushButton(self.centralwidget)
        self.label_45.move(500, 270)
        self.label_45.resize(40, 40)
        self.label_45.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_45.clicked.connect(lambda: self.choose_field(45))
        self.label_46 = QtWidgets.QPushButton(self.centralwidget)
        self.label_46.move(20, 210)
        self.label_46.resize(40, 40)
        self.label_46.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")

        self.label_46.clicked.connect(lambda: self.choose_field(46))

        self.label_47 = QtWidgets.QPushButton(self.centralwidget)
        self.label_47.move(80, 210)
        self.label_47.resize(40, 40)
        self.label_47.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_47.clicked.connect(lambda: self.choose_field(47))

        self.label_48 = QtWidgets.QPushButton(self.centralwidget)
        self.label_48.move(140, 210)
        self.label_48.resize(40, 40)
        self.label_48.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_48.clicked.connect(lambda: self.choose_field(48))
        self.label_49 = QtWidgets.QPushButton(self.centralwidget)
        self.label_49.move(200, 210)
        self.label_49.resize(40, 40)
        self.label_49.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_49.clicked.connect(lambda: self.choose_field(49))
        self.label_50 = QtWidgets.QPushButton(self.centralwidget)
        self.label_50.move(260, 210)
        self.label_50.resize(40, 40)
        self.label_50.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_50.clicked.connect(lambda: self.choose_field(50))
        self.label_51 = QtWidgets.QPushButton(self.centralwidget)
        self.label_51.move(320, 210)
        self.label_51.resize(40, 40)
        self.label_51.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_51.clicked.connect(lambda: self.choose_field(51))
        self.label_52 = QtWidgets.QPushButton(self.centralwidget)
        self.label_52.move(380, 210)
        self.label_52.resize(40, 40)
        self.label_52.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_52.clicked.connect(lambda: self.choose_field(52))
        self.label_53 = QtWidgets.QPushButton(self.centralwidget)
        self.label_53.move(440, 210)
        self.label_53.resize(40, 40)
        self.label_53.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_53.clicked.connect(lambda: self.choose_field(53))
        self.label_54 = QtWidgets.QPushButton(self.centralwidget)
        self.label_54.move(500, 210)
        self.label_54.resize(40, 40)
        self.label_54.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_54.clicked.connect(lambda: self.choose_field(54))
        self.label_55 = QtWidgets.QPushButton(self.centralwidget)
        self.label_55.move(20, 150)
        self.label_55.resize(40, 40)
        self.label_55.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")

        self.label_55.clicked.connect(lambda: self.choose_field(55))

        self.label_56 = QtWidgets.QPushButton(self.centralwidget)
        self.label_56.move(80, 150)
        self.label_56.resize(40, 40)
        self.label_56.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_56.clicked.connect(lambda: self.choose_field(56))

        self.label_57 = QtWidgets.QPushButton(self.centralwidget)
        self.label_57.move(140, 150)
        self.label_57.resize(40, 40)
        self.label_57.setStyleSheet("border-radius: 20px;"
                                    "background-color: #787878")
        self.label_57.clicked.connect(lambda: self.choose_field(57))
        self.label_58 = QtWidgets.QPushButton(self.centralwidget)
        self.label_58.move(200, 150)
        self.label_58.resize(40, 40)
        self.label_58.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_58.clicked.connect(lambda: self.choose_field(58))
        self.label_59 = QtWidgets.QPushButton(self.centralwidget)
        self.label_59.move(260, 150)
        self.label_59.resize(40, 40)
        self.label_59.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_59.clicked.connect(lambda: self.choose_field(59))
        self.label_60 = QtWidgets.QPushButton(self.centralwidget)
        self.label_60.move(320, 150)
        self.label_60.resize(40, 40)
        self.label_60.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_60.clicked.connect(lambda: self.choose_field(60))
        self.label_61 = QtWidgets.QPushButton(self.centralwidget)
        self.label_61.move(380, 150)
        self.label_61.resize(40, 40)
        self.label_61.setStyleSheet("border-radius: 20px;"
                                    "background-color: #787878")
        self.label_61.clicked.connect(lambda: self.choose_field(61))
        self.label_62 = QtWidgets.QPushButton(self.centralwidget)
        self.label_62.move(440, 150)
        self.label_62.resize(40, 40)
        self.label_62.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_62.clicked.connect(lambda: self.choose_field(62))
        self.label_63 = QtWidgets.QPushButton(self.centralwidget)
        self.label_63.move(500, 150)
        self.label_63.resize(40, 40)
        self.label_63.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_63.clicked.connect(lambda: self.choose_field(63))
        self.label_64 = QtWidgets.QPushButton(self.centralwidget)
        self.label_64.move(20, 90)
        self.label_64.resize(40, 40)
        self.label_64.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")

        self.label_64.clicked.connect(lambda: self.choose_field(64))

        self.label_65 = QtWidgets.QPushButton(self.centralwidget)
        self.label_65.move(80, 90)
        self.label_65.resize(40, 40)
        self.label_65.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_65.clicked.connect(lambda: self.choose_field(65))

        self.label_66 = QtWidgets.QPushButton(self.centralwidget)
        self.label_66.move(140, 90)
        self.label_66.resize(40, 40)
        self.label_66.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_66.clicked.connect(lambda: self.choose_field(66))
        self.label_67 = QtWidgets.QPushButton(self.centralwidget)
        self.label_67.move(200, 90)
        self.label_67.resize(40, 40)
        self.label_67.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_67.clicked.connect(lambda: self.choose_field(67))
        self.label_68 = QtWidgets.QPushButton(self.centralwidget)
        self.label_68.move(260, 90)
        self.label_68.resize(40, 40)
        self.label_68.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_68.clicked.connect(lambda: self.choose_field(68))
        self.label_69 = QtWidgets.QPushButton(self.centralwidget)
        self.label_69.move(320, 90)
        self.label_69.resize(40, 40)
        self.label_69.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_69.clicked.connect(lambda: self.choose_field(69))
        self.label_70 = QtWidgets.QPushButton(self.centralwidget)
        self.label_70.move(380, 90)
        self.label_70.resize(40, 40)
        self.label_70.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_70.clicked.connect(lambda: self.choose_field(70))
        self.label_71 = QtWidgets.QPushButton(self.centralwidget)
        self.label_71.move(440, 90)
        self.label_71.resize(40, 40)
        self.label_71.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_71.clicked.connect(lambda: self.choose_field(71))
        self.label_72 = QtWidgets.QPushButton(self.centralwidget)
        self.label_72.move(500, 90)
        self.label_72.resize(40, 40)
        self.label_72.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_72.clicked.connect(lambda: self.choose_field(72))
        self.label_73 = QtWidgets.QPushButton(self.centralwidget)
        self.label_73.move(20, 30)
        self.label_73.resize(40, 40)
        self.label_73.setStyleSheet("border-radius: 20px;"
                                   "background-color: #9B9B9B")

        self.label_73.clicked.connect(lambda: self.choose_field(73))

        self.label_74 = QtWidgets.QPushButton(self.centralwidget)
        self.label_74.move(80, 30)
        self.label_74.resize(40, 40)
        self.label_74.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_74.clicked.connect(lambda: self.choose_field(74))

        self.label_75 = QtWidgets.QPushButton(self.centralwidget)
        self.label_75.move(140, 30)
        self.label_75.resize(40, 40)
        self.label_75.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_75.clicked.connect(lambda: self.choose_field(75))
        self.label_76 = QtWidgets.QPushButton(self.centralwidget)
        self.label_76.move(200, 30)
        self.label_76.resize(40, 40)
        self.label_76.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_76.clicked.connect(lambda: self.choose_field(76))
        self.label_77 = QtWidgets.QPushButton(self.centralwidget)
        self.label_77.move(260, 30)
        self.label_77.resize(40, 40)
        self.label_77.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_77.clicked.connect(lambda: self.choose_field(77))
        self.label_78 = QtWidgets.QPushButton(self.centralwidget)
        self.label_78.move(320, 30)
        self.label_78.resize(40, 40)
        self.label_78.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_78.clicked.connect(lambda: self.choose_field(78))
        self.label_79 = QtWidgets.QPushButton(self.centralwidget)
        self.label_79.move(380, 30)
        self.label_79.resize(40, 40)
        self.label_79.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_79.clicked.connect(lambda: self.choose_field(79))
        self.label_80 = QtWidgets.QPushButton(self.centralwidget)
        self.label_80.move(440, 30)
        self.label_80.resize(40, 40)
        self.label_80.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_80.clicked.connect(lambda: self.choose_field(80))
        self.label_81 = QtWidgets.QPushButton(self.centralwidget)
        self.label_81.move(500, 30)
        self.label_81.resize(40, 40)
        self.label_81.setStyleSheet("border-radius: 20px;"
                                    "background-color: #9B9B9B")
        self.label_81.clicked.connect(lambda: self.choose_field(81))
        self.button_end = QtWidgets.QPushButton(self.centralwidget)
        self.button_end.move(350, 580)
        self.button_end.resize(200, 40)
        self.button_end.setStyleSheet("background-color: #FFFFFF")
        self.button_end.clicked.connect(lambda: self.on_close())
        self.stone[self.label]=1
        self.stone[self.label_2] = 2
        self.stone[self.label_3] = 3
        self.stone[self.label_4] = 4
        self.stone[self.label_5] = 5
        self.stone[self.label_6] = 6
        self.stone[self.label_7] = 7
        self.stone[self.label_8] = 8
        self.stone[self.label_9] = 9
        self.stone[self.label_10] = 10
        self.stone[self.label_11] = 11
        self.stone[self.label_12] = 12
        self.stone[self.label_13] = 13
        self.stone[self.label_14] = 14
        self.stone[self.label_15] = 15
        self.stone[self.label_16] = 16
        self.stone[self.label_17] = 17
        self.stone[self.label_18] = 18
        self.stone[self.label_19] = 19
        self.stone[self.label_20] = 20
        self.stone[self.label_21] = 21
        self.stone[self.label_22] = 22
        self.stone[self.label_23] = 23
        self.stone[self.label_24] = 24
        self.stone[self.label_25] = 25
        self.stone[self.label_26] = 26
        self.stone[self.label_27] = 27
        self.stone[self.label_28] = 28
        self.stone[self.label_29] = 29
        self.stone[self.label_30] = 30
        self.stone[self.label_31] = 31
        self.stone[self.label_32] = 32
        self.stone[self.label_33] = 33
        self.stone[self.label_34] = 34
        self.stone[self.label_35] = 35
        self.stone[self.label_36] = 36
        self.stone[self.label_37] = 37
        self.stone[self.label_38] = 38
        self.stone[self.label_39] = 39
        self.stone[self.label_40] = 40
        self.stone[self.label_41] = 41
        self.stone[self.label_42] = 42
        self.stone[self.label_43] = 43
        self.stone[self.label_44] = 44
        self.stone[self.label_45] = 45
        self.stone[self.label_46] = 46
        self.stone[self.label_47] = 47
        self.stone[self.label_48] = 48
        self.stone[self.label_49] = 49
        self.stone[self.label_50] = 50
        self.stone[self.label_51] = 51
        self.stone[self.label_52] = 52
        self.stone[self.label_53] = 53
        self.stone[self.label_54] = 54
        self.stone[self.label_55] = 55
        self.stone[self.label_56] = 56
        self.stone[self.label_57] = 57
        self.stone[self.label_58] = 58
        self.stone[self.label_59] = 59
        self.stone[self.label_60] = 60
        self.stone[self.label_61] = 61
        self.stone[self.label_62] = 62
        self.stone[self.label_63] = 63
        self.stone[self.label_64] = 64
        self.stone[self.label_65] = 65
        self.stone[self.label_66] = 66
        self.stone[self.label_67] = 67
        self.stone[self.label_68] = 68
        self.stone[self.label_69] = 69
        self.stone[self.label_70] = 70
        self.stone[self.label_71] = 71
        self.stone[self.label_72] = 72
        self.stone[self.label_73] = 73
        self.stone[self.label_74] = 74
        self.stone[self.label_75] = 75
        self.stone[self.label_76] = 76
        self.stone[self.label_77] = 77
        self.stone[self.label_78] = 78
        self.stone[self.label_79] = 79
        self.stone[self.label_80] = 80
        self.stone[self.label_81] = 81
        self.label_82 = QtWidgets.QLabel(self.centralwidget)
        self.label_82.setGeometry(QtCore.QRect(660, 10, 91, 28))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.label_82.setFont(font)
        self.label_82.setObjectName("label_82")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(600, 60, 75, 24))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.start_game)
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(690, 60, 75, 24))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_2.clicked.connect(self.stop_game)
        self.pushButton_3 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_3.setGeometry(QtCore.QRect(690, 100, 75, 24))
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_3.clicked.connect(self.resign)
        self.pushButton_4 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_4.setGeometry(QtCore.QRect(600, 100, 75, 24))
        self.pushButton_4.setObjectName("pushButton_4")
        self.pushButton_4.clicked.connect(self.pass_game)
        self.pushButton_5 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_5.setGeometry(QtCore.QRect(600, 140, 165, 24))
        self.pushButton_5.setObjectName("pushButton_5")
        self.pushButton_5.clicked.connect(self.play_against_computer)
        self.pushButton_6 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_6.setGeometry(QtCore.QRect(600, 170, 165, 24))
        self.pushButton_6.setObjectName("pushButton_6")
        self.pushButton_6.clicked.connect(self.start_from_this_position)
        self.pushButton_7 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_7.setGeometry(QtCore.QRect(600, 250, 165, 24))
        self.pushButton_7.setObjectName("pushButton_7")
        self.pushButton_7.clicked.connect(self.clear_board)
        self.pushButton_8 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_8.setGeometry(QtCore.QRect(600, 200, 165, 40))
        self.pushButton_8.setObjectName("pushButton_7")
        self.pushButton_8.clicked.connect(self.play_against_computer_from_this_position)

        self.textEdit = QtWidgets.QTextEdit(self.centralwidget)
        self.textEdit.setGeometry(QtCore.QRect(590, 280, 191, 141))
        self.textEdit.setObjectName("textEdit")
        self.label_83 = QtWidgets.QLabel(self.centralwidget)
        self.label_83.setGeometry(QtCore.QRect(20, 570, 191, 31))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.label_83.setFont(font)
        self.label_83.setObjectName("label_83")
        self.textEdit_2 = QtWidgets.QTextEdit(self.centralwidget)
        self.textEdit_2.setGeometry(QtCore.QRect(590, 430, 191, 160))
        self.textEdit_2.setObjectName("textEdit_2")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 799, 22))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Game go"))
        MainWindow.setStyleSheet("background-color: #1A2699")
        self.label_82.setText(_translate("MainWindow", "Go"))
        self.pushButton.setText(_translate("MainWindow", "Start game"))
        self.pushButton.setStyleSheet("background: #FCF9F9")
        self.pushButton_2.setText(_translate("MainWindow", "Stop game"))
        self.pushButton_2.setStyleSheet("background: #FCF9F9")
        self.pushButton_3.setText(_translate("MainWindow", "Resign"))
        self.pushButton_3.setStyleSheet("background: #FCF9F9")
        self.pushButton_4.setText(_translate("MainWindow", "Pass"))
        self.pushButton_4.setStyleSheet("background: #FCF9F9")
        self.pushButton_5.setText(_translate("MainWindow", "Play against computer"))
        self.pushButton_5.setStyleSheet("background: #FCF9F9")
        self.pushButton_6.setText(_translate("MainWindow", "Start from this position"))
        self.pushButton_6.setStyleSheet("background: #FCF9F9")
        self.pushButton_7.setText(_translate("MainWindow", "Clear board"))
        self.pushButton_7.setStyleSheet("background: #FCF9F9")
        self.pushButton_8.setText(_translate("MainWindow",
                                             "Start from this position\nagainst computer"))
        self.button_end.setText(_translate("MainWindow",
                                             "Disconnect from server"))
        self.pushButton_8.setStyleSheet("background: #FCF9F9")
        self.textEdit.setStyleSheet("background: #FCF9F9")
        self.textEdit_2.setStyleSheet("background: #FCF9F9")
        self.label_83.setText(_translate("MainWindow", ""))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
