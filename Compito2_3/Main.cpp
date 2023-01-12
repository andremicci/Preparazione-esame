#include <iostream>
#include "MatPoint.h"
#include "OdeSolver.h"
#include "Particle.h"
#include "TGraph.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "Vector.h"
#include "TAxis.h"


using namespace std;

Vector fExternal(double i,double t, vector<MatPoint> p){
  double F0=1;
  return Vector(F0,0,0);
}


Vector fInternal(double i,double j,double t,vector<MatPoint> p){
  return Vector();
  }

int main(){
  TApplication app("app",0,NULL);

  OdeSolver ode;
  ode.Step(1e-11);
  ode.T(0);

  
  MatPoint point(1,0,Vector(0,0,0),Vector(0,0,0));
  ode.SetMatPoint(point);

  ode.fExternal=fExternal;
  ode.fInternal=fInternal;
  
  auto can=new TCanvas();
  auto gr=new TGraph();
  gr->GetXaxis()->SetTitle("ct");
  gr->GetYaxis()->SetTitle("x");
  

  double tmax=5/consts::c;
  int i=0;

  cout << ode.GetMatPoint(0).R().X() << endl;
  
  while(ode.T()<tmax){

    ode.Solve();
    if(i%10){
    gr->SetPoint(i,consts::c*ode.T(),ode.GetMatPoint(0).R().X());
    gr->Draw("AP");
    }
    
    can->Modified();
    can->Update();
    i++;
    
  }
  
 
  app.Run(true);
}
