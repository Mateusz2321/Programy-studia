#define _USE_MATH_DEFINES
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>
#include<cstdlib>
#include<cmath>

using namespace std;
string file_name;
string line;
fstream file;
string number_of_vertices;
int nb_of_vertices;
string result_file_name;
string number;
string number2;
unsigned int line_length;
bool* visited;
int** wages_array;
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
int sum;
int temp;

typedef struct tabu_element	//Pojedynczy element listy tabu
{
	int first;
	int second;
	int kadencja;
};
vector<tabu_element> vec;	//Lista tabu
/*
Funkcja przekopiowuje zawartosc jednej tablicy do drugiej
*/
void copy_temp_path_to_path(int* t_path,int* dest_path) {
	for (int i = 0; i < nb_of_vertices; i++) {
		dest_path[i] = t_path[i];
	}

}
/*
Funkcja oblicza dlugosc podanej sciezki.
*/
int calculate_temp_path(int* p) {
	int cycle_sum = 0;
	for (int i = 1; i < nb_of_vertices; i++) {
		cycle_sum += wages_array[p[i-1] ][p[i]];
	}
	cycle_sum += wages_array[p[nb_of_vertices - 1]][p[0]];
	return cycle_sum;
}
/*
Funkcja zwraca wartosc losowa typu double z przedzia³u <0,1>
*/
double return_double_from0to1() {
	int x = rand() % 10001;
	return 1.00 * x / 10000.00;
}
/*
Funkcja zajmuje siê obliczaniem najkrótszej œcie¿ki dla problemu Komiwoja¿era przy pomocy metody symulowanego wy¿arzania.
*/
void tsp_symulowane_wyzarzanie() {
	
	double temperature = 40.00;				//Parametry pocz¹tkowe algorytmu
	int era_length = 100;
	float cooling_factor = 0.999f;
	double procent_improve = 0.5f;
	int steps_without_improving = 10;
	int loop_constraint = 100;
	
	int steps_counter=0;
	int first_node, second_node;
	sum = 0;
	int temp_shortest, temp_now;
	int* temp_path2;
	double temp_random;
	double goal_function_value;
	double temp_double;
	int value_before_era;
	temp_path2 = new int[nb_of_vertices];
	double t;
	int steps_inside_loop_counter = 0;

	cout << "Podaj wartosc temperatury poczatkowej: ";
	cin >> temperature;
	cout << "Podaj dlugosc pojedynczej ery: ";					//Wczytanie parametrów algorytmu.
	cin >> era_length;
	cout << "Podaj wartosc wspolczynnika chlodzenia: ";
	cin >> cooling_factor;
	cout << "Podaj minimalny procent wymaganej poprawy po wykonaniu petli wewnetrznej: ";
	cin >> procent_improve;
	cout << "Podaj maksymalna liczbe krokow petli zewnetrznej bez poprawy: ";
	cin >> steps_without_improving;
	cout << "Podaj maksymalna liczbe krokow petli wewnetrznej: ";
	cin >> loop_constraint;
	start_time = clock();
	temp = rand() % nb_of_vertices;
	temp_path[0] = temp;
	visited[temp] = true;

	for (int i = 1; i < nb_of_vertices; i++) {
		while (true) {
			temp = rand() % nb_of_vertices;					//Wygenerowanie rozwi¹zania losowego.
			if (visited[temp] == false) {
				visited[temp] = true;
				temp_path[i] = temp;
				sum += wages_array[temp_path[i-1]][temp];
				break;
			}
		}		
	}
	copy_temp_path_to_path(temp_path,path);
	sum += wages_array[temp][temp_path[0]];
	shortest_path = sum ;
	cout << "0  " << shortest_path << "  " << (shortest_path - optimal) / (1.0 * optimal) * 100<<" %" << endl;
	temp_shortest = shortest_path;
	int c = 1;
	bool better;
	while (true) {
		better = false;
		steps_counter++;
		value_before_era = temp_shortest;
		steps_inside_loop_counter=0;
		while(true){
			steps_inside_loop_counter++;
			for (int i = 0; i < era_length;i++) {
			
				copy_temp_path_to_path(temp_path, temp_path2);	
				first_node = rand() % nb_of_vertices;					//Wylosowanie dwóch wierzcho³ków
				second_node = rand() % nb_of_vertices;
				while (first_node == second_node) {
					second_node = rand() % nb_of_vertices;
				}
				swap(temp_path2[first_node], temp_path2[second_node]);	//Zamiana dwóch wierzcho³ków w œcie¿ce

				temp_now = calculate_temp_path(temp_path2);				//Obliczenie d³ugoœci nowej œcie¿ki
				if (temp_now < temp_shortest) {							//Sprawdzenie, czy œcie¿ka jest krótsza od obecnej
					temp_shortest = temp_now;							
					copy_temp_path_to_path(temp_path2, temp_path);		//Przyjêcie nowej scie¿ki jako obecnej
					if (temp_shortest < shortest_path) {				//Sprawdzenie, czy scie¿ka jest krótsza od aktualnie najkrótszej œcie¿ki
						better = true;
						shortest_path = temp_shortest;					//Jeœli tak, to przekopiowujemy j¹ do tablicy przechowuj¹cej najkrótsz¹ œcie¿kê
						copy_temp_path_to_path(temp_path, path);
					}
				}
				else {
					temp_random = return_double_from0to1();					//Wylosowanie losowej wartoœci z przedzia³u <0,1>
					goal_function_value = pow(M_E, -1.0 * (temp_now - temp_shortest) / temperature);
					if ( temp_random < goal_function_value ) {				//Je¿eli wartoœæ wylosowana jest mniejsza od wartoœci prawdopodobieñstwa
						temp_shortest = temp_now;							//przyjêcia gorszego rozwi¹zania, to przyjmujemy to rozwi¹zanie.
						copy_temp_path_to_path(temp_path2, temp_path);
					}
				}
			}
			t = 100.00*(value_before_era - temp_shortest) /(1.0*value_before_era);
			if ((t > procent_improve) ||(steps_inside_loop_counter>=loop_constraint) ) break;	//Warunek wyjœcia z pêtli
		}

		if (t > procent_improve) steps_counter = 0;
		if(steps_counter>=steps_without_improving) break;	//Wychodzimy z pêtli, gdy liczba kroków bez poprawy przekroczy ustalon¹ wartoœæ.

		temperature *= cooling_factor;		//zmniejszenie temperatury
		if (better) {
			cout<<c<<"  "<<shortest_path << "  " << (shortest_path - optimal) / (1.0 * optimal) * 100 << " %" << endl;
		}
		c++;
	}
	stop_time = clock();
	delete [] temp_path2;
}
/*
Funkcja sprawdza, czy para wierzcho³ków znajduje siê na liœcie tabu.
*/
bool tabu_contains( int first, int second) {
	for (int i = 0; i < vec.size(); i++) {
		if ((vec[i].first == first && vec[i].second == second) || (vec[i].first == second && vec[i].second == first)) return true;
	}
	return false;
}
/*
Funkcja usuwa elementy z listy tabu, których kadencja skoñczy³a siê.
*/
void remove_from_tabu_list() {
	
	for (auto it = vec.begin(); it != vec.end(); it++)
	{
		it->kadencja--;
		if (it->kadencja <= 0) {
			vec.erase(it);			
			it = vec.begin();
		}		
	}
}
/*
Funkcja zajmuje siê obliczaniem najkrótszej œcie¿ki dla problemu Komiwoja¿era przy pomocy metody symulowanego wy¿arzania.
*/
void tsp_tabu_search() {
	//
	int loop_iterations = 10000;
	int kadencja=2*nb_of_vertices;
	int max_iterations = 200;
	cout << "Podaj maksymalna liczbe iteracji: ";
	cin >> loop_iterations;
	cout << "Podaj maksymalna liczbe iteracji bez poprawy: ";
	cin >> max_iterations;
	//
	int* t  = new int[nb_of_vertices];	//Najlepszy s¹siad
	int* t1 = new int[nb_of_vertices];	//Pomocniczy
	int* t2 = new int[nb_of_vertices];	//Przechowuje poczatkowa sciezke
	int iterations_without_change;
	int first_node, second_node;
	int cycle_length;
	int current_shortest= 2147483647;
	start_time = clock();
	shortest_path = 0;
	path[0] = rand() % nb_of_vertices;
	visited[path[0]] = true;
	for (int i = 1; i < nb_of_vertices; i++) {
		while (true) {
			temp = rand() % nb_of_vertices;
			if (visited[temp] == false) {						//Wygenerowanie rozwi¹zania losowego.
				visited[temp] = true;
				path[i] = temp;
				shortest_path += wages_array[path[i-1]][temp];
				break;
			}
		}		
	}
	shortest_path += wages_array[temp][path[0]];
	cout << "0  " << shortest_path << "  " << (shortest_path - optimal) / (1.0 * optimal) * 100 << " %" << endl;
	copy_temp_path_to_path(path, t); //W t przechowujemy aktualnie najlepsza sciezke

	current_shortest = shortest_path;
	iterations_without_change = 0;
	bool better = false;
	for(int j=0;j<loop_iterations;j++){
		better = false;
		copy_temp_path_to_path(t,t2); //W t2 przechowujemy poczatkowa sciezke
	for (int i = 0; i < 4*sqrt(nb_of_vertices); i++) {
		first_node = rand() % nb_of_vertices;
		second_node = rand() % nb_of_vertices;
		while (first_node == second_node) second_node = rand() % nb_of_vertices;
		copy_temp_path_to_path(t2, t1);							
		if (!tabu_contains(first_node,second_node)) {	//Sprawdzenie czy jest na liœcie tabu
			swap(t1[first_node], t1[second_node]);
			cycle_length = calculate_temp_path(t1);
			if (cycle_length<calculate_temp_path(t)) {
				copy_temp_path_to_path(t1, t);
				current_shortest = cycle_length;
			}
		}
		else {
			swap(t1[first_node], t1[second_node]);
			cycle_length = calculate_temp_path(t1);		//Kryterium aspiracji
			if (cycle_length < shortest_path) {
				better = true;
				copy_temp_path_to_path(t1, t);
				current_shortest = cycle_length;
				copy_temp_path_to_path(t1, path);
				shortest_path = cycle_length;			//dodaæ iterations_without_change=0;
			}

		}
		remove_from_tabu_list();					//Zmniejszenie kadencji elementom na liœcie tabu
		if (current_shortest < shortest_path) {		//Je¿eli znaleziona œcie¿ka jest krótsza od najkrótszej wczeœniej znalezionej, to
			better = true;							//ustawiamy j¹ jako obecnie optymaln¹.
			shortest_path = current_shortest;
			copy_temp_path_to_path(t, path);
			iterations_without_change = 0;

		}
		else {
			iterations_without_change++;		
			tabu_element el;						//Dodanie wierzcho³ków na listê tabu
			el.first = first_node;
			el.second= second_node;
			el.kadencja = kadencja;
			vec.push_back(el);
		}
		if (iterations_without_change >= max_iterations) {		//Wygenerowanie nowej œcie¿ki
			for (int i = 0; i < 10*nb_of_vertices; i++) {
				first_node = rand() % nb_of_vertices;
				second_node = rand() % nb_of_vertices;
				swap(t[first_node], t[second_node]);				
			}
			iterations_without_change = 0;
		}
	}	
	if (better == true) {
		cout << j+1 << "  " << shortest_path << "  " << (shortest_path - optimal) / (1.0 * optimal) * 100 << " %" << endl;
		}
	}	
	stop_time = clock();
	delete [] t; 
	delete [] t1;
	delete [] t2;
}
/*
Funkcja zwalnia zaalokowan¹ pamiêæ.
*/
void dealocate_memory() {
	for (int i = 0; i < nb_of_vertices; i++) delete[] wages_array[i];
	delete [] wages_array;
	delete [] visited;
	delete [] path;
	delete [] temp_path;
}
/*
Funkcja wczytuje z wybranego przez u¿ytkownika pliku
wszelkie informacje o iloœci wierzcho³ków oraz d³ugoœci œæie¿ek pomiêdzy nimi.
Dane te s¹ zapisywane w tablicy dwuwymiarowej.
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
G³ówna funkcja steruj¹ca programem.
*/
int main() {
	srand(time(NULL));
	cout << "===================================================================================" << endl;
	cout << "Witaj w programie szukajacym minimalnego cyklu Hamiltona dla problemu komiwojazera." << endl;
	cout << "===================================================================================" << endl;
	cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane testowe: ";
	cin >> file_name;
	cout << "Wybierz metode rozwiazywania (1-symulowane wyzarzanie, 2- tabu search): ";
	cin >> choice;
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
	for (int i = 0; i < nb_of_vertices; i++) {
		visited[i] = false;
	}
	if (choice == 1) {
		cout << "Wybrana metoda: symulowane wyzarzanie." << endl;
		tsp_symulowane_wyzarzanie();	//Wywo³anie funkcji obliczaj¹cej d³ugoœæ najkrótszej œcie¿ki przy pomocy metody symulowanego wy¿arzania		
	}
	else {
		cout << "Wybrana metoda: tabu search." << endl;
		tsp_tabu_search();			//Wywo³anie funkcji obliczaj¹cej d³ugoœæ najkrótszej œcie¿ki przy pomocy metody tabu- search
	}
	algorithm_time = (double)(stop_time - start_time) / CLOCKS_PER_SEC;

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
		file << "Symulowane wy¿arzanie;" << shortest_path << ";" << optimal << ";" << PRD << ";" << algorithm_time<<";"<<number_of_vertices << endl;
	}
	else {
		file << "Tabu search;" << shortest_path << ";" << optimal << ";" << PRD << ";" << algorithm_time << ";" << number_of_vertices << endl;
	}
	file.close();
	dealocate_memory();

	cout << "Wcisnij ENTER, aby zakonczyc." << endl;
	getchar();
	getchar();
	return 0;
}