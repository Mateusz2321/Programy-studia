#define _USE_MATH_DEFINES
#include<windows.h>
#include<gl/gl.h>
#include<gl/glut.h>      
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
typedef float point3[3];
typedef float point4[4];
typedef struct Planet {         //Dane opisuj¹ce planetê
    float radius;               //Promieñ planety
	float distance_from_center;	//Odleg³oœæ od œrodka uk³adu s³onecznego
    float x_coordinate;         //Wspó³rzêdna x œrodka planety
    float y_coordinate;         //Wspó³rzêdna y œrodka planety
    float z_coordinate;         //Wspó³rzêdna z œrodka planety
	GLuint texture;				//WskaŸnik na teksturê planety
	bool plusX;					//Kierunek poruszania
	float aroundSunSpeed;		//Prêdkoœæ obrotu wokó³ s³oñca
	float aroundYourselfSpeed;	//Prêdkoœæ ruchu obrotowego
	float theta;				//Aktualny k¹t obrotu
};
typedef struct Sun {					//Dane opisuj¹ce s³oñce
	float radius;						//Promieñ s³oñca
	point4 l_s;							//Wspó³czynnik kierunkowy Ÿród³a œwiat³a - specular 
	point4 l_d;							//Wspó³czynnik dla œwiat³a rozproszonego - diffuse 
	point4 l_a;							//Wspó³æzynnik dla œwiat³a otoczenia - ambient 
	float att_constant;					//Wspó³czynnik sta³y oœwietlenia
	float att_linear;					//Wspó³czynnik liniowy oœwietlenia
	float att_quadratic;				//Wspó³czynnik kwadratowy oœwietlenia
	GLuint texture;						//WskaŸnik na teksturê s³oñca
	float aroundYourselfSpeed;			//Prêdkoœæ obrotu s³oñca
	float theta;						//Aktualny k¹t obrotu
};
struct Material {
	point4 k_s;                 //Wspó³czynnik materia³owy dla œwiat³a kierunkowego - specular powierzchni 
	point4 k_d;                 //Wspó³czynnik materia³owy dla œwiat³a rozproszonego - diffuse powierzchni 
	point4 k_a;                 //Wspó³æzynnik materia³owy dla œwiat³a otoczenia - ambient powierzchni 
	float shininess_factor;     //Wspó³czynnik po³ysku materia³u
}mat;
Planet* planets;					//WskaŸnik do tablicy zawieraj¹cej dane o planetach
Planet* moon=new Planet;			//WskaŸnik na ksiê¿yc
Sun* sun = new Sun;					//Wska¿nik na s³oñce
int N = 100;						//Gêstoœæ modeli s³oñca i planet
						
point3*** points;									//Punkty sfery
point3*** normal_vectors;							//Wektory normalne dla punktów
GLfloat*** texture_coordinates;						//Wspó³rzêdne do teksturowania
static GLfloat viewer[] = { 0.0, 0.0, 50.0 };		//Inicjalizacja po³o¿enia obserwatora
static GLfloat azimuthAngle = 0.0;					// k¹t azymutu, na którym znajduje siê obserwator
static GLfloat elevationAngle = 0.0;				// k¹t elewacji, na którym znajduje siê obserwator
static GLfloat pix2angleHor;						// przelicznik pikseli na stopnie
static GLfloat pix2angleVer;						// przelicznik pikseli na stopnie
static GLfloat pix2zoomVer;							// przelicznik pikseli na przyblizenie obserwatora
static GLint statusL = 0;							// stan lewego klawisza myszy
													// 0 - lewy klawisz niewciœniêty
													// 1 - lewy klawisz wciœniêty

static GLint statusR = 0;							// stan prawego klawisza myszy
													// 0 - prawy klawisz niewciœniêty
													// 1 - prawy klawisz wciœniêty
static int x_pos_old = 0;							// poprzednia pozycja kursora myszy

static int delta_x = 0;								// ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
													// i poprzedni¹ kursora myszy
static int y_pos_old = 0;							// poprzednia pozycja kursora myszy

static int delta_y = 0;								// ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
													// i poprzedni¹ kursora myszy
GLfloat upY = 1.0;									//argument upY z funkcji gluLookAt
static GLfloat radius = 10.0;						//promieñ sfery, na której znajduje siê obserwator
float speed = 0.32;									//Prêdkoœæ animacji

/*************************************************************************************/
 // Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie
 // FileName, alokuje pamiêæ i zwraca wskaŸnik (pBits) do bufora w którym
 // umieszczone s¹ dane.
 // Ponadto udostêpnia szerokoœæ (ImWidth), wysokoœæ (ImHeight) obrazu
 // tekstury oraz dane opisuj¹ce format obrazu wed³ug specyfikacji OpenGL
 // (ImComponents) i (ImFormat).
 // Jest to bardzo uproszczona wersja funkcji wczytuj¹cej dane z pliku TGA.
 // Dzia³a tylko dla obrazów wykorzystuj¹cych 8, 24, or 32 bitowy kolor.
 // Nie obs³uguje plików w formacie TGA kodowanych z kompresj¹ RLE.
