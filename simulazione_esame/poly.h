#ifndef _POLY
#define _POLY

#include <cmath>
#include <vector>

class poly: public std::vector<double>{
  
  public:
  
  poly(int n=0):std::vector<double>{double(n),0,0,0}{};
  poly(double p0,double p1):std::vector<double>{p0,p1,0,0}{};
  poly(double p0,double p1,double p2):std::vector<double>{p0,p1,p2,0}{};
  poly(double p0,double p1,double p2,double p3):std::vector<double>{p0,p1,p2,p3}{};

  poly operator+(poly);
  
  double eval(double);
  



 private:

  double m_n;
   
  
};
#endif
