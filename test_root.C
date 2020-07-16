{
  //TCanvas *c1 = new TCanvas("test","test",600,400); 
  TCanvas *c1 = new TCanvas("test","test");
  c1->Divide(2,2);

  c1->cd(1);
  TText t1(0.05,0.8,"Hello World !");
  t1.SetTextSize(0.15);
  t1.Draw();
 
  c1->cd(2);
  TText t2(0.05,0.8,"2");
  t2.SetTextSize(0.5);
  t2.Draw();
	   
  c1->cd(3);
  TText t3(0.05,0.8,"3");
  t3.SetTextSize(0.5);
  t3.Draw();
  
  c1->cd(4);
  TText t4(0.05,0.8,"4");
  t4.Draw();
  //*****************************************
  //Histogram 1D
  TH1F *h1 = new TH1F("h1","h1",100, -3,3);
  h1->FillRandom("gaus",10000);

  TCanvas *c2 = new TCanvas("h1","h1");
  //c2->Divide(1,0);
  h1->Draw("e");

  //*****************************************
  //Histogram 2D
  TH2F *h2 = new TH2F("h2","h2",5,0,5,5,0,5);
  h2->Fill(0,0);
  h2->Fill(4,4);
  h2->Fill(4,1);
  h2->Fill(1,4);

  TCanvas *c3 = new TCanvas("h2","h2");
  c3->Divide(2,1);

  c3->cd(1);
  h2->Draw();

  c3->cd(2);
  h2->Draw("colz");



}
