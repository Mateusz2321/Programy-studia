import copy
import time
import random
import json
import ast
from flask import Flask, request, Response, make_response
import pickle
import os
game_id = 1
engine_collection={}
operating_mode=2

def check_id(id):
    if operating_mode == 1:
        for a in engine_collection.keys():
            if a == id:
                return True
        return False
    elif operating_mode == 2:
        lst = os.listdir('./')
        for file in lst:
            temp = file
            if len(temp) > 7:
                if '.pickle' in temp:
                    temp = temp[: -7]
                    number = int(temp)
                    if number == id:
                        return True
        return False

app = Flask(__name__)

def reload_server():
    if operating_mode == 1:
        list=os.listdir('./')
        for file in list:
            temp=file
            if len(temp) > 7:
                if '.pickle' in temp:
                    temp = temp [: -7]
                    number=int(temp)
                    with open (file, 'rb') as one_game:
                        data= pickle.load(one_game)
                    engine_collection[number] = data
                    os.unlink('./'+ file)


    elif operating_mode == 2:
        remove = [k for k in engine_collection.keys()]
        for id in remove:
            file_name = str(id)+".pickle"
            game=engine_collection.get(id)
            with open(file_name, 'wb') as one_game:
                pickle.dump(game,one_game,pickle.HIGHEST_PROTOCOL)
            engine_collection.pop(id)
def save_to_file(en,id):
    file_name = str(id) + ".pickle"
    with open(file_name, 'wb') as one_game:
        pickle.dump(en, one_game, pickle.HIGHEST_PROTOCOL)
def get_class(id: int):
    if operating_mode == 1:
        return engine_collection.get(id)
    elif operating_mode == 2:
        lst = os.listdir('./')
        for file in lst:
            temp = file
            if len(temp) > 7:
                if '.pickle' in temp:
                    temp = temp[: -7]
                    number = int(temp)
                    if number == id:
                        with open(file, 'rb') as one_game:
                            data = pickle.load(one_game)
                        return data
        return None
@app.route("/<int:mode_value>/mode")
def set_mode(mode_value):
    global operating_mode
    if 1 <= mode_value <= 2:
        operating_mode = mode_value
        reload_server()
        return make_response("OK!", 204)
    return make_response("Podano niepoprawna wartosc!", 404)
@app.route("/add")
def add_game():
    global game_id
    if game_id<100000000:
        en=Engine()
        if operating_mode == 1:
            engine_collection[game_id] = en
        elif operating_mode == 2:
            file_name = str(game_id) + ".pickle"
            with open(file_name, 'wb') as one_game:
                pickle.dump(en, one_game, pickle.HIGHEST_PROTOCOL)
        game_id+=1
        answer=str(game_id-1)
        return answer
    return make_response("Server limit!", 404)
@app.route("/<int:id>/delete")
def delete(id):
    if operating_mode == 1:
        for a in engine_collection.keys():
            if a==id:
                engine_collection.pop(a)
                return make_response(f"Gra nr {id} została usunięta.", 204)
        return make_response("Nie istnieje gra o podanym id!", 404)
    elif operating_mode == 2:
        list = os.listdir('./')
        deleted = False
        for file in list:
            temp = file
            if len(temp) > 7:
                if '.pickle' in temp:
                    temp = temp[: -7]
                    number = int(temp)
                    if number == id:
                        os.unlink('./' + file)
                        deleted = True
                        break
        if deleted is True:
            return make_response(f"Gra nr {id} została usunięta.", 204)
        return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/move")
def flask_get_move(id):
    if check_id(id) is True:
        en= get_class(id)
        temp = en.get_move()
        if operating_mode == 2:
            save_to_file(en, id)
        return temp
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/black_result")
def flask_get_black_result(id):
    if check_id(id) is True:
        en= get_class(id)
        temp = en.get_black_result()
        if operating_mode == 2:
            save_to_file(en, id)
        return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/white_result")
def flask_get_white_result(id):
    if check_id(id) is True:
        en= get_class(id)
        temp = en.get_white_result()
        if operating_mode == 2:
            save_to_file(en, id)
        return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/pass_game")
def flask_pass_game(id):
    if check_id(id) is True:
        en= get_class(id)
        temp = en.pass_game()
        if operating_mode == 2:
            save_to_file(en, id)
        return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/start_game")
def flask_start_game(id):
    if check_id(id) is True:
        en = get_class(id)
        temp=en.start_game()
        if operating_mode == 2:
            save_to_file(en, id)
        return Response(json.dumps(temp), mimetype='application/json')
    return make_response("Nie istnieje gra o podanym id!", 404)

