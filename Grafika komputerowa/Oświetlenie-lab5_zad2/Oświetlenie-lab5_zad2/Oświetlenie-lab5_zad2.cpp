#define _USE_MATH_DEFINES
#include<windows.h>
#include<gl/gl.h>
#include<gl/glut.h>      
#include<iostream>
#include<cmath>
#include<string>									//Problem z kierunkiem wektora normalnego. kolejnośc wierzcholkow zgodnie z kierunkiem zegara. Odwrócić kierunek wektora dla połowy
using namespace std;								//model ambient defuse specular

typedef float point3[3];
unsigned int N;
point3** pointTab;
point3** normalVectorTable;
string title;
GLfloat vectorLength;
GLfloat x, y, z;
GLfloat xu, xv, yu, yv, zu, zv;
static GLint statusL = 0;							// stan lewego klawisza myszy
													// 0 - lewy klawisz niewciśnięty
													// 1 - lewy klawisz wciśnięty

static GLint statusR = 0;							// stan prawego klawisza myszy
													// 0 - prawy klawisz niewciśnięty
													// 1 - prawy klawisz wciśnięty
static int x_pos_old = 0;							// poprzednia pozycja kursora myszy

static int delta_x = 0;								// różnica pomiędzy pozycją bieżącą
													// i poprzednią kursora myszy
static int y_pos_old = 0;							// poprzednia pozycja kursora myszy

static int delta_y = 0;								// różnica pomiędzy pozycją bieżącą
													// i poprzednią kursora myszy
static int x_pos_old2 = 0;							// poprzednia pozycja kursora myszy

static int y_pos_old2 = 0;							// poprzednia pozycja kursora myszy

static GLfloat azimuthAngle = 0.0;					// kąt azymutu, na którym znajduje się światło nr 1
static GLfloat elevationAngle = 0.0;				// kąt elewacji, na którym znajduje się światło nr 1
static GLfloat azimuthAngle2 = 0.0;					// kąt azymutu, na którym znajduje się światło nr 2
static GLfloat elevationAngle2 = 0.0;				// kąt elewacji, na którym znajduje się światło nr 2
static GLfloat radius = 6.0;						// promien sfery, na której znajduje się światło 1
static GLfloat radius2 = 12.0;						// promien sfery, na której znajduje się światło 2
static GLfloat pix2angleHor;						// przelicznik pikseli na stopnie
static GLfloat pix2angleVer;						// przelicznik pikseli na stopnie
static GLfloat light_position[4]; 					//położenie źródła pierwszego

/*
Funkcja tworzy tablicę, która służy do zapisywania współrzednych punktów w przestrzeni 3-D.

*/
void createTabs(void) {

	cout << "Podaj liczbe przedzialow, na ktora ma zostac podzielony bok kwadratu" << endl;
	cout << "uzytego do tworzenia modelu jajka przy pomocy rownan parametrycznych (N): ";
	cin >> N;
	pointTab = new point3 * [N];
	normalVectorTable = new point3 * [N];
	for (int i = 0; i < N; i++) {
		normalVectorTable[i] = new point3[N];
		pointTab[i] = new point3[N];
	}

}
/*
Funkcja zwraca losową wartość typu float z przedziału <0,1>.
Jest używana do ustawiania kolorów.
*/
float returnBit() {
	float bit = ((float)(rand() % 101)) / 100.0f;
	return bit;
}
/*
Funkcja rysuje osie x,y i z na ekranie.
*/

void Axes(void) {

	point3 x_min = { -5.0,0.0,0.0 };			//Wyznaczenie punktów końcowych odcinków
	point3 x_max = { 5.0,0.0,0.0 };
	point3 y_min = { 0.0,-6.0,0.0 };
	point3 y_max = { 0.0,6.0,0.0 };

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex3fv(x_min);							//Narysowanie osi x
	glVertex3fv(x_max);

	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);
	glVertex3fv(y_min);							//Narysowanie osi y
	glVertex3fv(y_max);

	glEnd();


}
/*
Funkcja rysuje na ekranie jajko złożone z trójkątów.
*/

