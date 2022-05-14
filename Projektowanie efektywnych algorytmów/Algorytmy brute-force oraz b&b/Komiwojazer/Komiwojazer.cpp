#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<queue>
#include<vector>


using namespace std;
string file_name;
string line;
fstream file;
string number_of_vertices;
int nb_of_vertices;
string result_file_name;
string number;
string number2;
int** wages_array;
unsigned int line_length;
int start = -1;
bool* visited;
int shortest_path = 2147483647;
double algorithm_time;
clock_t start_time, stop_time;
int choice = 0;
int optimal = 0;
bool zero;
const int max_int = 2147483647;
int level = 1;
float PRD;
int* path;
int* temp_path;
bool shorter_path;
/*
Struktura przechowująca informacje o pojedynczym wierzchołku grafu. Jest używana w
metodzie branch and bound.
*/
typedef struct Node
{
	int cost;
	int level;
	int number;
	int** array;
	bool* list;
	vector<int> ancestors;
};
/*
Funkcja służaca do porównywania wierzchołków dodawanych do kelejki priorytetowej.
*/
struct compare_nodes
{
	bool operator()(const Node* node1, const Node* node2) {
		if (node1->cost > node2->cost) return true;
		if (node1->cost < node2->cost) return false;
		if (node1->level < node2->level) return true;
		if (node1->level > node2->level) return false;
		return false;
	}
};
priority_queue<Node*, vector<Node*>, compare_nodes> costs_queue;	//Kolejka priorytetowa przechowująca wierzchołki drzewa z biblioteki STL(złożoność O(log n)-kopiec)
Node* root;				//Wskaźnik do korzenia drzewa.
Node* temporary_node;	

vector<Node*> vec;		//Wektor przechowujący wierzchołki drzewa
/*
Funkcja redukuje macierz sąsiedztwa dla korzenia drzewa w celu
wyliczenia dolnego ograniczenia dla tego wierzchołka.
*/
int reduce_root_matrix(int** wages) {
	int reduced_cost = 0;
	int minimum;
	int temp = 0;
	for (int i = 0; i < nb_of_vertices; i++) {
		minimum = max_int;
		zero = false;
		for (int j = 0; j < nb_of_vertices; j++) {
			if (i == j) continue;
			temp = wages[i][j];
			if (temp < minimum) {
				minimum = temp;
			}
			if (wages[i][j] == 0) {
				zero = true;
				break;
			}
		}
		if (zero == false) {
			reduced_cost += minimum;
			for (int j = 0; j < nb_of_vertices; j++) {
				if (i == j)continue;
				wages[i][j] -= minimum;
			}
		}
	}
	for (int i = 0; i < nb_of_vertices; i++) {
		zero = false;
		minimum = max_int;
		for (int j = 0; j < nb_of_vertices; j++) {
			if (i == j) continue;
			temp = wages[j][i];
			if (temp < minimum) {
				minimum = temp;
			}
			if (wages[j][i] == 0) {
				zero = true;
				break;
			}
		}
		if (zero == false) {
			reduced_cost += minimum;
			for (int j = 0; j < nb_of_vertices; j++) {
				if (i == j) continue;
				wages[j][i] -= minimum;
			}
		}
	}
	return reduced_cost;

}
/*
Funkcja pomocnicza, zajmująca się kopiowaniem danych z wierzchołka node1 do wierzchołka node2.
*/
void copy_node1_node2(Node* node1, Node* node2) {

	for (int i = 0; i < nb_of_vertices; i++) {

		for (int j = 0; j < nb_of_vertices; j++) {
			node2->array[i][j] = node1->array[i][j];

		}
		node2->list[i] = node1->list[i];
	}
}
/*
Funkcja redukuje macierz sąsiedztwa dla dowolnego wierzchołka drzewa innego niż korzeń w celu
wyliczenia dolnego ograniczenia dla tego wierzchołka.
*/
int reduce_matrix(Node* node1, Node* node2) {
	int r_cost = 0;
	int minimum = max_int;
	int temp = 0;
	bool change;


	for (int i = 0; i < nb_of_vertices; i++) {
		if (node1->list[i] == true) node2->array[node2->number][i] = max_int;
		node2->array[node1->number][i] = max_int;
		node2->array[i][node2->number] = max_int;
	}

	for (int i = 0; i < nb_of_vertices; i++) {
		minimum = max_int;
		zero = false;
		change = false;
		for (int j = 0; j < nb_of_vertices; j++) {
			if (i == j) continue;
			temp = node2->array[i][j];
			if (temp == max_int) continue;

			if (temp < minimum) {
				change = true;
				minimum = temp;
			}
			if (temp == 0) {
				zero = true;
				break;
			}
		}
		if (zero == false && change == true) {
			
			r_cost += minimum;
			for (int j = 0; j < nb_of_vertices; j++) {
				if (node2->array[i][j] != max_int)
					node2->array[i][j] -= minimum;
			}
		}

	}

	for (int i = 0; i < nb_of_vertices; i++) {
		minimum = max_int;
		zero = false;
		change = false;
		for (int j = 0; j < nb_of_vertices; j++) {
			if (i == j) continue;
			temp = node2->array[j][i];
			if (temp == max_int) continue;

			if (temp < minimum) {
				change = true;
				minimum = temp;
			}
			if (temp == 0) {
				zero = true;
				break;
			}
		}
		if (zero == false && change == true) {
			r_cost += minimum;
			for (int j = 0; j < nb_of_vertices; j++) {
				if (node2->array[j][i] != max_int)
					node2->array[j][i] -= minimum;
			}
		}
	}
	return r_cost;
}

