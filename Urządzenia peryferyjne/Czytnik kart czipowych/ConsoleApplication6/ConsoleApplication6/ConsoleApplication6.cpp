#define MAX_READER_NAME_SIZE 40

// w systemie Windows nie ma definicji maksymalnego rozmiaru ATR
# ifndef MAX_ATR_SIZE
   #define MAX_ATR_SIZE 33
#endif
#include<winscard.h>		//Biblioteka służąca do  komunikacji z kartą
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<iostream>

using namespace std;


int main(int argc, char **argv)
{
	//Kontekst połączenia do zarządcy zasobów
		SCARDCONTEXT hContext;
	//Uchwyt połączenia do czytnika
		SCARDHANDLE hCard;
	//Zmienna przechowująca stan czytnika
		SCARD_READERSTATE_A rgReaderStates[1];
	//Pomocnicze zmienne(długosci buforów, stan czytnika, protokół) ´
		 DWORD dwReaderLen, dwState, dwProt, dwAtrLen;
		DWORD dwPref, dwReaders, dwRespLen;
	//Bufor na nazwę czytnika
		LPSTR pcReaders;
	//Bufor na listę czytników
		 LPSTR mszReaders;
	//Bufor na ATR
		BYTE pbAtr[MAX_ATR_SIZE];
	//Bufory na odpowiedzi z karty
		BYTE pbResp[30];
		BYTE pbResp1[30];
		BYTE pbResp2[200];
	//Pomocnicze zmienne
		LPCSTR mszGroups;
		LONG rv;
		int i, p, iReader;
		int iReaders[16];

	//Nawiązanie połączenia z lokalnym zarządcą zasobów
		printf("SCardEstablishContext : ");
		rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
		if(rv != SCARD_S_SUCCESS)
		{
			printf("failed\n");
			return -1;
		}
		else printf("success\n");
	//Pobranie wielkosć ciągu, jaki będzie potrzebny na listę
	//dostępnych czytników w systemie
		mszGroups = 0;
		rv = SCardListReaders(hContext, mszGroups, 0, &dwReaders);
		printf("SCardListReaders : ");
		if(rv != SCARD_S_SUCCESS)
		{
			SCardReleaseContext(hContext);
			printf("failed\n");
			return -1;
		}
		else printf("success\n");
	//Alokacja pamięci
		mszReaders = (LPSTR)malloc(sizeof(char) * dwReaders);
	//Pobranie listy czytników
		printf("SCardListReaders : ");
		rv = SCardListReaders(hContext, mszGroups, mszReaders, &dwReaders);

		if(rv != SCARD_S_SUCCESS)
		{	
			SCardReleaseContext(hContext);
			free(mszReaders);
			printf("failed\n");
			return -1;
		}
		else printf("success\n");
	//Wydruk listy znalezionych czytników
		p = 0;
		for (i = 0; i < dwReaders -1; ++i)
		{
			iReaders[++p] = i;
			printf("Reader %02d: %s\n", p, &mszReaders[i]);
	//Przesunięcie bufora do kolejnej nazwy czytnika
		while (mszReaders[++i] != '\0');
		}
	//Wybór czytnika do dalszych operacji
		do
		{
			printf("Select reader : ");
			scanf("%d", &iReader);

		} while (iReader > p || iReader <= 0);
	//Wypełnienie struktury stanu czytnika(nazwa czytnika i jego stan)
		rgReaderStates[0].szReader = &mszReaders[iReaders[iReader]];
		rgReaderStates[0].dwCurrentState = SCARD_STATE_EMPTY;
		printf("Insert card...\n");
	//Oczekiwanie na zmianę stanu czytnika(włożenie karty)
		printf("SCardGetStatusChange : ");
		rv = SCardGetStatusChange(hContext, INFINITE, rgReaderStates, 1);
		printf("[%02d]\n", rv);
	//Nawiązanie połączenia z czytnikiem
		printf("SCardConnect : ");
		rv = SCardConnect(hContext, &mszReaders[iReaders[iReader]],
		SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
		&hCard, &dwPref);
	
		if(rv != SCARD_S_SUCCESS)
		{
			SCardReleaseContext(hContext);
			free(mszReaders);
			printf("failed\n");
			return -1;
		}else printf("success\n");
	//Sprawdzenie stanu karty w czytniku
		printf("SCardStatus : ");
		dwReaderLen = MAX_READER_NAME_SIZE;
		pcReaders = (LPSTR)malloc(sizeof(char) * MAX_READER_NAME_SIZE);
		rv = SCardStatus(hCard, pcReaders, &dwReaderLen, &dwState,
		&dwProt, pbAtr, &dwAtrLen);
		if(rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			free(mszReaders);
			free(pcReaders);
			printf("failed\n");
			return -1;
		}else printf("success\n");

	// wydruk ATR
		for (i = 0; i < dwAtrLen; i++)
		{
			printf("%02X ", pbAtr[i]);	
		}
		printf("\n");
		free(pcReaders);
	//Rozpoczęcie transakcji z kartą
		printf("SCardBeginTransaction : ");
		rv = SCardBeginTransaction(hCard);
		if(rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failed\n");
			free(mszReaders);
			return -1;
		}else printf("success\n");
	//Przesłanie do karty komendy GET CHALLENGE
		printf("SCardTransmit : ");
		BYTE COMMAND[5]= { 0x00 , 0x84 , 0x00 , 0x00 , 0x08 };
		//string x;
		//int number;
		//for (int i = 0; i < 5; i++) {		//Nie działa
		//	number = 0;
		//	cin >> x;
		//	number += 16 *int(x[0]);
		//	number += int(x[1]);
		//	//cout << number << endl;
		//	COMMAND[i] = byte(number);
		//}
		rv = SCardTransmit(hCard, SCARD_PCI_T0, COMMAND,
		5, NULL, pbResp, &dwRespLen);
		if(rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failed\n");
			free(mszReaders);
			return -1;	
		}else printf("success\n");

		BYTE COMMAND2[7] = { 0xA0,0xA4,0x00,0x00,0x02,0x2d,0xe2 };
		dwRespLen = 30;
		rv = SCardTransmit(hCard, SCARD_PCI_T0, COMMAND2,
		7, NULL, pbResp, &dwRespLen);
		if (rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("faileds\n");
			free(mszReaders);
			return -1;
		}else printf("success\n");

		printf("Response\n");
		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp[i]);
		}

		dwRespLen = 30;
		BYTE COMMAND3[7] = { 0xA0, 0xA4, 0x00, 0x00, 0x02, 0x7F, 0x10 };
		dwRespLen = 30;
		rv = SCardTransmit(hCard, SCARD_PCI_T0, COMMAND3,
		7, NULL, pbResp, &dwRespLen);
		if(rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failedq\n");
			free(mszReaders);
			return -1;
		}else printf("success\n");

		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp1[i]);
		}
		printf("Response APDU : ");
	//Wydruk odpowiedzi karty
		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp1[i]);
		}
		printf("\n");
		dwRespLen = 178;

		BYTE COMMAND4[5] = { 0xA0,0xB2,0x9f,0x10,0xB0 };
		rv = SCardTransmit(hCard, SCARD_PCI_T0, COMMAND4,
		5, NULL, pbResp2, &dwRespLen);
		if(rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failedq\n");
			free(mszReaders);
			return -1;
		}else printf("success\n");

		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp2[i]);
		}

		printf("Response APDU : ");
	//Wydruk odpowiedzi karty
		for (i = 0; i < dwRespLen; i++)
		{
			printf("%02X ", pbResp2[i]);
		}
		printf("\n");

	//Zakończenie transakcji z kartą
		printf("SCardEndTransaction : ");
		rv = SCardEndTransaction(hCard, SCARD_LEAVE_CARD);
		if(rv != SCARD_S_SUCCESS)
		{
			SCardDisconnect(hCard, SCARD_RESET_CARD);
			SCardReleaseContext(hContext);
			printf("failed\n");
			free(mszReaders);
			return -1;
		}else printf("success\n");
	//Rozłączenie z czytnikiem
		printf("SCardDisconnect : ");

		rv = SCardDisconnect(hCard, SCARD_UNPOWER_CARD);
		if(rv != SCARD_S_SUCCESS)
		{
		SCardReleaseContext(hContext);
		printf("failed\n");
		free(mszReaders);
		return -1;
		}
		else printf("success\n");
	//Odłączenie od zarządcy zasobów PC / SC
		printf("SCardReleaseContext : ");
		rv = SCardReleaseContext(hContext);

		if(rv != SCARD_S_SUCCESS)
		{
			printf("failed\n");
			free(mszReaders);
			return -1;
		}else printf("success\n");
	//Zwolnienie pamięci
		free(mszReaders);
		return 0;
		}