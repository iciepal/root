void macro_pid(){

gROOT->Reset();
gStyle->SetNdivisions(505,"XY");
gStyle->SetStatBorderSize(1);
gStyle->SetStatW(0.2);
gStyle->SetStatH(0.1);
gStyle->SetCanvasBorderMode(0);
gStyle->SetPadBorderMode(0);
gStyle->SetCanvasColor(0);
gStyle->SetFrameBorderMode(0);
gStyle->SetPadColor(0);
gStyle->SetStatColor(0);
gStyle->SetLabelSize(.04,"xy");
gStyle->SetTitleXOffset(.9);
gStyle->SetTitleXSize(0.05);
gStyle->SetTitleYOffset(1.);
gStyle->SetTitleYSize(0.05);
gStyle->SetTitleW(0.5);
gStyle->SetTitleH(0.08);
gStyle->SetTitleBorderSize(1);
gStyle->SetTitleFillColor(0);
gStyle->SetPadLeftMargin(0.12);
gStyle->SetPadRightMargin(0.15);
gStyle->SetPadBottomMargin(.1);
gStyle->SetTextSize(.03);
gStyle->SetStatFontSize(.03);
//gStyle->SetOptStat(22);
gStyle->SetPalette(1);
//##################################################################

 TCanvas *c=new TCanvas("de-e","de-e",600,400);
 c->Divide(1,0);


       char file1[100];
       sprintf(file1,"ede_2_7.root");
       TFile *f1=new TFile(file1);
       TH2F *p1=(TH2F*)f1->Get("C3");
       c->cd(1);
       p1->Draw("colz");
       c->Draw();



}