/*
Funkcja alokuje potrzebną pamięć na wierzchołek.
*/
void alocate_array_and_list(Node* n) {
	n->list = new bool[nb_of_vertices];
	n->array = new int* [nb_of_vertices];
	for (int i = 0; i < nb_of_vertices; i++) {
		n->array[i] = new int[nb_of_vertices];
	}

}
/*
Funkcja zwalnia pamięć przeznaczoną na wierzchołek, który nie jest już potrzebny.
*/
void dealocate_node(Node* n) {
	//n->ancestors.clear();
	delete[] n->list;

	for (int i = 0; i < nb_of_vertices; i++) {
		delete[] n->array[i];
	}
	delete[] n->array;
	delete n;
}
/*
Funkcja oblicza dolne ograniczenia dla wszystkich potomków podanego
wierzchołka i dodaje wierzchołki do kolejki priorytetowej.
*/
void check_children(Node* node1) {
	int sum;
	int node1_number = node1->number;
	for (int i = 0; i < nb_of_vertices; i++) { //O(n)
		if (node1->list[i] == true) continue;
		Node* node2 = new Node;
		alocate_array_and_list(node2);
		copy_node1_node2(node1, node2);
		node2->number = i;
		for (vector<int>::iterator it = node1->ancestors.begin(); it!= node1->ancestors.end(); ++it) { 
			node2->ancestors.push_back(*it);							
		}
		node2->ancestors.push_back(node1->number);                                                         
		sum = reduce_matrix(node1, node2);			//O(n^2)
		sum += node1->array[node1_number][i];
		sum += node1->cost;
		node2->cost = sum;
		node2->list[node2->number] = true;
		node2->level = node1->level + 1;
		costs_queue.push(node2);
	}

}
/*
Funkcja rekurencyjna dla metody branch and bound.
*/
void execute_bb(Node* node1) {
	check_children(node1);	//O(n^3)
	dealocate_node(node1);
	if (!costs_queue.empty()) {
		temporary_node = costs_queue.top();
		costs_queue.pop();
		if (temporary_node->level == nb_of_vertices - 1) {
			if (temporary_node->cost < shortest_path) {
				shortest_path = temporary_node->cost;
				for (int i = 1; i < nb_of_vertices-1; i++) {
					path[i] = temporary_node->ancestors[i];
				}
				path[nb_of_vertices - 1] = temporary_node->number;
			}
			while (!costs_queue.empty()) {
				if (costs_queue.top()->cost <= shortest_path) {
					vec.push_back(costs_queue.top());
					costs_queue.pop();
				}
				else break;
			}
			while (!costs_queue.empty()) {
				temporary_node = costs_queue.top();
				costs_queue.pop();
				dealocate_node(temporary_node);
			}
			while (!vec.empty()) {
				temporary_node = vec.back();
				vec.pop_back();
				costs_queue.push(temporary_node);
			}
			if (!costs_queue.empty()) {
				temporary_node = costs_queue.top();
				costs_queue.pop();
				execute_bb(temporary_node);
			}
		}
		else
			execute_bb(temporary_node);
	}
}
/*
Funkcja zajmuje się obliczaniem najkrótszej ścieżki dla problemu Komiwojażera przy pomocy metody branch and bound.
*/
void find_shortest_cycle_branch_and_bound() {
	temporary_node = new Node;
	root = new Node;
	alocate_array_and_list(root);
	root->array = wages_array;
	for (int i = 0; i < nb_of_vertices; i++) {
		root->array[i][i] = max_int;
	}
	root->cost = reduce_root_matrix(root->array);
	root->number = start;
	root->list = new bool[nb_of_vertices];
	for (int i = 0; i < nb_of_vertices; i++) {
		root->list[i] = false;
	}
	root->list[start] = true;
	root->level = 0;
	execute_bb(root);
	temporary_node = nullptr;
	delete temporary_node;

}
/*
Funkcja zajmuje się obliczaniem najkrótszej ścieżki dla problemu Komiwojażera przy pomocy metody brute-force.
*/
void find_shortest_cycle_brute_force(int vertice, int step, int length) {
	int actual_vertice = vertice;
	int actual_step = step;
	temp_path[actual_step - 1] = actual_vertice;
	int actual_length = length;
	if (actual_step == nb_of_vertices) {
		actual_length += wages_array[actual_vertice][start];
		if (actual_length < shortest_path) {
			shortest_path = actual_length;
			for (int i = 1; i < nb_of_vertices; i++) {
				path[i] = temp_path[i];
			}
		}
		else shorter_path = false;
		return;
	}
	for (int j = 0; j < nb_of_vertices; j++) {
		if (j == actual_vertice || j == start) continue;
		if (visited[j] == true) continue;
		else visited[j] = true;
		find_shortest_cycle_brute_force(j, actual_step + 1, actual_length + wages_array[actual_vertice][j]);
		visited[j] = false;
	}
}
/*
Funkcja wczytuje z wybranego przez użytkownika pliku
wszelkie informacje o ilości wierzchołków oraz długości śćieżek pomiędzy nimi.
DAne te są zapisywane w tablicy dwuwymiarowej.
*/
void read_from_file() {
	file.open(file_name, ios::in);
	if (!file.good()) {
		cout << "Nie udalo sie otworzyc pliku!" << endl;
		cout << "Wcisnij ENTER, aby zakonczyc" << endl;
		getchar();
		getchar();
		exit(0);
	}

	result_file_name = file_name;
	while (result_file_name.at(result_file_name.length() - 1) != '.')
		result_file_name.pop_back();
	result_file_name.back() = '-';
	result_file_name.append("results.csv");
	getline(file, line);
	getline(file, number_of_vertices);
	nb_of_vertices = atoi(number_of_vertices.c_str());
	cout << "Podaj numer wierzcholka, od ktorego chcesz zaczac algorytm (numerowane od 0, max " << nb_of_vertices - 1 << "): ";
	cin >> start;
	//start = 0;
	if (start < 0 || start >= nb_of_vertices) {
		cout << "Wierzcholek o podanym indeksie nie istnieje!" << endl;
		cout << "Wcisnij ENTER, aby zakonczyc" << endl;
		getchar();
		getchar();
		exit(0);
	}
	visited = new bool[nb_of_vertices];
	wages_array = new int* [nb_of_vertices];
	for (int i = 0; i < nb_of_vertices; i++) {
		wages_array[i] = new int[nb_of_vertices];
	}

	for (int i = 0; i < nb_of_vertices; i++) {
		getline(file, line);
		line_length = line.length();
		int k = 0;
		for (int j = 0; j < nb_of_vertices; j++) {

			number.clear();
			while (k < line_length) {
				if ((line.at(k) < '0' || line.at(k) > '9') && line.at(k) != '-') {
					k++;
				}
				else break;
			}
			while (k < line_length) {
				if (line.at(k) == '-' || (line.at(k) >= '0' && line.at(k) <= '9')) {
					number2 = line.at(k);
					number.append(number2);
					k++;
				}
				else break;
			}
			wages_array[i][j] = atoi(number.c_str());
			while (k < line_length) {
				if ((line.at(k) < '0' || line.at(k) > '9') && line.at(k) != '-') {
					k++;
				}
				else break;
			}
		}
	}
	getline(file, line);
	optimal = atoi(line.c_str());
	file.close();
}
/*
Główna funkcja sterująca programem.
*/
int main() {
		int x = 0;
		cout << "===================================================================================" << endl;
		cout << "Witaj w programie szukajacym minimalnego cyklu Hamiltona dla problemu komiwojazera." << endl;
		cout << "===================================================================================" << endl;
		cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane testowe: ";
		cin >> file_name;
		cout << "Wybierz metode rozwiazywania (1-brute force,2-branch and bound): ";
		cin >> choice;
		//choice = 2;
		if (choice < 1 || choice>2) {
			cout << "Podales niepoprawna liczbe!" << endl;
			cout << "Wcisnij ENTER, aby zakonczyc" << endl;
			getchar();
			getchar();
			exit(0);
		}
		read_from_file();
		path = new int[nb_of_vertices];
		temp_path = new int[nb_of_vertices];
		path[0] = temp_path[0] = start;
		if (choice == 1) {
			for (int i = 0; i < nb_of_vertices; i++) {
				visited[i] = false;
			}

			start_time = clock();
			find_shortest_cycle_brute_force(start, 1, 0);	//Wywołanie funkcji obliczającej długość najkrótszej ścieżki przy pomocy metody brute-force
			stop_time = clock();
		}
		else {
			start_time = clock();
			find_shortest_cycle_branch_and_bound();			//Wywołanie funkcji obliczającej długość najkrótszej ścieżki przy pomocy metody branch and bound
			stop_time = clock();
		}
		algorithm_time = (double)(stop_time - start_time) / CLOCKS_PER_SEC;

		if (choice == 1) {
			cout << "Wybrana metoda: brute force." << endl;
		}
		else {
			cout << "Wybrana metoda: branch and bound." << endl;
		}
		PRD = (shortest_path - optimal) / (1.0 * optimal) * 100;
		cout << shortest_path << "  " << PRD << " %" << endl;
		for (int i = 0; i < nb_of_vertices; i++) {
			cout << path[i];
			if (i < nb_of_vertices - 1)cout << " -> ";
			if (i > 0 && i % 10 == 0)cout << endl;
		}
		cout << endl;
		cout << "Czas operacji: " << algorithm_time << " s." << endl;
		cout << "Wartosc optymalna: " << optimal << "." << endl;
		file.open(result_file_name, ios::out | ios::app);
		if (choice == 1) {
			file << "Brute-force;" << shortest_path << ";" << optimal << ";" << PRD << ";" << algorithm_time <<";"<<start << endl;
		}
		else {
			file << "Branch and bound;" << shortest_path << ";" << optimal << ";" << PRD << ";" << algorithm_time <<";"<<start<< endl;
		}

		file.close();
		wages_array = nullptr;
		delete wages_array;
		delete[] visited;
		delete[] temp_path;
		delete[] path;	
	cout << "Wcisnij ENTER, aby zakonczyc." << endl;
	getchar();
	getchar();
	return 0;
}