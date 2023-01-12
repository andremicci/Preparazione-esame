#include <iostream>
#include "OdeSolver.h"
#include "Particle.h"
#include "MatPoint.h"
#include "Vector.h"
#include <cmath>
#include "TCanvas.h"
#include "TGraph.h"
#include "TApplication.h"
#include <vector>
using namespace std;

const double mu= 0.001;
const double rho= 1;
const double  r= 0.01;
const double rho_0= 8000;
const double g =9.8;
  

const double Re= (2*rho*r)/mu;
const double  Volume= (4.0/3.0)*M_PI*pow(r,3.0);
const double mass=rho_0*Volume;



double C(Vector v){
  double v_mod=v.Mod();
  return (24*v_mod)/Re+(4.0/Re)*pow(v_mod,1.5)+0.4*pow(v_mod,2.0);
  }

Vector fExternal1(unsigned int i, double t, vector<MatPoint> p){

  double v=p[0].V().Mod();
  Vector F_visc=-0.5*C(v)*rho*M_PI*pow(r,2)*p[0].V().Vers();
  Vector F_g(0,0,mass*g);
  return F_visc+F_g;
}
Vector fExternal2(unsigned int i, double t, vector<MatPoint> p){

  double v=p[0].V().Mod();
  Vector F_visc=-0.5*C(v)*rho*M_PI*pow(r,2)*p[0].V().Vers();
  Vector F_arch(0,0,-rho*Volume*g);
  Vector F_g(0,0,mass*g);
 
  return F_visc+F_arch+F_g;
}
Vector fInternal(unsigned int i, unsigned int j, double t, vector<MatPoint> p)
{
  return Vector();
  
}

int main(){


  TApplication *app=new TApplication("app",0,NULL);
  

  
  double h=100;
  
  Vector x0(0,0,h);
  Vector v0(0,0,1e-10);
  MatPoint p(mass,0,x0,v0);

  OdeSolver ode_arch;
  OdeSolver ode;

  ode.SetMatPoint(p);
  ode_arch.SetMatPoint(p);

  ode_arch.fExternal=fExternal2;
  ode_arch.fInternal=fInternal;

  ode.fExternal=fExternal1;
  ode.fInternal=fInternal;
  
  double tmax=30;
  double dt=0.00001;
  
  ode.Step(dt);
  ode_arch.Step(dt);

  
  TGraph *g1=new TGraph();
  TGraph *g2=new TGraph();
  
  g1->SetMarkerStyle(7);
  g1->SetMarkerSize(5);
  g1->SetMarkerColor(kRed);
  
  g2->SetMarkerSize(20);
  g2->SetMarkerColor(kBlue);
  g2->SetMarkerStyle(18);

 
  
  int npoint=0;
  npoint++;
  int i=0;

    while(ode.T()<tmax){

    ode.Solve();
    ode_arch.Solve();
    double vz_arch=ode_arch.GetMatPoint(0).V().Z();
    double vz=ode.GetMatPoint(0).V().Z();

    
    if(i%15000==0){

   
    g1->SetPoint(npoint, ode.T(),vz);
    g2->SetPoint(npoint,ode.T(),vz_arch);
    
    
    g2->Draw("AP");
    g1->Draw("P");

    gPad->Modified();
    gPad->Update();
    npoint++;
    
    }
    i++;
  }

  app->Run(true);
  
  
  
  

  

}