/*************************************************************************************/

GLbyte* LoadTGAImage(const char* FileName, GLint* ImWidth, GLint* ImHeight, GLint* ImComponents, GLenum* ImFormat)
{
	// Struktura dla nag³ówka pliku  TGA
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

	// Wartoœci domyœlne zwracane w przypadku b³êdu

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Przeczytanie nag³ówka pliku 

	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);

	// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;

	// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity)

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	// Obliczenie rozmiaru bufora w pamiêci

	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Alokacja pamiêci dla danych obrazu

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
GLuint load_texture(string fn) {
	GLbyte* pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glEnable(GL_CULL_FACE);		//W³¹czenie trybu teksturowania, w którym teksturowanie jest prowadzone tylko po jednej stronie œciany

	pBytes = LoadTGAImage(fn.c_str(), &ImWidth, &ImHeight, &ImComponents, &ImFormat);	//Wywo³anie funkcji pobieraj¹cej obraz tekstury z pliku
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);	//Zdefiniowanie tekstury 2-D

	free(pBytes);		//Zwolnienie pamiêci przeznaczonej na przechowanie obrazu tekstury
	//Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Okreœlenie sposobu nak³adania tekstur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}
void drawOrbit(float distance, float x, float y, float z) {
	glDisable(GL_TEXTURE_2D);
	x += 1.5;
	float distance2 = 0.7 * distance;
	glPushMatrix();
	glBegin(GL_LINES);
	float x1, z1,x2=0.0f,z2=distance2;
	for (int i = 1; i < 1001; i++) {		
			x1 = x2;
			z1 = z2;
			x2 = i / 1000.00f*distance;
			z2 = sqrt((1 - (x2 * x2) / (distance * distance)) * distance2 * distance2);
			glVertex3f(x + x1, y + 0.0, z + z1);
			glVertex3f(x + x2, y + 0.0, z + z2);
	}
	x2 = distance, z2 = 0.0f;
	for (int i = 1000; i >=0; i--) {
		x1 = x2;
		z1 = z2;
		x2 = i / 1000.00f * distance;
		z2 = sqrt((1 - (x2 * x2) / (distance * distance)) * distance2 * distance2);
		glVertex3f(x + x1, y + 0.0, z - z1);
		glVertex3f(x + x2, y + 0.0, z - z2);
	}
	x2 = 0.0f, z2 = distance2;
	for (int i = 1; i < 1001; i++) {
		x1 = x2;
		z1 = z2;
		x2 = i / 1000.00f * distance;
		z2 = sqrt((1 - (x2 * x2) / (distance * distance)) * distance2 * distance2);
		glVertex3f(x - x1, y + 0.0, z - z1);
		glVertex3f(x - x2, y + 0.0, z - z2);
	}
	x2 = distance, z2 = 0.0f;
	for (int i = 1000; i >=0 ; i--) {
		x1 = x2;
		z1 = z2;
		x2 = i / 1000.00f * distance;
		z2 = sqrt((1 - (x2 * x2) / (distance * distance)) * distance2 * distance2);
		glVertex3f(x + x1, y + 0.0, z + z1);
		glVertex3f(x + x2, y + 0.0, z + z2);
		glVertex3f(x - x1, y + 0.0, z - z1);
		glVertex3f(x - x2, y + 0.0, z - z2);
		glVertex3f(x - x1, y + 0.0, z + z1);
		glVertex3f(x - x2, y + 0.0, z + z2);
		glVertex3f(x + x1, y + 0.0, z - z1);
		glVertex3f(x + x2, y + 0.0, z - z2);
	}
	glEnd();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}