void Egg(void) {
	float u, v;
	glColor3f(1.0f, 1.0f, 1.0f);				//Ustawienie koloru rysowania na biały
	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < N; j++) {
			u = i / (float)(N - 1);				//Obliczenie współrzędnej u punktu znajdującego się w kwadracie jednostkowym.
			v = j / (float)(N - 1);				//Obliczenie współrzędnej v punktu znajdującego się w kwadracie jednostkowym.

			pointTab[i][j][0] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u * u - 45 * u) * cos(M_PI * v);	//Obliczenie wspołrzędnej x punktu 
			pointTab[i][j][1] = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * u * u;												//Obliczenie wspołrzędnej y punktu 
			pointTab[i][j][2] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u * u - 45 * u) * sin(M_PI * v);	//Obliczenie wspołrzędnej z punktu 

			xu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * u * u + 360 * u - 45) * cos(M_PI * v);						//Obliczenie wektora normalnego dla wierzchołka
			yu = 640 * pow(u, 3) - 960 * u * u + 320 * u;
			zu = (-450 * pow(u, 4) + 900 * pow(u, 3) - 810 * pow(u, 2) + 360 * u - 45) * sin(M_PI * v);
			xv = M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u * u + 45 * u) * sin(M_PI * v);
			yv = 0;
			zv = -1.0 * M_PI * (90 * pow(u, 5) - 225 * pow(u, 4) + 270 * pow(u, 3) - 180 * u * u + 45 * u) * cos(M_PI * v);

			if (i == 0 || i == N - 1) {
				normalVectorTable[i][j][0] = 0;
				normalVectorTable[i][j][1] = 1;
				normalVectorTable[i][j][2] = 0;
			}
			else {
				normalVectorTable[i][j][0] = yu * zv - zu * yv;
				normalVectorTable[i][j][1] = zu * xv - xu * zv;
				normalVectorTable[i][j][2] = xu * yv - yu * xv;
				x = normalVectorTable[i][j][0] * normalVectorTable[i][j][0];
				y = normalVectorTable[i][j][1] * normalVectorTable[i][j][1];
				z = normalVectorTable[i][j][2] * normalVectorTable[i][j][2];
				vectorLength = sqrt(x + y + z);
				normalVectorTable[i][j][0] /= vectorLength;
				normalVectorTable[i][j][1] /= vectorLength;
				normalVectorTable[i][j][2] /= vectorLength;
				if (i < N / 2) {
					normalVectorTable[i][j][0] *= -1;
					normalVectorTable[i][j][1] *= -1;
					normalVectorTable[i][j][2] *= -1;
				}
			}
		}
	}

	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < N; j++) {

			glPushMatrix();									//Odłożenie macierzy na stos
			glRotatef(theta[0], 1.0, 0.0f, 0.0f);			//Rotacja punktu wokół osi x
			glRotatef(theta[1], 0.0f, 1.0f, 0.0f);			//Rotacja punktu wokół osi y
			glRotatef(theta[2], 0.0f, 0.0f, 1.0f);			//Rotacja punktu wokół osi z
			glTranslatef(0.0f, -5.0f, 0.0f);				//Przesunięcie punktu o wektor

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glBegin(GL_TRIANGLES);
			glNormal3fv(normalVectorTable[i][j]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i1][j1]);	//Narysowanie trójkąta- pierwszej połowy prostokąta
			glVertex3fv(pointTab[i1][j1]);
			glNormal3fv(normalVectorTable[i][j1]);
			glVertex3fv(pointTab[i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);
			glNormal3fv(normalVectorTable[i1][j1]);
			glVertex3fv(pointTab[i1][j1]);				//Narysowanie trójkąta- drugiej połowy prostokąta
			glNormal3fv(normalVectorTable[i][j]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i1][j]);
			glVertex3fv(pointTab[i1][j]);

			glEnd();

			glPopMatrix();		//Pobranie odłożonej macierzy ze stosu

		}
	}
}
/*
Funkcja zajmuje się renderowaniem obrazu.
*/
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Czyszczenie okna aktualnym kolorem czyszczącym
	glLoadIdentity();	//Wyczyszczenie macierzy
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// Zdefiniowanie położenia obserwatora
	if (statusL == 1)												// jeśli lewy klawisz myszy wcięnięty
	{
		azimuthAngle += delta_x * pix2angleHor * 1.5;					// modyfikacja kąta azymutu położenia obserwatora o kat proporcjonalny
																	// do różnicy położeń kursora myszy
		if (azimuthAngle > 360.0) azimuthAngle -= 360.0;
		else if (azimuthAngle < 0.0) azimuthAngle += 360.0;


		elevationAngle += delta_y * pix2angleVer * 1.5;				// modyfikacja kąta elewacji położenia obserwatora o kat proporcjonalny
																	// do różnicy położeń kursora myszy
		if (elevationAngle > 360.0) elevationAngle -= 360.0;
		else if (elevationAngle < 0.0) elevationAngle += 360.0;

		light_position[0] = radius * cos(M_PI * azimuthAngle / 180.0) * cos(M_PI * elevationAngle / 180.0);	//Ustawienie położenia pierwszego światła
		light_position[1] = radius * sin(M_PI * elevationAngle / 180.0);
		light_position[2] = radius * sin(M_PI * azimuthAngle / 180.0) * cos(M_PI * elevationAngle / 180.0);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (statusR == 1) {
		azimuthAngle2 += delta_x * pix2angleHor * 1.5;					// modyfikacja kąta azymutu położenia obserwatora o kat proporcjonalny
																		// do różnicy położeń kursora myszy
		if (azimuthAngle2 > 360.0) azimuthAngle2 -= 360.0;
		else if (azimuthAngle2 < 0.0) azimuthAngle2 += 360.0;


		elevationAngle2 += delta_y * pix2angleVer * 1.5;				// modyfikacja kąta elewacji położenia obserwatora o kat proporcjonalny
																		// do różnicy położeń kursora myszy
		if (elevationAngle2 > 360.0) elevationAngle2 -= 360.0;
		else if (elevationAngle2 < 0.0) elevationAngle2 += 360.0;

		light_position2[0] = radius2 * cos(M_PI * azimuthAngle2 / 180.0) * cos(M_PI * elevationAngle2 / 180.0);	//Ustawienie położenia drugiego światła
		light_position2[1] = radius2 * sin(M_PI * elevationAngle2 / 180.0);
		light_position2[2] = radius2 * sin(M_PI * azimuthAngle2 / 180.0) * cos(M_PI * elevationAngle2 / 180.0);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

	}
	Axes();				//Narysowanie osi współrzędnych
	Egg();				//Narysowanie jajka


	glFlush();			//Przekazanie poleceń do wykonania

	glutSwapBuffers();	//Zamienia bufory aktualnego okna, jeżeli jest podwójnie buforowane

}

