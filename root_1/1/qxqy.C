void qxqy(){
#include<iomanip>
gROOT->Reset();

gStyle->SetPalette(1);
gStyle->SetOptStat("e");



ifstream stream;
float x, y;

TH2D *qy_vs_qx;
TH1F *qx, *qy;



qx=new TH1F("","", 100, -20, 20);
qy=new TH1F("","", 100, -20, 20);


qy_vs_qx = new TH2D("","", 200, -20, 20, 200, -20, 20);


stream.open("qxy.dat");
if(!stream){  cout<<"Brak pliku "<<endl; return 0; }


while(!stream.eof())
  {

    stream>>x>>y;

    qy_vs_qx->Fill(y,x);
    qx->Fill(x);
    qy->Fill(y);
  }

 stream.close();

//##############################################################################################
float x1,x2,y1,y2;
x1=0.2,y1=0.73,x2=0.35, y2=0.88;
TPaveText *pt,*pt1;
TCanvas  *c1;
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

c1 = new TCanvas("qx qy","qx qy");
//gStyle->SetOptStat(kFALSE);
c1->SetFillColor(10);
c1->Divide(2,2);


c1->cd(1);
gPad->SetLogz();
qy_vs_qx->GetXaxis()->SetTitle("qx");
qy_vs_qx->GetXaxis()->SetTitleColor(2);
qy_vs_qx->GetYaxis()->SetTitle("qy");
qy_vs_qx->GetYaxis()->SetTitleColor(2);
qy_vs_qx->Draw("colz");

pt1=new TPaveText(x1,y1,x2,y2,"NDC");
pt1->SetFillColor(0);
pt1->AddText("qy vs qx");
pt1->SetBorderSize(0);
pt1->SetTextSize(0.06);
pt1->SetTextColor(2);
pt1->Draw();

c1->cd(2);
//gPad->SetLogz();
qy_vs_qx->GetXaxis()->SetTitle("qx");
qy_vs_qx->GetXaxis()->SetTitleColor(2);
qy_vs_qx->GetYaxis()->SetTitle("qy");
qy_vs_qx->GetYaxis()->SetTitleColor(2);
qy_vs_qx->Draw();

pt1=new TPaveText(x1,y1,x2,y2,"NDC");
pt1->SetFillColor(0);
pt1->AddText("qy vs qx");
pt1->SetBorderSize(0);
pt1->SetTextSize(0.06);
pt1->SetTextColor(4);
pt1->Draw();

c1->cd(3);
//gPad->SetLogz();
qx->GetXaxis()->SetTitle("qx");
qx->GetXaxis()->SetTitleColor(2);
qx->GetYaxis()->SetTitle("counts");
qx->GetYaxis()->SetTitleColor(2);
qx->Draw();

pt1=new TPaveText(x1,y1,x2,y2,"NDC");
pt1->SetFillColor(0);
pt1->AddText("qx");
pt1->SetBorderSize(0);
pt1->SetTextSize(0.06);
pt1->SetTextColor(4);
pt1->Draw();

c1->cd(4);
//gPad->SetLogz();
qy->GetXaxis()->SetTitle("qy");
qy->GetXaxis()->SetTitleColor(2);
qy->GetYaxis()->SetTitle("counts");
qy->GetYaxis()->SetTitleColor(2);
qy->Draw();

pt1=new TPaveText(x1,y1,x2,y2,"NDC");
pt1->SetFillColor(0);
pt1->AddText("qy");
pt1->SetBorderSize(0);
pt1->SetTextSize(0.06);
pt1->SetTextColor(4);
pt1->Draw();

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


}
