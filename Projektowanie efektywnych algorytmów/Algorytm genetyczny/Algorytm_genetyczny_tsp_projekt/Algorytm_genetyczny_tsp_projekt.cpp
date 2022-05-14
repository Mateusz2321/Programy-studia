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
int** wages_array;
int max_int = 2147483647;
int shortest_path = 2147483647;
double algorithm_time;
clock_t start_time, stop_time;
int optimal;
double PRD;
int* path;
int* newFirst;
int* newSecond;
int number_of_specimens=2;
int best_specimens;			//Liczba najlepszych osobników do krzyżowania
double m_probability;		//Prawdopodobieństwo mutacji
int max_iterations;
int length_after_mutation;
int mix_spec = 3;
int new_population = 300;
int crossing = 1;
/*
Funkcja przekopiowuje zawartosc jednej tablicy do drugiej
*/
void copy_temp_path_to_path(int* t_path, int* dest_path) {
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
		cycle_sum += wages_array[p[i - 1]][p[i]];
	}
	cycle_sum += wages_array[p[nb_of_vertices - 1]][p[0]];
	return cycle_sum;
}
/*
Funkcja zwraca wartosc losowa typu double z przedziału <0,1>
*/
double return_double_from0to1() {
	int x = rand() % 10001;
	return 1.00 * x / 10000.00;
}

