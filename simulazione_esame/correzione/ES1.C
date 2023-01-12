{
  TRandom3 rnd;
  rnd.SetSeed(123456789);

  double lambda=1;
  double k=1.5;

  int ntot=1000;
  TH1D *h=new TH1D("h","h",50,0,5);

  for(int i=0;i<ntot;i++){

    double eta=rnd.Rndm();
    double x=lambda*(pow(-TMath::Log(1-eta),1/k));
    h->Fill(x);
    

  }

  h->Draw();


}
