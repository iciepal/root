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
#include "TH2.h"
#include "TH1.h"
#include "TCanvas.h"

using namespace std;
#define Pi_180 0.01745329251994
	TCanvas *c1;
	float fZ=297;

int CzytanieDrzewa() {

	clock_t fbegin;
	fbegin = clock(); //Start clock

	//Definiujemy ile różnych konfiguracji kątowych będziemy wczytywać, na razie tylko 1
	int theta1[]={19}; 	//Kąt Theta pierwszego protonu
	int theta2[]={23};	//Kąt Theta drugiego protonu

	for(int konf=0;konf<sizeof(theta1)/sizeof(*theta1);konf++){		//tutaj iterujemy po każdej konfiguracji

	char file1[200];

	//Otwieramy plik rootowy z symulacjami (z poprzedniego cwiczenia)
	sprintf(file1,"./wyniki/Raw_Sim_ppn_%d_%d.root",theta1[konf],theta2[konf]);
	TFile *RawFile= new TFile(file1,"READ");
	TTree *Raw_Tree=(TTree*)RawFile->Get("Raw");		//Tak dobieramy się do obiektów w pliku rootowym
	if(RawFile) cout<<"Otworzono RawFile\n";
	//Albo Tak
	//TTree *Raw_Tree;
	//RawFile->GetObject("Raw",Raw_Tree);

	//Możemy teraz przypisać wartości z gałęzi do jakiś zmiennych, np tak jak poprzednio do wiersz[]
	const int column=15;
	Float_t wiersz[column];
	char branchName[10];
	for (int i = 0; i < column; i++)
		 {
						//inicjalizujemy gałęzie w drzewie, jedna gałąź na jedną wartość z symulacji
						sprintf(branchName, "col%d", i);	//nazwa gałęzi
						Raw_Tree->SetBranchAddress(branchName, &wiersz[i]);
						//Przypisujemy danej gałęzi adres jakiejś zmiennej, jeszcze nic nie jest odczytywane
		}

		//Tworzymy nowy plik rootowy, w ktorym przechowamy przesortowane symulacje
	char file2[200];
	sprintf(file2,"./wyniki/Sorted_Sim_ppn_%d_%d.root",theta1[konf],theta2[konf]);
	TFile *SimFile= new TFile(file2,"RECREATE");
	TTree *Sorted_Tree=new TTree("Sor","Posortowane_czastki");
	if(SimFile) cout<<"Utworzono SimFile\n";

	//Trochę zmiennych
	ULong64_t Entry;
	Double_t P1Type;
	Double_t P2Type;
	Double_t P3Type;
	Double_t En1;
	Double_t En2;
	Double_t En3;
	Int_t E1;
	Int_t E2;
	Int_t E3;
	Int_t dE1;
	Int_t dE2;
	Int_t dE3;
	Double_t X1;
	Double_t X2;
	Double_t X3;
	Double_t Y1;
	Double_t Y2;
	Double_t Y3;
	Double_t Th1;
	Double_t Th2;
	Double_t Th3;
	Double_t Phi1;
	Double_t Phi2;
	Double_t Phi3;
	Double_t dPhi;
	//Inicjalizacja gałęzi w nowym drzewie

	Sorted_Tree->Branch("Entry",&Entry,"Entry/l");
	Sorted_Tree->Branch("P1Type",&P1Type,"P1Type/D");
	Sorted_Tree->Branch("P2Type",&P2Type,"P2Type/D");
	Sorted_Tree->Branch("P3Type",&P3Type,"P3Type/D");
	Sorted_Tree->Branch("E1",&E1,"E1/I");
	Sorted_Tree->Branch("E2",&E2,"E2/I");
	Sorted_Tree->Branch("E3",&E3,"E3/I");
	Sorted_Tree->Branch("dE1",&dE1,"dE1/I");
	Sorted_Tree->Branch("dE2",&dE2,"dE2/I");
	Sorted_Tree->Branch("dE3",&dE3,"dE3/I");
	Sorted_Tree->Branch("En1",&En1,"En1/D");
	Sorted_Tree->Branch("En2",&En2,"En2/D");
	Sorted_Tree->Branch("En3",&En3,"En3/D");
	Sorted_Tree->Branch("X1",&X1,"X1/D");
	Sorted_Tree->Branch("X2",&X2,"X2/D");
	Sorted_Tree->Branch("X3",&X3,"X3/D");
	Sorted_Tree->Branch("Y1",&Y1,"Y1/D");
	Sorted_Tree->Branch("Y2",&Y2,"Y2/D");
	Sorted_Tree->Branch("Y3",&Y3,"Y3/D");
	Sorted_Tree->Branch("Phi1",&Phi1,"Phi1/D");
	Sorted_Tree->Branch("Phi2",&Phi2,"Phi2/D");
	Sorted_Tree->Branch("Phi3",&Phi3,"Phi3/D");
	Sorted_Tree->Branch("Th1",&Th1,"Th1/D");
	Sorted_Tree->Branch("Th2",&Th2,"Th2/D");
	Sorted_Tree->Branch("Th3",&Th3,"Th3/D");
	Sorted_Tree->Branch("dPhi",&dPhi,"dPhi/D");

	//Trochę histogramów kontrolnych
	TH2F *E_E_hist= new TH2F("E_E_hist","E1 vs E2",200,1,201,200,1,201);
	TH2F *MWPC= new TH2F("MWPC","Polozenie X Y",400,-200,200,400,-200,200);
	TH1F *dPhi_hist= new TH1F("dPhi_hist","Phi wzgledne czastek",180,0,180);
	TH1F *Th1_hist= new TH1F("Th1_hist","histogram Th1",100,10,40);
	TH1F *Th2_hist= new TH1F("Th2_hist","histogram Th2",100,10,40);

	Int_t last_ev_num=0;	//Zmienna do zapamiętywania numeru eventu
	Int_t isPierwsza=0; //Zmienna do zapamietywania ktora to czastka
	ULong64_t Entries;
	Entries=Raw_Tree->GetEntries();
	cout<<"Entries="<<Entries<<"\n";
	for(ULong64_t event=0;event<Entries;event++){
		Raw_Tree->GetEntry(event);	//W tym momencie pobieramy wartości z drzewa Raw_Tree i wkładamy do tablicy wiersz[]
		if(wiersz[0]>last_ev_num){
			//Jeżeli pole wiersz[0] (numer eventu) jest większe od poprzedneigo zapamiętanego eventu
			//To wchodzimy tutaj i zapisujemy nowe drzewo i uzupełniamy histogramy
			dPhi=std::abs(Phi1-Phi2);
			if(dPhi>180) dPhi=360-dPhi;	//Obliczenie kąta względnego dPhi pomiędzy cząstkami 1 i 2

			Sorted_Tree->Fill();	//Wypełnianie drzewa i histogramów
			dPhi_hist->Fill(dPhi);
			E_E_hist->Fill(En1,En2);
			MWPC->Fill(X1,Y1);
			MWPC->Fill(X2,Y2);
			Th1_hist->Fill(Th1);
			Th2_hist->Fill(Th2);

		}

		if((int)wiersz[1]==2){ //Protony, wiersz[1] przechowuje typ cząstki, 1-neutron 2-proton, 3-deuteron

				if(isPierwsza==0){	//Pierwszy proton
					Entry=wiersz[0];	//Zapisujemy wartości ze starego do nowego drzewa
					P1Type=wiersz[1];
					dE1=wiersz[8];
					E1=wiersz[12];
					En1=wiersz[11];
					X1=wiersz[5];
					Y1=wiersz[6];
					Th1=atan2f(sqrt(X1*X1+Y1*Y1),fZ)/Pi_180;
					Phi1=atan2f(X1,Y1)/Pi_180;
					isPierwsza++;
				}
				else{								// Drugi proton
					P2Type=wiersz[1];
					dE2=wiersz[8];
					E2=wiersz[12];
					En2=wiersz[11];
					X2=wiersz[5];
					Y2=wiersz[6];
					Th2=atan2f(sqrt(X2*X2+Y2*Y2),fZ)/Pi_180;
					Phi2=atan2f(X2,Y2)/Pi_180;
					isPierwsza=0;
				}

		}
		if((int)wiersz[1]==1){			//Neutron
					P3Type=wiersz[1];
					dE3=wiersz[8];
					E3=wiersz[12];
					En3=wiersz[11];
					X3=wiersz[5];
					Y3=wiersz[6];
					Th3=atan2f(sqrt(X3*X3+Y3*Y3),fZ)/Pi_180;
					Phi3=atan2f(X3,Y3)/Pi_180;
		}
		last_ev_num=wiersz[0];			//Na koniec pętli for zapisujemy numer eventu z wiersza
	}	//Koniec pętli for

	Sorted_Tree->Write();		//Zapisujemy drzewo
	SimFile->Write();				//Zapisujemy Plik
	RawFile->Close();				//Zamykamy plik z symulacjami
	//Rysujemy wypelnione przez nas kontrolne histogramy
	c1=new TCanvas("QA_plots","QA plots",900,600);

	c1->Divide(2,2); //Dzielimy Canvas na 4 czesci
	c1->cd(1); //1 cześć
	MWPC->GetXaxis()->SetTitle("X czastki");
	MWPC->GetYaxis()->SetTitle("Y czastki");
	MWPC->DrawCopy("colz");


	c1->cd(2);
	E_E_hist->GetXaxis()->SetTitle("Energia 1 protonu");
	E_E_hist->GetYaxis()->SetTitle("Energia 2 protonu");
	E_E_hist->DrawCopy("colz");



	c1->cd(3);
	dPhi_hist->GetXaxis()->SetTitle("Kat wzgledny #Delta#Phi");
	dPhi_hist->SetLineWidth(3);
	dPhi_hist->DrawCopy();
	c1->cd(4);
	Th1_hist->SetLineColor(kBlue);
	Th1_hist->SetLineWidth(3);
	Th1_hist->GetXaxis()->SetTitle("Kat #Theta protonu");
	Th1_hist->DrawCopy();
	Th2_hist->SetLineColor(kRed);
	Th2_hist->SetLineWidth(3);
	Th2_hist->DrawCopy("same");

	char nazwa[200];
	sprintf(nazwa,"./wyniki/QA_ppn_%d_%d.png",theta1[konf],theta2[konf]);
	c1->SaveAs(nazwa);
	SimFile->Close();


}
clock_t fend;
fend = clock();
Double_t time_spent;
time_spent = (Double_t)(fend - fbegin) / CLOCKS_PER_SEC;
printf("Czas wykonywania programu =%f s.\n",time_spent);
return 0;
}