/*
Funkcja zwalnia zaalokowaną pamięć.
*/
void dealocate_memory() {
	for (int i = 0; i < nb_of_vertices; i++) {
		delete [] wages_array[i];
	}
	delete[] wages_array;
	delete[] path;
	delete[] newFirst;
	delete[] newSecond;
}
/*
Funkcja wczytuje z wybranego przez użytkownika pliku
wszelkie informacje o ilości wierzchołków oraz długości śćieżek pomiędzy nimi.
Dane te są zapisywane w tablicy dwuwymiarowej.
*/
void read_from_file() {
	int line_length;
	string number, number2;
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
Funkcja wykonująca mutację poprzez zamianę dwóch losowych wierzchołków w ścieżce-transpozycja.
*/
bool do_mutation(int* p,double probability,int length) {			
	double prob = double(rand() % 10001) / 10000.00;				
	if (prob < probability) {
		int first = rand() % nb_of_vertices;
		int second = rand() % nb_of_vertices;
		if (first == second) {
			bool found = false;
			for (int i = 0; i < 100; i++) {
				second = rand() % nb_of_vertices;
				if (first != second) {
					found = true;
					break;
				}
			}
			if (found == false) {
				if (first == nb_of_vertices - 1) second = 0;
				else second = first + 1;
			}
		}
		if (first > second) swap(first, second);
		/// Obliczanie długości  ścieżki po mutacji.
		int l=0;
		if (first == 0 && second == nb_of_vertices - 1 ) {
			l -= wages_array[p[nb_of_vertices - 2]][p[nb_of_vertices - 1]];
			l -= wages_array[p[nb_of_vertices - 1]][p[0]];
			l -= wages_array[p[0]][p[1]];
			int temp = *(p + first);
			*(p + first) = *(p + second);
			*(p + second) = temp;
			l += wages_array[p[nb_of_vertices - 2]][p[nb_of_vertices - 1]];
			l += wages_array[p[nb_of_vertices - 1]][p[0]];
			l += wages_array[p[0]][p[1]];
		}
		else if(first==0) {
			if (second == 1) {
				l -= wages_array[p[nb_of_vertices - 1]][p[0]];
				l -= wages_array[p[0]][p[1]];
				l -= wages_array[p[1]][p[2]];
				int temp = *(p + first);
				*(p + first) = *(p + second);
				*(p + second) = temp;
				l += wages_array[p[nb_of_vertices - 1]][p[0]];
				l += wages_array[p[0]][p[1]];
				l += wages_array[p[1]][p[2]];
			}
			else {
				l -= wages_array[p[nb_of_vertices - 1]][p[0]];
				l -= wages_array[p[0]][p[1]];
				l -= wages_array[p[second - 1]][p[second]];
				l -= wages_array[p[second]][p[second+1]];
				int temp = *(p + first);
				*(p + first) = *(p + second);
				*(p + second) = temp;
				l += wages_array[p[nb_of_vertices - 1]][p[0]];
				l += wages_array[p[0]][p[1]];
				l += wages_array[p[second - 1]][p[second]];
				l += wages_array[p[second]][p[second + 1]];
			}
		}
		else if (second== nb_of_vertices-1) {
			if (first == nb_of_vertices - 2) {
				l -= wages_array[p[nb_of_vertices - 3]][p[nb_of_vertices - 2]];
				l -= wages_array[p[nb_of_vertices - 2]][p[nb_of_vertices - 1]];
				l -= wages_array[p[nb_of_vertices - 1]][p[0]];
				int temp = *(p + first);
				*(p + first) = *(p + second);
				*(p + second) = temp;
				l += wages_array[p[nb_of_vertices - 3]][p[nb_of_vertices - 2]];
				l += wages_array[p[nb_of_vertices - 2]][p[nb_of_vertices - 1]];
				l += wages_array[p[nb_of_vertices - 1]][p[0]];
			}
			else {
				l -= wages_array[p[first - 1]][p[first]];
				l -= wages_array[p[first]][p[first+1]];
				l -= wages_array[p[nb_of_vertices-2]][p[nb_of_vertices - 1]];
				l -= wages_array[p[nb_of_vertices - 1]][p[0]];
				int temp = *(p + first);
				*(p + first) = *(p + second);
				*(p + second) = temp;
				l += wages_array[p[first - 1]][p[first]];
				l += wages_array[p[first]][p[first + 1]];
				l += wages_array[p[nb_of_vertices - 2]][p[nb_of_vertices - 1]];
				l += wages_array[p[nb_of_vertices - 1]][p[0]];
			}
		}
		else {
			if (first == second - 1) {
				l -= wages_array[p[first-1]][p[first]];
				l -= wages_array[p[first]][p[second]];
				l -= wages_array[p[second]][p[second+1]];
				int temp = *(p + first);
				*(p + first) = *(p + second);
				*(p + second) = temp;
				l += wages_array[p[first - 1]][p[first]];
				l += wages_array[p[first]][p[second]];
				l += wages_array[p[second]][p[second + 1]];
			}
			else {
				l -= wages_array[p[first-1]][p[first]];
				l -= wages_array[p[first]][p[first+1]];
				l -= wages_array[p[second-1]][p[second]];
				l -= wages_array[p[second]][p[second+1]];
				int temp = *(p + first);
				*(p + first) = *(p + second);
				*(p + second) = temp;
				l += wages_array[p[first - 1]][p[first]];
				l += wages_array[p[first]][p[first + 1]];
				l += wages_array[p[second - 1]][p[second]];
				l += wages_array[p[second]][p[second + 1]];
			}
		}
		length_after_mutation = length + l;
		return true;
	}
	return false;
}
/*
Funkcja wykonująca krzyżowanie PMX osobników.
*/
void crossSpecimensUsingPMX(int *first,int*second) {
	int t1, t2,t3=-1;
	bool copied = false;
	int firstDivide = rand() % (nb_of_vertices-2)+1;
	int secondDivide= rand() % (nb_of_vertices-2)+1;
	while(secondDivide==firstDivide) secondDivide= rand() % (nb_of_vertices-2)+1;
	if (firstDivide > secondDivide) swap (firstDivide, secondDivide);
	for (int i = 0; i <firstDivide; i++) {
		*(newSecond + i) = *(second + i);
		*(newFirst + i) = *(first + i);
	}
	for (int i = firstDivide; i <=secondDivide; i++) {
		*(newSecond + i) = *(first + i);
		*(newFirst + i) = *(second + i);
	}
	for (int i = secondDivide+1; i < nb_of_vertices; i++) {
		*(newSecond + i) = *(second + i);
		*(newFirst + i) = *(first + i);
	}	
	for (int i = firstDivide; i <= secondDivide; i++) {		//Przejście przez wszystkie elementy
		t2 = *(second + i);
		copied = false;
		for (int j = firstDivide; j <= secondDivide; j++) {	//Sprawdzenie, czy element został skopiowany
			if (t2 ==*(first+j) ) {
				copied = true;
				break;
			}
		}
		if (copied == false) {	//Jeżeli element nie został skopiowany
			t1 = *(first + i);	//Określenie, jaki element został skopiowany na jego miejsce
			for (int j = firstDivide; j <= secondDivide; j++) {
				if (t1 == *(second + j)) {
					copied = true;
					break;
				}
			}
			if (copied == true) {
				while (true) {
					t3 = -1;		//pozycja drugi rodzic
					for (int j = firstDivide; j <= secondDivide; j++) {	//
						if (*(second + j) == t1) {
							t3 = j;
							break;
						}
					}
					if (t3 < 0) {
						break;
					}
					t1 = *(first + t3);					
				}
				t3 = -1;
				for (int j = 0; j < firstDivide; j++) {
					if (*(second + j) == t1) {
						t3 = j;
						break;
					}
				}
				if (t3 < 0) {
					for (int j = secondDivide + 1; j < nb_of_vertices; j++) {
						if (*(second + j) == t1) {
							t3 = j;
							break;
						}
					}
				}
				*(newSecond + t3) = t2;  
			}
			else {
				t3 = -1;
				for (int j = 0; j < firstDivide; j++) {
					if (*(second + j) == t1) {
						t3 = j;
						break;
					}
				}
				if (t3 < 0) {
					for (int j = secondDivide + 1; j < nb_of_vertices; j++) {
						if (*(second + j) == t1) {
							t3 = j;
							break;
						}
					}
				}
				*(newSecond + t3) = t2;
			}
		}
		//Dla drugiego potomka
		t2 = *(first + i);
		copied = false;
		for (int j = firstDivide; j <= secondDivide; j++) {	//Sprawdzenie, czy element został skopiowany
			if (t2 == *(second + j)) {
				copied = true;
				break;
			}
		}
		if (copied == false) {	//Jeżeli element nie został skopiowany
			t1 = *(second + i);	//Określenie, jaki element został skopiowany na jego miejsce
			for (int j = firstDivide; j <= secondDivide; j++) {
				if (t1 == *(first + j)) {
					copied = true;
					break;
				}
			}			
			if (copied == true) {
				while (true) {
					t3 = -1;		
					for (int j = firstDivide; j <= secondDivide; j++) {	
						if (*(first + j) == t1) {
							t3 = j;
							break;
						}
					}
					if (t3 < 0) {
						break;
					}
					t1 = *(second + t3);
				}
				t3 = -1;
				for (int j = 0; j < firstDivide; j++) {
					if (*(first + j) == t1) {
						t3 = j;
						break;
					}

				}
				if (t3 < 0) {
					for (int j = secondDivide + 1; j < nb_of_vertices; j++) {
						if (*(first + j) == t1) {
							t3 = j;
							break;
						}
					}
				}
				*(newFirst + t3) = t2;
			}
			else {
				t3 = -1;
				for (int j = 0; j < firstDivide; j++) {
					if (*(first + j) == t1) {
						t3 = j;
						break;
					}
				}
				if (t3 < 0) {
					for (int j = secondDivide + 1; j < nb_of_vertices; j++) {
						if (*(first + j) == t1) {
							t3 = j;
							break;
						}
					}
				}
				*(newFirst + t3) = t2;
			}
		}
	}
}
/*
Funkcja wykonująca krzyżowanie OX osobników.
*/
void crossSpecimensUsingOX(int* first, int* second) {
	int firstDivide = rand() % (nb_of_vertices - 2) + 1;
	int secondDivide = rand() % (nb_of_vertices - 2) + 1;
	while (secondDivide == firstDivide) secondDivide = rand() % (nb_of_vertices - 2) + 1;
	if (firstDivide > secondDivide) swap(firstDivide, secondDivide);
	for (int i = firstDivide; i <= secondDivide; i++) {	//Skopiowanie segmentu rodzica do potomka
		*(newFirst + i) = *(first + i);
		*(newSecond + i) = *(second + i);
	}
	bool contains = false;
	int counter = secondDivide + 1;
	for (int i = secondDivide + 1; i < nb_of_vertices; i++) {
		contains = false;
		for (int j = firstDivide; j <= secondDivide; j++) {
			if (*(first + j) == *(second + i)) {
				contains = true;
				break;
			}
		}
		if (contains == false) {
			*(newFirst + counter) = *(second + i);
			if (counter < nb_of_vertices - 1) counter++;
			else counter = 0;
		}
	}
	for (int i = 0; i <= secondDivide; i++) {
		contains = false;
		for (int j = firstDivide; j <= secondDivide; j++) {
			if (*(first + j) == *(second + i)) {
				contains = true;
				break;
			}
		}
		if (contains == false) {
			*(newFirst + counter) = *(second + i);
			if (counter < nb_of_vertices - 1) counter++;
			else counter = 0;
		}
	}
	//Dla drugiego potomka
	counter = secondDivide + 1;
	for (int i = secondDivide + 1; i < nb_of_vertices; i++) {
		contains = false;
		for (int j = firstDivide; j <= secondDivide; j++) {
			if (*(second + j) == *(first + i)) {
				contains = true;
				break;
			}
		}
		if (contains == false) {
			*(newSecond + counter) = *(first + i);
			if (counter < nb_of_vertices - 1) counter++;
			else counter = 0;
		}
	}
	for (int i = 0; i <= secondDivide; i++) {
		contains = false;
		for (int j = firstDivide; j <= secondDivide; j++) {
			if (*(second + j) == *(first + i)) {
				contains = true;
				break;
			}
		}
		if (contains == false) {
			*(newSecond + counter) = *(first + i);
			if (counter < nb_of_vertices - 1) counter++;
			else counter = 0;
		}
	}

}
/*
Funkcja generuje rozwiązanie początkowe dla pojedynczego osobnika. Rozwiązanie początkowe jest wygenerowane w sposób losowy
lub przy pomocy algorytmu zachłannego, w zależności, które rozwiązanie jest lepsze.
*/
int generate_population(int* p,int f) {						//Wybór populacji początkowej 
	for (int i = 0; i < nb_of_vertices; i++) *(p + i) = i;		//Losowa populacja początkowa
	for (int i = 0; i < 3 * nb_of_vertices; i++) {
		int first = rand() % nb_of_vertices;
		int second = rand() % nb_of_vertices;
		if (first == second) {
			bool found = false;
			for (int j = 0; j < 100; j++) {
				second = rand() % nb_of_vertices;
				if (first != second) {
					found = true;
					break;
				}
			}
			if (found == false) {
				if (first == nb_of_vertices - 1) second = 0;
				else second = first + 1;
			}
		}
		int temp = *(p + first);
		*(p + first) = *(p + second);
		*(p + second) = temp;
	}
	int random_cost = calculate_temp_path(p);		//Koszt losowej populacji początkowej
	int* greedy_algorithm_path = new int[nb_of_vertices];	//Algorytm zachłanny
	int first = f;
	greedy_algorithm_path[0] = first;
	vector<int> v;
	for (int i = 0; i < first; i++) v.push_back(i);
	for (int i = first + 1; i < nb_of_vertices; i++) v.push_back(i);
	int greedy_path_length = 0;
	int nearest_vertice;
	int nearest_length;
	int way;
	for (int i = 0; i < nb_of_vertices-1; i++) {
		nearest_length= max_int;
		for (auto it = v.begin(); it != v.end(); it++)
		{
			way = wages_array[first][*it];
			if (way < nearest_length) {
				nearest_length = way;
				nearest_vertice = *it;
			}
		}
		for (auto it = v.begin(); it != v.end(); it++)
		{
			if (*it==nearest_vertice) {
				v.erase(it);
				break;
			}
		}
		greedy_algorithm_path[i + 1] = nearest_vertice;
		first = nearest_vertice;
	}
	greedy_path_length = calculate_temp_path(greedy_algorithm_path);
	if (greedy_path_length < random_cost) {					//Sprawdzenie, który algorytm okazał się lepszy
		copy_temp_path_to_path(greedy_algorithm_path, p);
		random_cost = greedy_path_length;
	}
	if (random_cost < shortest_path) {
		shortest_path = random_cost;
		copy_temp_path_to_path(p, path);
	}

	delete[] greedy_algorithm_path;
	return random_cost;
}
/*
Funkcja generuje rozwiązanie początkowe dla osobnika w sposób losowy.
*/
int generate_population_randomly(int* p) {						//Wybór populacji początkowej 
	for (int i = 0; i < nb_of_vertices; i++) *(p + i) = i;		//Losowa populacja początkowa
	for (int i = 0; i < 4 * nb_of_vertices; i++) {
		int first = rand() % nb_of_vertices;
		int second = rand() % nb_of_vertices;
		if (first == second) {
			bool found = false;
			for (int j = 0; j < 100; j++) {
				second = rand() % nb_of_vertices;
				if (first != second) {
					found = true;
					break;
				}
			}
			if (found == false) {
				if (first == nb_of_vertices - 1) second = 0;
				else second = first + 1;
			}
		}
		int temp = *(p + first);
		*(p + first) = *(p + second);
		*(p + second) = temp;
	}
	int random_cost = calculate_temp_path(p);		//Koszt losowej populacji początkowej
	
	if (random_cost < shortest_path) {
		shortest_path = random_cost;
		copy_temp_path_to_path(p, path);
	}
	return random_cost;
}
/*
Struktura przechowująca dane o pojedynczym osobniku.
*/
typedef struct specimen_data {
	int path_length;
	int* specimen_path;
};
/*
Funkcja porównująca dane przy pomocy algorytmu sortowania quicksort.
*/
int compare(const void* a, const void* b)
{
	const specimen_data* x = (specimen_data*)a;
	const specimen_data* y = (specimen_data*)b;

	if (x->path_length > y->path_length)
		return 1;
	else if (x->path_length < y->path_length)
		return -1;

	return 0;
}
/*
Funkcja miesza wszystkie osobniki przeznaczone do krzyżowania, aby zachować losowość. Powoduje to także większą eksplorację rozwiązań.
*/
void mix_specimens(specimen_data* spec_data) {
	specimen_data ts;
	for (int i = 0; i < 3 * best_specimens; i++) {
		int first = rand() % best_specimens;
		int second = rand() % best_specimens;
		if (first == second) {
			bool found = false;
			for (int i = 0; i < 100; i++) {
				second = rand() % best_specimens;
				if (first != second) {
					found = true;
					break;
				}
			}
			if (found == false) {
				if (first == best_specimens - 1) second = 0;
				else second = first + 1;
			}
		}
		ts = spec_data[first];
		spec_data[first] = spec_data[second];
		spec_data[second] = ts;
	}
}
/*
Funkcja miesza gorszą połowę osobników przeznaczonych do krzyżowania, aby zachować losowość. 
Powoduje to także większą eksplorację rozwiązań.
*/
void mix_half_specimens(specimen_data* spec_data) {
	specimen_data ts;
	for (int i = 0; i < 2 * best_specimens; i++) {
		int first = rand() % (best_specimens/2);
		int second = rand() % (best_specimens / 2);
		if (first == second) {
			bool found = false;
			for (int i = 0; i < 100; i++) {
				second = rand() % (best_specimens / 2);
				if (first != second) {
					found = true;
					break;
				}
			}
			if (found == false) {
				if (first == best_specimens / 2 - 1) second = 0;
				else second = first + 1;
			}
		}
		first = best_specimens - 1 - first;
		second = best_specimens - 1 - second;
		ts = spec_data[first];
		spec_data[first] = spec_data[second];
		spec_data[second] = ts;
	}
}
/*
Funkcja realizująca algorytm genetyczny.
*/
void tsp_genetic_algorithm() {
	specimen_data* specimens = new specimen_data[number_of_specimens];
	for (int i = 0; i < number_of_specimens; i++) {
		specimens[i].specimen_path= new int[nb_of_vertices];
	}
	int temp_length;
	for (int i = 0; i < nb_of_vertices; i++)	//Wygenerowanie populacji początkowej
	specimens[i].path_length=generate_population(specimens[i].specimen_path,i);
	for (int i = nb_of_vertices; i < number_of_specimens; i++)
		specimens[i].path_length = generate_population_randomly(specimens[i].specimen_path);
	PRD = (shortest_path - optimal) / (1.0 * optimal) * 100;
	cout << "0  " << shortest_path << "  " << PRD <<" %" << endl;
	int iteration_counter = 0;
	int iteration=0;
	int length_before;	//Zapamiętanie długości aktualnie najkrótszej ścieżki
	while (true) {
		length_before = shortest_path;
		//Sortowanie osobników
		qsort(specimens, number_of_specimens, sizeof(specimen_data), compare);
		if (mix_spec == 2)
			mix_specimens(specimens);
		else if (mix_spec == 3)mix_half_specimens(specimens);

		for (int i = 0; i < best_specimens; i+=2) {											//Krzyżowanie
			if(crossing==1)
				crossSpecimensUsingPMX(specimens[i].specimen_path, specimens[i + 1].specimen_path);
			else if (crossing == 2)
				crossSpecimensUsingOX(specimens[i].specimen_path, specimens[i + 1].specimen_path);
			copy_temp_path_to_path(newFirst, specimens[number_of_specimens - 1 - i].specimen_path);
			copy_temp_path_to_path(newSecond, specimens[number_of_specimens - 2 - i].specimen_path);
			specimens[number_of_specimens - 1 - i].path_length = calculate_temp_path(newFirst);
			specimens[number_of_specimens - 2 - i].path_length = calculate_temp_path(newSecond);
			if (specimens[number_of_specimens - 1 - i].path_length < shortest_path) {
				shortest_path = specimens[number_of_specimens - 1 - i].path_length;
				copy_temp_path_to_path(specimens[number_of_specimens - 1 - i].specimen_path, path);
			}
			if (specimens[number_of_specimens - 2 - i].path_length < shortest_path) {
				shortest_path = specimens[number_of_specimens - 2 - i].path_length;
				copy_temp_path_to_path(specimens[number_of_specimens - 2 - i].specimen_path, path);
			}
		}
		for (int i = 0; i < number_of_specimens;i++) {								//Mutacja
			if (do_mutation(specimens[i].specimen_path,m_probability,specimens[i].path_length) == true) {
				temp_length = length_after_mutation;
				specimens[i].path_length = temp_length;
				if (temp_length < shortest_path) {
					shortest_path = temp_length;
					copy_temp_path_to_path(specimens[i].specimen_path, path);
				}
			}
		}
		iteration++;
		iteration_counter++;
		if (shortest_path < length_before) {
			iteration_counter = 0;
			PRD = (shortest_path - optimal) / (1.0 * optimal) * 100;
			cout << iteration << "  " << shortest_path << "  " << PRD << " % " << endl;
		}
		else if (iteration_counter >= max_iterations) break;
		else if (iteration_counter>0 && iteration_counter % new_population==0) {
			int l_bef = shortest_path;
			for (int i = 0; i < number_of_specimens; i++)
				specimens[i].path_length = generate_population_randomly(specimens[i].specimen_path);
			if (shortest_path < l_bef) {
				PRD = (shortest_path - optimal) / (1.0 * optimal) * 100;
				cout << iteration << "  " << shortest_path << "  " << PRD << " % " << endl;
				iteration_counter = 0;
			}
		}
	}
	for (int i = 0; i < number_of_specimens; i++) {		//Dealokacja używanej pamięci
		delete[] specimens[i].specimen_path;
	}
	delete[] specimens;
}
/*
Główna funkcja sterująca programem.
*/
int main() {
	
	srand(time(NULL));
	cout << "===================================================================================" << endl;
	cout << "Witaj w programie szukajacym minimalnego cyklu Hamiltona dla problemu komiwojazera." << endl;
	cout << "===================================================================================" << endl;
	cout << "Etap III: algorytm genetyczny." << endl;
	cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane testowe: ";
	cin >> file_name;
	read_from_file();
	path = new int[nb_of_vertices];
	while (true) {
		cout << "Ile osobnikow ma liczyc populacja (liczba parzysta): ";
		cin >> number_of_specimens;
		if (number_of_specimens > 0) {
			if (number_of_specimens % 2 == 1) number_of_specimens++;
			break;
		}
	}
	while (true) {
		cout << "Podaj liczbe najlepszych osobnikow do krzyzowania (liczba parzysta, nie wiecej niz 50 % populacji): ";
		cin >> best_specimens;
		if (best_specimens > 0 && best_specimens<=number_of_specimens/2) {
			if (best_specimens % 2 == 1) best_specimens++;
			break;
		}
	}
	while (true) {
		cout << "Podaj prawdopodobienstwo mutacji(0.0-1.0): ";
		cin >> m_probability;
		if (m_probability > 0.00 && m_probability < 1.00) break;
	}
	while (true) {
		cout << "Podaj maksymalna liczbe iteracji algorytmu bez poprawy: ";
		cin >> max_iterations;
		if (max_iterations>0) break;
	}
	while (true) {
		cout << "Po ilu iteracjach bez poprawy chcesz wygenerowac nowa populacje( liczba iteracji>100): ";
		cin >> new_population;
		if (new_population>100) break;
	}
	while (true) {
		cout << "Czy chcesz mieszac osobniki przed krzyzowaniem? (1-nie, 2-tak, 3-gorsza polowe) : ";
		cin >> mix_spec;
		if (mix_spec>0 && mix_spec<4) break;
	}	
	while (true) {
		cout << "Rodzaj krzyzowania (1- PMX, 2-OX): ";
		cin >> crossing;
		if (crossing > 0 && crossing < 3) break;
	}
	newFirst = new int[nb_of_vertices];	
	newSecond = new int[nb_of_vertices];
	start_time = clock();
	tsp_genetic_algorithm();
	stop_time = clock();

	algorithm_time = (double)(stop_time - start_time) / CLOCKS_PER_SEC;
	PRD = (shortest_path - optimal) / (1.0 * optimal) * 100;
	cout << "=============================" << endl;
	cout << "Algorytm zakonczyl dzialanie." << endl;
	cout <<"Dlugosc najkrotszej sciezki: "<< shortest_path << "  " << PRD << " %" << endl;
	for (int i = 0; i < nb_of_vertices; i++) {
		cout << path[i];
		if (i < nb_of_vertices - 1)cout << " -> ";
		if (i > 0 && i % 10 == 0)cout << endl;
	}
	cout << endl;
	cout << "Czas operacji: " << algorithm_time << " s." << endl;
	cout << "Wartosc optymalna: " << optimal << "." << endl;
	file.open(result_file_name, ios::out | ios::app);	
	if (!file.good()) cout << "Blad zapisu!" << endl;
	file << "Algorytm genetyczny;" << shortest_path << ";" << optimal << ";" << PRD << ";" << algorithm_time << ";" << number_of_vertices << ";";
	if (crossing == 1) file << "PMX";
	else file << "OX";
	file<< endl;
	file.close();
	dealocate_memory();

	cout << "Wcisnij ENTER, aby zakonczyc." << endl;
	getchar();
	getchar();
	return 0;
}