/*
Funkcja obsługuje zmiany rozmiaru okna
*/
void ChangeSize(GLsizei horizontal, GLsizei vertical) {
	pix2angleHor = 360.0 / (float)horizontal;	// przeliczenie pikseli na stopnie
	pix2angleVer = 360.0 / (float)vertical;		// przeliczenie pikseli na stopnie
	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bieżącej

	gluPerspective(70.0, 1.0, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkości okna okna widoku (viewport) w zależności
	// relacji pomiędzy wysokością i szerokością okna

	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bieżącej

}
/*
Funkcja ustala stan renderowania.
*/
void MyInit(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		//Ustawienie koloru czyszczącego
	/*************************************************************************************/
// Definicja materiału z jakiego zrobiony jest czajnik

	GLfloat mat_ambient[] = { 0.55, 0.55, 0.55, 1.0};
	// współczynniki ka =[kar,kag,kab] dla światła otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki ks =[ksr,ksg,ksb] dla światła odbitego               

	GLfloat mat_shininess = { 20.0 };
	// współczynnik n opisujący połysk powierzchni


/*************************************************************************************/
// Definicja źródła światła	
	light_position[0] = -radius;
	light_position[1] = 0.0;
	light_position[2] = 0.0;
	light_position[3] = 1.0;
	GLfloat light_ambient[] = { 0.1, 0.0, 0.0, 1.0 };
	// składowe intensywności świecenia źródła światła otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	// składowe intensywności świecenia źródła światła powodującego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 0.0, 0.0, 1.0 };
	// składowe intensywności świecenia źródła światła powodującego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0 };
	// składowa stała ds dla modelu zmian oświetlenia w funkcji
	// odległości od źródła

	GLfloat att_linear = { 0.05 };
	// składowa liniowa dl dla modelu zmian oświetlenia w funkcji
	// odległości od źródła

	GLfloat att_quadratic = { 0.001 };
	// składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
	// odległości od źródła



/*************************************************************************************/
// Ustawienie parametrów materiału i źródła światła

/*************************************************************************************/
// Ustawienie patrametrów materiału


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


	/*************************************************************************************/
	// Ustawienie parametrów źródła

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);


	/*************************************************************************************/
	// Ustawienie opcji systemu oświetlania sceny

	glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
	glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
	glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
	glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

/*************************************************************************************/

}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		x_pos_old = x;			// przypisanie aktualnie odczytanej pozycji kursora
								// jako pozycji poprzedniej
		y_pos_old = y;			// przypisanie aktualnie odczytanej pozycji kursora
								// jako pozycji poprzedniej
		statusL = 1;			// wcięnięty został lewy klawisz myszy
	}
	else

		statusL = 0;			// nie został wcięnięty lewy klawisz

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		x_pos_old = x;			// przypisanie aktualnie odczytanej pozycji kursora
								// jako pozycji poprzedniej
		y_pos_old = y;			// przypisanie aktualnie odczytanej pozycji kursora
								// jako pozycji poprzedniej
		statusR = 1;			// wciśnięty został prawy klawisz myszy
	}
	else statusR = 0;			// nie został wcięnięty prawy klawisz

}
/*
Funkcja obsluguje poruszanie myszka przez uzytkownika.
*/
void mouseMotion(int x, int y) {
	delta_x = x - x_pos_old;		// obliczenie różnicy położenia kursora myszy

	x_pos_old = x;					// podstawienie bieżącego położenia jako poprzednie

	delta_y = y - y_pos_old;		// obliczenie różnicy położenia kursora myszy

	y_pos_old = y;					// podstawienie bieżącego położenia jako poprzednie

	glutPostRedisplay();			// przerysowanie obrazu sceny


}
/*
Funkcja zwalnia zaalokowaną pamięć.
*/
void freeAllocatedMemory() {
	for (int i = 0; i < N; i++) {
		delete[] pointTab[i];
		delete[] normalVectorTable[i];
	}
	delete[] pointTab;
	delete[] normalVectorTable;
}
/*
Główna funkcja sterująca programem.
*/
void main(void) {
	cout << "Sterowanie polozeniem czerwonego swiatla jest mozliwe przy pomocy lewego przycisku myszy," << endl;
	cout << "a polozeniem swiatla niebieskiego przy pomocy prawego przycisku myszki." << endl;
	cout << "Ruch myszki w kierunku pionowym powoduje zmiane kata elewacji polozenia zrodla, a poziomym zmiane kata elewacji." << endl;
	cout << endl;
	createTabs();			//Stworzenie tablicy wspołrzędnych punktów i wektorów normalnych 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);		//Ustawienie trybu wyświetlania
	glutInitWindowSize(600, 600);									//Ustawienie wielkości okna

	title = "Jajko, N=";											//Zapisanie tytułu okna do zmiennej
	title.append(to_string(N));

	glutCreateWindow(title.c_str());								//Stworzenie okna

	glutDisplayFunc(RenderScene);									//Ustawienie, że funkcja RenderScene będzie przerysowywać okno
	glutReshapeFunc(ChangeSize);									//Ustawienie, że funkcja ChangeSize będzie obsługiwać zmiany wielkości okna
	glutMouseFunc(mouse);											//ustawienie, że funkcja mouse bedzie obsługiwać kliknięcia myszką
	glutMotionFunc(mouseMotion);									//ustawienie, że funkcja mouseMotion będzie obsługiwać ruch myszki
	MyInit();														//Wykonanie inicjalizacji przed przystąpieniem do renderowania

	glEnable(GL_DEPTH_TEST);										//Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();													//Pętla główna programu

	freeAllocatedMemory();											//Wywołanie funkcji zwalniających zaalokowaną pamięć

}