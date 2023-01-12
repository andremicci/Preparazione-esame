#ifndef _ODESOLVER
#define _ODESOLVER

#include <vector>
#include<cmath>
#include "Vector.h"
#include "MatPoint.h"
#include <functional>

using namespace std;

class OdeSolver{
 public:
  OdeSolver(string method="Rk2", vector<MatPoint> p=vector<MatPoint>(0)):m_method(method),m_p(p),m_t(0),m_h(0.1){}
  
  void             SetMatPoint(MatPoint tmp);
  MatPoint         GetMatPoint(unsigned int i);
  vector<MatPoint> GetMatPoints();
  unsigned int   N();
  void           T(double t0);
  double         T();
  void           Step(double h);
  double         Step();
  void           Solve();
  void           SetMethod(string);
  string         GetMethod();
  std::function < Vector(unsigned int i,unsigned int j, double t, vector<MatPoint> p) > fInternal;
  std::function < Vector(unsigned int i,double t, vector<MatPoint> p) >        fExternal;
  OdeSolver operator=(const OdeSolver);
 private:
  string   m_method;
  vector<MatPoint> m_p;
  double   m_t,m_h; 
  Vector  m_eqDiff(unsigned int i, double t, vector<MatPoint>);


};


#endif