@app.route("/<int:id>/stop_game")
def flask_stop_game(id):
    if check_id(id) is True:
        en= get_class(id)
        en.stop_game()
        if operating_mode == 2:
            save_to_file(en, id)
        my_str="Gra nr "+str(id)+" została zakończona."
        return make_response(my_str, 204)
    return make_response("Nie istnieje gra o podanym id!", 404)

@app.route("/<int:id>/put_stone/<color>/<int:position>/")
def flask_put_a_stone(id,color,position):
    if check_id(id) is True:
        en= get_class(id)
        temp = en.put_a_stone(color,position)
        if operating_mode == 2:
            save_to_file(en, id)
        return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)

@app.route("/<int:id>/message")
def flask_get_message(id):
    if check_id(id) is True:
        en = get_class(id)
        temp = en.get_message()
        if operating_mode == 2:
            save_to_file(en, id)
        return temp
    return make_response("Nie istnieje gra o podanym id!", 404)

@app.route("/<int:id>/start_status")
def flask_get_start_status(id):
    if check_id(id) is True:
        en = get_class(id)
        temp = en.get_start_status()
        if operating_mode == 2:
            save_to_file(en, id)
        return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)

@app.route("/<int:id>/start_computer_status")
def flask_get_start_against_computer_status(id):
    if check_id(id) is True:
        en = get_class(id)
        temp = en.get_start_against_computer_status()
        if operating_mode == 2:
            save_to_file(en, id)
        return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)

@app.route("/<int:id>/start_position", methods=["POST"])
def flask_start_from_this_position(id):
    if check_id(id) is True:
        if request.is_json:
            json_data=request.get_json()
            layout_list = ast.literal_eval(json_data)
            layout_list = [n.strip() for n in layout_list]
            if len(layout_list)<81:
                return make_response("Lista parametrow ma nieodpowiednia dlugosc!", 404)
            lst=[]
            for i in range(9):
                lst2=[]
                for j in range(9):
                    lst2.append(layout_list[i*9+j])
                lst.append(lst2)
                en = get_class(id)
                temp = en.start_from_this_position(lst)
                if operating_mode == 2:
                    save_to_file(en, id)
            return str(temp)
        return make_response("Nie wprowadzono danych w formacie json!", 404)
    return make_response("Nie istnieje gra o podanym id!", 404)

@app.route("/<int:id>/start_computer_position",methods=["POST"])
def flask_start_against_computer_from_this_position(id):
    if check_id(id) is True:
        if request.is_json:
            json_data = request.get_json()
            layout_list = ast.literal_eval(json_data)
            layout_list = [n.strip() for n in layout_list]
            if len(layout_list)<81:
                return make_response("Lista parametrow ma nieodpowiednia dlugosc!", 404)
            lst = []
            for i in range(9):
                lst2 = []
                for j in range(9):
                    lst2.append(layout_list[i * 9 + j])
                lst.append(lst2)
            en = get_class(id)
            temp = en.start_game_against_computer_from_this_position(lst)
            if operating_mode == 2:
                save_to_file(en, id)
            return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/clear_board")
def flask_clear_board(id):
    if check_id(id) is True:
        en = get_class(id)
        temp = en.clear_board()
        if operating_mode == 2:
            save_to_file(en, id)
        return Response(json.dumps(temp), mimetype='application/json')
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/status")
def flask_get_status(id):
    if check_id(id) is True:
        en = get_class(id)
        temp = en.get_status()
        if operating_mode == 2:
            save_to_file(en, id)
        return str(temp)
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/start_computer")
def flask_start_game_against_computer(id):
    if check_id(id) is True:
        en = get_class(id)
        temp = en.start_game_against_computer()
        if operating_mode == 2:
            save_to_file(en, id)
        return Response(json.dumps(temp), mimetype='application/json')
    return make_response("Nie istnieje gra o podanym id!", 404)
@app.route("/<int:id>/stone_layout")
def flask_get_stone_layout(id):
    if check_id(id) is True:
        en = get_class(id)
        temp = en.get_stone_layout()
        if operating_mode == 2:
            save_to_file(en, id)
        return Response(json.dumps(temp), mimetype='application/json')
    return make_response("Nie istnieje gra o podanym id!", 404)

