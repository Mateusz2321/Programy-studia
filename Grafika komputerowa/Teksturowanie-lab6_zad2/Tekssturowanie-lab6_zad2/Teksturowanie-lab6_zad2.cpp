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
GLfloat*** texture_coordinates;
string title;
GLfloat vectorLength;
GLfloat x, y, z;
GLfloat xu, xv, yu, yv, zu, zv;
static GLfloat viewer[] = { 0.0, 0.0, 10.0 };		// inicjalizacja położenia obserwatora
static GLfloat azimuthAngle = 0.0;					// kąt azymutu, na którym znajduje się obserwator
static GLfloat elevationAngle = 0.0;				// kąt elewacji, na którym znajduje się obserwator
static GLfloat pix2angleHor;						// przelicznik pikseli na stopnie
static GLfloat pix2angleVer;						// przelicznik pikseli na stopnie
static GLfloat pix2zoomVer;							// przelicznik pikseli na przyblizenie obserwatora
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
GLfloat upY = 1.0;									//argument upY z funkcji gluLookAt
static GLfloat radius = 10.0;						//promień sfery, na której znajduje się obserwator
string file_name = "t_512.tga";
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
	texture_coordinates = new GLfloat ** [N];
	for (int i = 0; i < N; i++) {
		texture_coordinates[i] = new GLfloat*[N];
	}
	for (int i = 0; i < N; i++) {
		
		for (int j = 0; j < N; j++) {
			texture_coordinates[i][j] = new GLfloat[2];
		}
	}
	GLfloat step = 1.0 / N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			texture_coordinates[i][j][0] = i * step;
			texture_coordinates[i][j][1] = j * step;
		}
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

	point3 x_min = { -6.0,0.0,0.0 };			//Wyznaczenie punktów końcowych odcinków
	point3 x_max = { 6.0,0.0,0.0 };
	point3 y_min = { 0.0,-6.0,0.0 };
	point3 y_max = { 0.0,6.0,0.0 };
	point3 z_min = { 0.0,0.0,-6.0 };
	point3 z_max = { 0.0,0.0,6.0 };

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3fv(x_min);							//Narysowanie osi x
	glVertex3fv(x_max);
	glEnd();
	glBegin(GL_LINES);
	glVertex3fv(y_min);							//Narysowanie osi y
	glVertex3fv(y_max);
	glEnd();
	glBegin(GL_LINES);
	glVertex3fv(z_min);							//Narysowanie osi z
	glVertex3fv(z_max);
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

			if (i == 0 || i == N - 1) {					//Obliczenie wartosci skladowych wektora normalnego.
				normalVectorTable[i][j][0] = 0;
				normalVectorTable[i][j][1] = -1;
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
				if (i >= N / 2) {
					normalVectorTable[i][j][0] *= -1;
					normalVectorTable[i][j][1] *= -1;
					normalVectorTable[i][j][2] *= -1;
				}
			}
		}
	}
	for (unsigned int i = 0; i <N/2; i++) {
		for (unsigned int j = 1; j < N; j++) {

			glPushMatrix();									//Odłożenie macierzy na stos
			glTranslatef(0.0f, -5.0f, 0.0f);				//Przesunięcie punktu o wektor

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- pierwszej połowy prostokąta
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i1][j1]);	
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);
			glNormal3fv(normalVectorTable[i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(pointTab[i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- drugiej połowy prostokąta
			glNormal3fv(normalVectorTable[i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);				
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(pointTab[i1][j]);

			glEnd();

			glPopMatrix();		//Pobranie odłożonej macierzy ze stosu

		}
	}
		int i = N / 2;
		for (unsigned int j = 0; j < N/2; j++) {

			glPushMatrix();									//Odłożenie macierzy na stos
			glTranslatef(0.0f, -5.0f, 0.0f);				//Przesunięcie punktu o wektor

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- pierwszej połowy prostokąta
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(pointTab[i][j1]);
			glNormal3fv(normalVectorTable[i1][j1]);	
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);
			
			glEnd();									
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- drugiej połowy prostokąta
			glNormal3fv(normalVectorTable[i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);				
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(pointTab[i1][j]);

			glEnd();

			glPopMatrix();		//Pobranie odłożonej macierzy ze stosu

		}
		for (unsigned int j = N/2; j < N ; j++) {

			glPushMatrix();									//Odłożenie macierzy na stos
			glTranslatef(0.0f, -5.0f, 0.0f);				//Przesunięcie punktu o wektor

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- pierwszej połowy prostokąta
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(pointTab[i][j1]);
			glNormal3fv(normalVectorTable[i1][j1]);	
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);

			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- drugiej połowy prostokąta
			glNormal3fv(normalVectorTable[i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);				
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(pointTab[i1][j]);

			glEnd();

			glPopMatrix();		//Pobranie odłożonej macierzy ze stosu

		}
	
	for (unsigned int i = N/2+1; i < N; i++) {
		for (unsigned int j = 1; j < N; j++) {

			glPushMatrix();									//Odłożenie macierzy na stos
			glTranslatef(0.0f, -5.0f, 0.0f);				//Przesunięcie punktu o wektor

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- pierwszej połowy prostokąta
			
			glNormal3fv(normalVectorTable[i1][j1]);	
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);
			glNormal3fv(normalVectorTable[i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(pointTab[i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójkąta- drugiej połowy prostokąta
			glNormal3fv(normalVectorTable[i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(pointTab[i1][j1]);				
			
			glNormal3fv(normalVectorTable[i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(pointTab[i1][j]);
			glNormal3fv(normalVectorTable[i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(pointTab[i][j]);

			glEnd();

			glPopMatrix();		//Pobranie odłożonej macierzy ze stosu

		}
	}
}
/*************************************************************************************/
 // Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie
 // FileName, alokuje pamięć i zwraca wskaźnik (pBits) do bufora w którym
 // umieszczone są dane.
 // Ponadto udostępnia szerokość (ImWidth), wysokość (ImHeight) obrazu
 // tekstury oraz dane opisujące format obrazu według specyfikacji OpenGL
 // (ImComponents) i (ImFormat).
 // Jest to bardzo uproszczona wersja funkcji wczytującej dane z pliku TGA.
 // Działa tylko dla obrazów wykorzystujących 8, 24, or 32 bitowy kolor.
 // Nie obsługuje plików w formacie TGA kodowanych z kompresją RLE.
/*************************************************************************************/

GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
{
	// Struktura dla nagłówka pliku  TGA
#pragma pack(1)           
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE* pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte* pbitsperpixel = NULL;

	// Wartości domyślne zwracane w przypadku błędu

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Przeczytanie nagłówka pliku 

	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

	// Odczytanie szerokości, wysokości i głębi obrazu

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;

	// Sprawdzenie, czy głębia spełnia założone warunki (8, 24, lub 32 bity)

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	// Obliczenie rozmiaru bufora w pamięci

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Alokacja pamięci dla danych obrazu

	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}

	// Ustawienie formatu OpenGL

	switch (sDepth)
	{
	case 3:
		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		break;
	case 4:
		*ImFormat = GL_BGRA_EXT;
		*ImComponents = GL_RGBA8;
		break;
	case 1:
		*ImFormat = GL_LUMINANCE;
		*ImComponents = GL_LUMINANCE8;
		break;
	};
	fclose(pFile);
	return pbitsperpixel;
}
/*
Funkcja zajmuje się renderowaniem obrazu.
*/
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Czyszczenie okna aktualnym kolorem czyszczącym
	glLoadIdentity();	//Wyczyszczenie macierzy
	if (statusL == 1)												// jeśli lewy klawisz myszy wcięnięty
	{
		azimuthAngle += delta_x * pix2angleHor * 2.0;					// modyfikacja kąta azymutu położenia obserwatora o kat proporcjonalny
																	// do różnicy położeń kursora myszy
		if (azimuthAngle > 360.0) azimuthAngle -= 360.0;
		if (azimuthAngle < 0.0) azimuthAngle += 360.0;


		elevationAngle += delta_y * pix2angleVer * 2.0;				// modyfikacja kąta elewacji położenia obserwatora o kat proporcjonalny
																	// do różnicy położeń kursora myszy
		if (elevationAngle > 360.0) elevationAngle -= 360.0;
		if (elevationAngle < 0.0) elevationAngle += 360.0;

		if (elevationAngle > 90.0 && elevationAngle <= 270.0)			//ustawienie parametru upY z funkcji gluLookAt na -1, gdy kąt elewacji
			upY = -1.0;												//będzie większy niż 09 stopni, ale nie większy niż 270, w przeciwnym wypadku na 1
		else
			upY = 1.0;

	}
	if (statusR == 1) {
		radius += delta_y * pix2zoomVer * 10.0;						//modyfikacja promienia sfery, na której znajduje się obserwator

	}
	viewer[0] = radius * cos(M_PI * azimuthAngle / 180.0) * cos(M_PI * elevationAngle / 180.0);	//ustawienie położenia obserwatora
	viewer[1] = radius * sin(M_PI * elevationAngle / 180.0);
	viewer[2] = radius * sin(M_PI * azimuthAngle / 180.0) * cos(M_PI * elevationAngle / 180.0);
	if(radius>=0)
	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, upY, 0.0);  // Zdefiniowanie położenia obserwatora
	else gluLookAt(viewer[0], viewer[1], viewer[2], 2.0*viewer[0], 2.0 * viewer[1], 2.0 * viewer[2], 0.0, upY, 0.0);  
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
	pix2zoomVer = 10.0 / (float)vertical;		// przeliczenie pikseli na stopień przybliżenia
	glMatrixMode(GL_PROJECTION);				// Przełączenie macierzy bieżącej na macierz projekcji			

	glLoadIdentity();							// Czyszcznie macierzy bieżącej	

	gluPerspective(70, 1.0, 1.0, 30.0);			// Ustawienie parametrów dla rzutu perspektywicznego

	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkości okna okna widoku (viewport) w zależności
	// relacji pomiędzy wysokością i szerokością okna

	glMatrixMode(GL_MODELVIEW);					// Przełączenie macierzy bieżącej na macierz widoku modelu 	 

	glLoadIdentity();							// Czyszczenie macierzy bieżącej
}
/*
Funkcja ustala stan renderowania.
*/
void MyInit(void) {

	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);		//Ustawienie koloru czyszczącego
 
// Definicja materiału

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki ka =[kar,kag,kab] dla światła otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki ks =[ksr,ksg,ksb] dla światła odbitego               

	GLfloat mat_shininess = { 30.0 };
	// współczynnik n opisujący połysk powierzchni

// Definicja źródła światła

	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	// położenie źródła

	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// składowe intensywności świecenia źródła światła otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
	// składowe intensywności świecenia źródła światła powodującego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 0.0, 1.0 };
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


	// Ustawienie patrametrów materiału
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
	// Ustawienie parametrów źródła
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);
	// Ustawienie opcji systemu oświetlania sceny
	glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
	glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
	glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
	glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

// Zmienne dla obrazu tekstury

	GLbyte* pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;

	glEnable(GL_CULL_FACE);		//Włączenie trybu teksturowania, w którym teksturowanie jest prowadzone tylko po jednej stronie ściany

	pBytes = LoadTGAImage(file_name.c_str(), &ImWidth, &ImHeight, &ImComponents, &ImFormat);	//Wywołanie funkcji pobierającej obraz tekstury z pliku

	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);	//Zdefiniowanie tekstury 2-D

	free(pBytes);		//Zwolnienie pamięci przeznaczonej na przechowanie obrazu tekstury

	glEnable(GL_TEXTURE_2D);		//Włączenie mechanizmu teksturowania

	//Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//Ustawienie trybu łączenia pikseli tekstury z pikselami ekranu na GL_MODULATE

	// Określenie sposobu nakładania tekstur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Określenie sposobu, w jaki następuje pomniejszanie tekstury (usuwanie pikseli)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Określenie sposobu, w jaki następuje powiększanie tekstury (dodawanie pikseli)

}
/*
Funkcja obsluguje klikniecia myszka.
*/
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

	if (button == GLUT_RIGHT_BUTTON) {
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
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			delete[] texture_coordinates[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		delete [] texture_coordinates[i];
	}
	delete[] texture_coordinates;
}
/*
Główna funkcja sterująca programem.
*/
void main(void) {
	cout << "Witaj w programie tworzacym model jajka." << endl;
	cout << "Stworzony model posiada teksture i jest oswietlony swiatlem zoltym." << endl;
	cout << "Program umozliwia obserwacje obiektu przy pomocy zmiany polozenia obserwatora." << endl;
	cout << "Sterowanie:" << endl;
	cout << "- wcisniety lewy klawisz myszy- zmiana kata elewacji polozenia obserwatora (ruch pionowy myszka)," << endl;
	cout << "zmiana kata azymutu polozenia obserwatora(ruch poziomy myszka)" << endl;
	cout << "- wcisniety prawy klawisz myszy- zmiana odleglosci obserwatora od obiektu(ruch pionowy myszka)." << endl;
	cout << "===============================================================================================" << endl;
	createTabs();			//Stworzenie tablicy wspołrzędnych punktów i wektorów normalnych 

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);		//Ustawienie trybu wyświetlania
	glutInitWindowSize(700, 700);									//Ustawienie wielkości okna

	title = "Jajko- teksturowanie, N=";								//Zapisanie tytułu okna do zmiennej
	title.append(to_string(N));

	glutCreateWindow(title.c_str());								//Stworzenie okna

	glutDisplayFunc(RenderScene);									//Ustawienie, że funkcja RenderScene będzie przerysowywać okno

	glutReshapeFunc(ChangeSize);									//Ustawienie, że funkcja ChangeSize będzie obsługiwać zmiany wielkości okna
	glutMouseFunc(mouse);											//Ustawienie, że funkcja mouse bedzie obsługiwać kliknięcia myszką
	glutMotionFunc(mouseMotion);									//Ustawienie, że funkcja mouseMotion będzie obsługiwać ruch myszki
	MyInit();														//Wykonanie inicjalizacji przed przystąpieniem do renderowania

	glEnable(GL_DEPTH_TEST);										//Włączenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();													//Pętla główna programu

	freeAllocatedMemory();											//Wywołanie funkcji zwalniających zaalokowaną pamięć

}