void drawPlanet(int nr) {
	int i1, j1;
	for (unsigned int i = 0; i <= N / 2; i++) {
		for (unsigned int j = 1; j < N; j++) {

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glPushMatrix();			//Od³o¿enie macierzy na stos
		
			glTranslatef(planets[nr].x_coordinate, planets[nr].y_coordinate, planets[nr].z_coordinate);	
			glRotatef(planets[nr].theta, 0.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- pierwszej po³owy prostok¹ta
			glNormal3fv(normal_vectors[nr][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[nr][i][j]);
			glNormal3fv(normal_vectors[nr][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[nr][i1][j1]);
			glNormal3fv(normal_vectors[nr][i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(points[nr][i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- drugiej po³owy prostok¹ta
			glNormal3fv(normal_vectors[nr][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[nr][i1][j1]);
			glNormal3fv(normal_vectors[nr][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[nr][i][j]);
			glNormal3fv(normal_vectors[nr][i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(points[nr][i1][j]);

			glEnd();

			glPopMatrix();		//Pobranie od³o¿onej macierzy ze stosu

		}
	}
	for (unsigned int i = N / 2 + 1; i < N; i++) {
		for (unsigned int j = 1; j < N; j++) {

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glPushMatrix();		//Od³o¿enie macierzy na stos
			glTranslatef(planets[nr].x_coordinate, planets[nr].y_coordinate, planets[nr].z_coordinate);
			glRotatef(planets[nr].theta, 0.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- pierwszej po³owy prostok¹ta
			
			glNormal3fv(normal_vectors[nr][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[nr][i][j]);
			glNormal3fv(normal_vectors[nr][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[nr][i1][j1]);
			glNormal3fv(normal_vectors[nr][i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(points[nr][i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- drugiej po³owy prostok¹ta
			

			glNormal3fv(normal_vectors[nr][i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(points[nr][i1][j]);
			glNormal3fv(normal_vectors[nr][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[nr][i1][j1]);
			glNormal3fv(normal_vectors[nr][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[nr][i][j]);

			glEnd();

			glPopMatrix();		//Pobranie od³o¿onej macierzy ze stosu

		}
	}	

}
void drawSun() {
	int i1, j1;
	for (unsigned int i = 0; i <= N / 2; i++) {
		for (unsigned int j = 1; j < N; j++) {

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glPushMatrix();			//Od³o¿enie macierzy na stos
			glRotatef(sun->theta, 0.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- pierwszej po³owy prostok¹ta
			glNormal3fv(normal_vectors[8][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[8][i][j]);
			glNormal3fv(normal_vectors[8][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[8][i1][j1]);
			glNormal3fv(normal_vectors[8][i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(points[8][i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- drugiej po³owy prostok¹ta
			glNormal3fv(normal_vectors[8][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[8][i1][j1]);
			glNormal3fv(normal_vectors[8][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[8][i][j]);
			glNormal3fv(normal_vectors[8][i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(points[8][i1][j]);

			glEnd();

			glPopMatrix();		//Pobranie od³o¿onej macierzy ze stosu

		}
	}
	for (unsigned int i = N / 2 + 1; i < N; i++) {
		for (unsigned int j = 1; j < N; j++) {

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glPushMatrix();					//Od³o¿enie macierzy na stos
			glRotatef(sun->theta, 0.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- pierwszej po³owy prostok¹ta

			
			glNormal3fv(normal_vectors[8][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[8][i][j]);
			glNormal3fv(normal_vectors[8][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[8][i1][j1]);
			glNormal3fv(normal_vectors[8][i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(points[8][i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- drugiej po³owy prostok¹ta
			

			glNormal3fv(normal_vectors[8][i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(points[8][i1][j]);
			glNormal3fv(normal_vectors[8][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[8][i1][j1]);
			glNormal3fv(normal_vectors[8][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[8][i][j]);

			glEnd();

			glPopMatrix();		//Pobranie od³o¿onej macierzy ze stosu

		}
	}
}
void drawMoon() {
	int i1, j1;
	for (unsigned int i = 0; i <= N / 2; i++) {
		for (unsigned int j = 1; j < N; j++) {

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glPushMatrix();				//Od³o¿enie macierzy na stos
			glTranslatef(planets[2].x_coordinate+moon->x_coordinate-1.4, planets[2].y_coordinate + moon->y_coordinate, planets[2].z_coordinate + moon->z_coordinate);
			glRotatef(moon->theta, 0.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- pierwszej po³owy prostok¹ta
			glNormal3fv(normal_vectors[9][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[9][i][j]);
			glNormal3fv(normal_vectors[9][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[9][i1][j1]);
			glNormal3fv(normal_vectors[9][i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(points[9][i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- drugiej po³owy prostok¹ta
			glNormal3fv(normal_vectors[9][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[9][i1][j1]);
			glNormal3fv(normal_vectors[9][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[9][i][j]);
			glNormal3fv(normal_vectors[9][i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(points[9][i1][j]);

			glEnd();

			glPopMatrix();		//Pobranie od³o¿onej macierzy ze stosu

		}
	}
	for (unsigned int i = N / 2 + 1; i < N; i++) {
		for (unsigned int j = 1; j < N; j++) {

			int i1, j1;
			i1 = i - 1;
			j1 = j - 1;
			if (i1 < 0) i1 = N - 1;
			if (j1 < 0) j1 = N - 1;
			glPushMatrix();				//Od³o¿enie macierzy na stos
			glTranslatef(planets[2].x_coordinate + moon->x_coordinate - 1.4, planets[2].y_coordinate + moon->y_coordinate, planets[2].z_coordinate + moon->z_coordinate);
			glRotatef(moon->theta, 0.0f, 1.0f, 0.0f);
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- pierwszej po³owy prostok¹ta


			glNormal3fv(normal_vectors[9][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[9][i][j]);
			glNormal3fv(normal_vectors[9][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[9][i1][j1]);
			glNormal3fv(normal_vectors[9][i][j1]);
			glTexCoord2f(texture_coordinates[i][j1][0], texture_coordinates[i][j1][1]);
			glVertex3fv(points[9][i][j1]);
			glEnd();
			glBegin(GL_TRIANGLES);						//Narysowanie trójk¹ta- drugiej po³owy prostok¹ta


			glNormal3fv(normal_vectors[9][i1][j]);
			glTexCoord2f(texture_coordinates[i1][j][0], texture_coordinates[i1][j][1]);
			glVertex3fv(points[9][i1][j]);
			glNormal3fv(normal_vectors[9][i1][j1]);
			glTexCoord2f(texture_coordinates[i1][j1][0], texture_coordinates[i1][j1][1]);
			glVertex3fv(points[9][i1][j1]);
			glNormal3fv(normal_vectors[9][i][j]);
			glTexCoord2f(texture_coordinates[i][j][0], texture_coordinates[i][j][1]);
			glVertex3fv(points[9][i][j]);

			glEnd();

			glPopMatrix();		//Pobranie od³o¿onej macierzy ze stosu

		}
	}
}
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Czyszczenie okna aktualnym kolorem czyszcz¹cym
	glLoadIdentity();	//Wyczyszczenie macierzy
	if (statusL == 1)												// jeœli lewy klawisz myszy wciêniêty
	{
		azimuthAngle += delta_x * pix2angleHor * 2.0;					// modyfikacja k¹ta azymutu po³o¿enia obserwatora o kat proporcjonalny
																	// do ró¿nicy po³o¿eñ kursora myszy
		if (azimuthAngle > 360.0) azimuthAngle -= 360.0;
		if (azimuthAngle < 0.0) azimuthAngle += 360.0;


		elevationAngle += delta_y * pix2angleVer * 2.0;				// modyfikacja k¹ta elewacji po³o¿enia obserwatora o kat proporcjonalny
																	// do ró¿nicy po³o¿eñ kursora myszy
		if (elevationAngle > 360.0) elevationAngle -= 360.0;
		if (elevationAngle < 0.0) elevationAngle += 360.0;

		if (elevationAngle > 90.0 && elevationAngle <= 270.0)			//ustawienie parametru upY z funkcji gluLookAt na -1, gdy k¹t elewacji
			upY = -1.0;												//bêdzie wiêkszy ni¿ 09 stopni, ale nie wiêkszy ni¿ 270, w przeciwnym wypadku na 1
		else
			upY = 1.0;

	}
	if (statusR == 1) {
		radius += delta_y * pix2zoomVer * 10.0;						//modyfikacja promienia sfery, na której znajduje siê obserwator

	}
	viewer[0] = radius * cos(M_PI * azimuthAngle / 180.0) * cos(M_PI * elevationAngle / 180.0);	//ustawienie po³o¿enia obserwatora
	viewer[1] = radius * sin(M_PI * elevationAngle / 180.0);
	viewer[2] = radius * sin(M_PI * azimuthAngle / 180.0) * cos(M_PI * elevationAngle / 180.0);
	if (radius >= 0)
		gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, upY, 0.0);  // Zdefiniowanie po³o¿enia obserwatora
	else gluLookAt(viewer[0], viewer[1], viewer[2], 2.0 * viewer[0], 2.0 * viewer[1], 2.0 * viewer[2], 0.0, upY, 0.0);
	glColor3f(1.00f, 1.00f, 1.00f);
	drawOrbit(moon->distance_from_center, planets[2].x_coordinate-1.4, planets[2].y_coordinate, planets[2].z_coordinate);
	for (int i = 0; i < 8; i++) {			
		drawOrbit(planets[i].distance_from_center, 0.0f, 0.0f, 0.0f);	//Narysowanie orbit dla planet
		glBindTexture(GL_TEXTURE_2D, planets[i].texture);
		drawPlanet(i);	//Narysowanie planety		
	}		
		glBindTexture(GL_TEXTURE_2D, sun->texture);
		drawSun();	//Narysowanie s³oñca	
		glBindTexture(GL_TEXTURE_2D, moon->texture);
		drawMoon();	//Narysowanie ksiê¿yca


	glFlush();			//Przekazanie poleceñ do wykonania

	glutSwapBuffers();	//Zamienia bufory aktualnego okna, je¿eli jest podwójnie buforowane
}
void ChangeSize(GLsizei horizontal, GLsizei vertical) {
	pix2angleHor = 360.0 / (float)horizontal;	// przeliczenie pikseli na stopnie
	pix2angleVer = 360.0 / (float)vertical;		// przeliczenie pikseli na stopnie
	pix2zoomVer = 10.0 / (float)vertical;		// przeliczenie pikseli na stopieñ przybli¿enia
	glMatrixMode(GL_PROJECTION);				// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji			

	glLoadIdentity();							// Czyszcznie macierzy bie¿¹cej	

	gluPerspective(70, 1.0, 1.0, 200.0);			// Ustawienie parametrów dla rzutu perspektywicznego

	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);					// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu 	 

	glLoadIdentity();							// Czyszczenie macierzy bie¿¹cej


}

void MyInit(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		//Ustawienie koloru czyszcz¹cego
	glEnable(GL_TEXTURE_2D);		//W³¹czenie mechanizmu teksturowania
	
	/*************************************************************************************/
// Ustawienie patrametrów materia³u

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.k_s);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.k_a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.k_d);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shininess_factor);

	/*************************************************************************************/
	// Ustawienie parametrów Ÿród³a

	glLightfv(GL_LIGHT0, GL_AMBIENT, sun->l_a);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun->l_d);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun->l_s);
	float light_position[4] = { 0.0f,0.0f,0.0f,1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, sun->att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,sun-> att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,sun-> att_quadratic);

	/*************************************************************************************/
	// Ustawienie opcji systemu oœwietlania sceny

	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora

/*************************************************************************************/
	planets[0].texture = load_texture("mercury.tga");
	drawPlanet(0);	//Narysowanie planety				
	planets[1].texture = load_texture("venus.tga");
	drawPlanet(1);	//Narysowanie planety
	planets[2].texture = load_texture("earth.tga");
	drawPlanet(2);	//Narysowanie planety
	planets[3].texture = load_texture("mars.tga");
	drawPlanet(3);	//Narysowanie planety
	planets[4].texture = load_texture("jupiter.tga");
	drawPlanet(4);	//Narysowanie planety
	planets[5].texture = load_texture("saturn.tga");
	drawPlanet(5);	//Narysowanie planety
	planets[6].texture = load_texture("uranus.tga");
	drawPlanet(6);	//Narysowanie planety
	planets[7].texture = load_texture("neptune.tga");
	drawPlanet(7);	//Narysowanie planet
	sun->texture = load_texture("sun.tga");
	drawSun();	//Narysowanie s³oñca	
	moon->texture = load_texture("moon.tga");
	drawMoon();
}
float get_z_coordinate(Planet* p, bool plus) {
	float distance = p->distance_from_center;
	float distance2 = 0.7 * distance;
	float x = p->x_coordinate;
	float z = sqrt((1 - (x * x) / (distance * distance)) * distance2 * distance2);
	if (plus == true)
		return z;
	else return -z;
}
void spinnPlanets(void) {
	float x,z,distance,second_distance;
	for (int i = 0; i < 8; i++) {
		x = planets[i].x_coordinate-1.5;
		z = planets[i].z_coordinate;
		distance = planets[i].distance_from_center;
		second_distance = 0.7 * distance;
		if (z >= 0&& x<distance) {
			planets[i].plusX = true;
		}
		else {
			planets[i].plusX = false;

		}
		 if (planets[i].plusX == true) {
			x += 0.01 * speed*planets[i].aroundSunSpeed;
			 if (x >= distance) {
				planets[i].x_coordinate = 2*distance-x;
				planets[i].z_coordinate = get_z_coordinate(&(planets[i]), false);
				planets[i].x_coordinate += 1.5;
			}
			 else if (x==distance) {
				 planets[i].x_coordinate -= 0.01 * speed*planets[i].aroundSunSpeed;
				 planets[i].z_coordinate = get_z_coordinate(&(planets[i]), false);
				 planets[i].x_coordinate += 1.5;
			 }
			else {
				planets[i].x_coordinate = x;
				planets[i].z_coordinate = get_z_coordinate(&(planets[i]), true);
				planets[i].x_coordinate +=1.5;
			}
		}
		else {
			x -= 0.01 * speed*planets[i].aroundSunSpeed;
			if (x <= -distance) {
				planets[i].x_coordinate = -2*distance-x;
				planets[i].z_coordinate = get_z_coordinate(&(planets[i]), true);
				planets[i].x_coordinate += 1.5;
			}
			else if (x==-distance) {
				planets[i].x_coordinate += 0.01 * speed * planets[i].aroundSunSpeed;
				planets[i].z_coordinate = get_z_coordinate(&(planets[i]), true);
				planets[i].x_coordinate += 1.5;
			}
			else {
				planets[i].x_coordinate = x;
				planets[i].z_coordinate = get_z_coordinate(&(planets[i]), false);
				planets[i].x_coordinate += 1.5;
			}
		}
		//ruch obrotowy
		 planets[i].theta +=  3.0*speed * planets[i].aroundYourselfSpeed;
		 if (planets[i].theta > 360.0f)planets[i].theta -= 360.0f;

	}	
	x = moon->x_coordinate - 1.5;
	z = moon->z_coordinate;
	distance = moon->distance_from_center;
	second_distance = 0.7 * distance;
	if (z >= 0 && x < distance) {
		moon->plusX = true;
	}
	else {
		moon->plusX = false;

	}
	if (moon->plusX == true) {
		x += 0.01 * speed * moon->aroundSunSpeed;
		if (x >= distance) {
			moon->x_coordinate = 2 * distance - x;
			moon->z_coordinate = get_z_coordinate(moon, false);
			moon->x_coordinate += 1.5;
		}
		else if (x == distance) {
			moon->x_coordinate -= 0.01 * speed * moon->aroundSunSpeed;
			moon->z_coordinate = get_z_coordinate(moon, false);
			moon->x_coordinate += 1.5;
		}
		else {
			moon->x_coordinate = x;
			moon->z_coordinate = get_z_coordinate(moon, true);
			moon->x_coordinate += 1.5;
		}
	}
	else {
		x -= 0.01 * speed * moon->aroundSunSpeed;
		if (x <= -distance) {
			moon->x_coordinate = -2 * distance - x;
			moon->z_coordinate = get_z_coordinate(moon, true);
			moon->x_coordinate += 1.5;
		}
		else if (x == -distance) {
			moon->x_coordinate += 0.01 * speed * moon->aroundSunSpeed;
			moon->z_coordinate = get_z_coordinate(moon, true);
			moon->x_coordinate += 1.5;
		}
		else {
			moon->x_coordinate = x;
			moon->z_coordinate = get_z_coordinate(moon, false);
			moon->x_coordinate += 1.5;
		}
	}
	//ruch obrotowy
	moon->theta += 3.0 * speed * moon->aroundYourselfSpeed;
	if (moon->theta > 360.0f)moon->theta -= 360.0f;
	sun->theta += 3.0 * speed * sun->aroundYourselfSpeed;
	if (sun->theta > 360.0f)sun->theta -= 360.0f;
	glutPostRedisplay();
}
float random_x(float range) {
	int x;
	if ((int)range == 0)x = 0;
	else
	x = rand() % ((int)range);
	int y = rand() % 10001;
	float z = 1.0 * x + y / 10000.0f;
	if (z > range)z = range;
	if (rand() % 2 == 1)z *= -1.0;
	return z;
}
void initialize(Planet* p, Sun* s) {
	//Odleg³oœci od s³oñca
	p[0].distance_from_center = 7.00f;
	p[1].distance_from_center = 10.00f;
	p[2].distance_from_center = 14.00f;
	p[3].distance_from_center = 18.00f;
	p[4].distance_from_center = 21.60f;
	p[5].distance_from_center = 30.00f;
	p[6].distance_from_center = 38.00f;
	p[7].distance_from_center = 46.00f;
	moon->distance_from_center = 1.30f;
	//Po³ozenie planet
	p[0].x_coordinate = random_x(p[0].distance_from_center);
	p[0].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[0].z_coordinate = get_z_coordinate(&(p[0]), true);
	else p[0].z_coordinate = get_z_coordinate(&(p[0]), false);
	p[0].x_coordinate += 1.5;
	p[1].x_coordinate = random_x(p[1].distance_from_center);
	p[1].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[1].z_coordinate = get_z_coordinate(&(p[1]), true);
	else p[1].z_coordinate = get_z_coordinate(&(p[1]), false);
	p[1].x_coordinate += 1.5;
	p[2].x_coordinate = random_x(p[2].distance_from_center);
	p[2].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[2].z_coordinate = get_z_coordinate(&(p[2]), true);
	else p[2].z_coordinate = get_z_coordinate(&(p[2]), false);
	p[2].x_coordinate += 1.5;
	p[3].x_coordinate = random_x(p[3].distance_from_center);
	p[3].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[3].z_coordinate = get_z_coordinate(&(p[3]), true);
	else p[3].z_coordinate = get_z_coordinate(&(p[3]), false);
	p[3].x_coordinate += 1.5;
	p[4].x_coordinate = random_x(p[4].distance_from_center);
	p[4].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[4].z_coordinate = get_z_coordinate(&(p[4]), true);
	else p[4].z_coordinate = get_z_coordinate(&(p[4]), false);
	p[4].x_coordinate += 1.5;
	p[5].x_coordinate = random_x(p[5].distance_from_center);
	p[5].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[5].z_coordinate = get_z_coordinate(&(p[5]), true);
	else p[5].z_coordinate = get_z_coordinate(&(p[5]), false);
	p[5].x_coordinate += 1.5;
	p[6].x_coordinate = random_x(p[6].distance_from_center);
	p[6].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[6].z_coordinate = get_z_coordinate(&(p[6]), true);
	else p[6].z_coordinate = get_z_coordinate(&(p[6]), false);
	p[6].x_coordinate += 1.5;
	p[7].x_coordinate = random_x(p[7].distance_from_center);
	p[7].y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		p[7].z_coordinate = get_z_coordinate(&(p[7]), true);
	else p[7].z_coordinate = get_z_coordinate(&(p[7]), false);
	p[7].x_coordinate += 1.5;
	moon->x_coordinate = random_x(moon->distance_from_center);
	moon->y_coordinate = 0.0f;
	if (rand() % 2 == 0)
		moon->z_coordinate = get_z_coordinate(moon, true);
	else moon->z_coordinate = get_z_coordinate(moon, false);
	moon->x_coordinate += 1.5;
	//ustawienie promieni planet
	p[0].radius = 0.8f;
	p[1].radius = 0.8f;
	p[2].radius = 0.8f;
	p[3].radius = 0.8f;
	p[4].radius = 1.2f;
	p[5].radius = 1.2f;
	p[6].radius = 1.0f;
	p[7].radius = 1.0f;
	moon->radius = 0.1f;
	//ustawienie prêdkosci planet
	p[0].aroundSunSpeed = 70.0f;
	p[1].aroundSunSpeed = 50.00f;
	p[2].aroundSunSpeed = 28.000f;
	p[3].aroundSunSpeed = 12.000f;
	p[4].aroundSunSpeed = 7.20f;
	p[5].aroundSunSpeed = 5.0f;
	p[6].aroundSunSpeed = 5.42f;
	p[7].aroundSunSpeed = 2.3f;
	moon->aroundSunSpeed = 0.100f;
	p[0].aroundYourselfSpeed = 0.75f;
	p[1].aroundYourselfSpeed = 1.5f;
	p[2].aroundYourselfSpeed = 15.0f;
	p[3].aroundYourselfSpeed = 14.5f;
	p[4].aroundYourselfSpeed = 25.0f;
	p[5].aroundYourselfSpeed = 23.0f;
	p[6].aroundYourselfSpeed = 19.0f;
	p[7].aroundYourselfSpeed = 18.0f;
	moon->aroundYourselfSpeed = 1.0f;
	//ustawieenie pocz¹tkowego kata obrotu planety
	p[0].theta = 20.0f;
	p[1].theta = 20.0f;
	p[2].theta = 20.0f;
	p[3].theta = 20.0f;
	p[4].theta = 20.0f;
	p[5].theta = 20.0f;
	p[6].theta = 20.0f;
	p[7].theta = 20.0f;
	moon->theta = 20.0f;
	//ustawienie danych s³oñca
	s->radius = 3.0f;
	s->l_a[0] = 0.1f;
	s->l_a[1] = 0.1f;
	s->l_a[2] = 0.1f;
	s->l_a[3] = 1.0f;
	s->l_d[0] = 1.0f;
	s->l_d[1] = 1.0f;
	s->l_d[2] = 1.0f;
	s->l_d[3] = 1.0f;
	s->l_s[0] = 1.0f;
	s->l_s[1] = 1.0f;
	s->l_s[2] = 1.0f;
	s->l_s[3] = 1.0f;
	s->aroundYourselfSpeed = 1.0f;
	s->theta = 0.0f;
	//ustawienie danych materia³u
	mat.k_a[0] = 0.4f;
	mat.k_a[1] = 0.4f;
	mat.k_a[2] = 0.4f;
	mat.k_a[3]	= 1.0f;
	mat.k_d[0] = 1.0f;
	mat.k_d[1] = 1.0f;
	mat.k_d[2] = 1.0f;
	mat.k_d[3] = 1.0f;
	mat.k_s[0] = 1.0f;
	mat.k_s[1] = 1.0f;
	mat.k_s[2] = 1.0f;
	mat.k_s[3] = 1.0f;
	mat.shininess_factor  = 20.0f;
	
	s->att_constant = 1.0f;
	s->att_linear = 0.05f;
	s->att_quadratic = 0.001f;

}
void dealocate_memory(Planet* p, Sun* s) {
	delete[] p;
	delete s;
	delete moon;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < N; j++) {
			delete[] points[i][j];
		}
	}
	for (int i = 0; i < 9; i++) {
		delete[] points[i];
	}
	delete[] points;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < N; j++) {
			delete[] normal_vectors[i][j];
		}
	}
	for (int i = 0; i < 9; i++) {
		delete[] normal_vectors[i];
	}
	delete[] normal_vectors;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			delete[] texture_coordinates[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		delete[] texture_coordinates[i];
	}
	delete[] texture_coordinates;
}
void Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		x_pos_old = x;			// przypisanie aktualnie odczytanej pozycji kursora
								// jako pozycji poprzedniej
		y_pos_old = y;			// przypisanie aktualnie odczytanej pozycji kursora
								// jako pozycji poprzedniej
		statusL = 1;			// wciêniêty zosta³ lewy klawisz myszy
	}
	else

		statusL = 0;			// nie zosta³ wciêniêty lewy klawisz

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		y_pos_old = y;			// przypisanie aktualnie odczytanej pozycji kursora
								// jako pozycji poprzedniej
		statusR = 1;			// wciœniêty zosta³ prawy klawisz myszy
	}
	else statusR = 0;			// nie zosta³ wciêniêty prawy klawisz
}
void MouseMotion(int x, int y) {
	delta_x = x - x_pos_old;		// obliczenie ró¿nicy po³o¿enia kursora myszy

	x_pos_old = x;					// podstawienie bie¿¹cego po³o¿enia jako poprzednie

	delta_y = y - y_pos_old;		// obliczenie ró¿nicy po³o¿enia kursora myszy

	y_pos_old = y;					// podstawienie bie¿¹cego po³o¿enia jako poprzednie

	glutPostRedisplay();			// przerysowanie obrazu sceny
}
void create_sphere_tab() {
	points = new point3**[10];
	for (int i = 0; i < 10; i++) {
		points[i] = new point3 * [N];
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < N; j++) {
			points[i][j] = new point3[N];
		}
	}
	normal_vectors = new point3 * *[10];
	for (int i = 0; i < 10; i++) {
		normal_vectors[i] = new point3 * [N];
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < N; j++) {
			normal_vectors[i][j] = new point3[N];
		}
	}
	//obliczanie wspó³rzêdnych punktów sfery i wektorów normalnych do punktów
	float u, v;
	for (int k = 0; k < 8;k++) {
		for (int i = 0; i < N; i++) {
			u = 1.0* i/(N-1);
			for (int j = 0; j < N; j++) {			//planety
				v = 1.0 * j/(N-1);
				points[k][i][j][0] = planets[k].radius * sinf(M_PI * u) * cosf(2 * M_PI * v);
				points[k][i][j][1] = planets[k].radius * sinf(M_PI * u) * sinf(2 * M_PI * v);
				points[k][i][j][2] = planets[k].radius * cosf(M_PI * u);
				normal_vectors[k][i][j][0] = sinf(M_PI * u) * cosf(2 * M_PI * v);
				normal_vectors[k][i][j][1] = sinf(M_PI * u) * sinf(2 * M_PI * v);
				normal_vectors[k][i][j][2] = cosf(M_PI * u);

			}
		}
	}
	for (int i = 0; i < N; i++) {
		u = 1.0 * i / (N - 1);
		for (int j = 0; j < N; j++) {		//s³oñce i ksiê¿yc
			v = 1.0 * j / (N - 1);
			points[8][i][j][0] = sun->radius * sinf(M_PI * u) * cosf(2 * M_PI * v);
			points[8][i][j][1] = sun->radius * sinf(M_PI * u) * sinf(2 * M_PI * v);
			points[8][i][j][2] = sun->radius * cosf(M_PI * u);
			normal_vectors[8][i][j][0] = sinf(M_PI * u) * cosf(2 * M_PI * v);
			normal_vectors[8][i][j][1] = sinf(M_PI * u) * sinf(2 * M_PI * v);
			normal_vectors[8][i][j][2] = cosf(M_PI * u);
			points[9][i][j][0] = moon->radius * sinf(M_PI * u) * cosf(2 * M_PI * v);
			points[9][i][j][1] = moon->radius * sinf(M_PI * u) * sinf(2 * M_PI * v);
			points[9][i][j][2] = moon->radius * cosf(M_PI * u);
			normal_vectors[9][i][j][0] = sinf(M_PI * u) * cosf(2 * M_PI * v);
			normal_vectors[9][i][j][1] = sinf(M_PI * u) * sinf(2 * M_PI * v);
			normal_vectors[9][i][j][2] = cosf(M_PI * u);
		}
	}
	//teksturowanie
	texture_coordinates = new GLfloat * *[N];
	for (int i = 0; i < N; i++) {
		texture_coordinates[i] = new GLfloat * [N];
	}
	for (int i = 0; i < N; i++) {

		for (int j = 0; j < N; j++) {
			texture_coordinates[i][j] = new GLfloat[2];
		}
	}
	GLfloat step = 1.0 / N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N/2; j++) {
			texture_coordinates[i][j][0] = i * step;
			texture_coordinates[i][j][1] = j * step;
		}
		for (int j = N/2; j < N; j++) {
			texture_coordinates[i][j][0] = i * step;
			texture_coordinates[i][j][1] = j * step;
		}
	}
	for (int i = N/2; i < N; i++) {
		for (int j = 0; j < N / 2; j++) {
			texture_coordinates[i][N - 1 - j][0] = i * step;
			texture_coordinates[i][N - 1 - j][1] = j * step;
		}
		for (int j = N / 2; j < N; j++) {
			texture_coordinates[i][j][0] = i * step;
			texture_coordinates[i][j][1] = j * step;
		}
	}
}

int main(void) {
	srand(time(NULL));
	planets = new Planet[8];
	initialize(planets, sun);
	create_sphere_tab();
	cout << "=============================================================" << endl;
	cout << "Witaj w programie wyswietlajacym animacje ukladu slonecznego." << endl;
	cout << "Sterowanie:" << endl;
	cout << "- wcisniety lewy klawisz myszy- zmiana kata elewacji polozenia obserwatora (ruch pionowy myszka)," << endl;
	cout << "zmiana kata azymutu polozenia obserwatora(ruch poziomy myszka)" << endl;
	cout << "- wcisniety prawy klawisz myszy- zmiana odleglosci obserwatora od obiektu(ruch pionowy myszka)" << endl;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);		//Ustawienie trybu wyœwietlania
	glutInitWindowSize(700, 700);									//Ustawienie wielkoœci okna
	glutCreateWindow("Mini projekt- animacja uk³adu s³onecznego");	//Stworzenie okna

	glutDisplayFunc(RenderScene);									//Ustawienie, ¿e funkcja RenderScene bêdzie przerysowywaæ okno

	glutReshapeFunc(ChangeSize);									//Ustawienie, ¿e funkcja ChangeSize bêdzie obs³ugiwaæ zmiany wielkoœci okna

	glutIdleFunc(spinnPlanets);										//Ustawienie, ¿e funkcja spinnPlanets bêdzie obs³ugiwaæ poruszanie siê planet

	glutMouseFunc(Mouse);											//Ustawienie, ¿e funkcja Mouse bêdzie obs³ugiwaæ klikniêcia myszk¹

	glutMotionFunc(MouseMotion);									//Ustawienie, ¿e funkcja MouseMotion bêdzie obs³ugiwaæ poruszanie myszk¹

	MyInit();														//Wykonanie inicjalizacji przed przyst¹pieniem do renderowania

	glEnable(GL_DEPTH_TEST);										//W³¹czenie mechanizmu usuwania powierzchni niewidocznych

	glutMainLoop();													//Pêtla g³ówna programu
	dealocate_memory(planets, sun);
	return 0;
}