class Engine(object):
    def __init__(self):
        self.color="black"
        self.initialize=False
        self.start=False
        self.start_against_computer=False
        self.position_table=[[1] * 9 for _ in range(9)]
        self.temp_position=[[1] * 9 for _ in range(9)]
        self.black_result=0
        self.white_result=7.5
        self.set_start_layout()
        self.position_before_white = [[1] * 9 for _ in range(9)]
        self.position_before_white = copy.deepcopy(self.position_table)
        self.position_before_black = [[1] * 9 for _ in range(9)]
        self.position_before_black = copy.deepcopy(self.position_table)
        self.positions_before = [[1] * 9 for _ in range(9)]
        self.message=""
        self.friends_positions = []
        self.opponent_positions = []
        self.visited_positions = []
        self.computer_list = []
        self.passed=0
        for i in range(9):
            for j in range(9):
                l=[i,j]
                self.computer_list.append(l)

    def get_move(self):
        return self.color

    def get_black_result(self):
        return self.black_result

    def get_white_result(self):
        return self.white_result

    def pass_game(self):
        if self.get_status() is True:
            self.passed = self.passed + 1
            if self.passed==2:
                self.stop_game()
                self.message="The game ended with consent of two players"
                return True
            self.message="First gamer passed"
            return False
        self.message = "You are not during any game"
        return False

    def start_game(self):
        if self.get_status() is False:
            self.white_result=7.5
            self.black_result=0
            self.start=True
            self.set_start_layout()
            self.color='black'
            self.white_result=7.5
            return self.get_stone_layout()
        return None

    def stop_game(self):
        self.start=False
        self.start_against_computer = False

    def put_a_stone(self,color:str,position:int):
        self.passed=0
        temp_pos = position - 1
        x = temp_pos % 9
        y = int(temp_pos / 9)
        b=0
        c=0
        if self.get_status() is False:
            self.position_table[y][x]=color
            return True
        elif self.get_start_status() is True:
            if self.position_table[y][x] == 'black' or self.position_table[y][x] == 'white':
                self.message="You cannot put a stone on taken seat!"
                return False
            else:
                self.temp_position=copy.deepcopy(self.position_table)
                self.temp_position[y][x] = self.color

                if self.check_kill_possibility(y,x) is True:
                    if self.check_kill_opponent_possibility(y,x) is True:
                        for a in self.friends_positions:
                            b = a[0]
                            c = a[1]
                            self.temp_position[b][c] = 'gray'
                        if self.color == 'black':
                            if Engine.compare_states(self.temp_position,
                                                     self.position_before_black) is True:
                                self.message = "You cannot do this move because of ko rule!"
                                return False
                        else:
                            if Engine.compare_states(self.temp_position,
                                                     self.position_before_white) is True:
                                self.message = "You cannot do this move because of ko rule!"
                                return False

                        if self.color == 'black':
                            self.black_result = self.black_result + len(self.friends_positions)
                        else:
                            self.white_result = self.white_result\
                                                + len(self.friends_positions)
                    else:
                        self.message = "You cannot do this move!" \
                                       " You would be surrounded by opponent"
                        return False

                else:
                    if self.check_kill_opponent_possibility(y,x) is True:
                        for a in self.friends_positions:
                            b=a[0]
                            c=a[1]
                            self.temp_position[b][c]='gray'
                        if self.color=='black':
                            self.black_result=self.black_result+len(self.friends_positions)
                        else:
                            self.white_result=self.white_result+len(self.friends_positions)
                self.position_table = copy.deepcopy(self.temp_position)
                if self.color == 'black':
                    self.position_before_black = copy.deepcopy(self.position_table)
                    self.color = 'white'
                else:
                    self.position_before_white = copy.deepcopy(self.position_table)
                    self.color = 'black'
                self.message=''
                return True

        elif self.get_start_against_computer_status() is True:
            if self.position_table[y][x] == 'black' or self.position_table[y][x] == 'white':
                self.message="You cannot put a stone on taken seat!"
                return False
            else:
                self.temp_position=copy.deepcopy(self.position_table)
                self.temp_position[y][x] = self.color

                if self.check_kill_possibility(y,x) is True:
                    if self.check_kill_opponent_possibility(y,x) is True:
                        for a in self.friends_positions:
                            b = a[0]
                            c = a[1]
                            self.temp_position[b][c] = 'gray'
                        if self.color == 'black':
                            if Engine.compare_states(self.temp_position,
                                                     self.position_before_black) is True:
                                self.message = "You cannot do this move because of ko rule!"
                                return False
                        else:
                            if Engine.compare_states(self.temp_position,
                                                     self.position_before_white) is True:
                                self.message = "You cannot do this move because of ko rule!"
                                return False

                        if self.color == 'black':
                            self.black_result = self.black_result\
                                                + len(self.friends_positions)
                        else:
                            self.white_result = self.white_result\
                                                + len(self.friends_positions)
                    else:
                        self.message = "You cannot do this move!" \
                                       " You would be surrounded by opponent"
                        return False

                else:
                    if self.check_kill_opponent_possibility(y,x) is True:
                        for a in self.friends_positions:
                            b=a[0]
                            c=a[1]
                            self.temp_position[b][c]='gray'
                        if self.color=='black':
                            self.black_result=self.black_result+len(self.friends_positions)
                        else:
                            self.white_result=self.white_result+len(self.friends_positions)
                self.position_table = copy.deepcopy(self.temp_position)
                self.position_before_black = copy.deepcopy(self.position_table)
                self.color = 'white'
                self.message=''
                return self.computer_move()


    def get_message(self):
        return self.message

    def get_start_status(self):
        return self.start

    def get_start_against_computer_status(self):
        return self.start_against_computer

    def start_from_this_position(self,list: list):
        if self.get_status() is False:
            self.temp_position=copy.deepcopy(list)
            if self.check_position_correctness() is False:
                self.message="Position incorrect! You cannot start game!"
                return False
            else:
                self.message=""
            self.white_result = 7.5
            self.black_result = 0
            self.start = True
            self.color = 'black'
            return True

        self.message = "You are during another game!"
        return False

    def start_game_against_computer_from_this_position(self,list:list):
        if self.get_status() is False:
            self.temp_position = copy.deepcopy(list)
            if self.check_position_correctness() is False:
                self.message = "Position incorrect! You cannot start game!"
                return False
            else:
                self.message = ""
            self.white_result = 7.5
            self.black_result = 0
            self.start_against_computer = True
            self.color = 'black'
            return True

        self.message = "You are during another game!"
        return False

    def clear_board(self):
        if self.get_status() is False:
            self.set_start_layout()
        return self.get_stone_layout()

    def get_status(self):
        if self.start or self.start_against_computer:
            return True
        return False

    def start_game_against_computer(self):
        if self.get_status() is False:
            self.white_result = 7.5
            self.black_result = 0
            self.start_against_computer = True
            self.set_start_layout()
            self.color = 'black'
            return self.get_stone_layout()
        return None

    def get_stone_layout(self):
        return self.make_array_single_dimension(self.position_table)

    @staticmethod
    def compare_states(l1 : list,l2 : list):
        for i in range(9):
            for j in range(9):
                if l1[i][j] != l2[i][j]:
                    return False
        return True

    def contains_friends(self,list:list):
        if len(self.friends_positions)==0:
            return False
        for a in self.friends_positions:
            if a[0]==list[0] and a[1]==list[1]:
                return True
        return False

    def contains_opponent(self, list: list):
        if len(self.opponent_positions)==0:
            return False
        for a in self.opponent_positions:
            if a[0] == list[0] and a[1] == list[1]:
                return True
        return False
    def contains_visited(self, list: list):
        if len(self.visited_positions)==0:
            return False
        for a in self.visited_positions:
            if a[0] == list[0] and a[1] == list[1]:
                return True
        return False


    def check_kill_possibility(self,first:int,second:int):
        self.friends_positions.clear()
        self.opponent_positions.clear()
        self.visited_positions.clear()
        return self.check_position_neighbours(first,second,self.color)

    def check_kill_opponent_possibility(self, first: int, second: int):
        killed=False
        killed_now=False
        self.friends_positions.clear()
        self.opponent_positions.clear()
        self.visited_positions.clear()
        c=None
        if self.color == 'black':
            c = 'white'
        else:
            c = 'black'
        self.positions_before=copy.deepcopy(self.friends_positions)
        if first>0:
            if self.temp_position[first-1][second]==c:
                if self.check_position_neighbours(first-1, second,c) is True:
                    killed=True
                    killed_now=True
        if killed_now is False:
            self.friends_positions=copy.deepcopy(self.positions_before)
        else:
            self.positions_before = copy.deepcopy(self.friends_positions)
        self.opponent_positions.clear()
        self.visited_positions.clear()
        killed_now=False
        if first<8:
            if self.temp_position[first + 1][second] == c:
                if self.check_position_neighbours(first+1, second,c) is True:
                    killed=True
                    killed_now=True
        if killed_now is False:
            self.friends_positions=copy.deepcopy(self.positions_before)
        else:
            self.positions_before = copy.deepcopy(self.friends_positions)
        self.opponent_positions.clear()
        self.visited_positions.clear()
        killed_now=False
        if second>0:
            if self.temp_position[first][second-1] == c:
                if self.check_position_neighbours(first, second-1,c) is True:
                    killed=True
                    killed_now=True
        if killed_now is False:
            self.friends_positions=copy.deepcopy(self.positions_before)
        else:
            self.positions_before = copy.deepcopy(self.friends_positions)
        self.opponent_positions.clear()
        self.visited_positions.clear()
        killed_now=False
        if second<8:
            if self.temp_position[first][second+1] == c:
                if self.check_position_neighbours(first, second+1,c) is True:
                    killed=True
                    killed_now=True
        if killed_now is False:
            self.friends_positions=copy.deepcopy(self.positions_before)
        else:
            self.positions_before = copy.deepcopy(self.friends_positions)
        return killed

    def check_position_neighbours(self,first:int,second:int,c:str):
        temp = [first, second]
        if self.contains_visited(temp)  is True:
            return True
        self.visited_positions.append(temp)
        if c == 'black':
            if self.temp_position[first][second]=='black':
                if self.contains_friends(temp) is False:
                    self.friends_positions.append(temp)
            elif self.temp_position[first][second]=='white':
                if self.contains_opponent(temp) is False:
                    self.opponent_positions.append(temp)
                return True
            else:
                return False
        elif c == 'white':
            if self.temp_position[first][second] == 'white':
                if self.contains_friends(temp) is False:
                    self.friends_positions.append(temp)
            elif self.temp_position[first][second] == 'black':
                if self.contains_opponent(temp) is False:
                    self.opponent_positions.append(temp)
                return True
            else:
                return False
        if first>0:
            if self.check_position_neighbours(first-1, second,c) is False:
                return False
        if first<8:
            if self.check_position_neighbours(first+1, second,c) is False:
                return False
        if second>0:
            if self.check_position_neighbours(first, second-1,c) is False:
                return False
        if second<8:
            if self.check_position_neighbours(first, second+1,c) is False:
                return False
        return True

    def computer_move(self):
        time.sleep(0.05)
        x = None
        y = None
        z = None
        for i in range(100):
            x = random.randint(0, 80)
            y = random.randint(0, 80)
            z = self.computer_list[x]
            self.computer_list[x] = self.computer_list[y]
            self.computer_list[y] = z
        for a in range(81):
            z = self.computer_list[a]
            y = z[0]
            x = z[1]
            if self.position_table[y][x] != 'black' and self.position_table[y][x] != 'white':

                self.temp_position = copy.deepcopy(self.position_table)
                self.temp_position[y][x] = 'white'

                if self.check_kill_possibility(y, x) is True:
                    if self.check_kill_opponent_possibility(y, x) is True:
                        for a in self.friends_positions:
                            b = a[0]
                            c = a[1]
                            self.temp_position[b][c] = 'gray'

                            if Engine.compare_states(self.temp_position,
                                                     self.position_before_white)  is True:
                                self.message = "You cannot do this move because of ko rule!"
                                continue

                            self.white_result = self.white_result\
                                                + len(self.friends_positions)
                    else:
                        continue
                else:
                    if self.check_kill_opponent_possibility(y, x) is True:
                        for a in self.friends_positions:
                            b = a[0]
                            c = a[1]
                            self.temp_position[b][c] = 'gray'
                        if self.color == 'black':
                            self.black_result = self.black_result\
                                                + len(self.friends_positions)
                        else:
                            self.white_result = self.white_result\
                                                + len(self.friends_positions)
                self.position_table = copy.deepcopy(self.temp_position)
                if self.color == 'black':
                    self.position_before_black = copy.deepcopy(self.position_table)
                    self.color = 'white'
                else:
                    self.position_before_white = copy.deepcopy(self.position_table)
                    self.color = 'black'
                self.message = ''
                return True
        self.stop_game()
        return False

    def check_position_correctness(self):
        for x in range(9):
            for y in range(9):
                if self.temp_position[x][y]=='black' or self.temp_position[x][y]=='white':
                    self.friends_positions.clear()
                    self.opponent_positions.clear()
                    self.visited_positions.clear()
                    if self.check_position_neighbours(x,y,self.temp_position[x][y]) is True:
                        return False
        return True


    def set_start_layout(self):
        for i in range(9):
            for j in range(9):
                self.position_table[i][j] = 'gray'

    @staticmethod
    def make_array_single_dimension(l):
        l2 = []
        for x in l:
            if type(x).__name__ == "list":
                l2 += Engine.make_array_single_dimension(x)
            else:
                l2.append(x)
        return l2

if __name__ == "__main__":
    #server mode
    operating_mode=2
    ############
    if operating_mode == 1:
        lst = os.listdir('./')
        for file in lst:
            temp = file
            if len(temp) > 7:
                if '.pickle' in temp:
                    os.unlink('./' + file)
    app.debug=True
    app.run()