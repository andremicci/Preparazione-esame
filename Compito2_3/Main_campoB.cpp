#include "OdeSolver.h"
#include "MatPoint.h"
#include "Vector.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "Electron.h"
#include <TMath.h>
#include "TApplication.h"
#include <iostream>
using namespace std;

Vector fB(Vector r){
  double BMin      = 1.4e-5, BMax=7e-5;
  double BottleLen = 10.0;
  double rho       = sqrt(r.X()*r.X()+r.Y()*r.Y());
  double phi       = atan2(r.Y(),r.X());
  double Bz        = BMin+(BMax-BMin)*(1 + 1/2.*(TMath::Erf(r.Z()-BottleLen/2) - TMath::Erf(r.Z()+BottleLen/2)));
  double DerivBZ   = (BMax-BMin)/sqrt(M_PI)*(TMath::Exp(-pow(r.Z()-BottleLen/2,2))-TMath::Exp(-pow(r.Z()+BottleLen/2,2)));
  double Br        = -DerivBZ*rho/2;
  double Bx        = Br*cos(phi);
  double By        = Br*sin(phi);
  return Vector(Bx,By,Bz);
}


Vector fE(Vector r){
  
  double Ex=0;
  double Ey=0;
  double Ez=0;
  
  return Vector(Ex,Ey,Ez);

}

Vector fLorentz(Vector v,double q,Vector E,Vector B){

  return q*E+q*(v.Cross(B));
  
}

Vector fExternal(unsigned int i, double t, vector<MatPoint> p){

  
  Vector E=fE(p[i].R());
  Vector B=fB(p[i].R());
  Vector fL=fLorentz(p[i].P()*(1/p[i].Mass()),p[i].Charge(),E,B);
  return fL;


}


Vector fInternal(unsigned int i, unsigned int j, double t, vector<MatPoint> p)
{
  return Vector();}




int main(){

  TApplication app("app",0,NULL);


  cout << "Programma che simula il moto di una particella relativistica in una bottiglia magnetica " << endl;
  cout << " ------------------------------------------------------------------------------------------" << endl;

  
  Electron e1;
  OdeSolver Ode;
  
  Vector r0(1,1,1);
  Vector v0(1,1,1);
  v0=v0*pow(10,6);

  MatPoint point(e1,r0,v0);
  
  Ode.SetMatPoint(point);
  Ode.fExternal=fExternal;
  Ode.fInternal=fInternal;

  
  double dt=1e-08;
  Ode.Step(dt);
  
  double t_max=5;
  
  auto can=new TCanvas("c","c", 500, 500);
  auto can2 =new TCanvas("c2","c2",500,500);
  auto can3= new TCanvas("c3","c3",500,500);
  
  
 
  auto gr=new TGraph();
  gr->SetTitle("x vs. y");
  auto gr2=new TGraph();
  gr2->SetTitle("y vs. z");
  auto gr3=new TGraph();
  gr3->SetTitle("x vs. z");


  gr->SetMarkerStyle(20);
  gr2->SetMarkerStyle(20);
  gr3->SetMarkerStyle(20);
  
  gr->SetMarkerColor(kRed);
  gr->SetMarkerSize(0.6);
  gr2->SetMarkerColor(kBlue);
  gr2->SetMarkerSize(0.6);
  gr3->SetMarkerColor(kGreen);
  gr3->SetMarkerSize(0.6);

  int i=0;

   while(Ode.T()<t_max){

    Ode.Solve();

    can->cd();
    gr->SetPoint(i,Ode.GetMatPoint(0).R().X(),Ode.GetMatPoint(0).R().Y());
    gr->Draw("AP");
    can->Modified();
    can->Update();
   

    can2->cd();
    gr2->SetPoint(i,Ode.GetMatPoint(0).R().Z(),Ode.GetMatPoint(0).R().Y());
    gr2->Draw("AP");
    can2->Modified();
    can2->Update();
    

    can3->cd();
    gr3->SetPoint(i,Ode.GetMatPoint(0).R().Z(),Ode.GetMatPoint(0).R().X());
    gr3->Draw("AP");
    
    /*
    cout <<Ode.GetMatPoint(0).R().X()<< " "<<  Ode.GetMatPoint(0).R().Y()<< endl;
    cout << endl;
    cout <<Ode.GetMatPoint(0).R().Y()<< " "<<  Ode.GetMatPoint(0).R().Z()<< endl;
    cout << endl;
    cout <<Ode.GetMatPoint(0).R().X()<< " "<<  Ode.GetMatPoint(0).R().Z()<< endl;*/
    
    can3->Modified();
    can3->Update();
    i++;
    
    }
  

  app.Run(true);
  return 0;
}
