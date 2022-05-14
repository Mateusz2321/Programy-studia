#include<windows.h>
#include<gl/gl.h>
#include<gl/glut.h>
#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;
unsigned int j = 0;
typedef float point2[2];
HANDLE hOut;
unsigned int number_of_divide_square = 7;   //Zmienne uzywane do inicjalizacji dywanu Sierpinskiego
float rotate_angle = 3.0f;
float translate_distance = 3.0f;
/*
Funkcja zwraca wartość typu GLFloat zprzedziału <0,1>.
Jest używana do ustawienia losowego koloru.
*/
GLfloat returnBit() {                              
	float bit1 = ((float)(rand() % 101))/100.0f;   
	GLfloat bit = (GLfloat)bit1;
	return bit;
}
/*
Funkcja zwraca losowa wartosc kata obrotu kwadratow w dywanie.
Wartosc ta jest nie wieksza niz podana przez uzytkownika.
*/
GLfloat returnRotateAngle() {					   
	return (GLfloat)(rotate_angle/180.0f*(rand() % 360 + rand() % 101 / 100.0f - 180.0f)); 
}
/*
Funkcja zwraca losowa wartosc przesuniecia kwadratow w dywanie.
Wartosc ta jest nie wieksza niz podana przez uzytkownika.
*/
GLfloat returnDistance(float length) {				
	return (GLfloat)(rand()%101/100.0f*translate_distance/100.0f*float(length));	
}
/*
Funkcja wczytuje dane inicjalizujace dywan Sierpinskiego.
*/
bool read_data() {
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
	cout << "===================" << endl;
	cout << "Dywan Sierpinskiego" << endl;
	cout << "===================" << endl;

	cout << "Podaj parametry inicjalizujace Dywan Sierpinskiego." << endl;
	SetConsoleTextAttribute(hOut, FOREGROUND_RED);
	cout << "Parametry dywanu mozna zmienic w trakcie dzialania programu klikajac klawisz Spacja przy"<<endl;
	cout<<"otwartym oknie z dywanem i zmieniajac parametry w konsoli." << endl;
	SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
	cout << "Stopien dywanu (liczba calkowita >= 1): ";
	cin >> number_of_divide_square;
	if (number_of_divide_square < 1) {
		cout << "Podano zbyt maly stopien skomplikowania dywanu." << endl;
		cout << "Program zakonczyl dzialanie." << endl;
		return false;
	}
	cout << "Podaj parametry deformacji dywanu. Aby uzyskac niezdeformowany dywan, wpisz 0." << endl;
	cout << "Kat rotacji kolorowych kwadratow w dywanie (float >=0, zalecane <=3): ";
	cin >> rotate_angle;
	cout << "Wartosc przesuniecia kolorowych kwadratow w dywanie(float >= 0, zalecane <= 3): ";
	cin >> translate_distance;
	if (translate_distance < 0.0f) {
		cout << "Wartosc przesuniecia nie moze byc mniejsza niz 0.0f." << endl;
		cout << "Program zakonczyl dzialanie." << endl;
		return false;
	}
	return true;
}
/*
Funkcja rysuje dywan Sierpinskiego na ekranie.
*/
void drawSquare(float x, float y, float length) {
	point2 LeftUpper, RightUpper, LeftBottom, RightBottom; //Zmienne przechowujace wspolrzedne wierzcholkow kwadratow
	point2 SquareLeftUpper, SquareRightUpper, SquareLeftBottom, SquareRightBottom, SquareLeft, SquareRight, SquareBottom, SquareUpper;

	float newLength = length / 3;  //Zmienna przechowujaca dlugosc boku nowego kwadratu

	LeftUpper[0] = x - length / 6;  //Obliczanie wspolrzednych wierzcholkow aktualnie rysowanego kwadratu
	LeftUpper[1] = y + length / 6;
	RightUpper[0] = x + length / 6;
	RightUpper[1] = y + length / 6;
	LeftBottom[0] = x - length / 6;
	LeftBottom[1] = y - length / 6;
	RightBottom[0] = x + length / 6;
	RightBottom[1] = y - length / 6;

	SquareLeftUpper[0] = x - newLength;  //Obliczanie wspolrzednych srodkow kwadratow sasiadujacych 
	SquareLeftUpper[1] = y + newLength;
	SquareRightUpper[0] = x + newLength;
	SquareRightUpper[1] = y + newLength;
	SquareLeftBottom[0] = x - newLength;
	SquareLeftBottom[1] = y - newLength;
	SquareRightBottom[0] = x + newLength;
	SquareRightBottom[1] = y - newLength;
	SquareLeft[0] = x - newLength;
	SquareLeft[1] = y;
	SquareRight[0] = x + newLength;
	SquareRight[1] = y;
	SquareBottom[0] = x;
	SquareBottom[1] = y - newLength;
	SquareUpper[0] = x;
	SquareUpper[1] = y + newLength;

	if (j < number_of_divide_square) {
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);      //Pomalowanie srodkowego kwadratu na czarno
		glVertex2fv(LeftUpper);
		glVertex2fv(RightUpper);
		glVertex2fv(RightBottom);
		glVertex2fv(LeftBottom);
		glEnd();
		j++;
		if (j == number_of_divide_square) {
			drawSquare(SquareLeftUpper[0], SquareLeftUpper[1], length);       //Pomalowanie sasiadujacych kwadratow kolorem
			drawSquare(SquareUpper[0], SquareUpper[1], length);
			drawSquare(SquareRightUpper[0], SquareRightUpper[1], length);
			drawSquare(SquareRight[0], SquareRight[1], length);
			drawSquare(SquareRightBottom[0], SquareRightBottom[1], length);
			drawSquare(SquareBottom[0],SquareBottom[1], length);
			drawSquare(SquareLeftBottom[0], SquareLeftBottom[1], length);
			drawSquare(SquareLeft[0], SquareLeft[1], length);
			j--;
			return;
		}
		else {
			drawSquare(SquareLeftUpper[0], SquareLeftUpper[1], newLength);    //Przejscie do sasiadujacych kwadratow 
			drawSquare(SquareUpper[0], SquareUpper[1], newLength);
			drawSquare(SquareRightUpper[0], SquareRightUpper[1], newLength);
			drawSquare(SquareRight[0], SquareRight[1], newLength);
			drawSquare(SquareRightBottom[0], SquareRightBottom[1], newLength);
			drawSquare(SquareBottom[0],SquareBottom[1], newLength);
			drawSquare(SquareLeftBottom[0], SquareLeftBottom[1], newLength);
			drawSquare(SquareLeft[0], SquareLeft[1], newLength);
			j--;
		}		
	}
	else {
		float vector_length =sqrt( x * x + y * y + 1);              
		x /= vector_length;
		y /= vector_length;
		glPushMatrix();											 //Odlozenie macierzy na stos
		glRotatef(returnRotateAngle(), x, y, 1.0f);				//Rotacja kwadratow o zadany kat
		glBegin(GL_POLYGON);
		glColor3f(returnBit(), returnBit(), returnBit());         //Pomalowanie sasiadujacych kwadratow na kolor
		glVertex2fv(LeftUpper);
		glColor3f(returnBit(), returnBit(), returnBit());
		glVertex2fv(RightUpper);
		glColor3f(returnBit(), returnBit(), returnBit());
		glVertex2fv(RightBottom);
		glColor3f(returnBit(), returnBit(), returnBit());
		glVertex2fv(LeftBottom);
		glEnd();
		glTranslatef(returnDistance(length), returnDistance(length), returnDistance(length));  //Przesuniecie kwadratow w dywanie o wektor [x,y]
		glPopMatrix();											  //Pobranie macierzy ze stosu
	}
}
/*
Funkcja okresla, co ma zostac narysowane. Jest wywolywana za kazdym razem, gdy trzeba przerysowac scene.
*/
void RenderScene() {	
	glClear(GL_COLOR_BUFFER_BIT);
	j = 0;
	drawSquare(0.0f, 0.0f, 180.0f);
	glFlush();
}
/*
Funkcja obsluguje zdarzenia wywolane przez klawiature.
*/
void key_pressed(unsigned char key, int x, int y) {
	switch (key)
	{
	case 32:                  //Spacja
		read_data();
		glutPostRedisplay();  //Odswiezenie dywanu
		break;
	}
}
/*
Funkcja ustala stan renderowania.
*/
void MyInit(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);	//Ustawienie koloru wnetrza okna na szary
}
/*
Funkcja zajmuje sie dostosowywaniem wyswietlanego obrazu do aktualnego rozmiaru okna.
*/
void ChangeSize(GLsizei horizontal, GLsizei vertical) {
	GLfloat AspectRatio;
	if (vertical == 0)
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
}
/*
Glowna funkcja sterujaca programem.
*/
int main() {	
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		
	srand(time(NULL));							
	if (!read_data()) exit(0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   //Ustawienie trybu wyswietlania
	glutInitWindowSize(690, 690);					//Ustawienie wielkosci okna
	glutCreateWindow("Dywan Sierpińskiego");        //Ustawienie nazwy okna
	glutDisplayFunc(RenderScene);					//Okreslenie, ze funkcja RenderScene bedzie sluzyc do przerysowania okna			
	glutReshapeFunc(ChangeSize);					//Okreslenie, ze funkcja ChangeSize bedzie sluzyc do obslugi zmiany wielkosci okna
	MyInit();										//Funkcja wykonuje wszelkie inicjalizacje przed renderowaniem
	glutKeyboardFunc(key_pressed);					//Funkcja obsluguje klawiature
	glutMainLoop();									//Petla glowna programu
	return 0;
}
