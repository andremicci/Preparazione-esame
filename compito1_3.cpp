
#include <iostream>
#include <vector>
#include "TVector2.h"
#include <cmath>
#include <string>
#include "TCanvas.h"
#include "TGraph.h"
#include "TApplication.h"
using namespace std;

class punto: public  TVector2{
  
public:
  punto(double x=0,double y=0):TVector2(x,y){};
private:
   
};


  class poligono{
  public:
    poligono(const vector <punto>& punti):m_punti(punti){};
    poligono():poligono(vector<punto>(0)){};

    double lato(double i, double j){ return (m_punti[i]-m_punti[j]).Mod();} //metodo che ritorna la lunghezza del lato compreso tra l'i-esimo e il j-esimo punto

    double N(){return m_n;}

    double Perimetro(){

      double perimetro=(*this).lato(0,m_n-1); 
		     
      for(int i=0;i<m_n-1;i++){
       	double lato= (*this).lato(i,i+1); 
	perimetro=perimetro+lato;
      }
      return perimetro;
    }

    void Draw(){
      
      TGraph *gr=new TGraph();
      
      int ctr=0;
      for(auto p : m_punti){
	gr->SetPoint(ctr,p.X(),p.Y());
	ctr++;
      }
      gr->Draw("APL");}
      
      
       

    virtual double Area()=0;
    
    protected:
    vector<punto> m_punti;
    double m_n=m_punti.size();
    double m_Area=0;
 };

class triangolo: public poligono{

  public:
  using poligono::poligono;
  
  triangolo(punto v1,punto v2,punto v3):poligono(){
    m_punti.push_back(v1);
    m_punti.push_back(v2);
    m_punti.push_back(v3);
  }
  triangolo(double l1,double l2,double theta):poligono(){
    
    m_punti.push_back(punto(0,0));
    m_punti.push_back(punto(l1,0));
    m_punti.push_back(punto(l2*cos(theta),l2*sin(theta)));
    m_Area=0.5*l1*l2*sin(theta);
}
  
					     

  double Area(){
    if(m_Area !=0){return m_Area;}
    
    else{
    TVector2 v1=m_punti[1]-m_punti[0];
    TVector2 v2=m_punti[2]-m_punti[0];
    double phi= v1.DeltaPhi(v2);
    m_Area= abs((v1.Mod()*v2.Mod()*sin(phi)))*0.5;
    return m_Area;}
  }
};
				  
  
int main(){
  TApplication app("app",0,NULL);
  //auto can=TCanvas(
   
     


  punto p1(0,0);
  punto p2(1,0);
  punto p3(1,1);
  punto p4(0,1);
 
 


  triangolo tr1(p1,p2,p3);
  cout << tr1.Area() << endl;

  triangolo tr2(2,2,M_PI/2);
  tr2.Draw();
  cout << tr2.Area() << endl;
  


  cout << "_____________________________________________________________________________________________________________________________________"<< endl;
  cout << "_____________________________________________________________________________________________________________________________________"<< endl;
  cout << "_____________________________________________________________________________________________________________________________________"<< endl;
  cout << endl;
  
  poligono *p;
  string input;
  
  cout << "inserisci tipo poligono: es T per triangolo "<< endl;
  cin >> input ;
  
  if(input=="T"){
    
    double l1,l2,theta;
    cout << "inserisci 2 lati e angolo compreso es: l1 l2 theta "<< endl;
    cin >> l1 >> l2 >> theta;
    
    p=new triangolo(l1,l2,theta);
  }
   cout << "L'area del poligono  dato è:  "<<  p->Area() << endl;
   cout << "Il perimetro del poligono dato è: "<<  p->Perimetro() << endl;
     
  

   app.Run(true);
   return 0; 
    }
