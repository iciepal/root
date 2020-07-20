/*
***************************************************************************
Struktura pliku symulacji Bina_out1.txt
Column					Description
1								Event number
2								Particle type: 1-neutron, 2-proton, 3-deuteron
3								Detection in MWPC: 0-no, 1-yes
4								Detection in dE: 0-no signal, 1-one detector fired, 2-two detectors fired (cross-over)
5								Detection in E: 0-no signal, 1-one detector fired, 2-two detectors fired (cross-over)
6								Position in MWPC along x-axis (second plane of detection)
7								Position in MWPC along y-axis (second plane of detection)
8								dE energy deposition
9								dE detector number
10							Energy deposition in second dE detector, in case of cross-over
11							Second dE number, in case of cross-over
12							E detector energy deposition
13							E detector number, (1-149 for Backward Ball, larger than 199 for the wall)
14							Second E detector energy deposition, in case of cross-over
15							Second E detector number, in case of cross-over
************************************************************************
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "time.h"

using namespace std;

int ZapisDoDrzewa() {
	clock_t fbegin;
	fbegin = clock(); //Start clock

	//Definiujemy ile różnych konfiguracji kątowych będziemy wczytywać, na razie tylko 1
	int theta1[]={19}; 	//Kąt Theta pierwszego protonu
	int theta2[]={23};	//Kąt Theta drugiego protonu

	for(int konf=0;konf<sizeof(theta1)/sizeof(*theta1);konf++){		//tutaj iterujemy po każdej konfiguracji

			//Tworzymy plik rootowy do którego będziemy przepisywać symulacje
			char file1[200];
			sprintf(file1,"./wyniki/Raw_Sim_ppn_%d_%d.root",theta1[konf],theta2[konf]);
			TFile *OutputFile = new TFile(file1,"RECREATE");		//parametr RECREATE tworzy nowy plik, jak istnieje to go nadpisuje
			if(OutputFile) 	cout <<"Otwarto plik: "<<file1<<"\n";

			TTree *Raw_Tree=new TTree("Raw","Surowe_wyniki");		//inicjalizacja drzewa o nazwie "Raw" i Title "Surowe_wyniki"

			char branchName[10];
			char leafType[10];
			int column=15;		//Tyle kolumn na plik symulacyjny
			Float_t wiersz[column];		//tablica przechowująca pojedynczy wiersz symulacji

			for (int i = 0; i < column; i++)
				 {
								//inicjalizujemy gałęzie w drzewie, jedna gałąź na jedną wartość z symulacji
				    		sprintf(branchName, "col%d", i);	//nazwa gałęzi
								Raw_Tree->Branch(branchName, &wiersz[i]);	//Podajemy nazwę i adres zmiennej z której bierzemy wartość

								// inna inicjalizacja, dodajemy jeszcze typ zmiennej, przydatne gdy w gałęzi chcemy dać tablicę
								//		sprintf(leafType, "col%d/f", i);	//typ zmiennej w danej gałęzi
								//		Raw_Tree->Branch(branchName, &wiersz[i], leafType);
				}

				char file2[200];
				sprintf(file2,"./symulacje/%d_%d_ppn/Bina_out1.dat",theta1[konf], theta2[konf]);
				ifstream stream1;
				stream1.open(file2); //Inicjalizujemy ifstream ze ścieżką do pliku z symulacjami

				if(stream1.good()){ //warto pamiętać o sprawdzeniu czy plik działa
					cout<<"Czytam plik symulacji: "<<file2<<"\n";
					while(!stream1.eof()) {

						for (int i = 0; i < column; i++){
							stream1>>wiersz[i];		//zapisujemy po kolei po jeden wiersz symulacji
						}
						Raw_Tree->Fill();		//I uzupełniamy drzewo, w tym momencie wartości z wiersz[] jest zapisywany w drzewie
					}
					stream1.close();
				}
				else{
				cout<<"File Doesnt Exist\n";
				}

				Raw_Tree->Print(); //Mozna wypisać zawartość drzewa

				OutputFile->Write();	//Zapisujemy wszystkie otwarte obiekty w pliku rootowym (drzewa, histogramy itp)
				OutputFile->Close();	//Zamykamy plik, Powinno się zamykać automatycznie przy wywołaniu destruktora ale kto tam wie..

		}
	cout<<"koniec czytania symulacji\n";
	clock_t fend;
	fend = clock();
	Double_t time_spent;
	time_spent = (Double_t)(fend - fbegin) / CLOCKS_PER_SEC;
	printf("Czas wykonywania programu =%f s.\n",time_spent);
	return 0;
}
