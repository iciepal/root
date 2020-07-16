{
gROOT->Reset();
gStyle->SetOptStat(1);
gStyle->SetPalette(1);
using namespace std;

TH1D *h1,*h2;
TCanvas *c1;

c1=new TCanvas("h1h2","h1h2");
c1->Divide(2,1);

h2=new TH1D("", "", 100, -10, 30);
h1=new TH1D("", "", 100, -1, 10);

 
TRandom3 r;

   // generate a gaussian distributed number with:
   // mu=0, sigma=1 (default values)
 double x1 =0., x2=0., x3=0.;


 for (int i=0;i<10000;i++){
   
   x1= r.Gaus();
   x2 = r.Gaus(10,3);  

   x3=r.Uniform(0,6);
   h2->Fill(x1);
   h2->Fill(x2);

   h1->Fill(x3);
 }
 c1->cd(1);
 h2->Draw();
 c1->cd(2);
 h1->Draw();






}
