#include <iostream>
#include "fstream"
#include "stdio.h"
#include "string"
#include "windows.h"

using namespace std;

void print()
{
	//zmienna przechowująca kod klawisza <ESC>
	char esc = 27;
	//nasz znak- litera Ę
	int naszZnak[] = { 254,146,146,146,147 };

	fstream lpt;
	string port = "LPT3";
	//Otwarcie portu LPT3
	lpt.open(port, ios::out);
	//Sprawdzenie, czy port jest otwarty
	if (lpt.is_open())
	{
		//Zdefiniowanie tekstu do wydrukowania
		string tekst = " POLITECHNIKA WROCLAWSKA ZNAJDU~ SI~ NA WYBRZEZU WYSPIANSKIEGO ";

		//Ustawienie lewego marginesu na 0.
		lpt << esc << "l" << char(0);
		//Ustawienie rozmiaru znaków na normalną wielkość
		lpt << esc << "h" << char(0);

		//Wybór czcionki
		// Polecenie cout<<esc<<"x1" powoduje zmianę z draft quality na letter quality
		lpt << esc << "k0" << esc << "x1" << "Roman: " << tekst << endl;
		lpt << esc << "k1" << esc << "x1" << "Sanserif: " << tekst << endl;
		lpt << esc << "k2" << esc << "x1" << "Courier: " << tekst << endl;
		lpt << esc << "k3" << esc << "x1" << "Prestige: " << tekst << endl;
		lpt << esc << "k4" << esc << "x1" << "Script: " << tekst << endl;

	   //Zmiana wielkości interlinii
		lpt << esc << "0" << esc << "k0" << esc << "x1" << "Roman 1/8: " << tekst << endl;
		lpt << esc << "1" << esc << "k0" << esc << "x1" << "Roman 7/60: " << tekst << endl;
		lpt << esc << "2" << esc << "k0" << esc << "x1" << "Roman 1/6: " << tekst << endl;
		lpt << esc << "+" << char(80) << esc << "k0" << esc << "x1" << "Roman 80/360: " << tekst << endl;

		//powrót do interlinii 1/8
		lpt << esc << "0" << esc << "k0" << esc << "x1";

		//ustawienie marginesów
		lpt << esc << "l" << char(15) << "Margines 15 :" << tekst << endl;
		lpt << esc << "l" << char(50) << "Margines 50 :" << tekst << endl;
		
		//Ustawienie marginesu
		lpt << esc << "l" << char(40);

		//Wczytanie pamięci ROM do RAM
		lpt << esc << ":" << char(0) << char(0) << char(0);
		
		//Zmiana z draft quality na letter quality
		lpt << esc << "x1";

		//Zdefiniowanie znaku "~" do zamiany
		lpt << esc << "&" << char(0);		
		lpt << char(126) << char(126);	//126- kod ASCII znaku "~"

		//Zdefiniowanie rozmiaru tablicy bajtów nowego znaku
		lpt << char(1) << char(5) << char(2);

		//Wczytanie znaku jako ciąg bajtów
		for (int i = 0; i < 5 * 1; i++)
			lpt << char(naszZnak[i]);

		//wybranie pobranego znaku
		lpt << esc << "%" << char(1);
		lpt << char(126);

		//Wydrukowanie nowego znaku
		lpt << tekst << endl;

		//Zamknięcie portu LPT3
		lpt.close();
	}
}
int main()
{
	print();
}

