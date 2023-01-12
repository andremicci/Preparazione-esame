#ifndef _MATPOINT
#define _MATPOINT
#include "Particle.h"
#include "Vector.h"

namespace consts{
  const double c = 299792458;
  const double G = 1;
};

class MatPoint: public Particle{
 public:
  MatPoint(Particle p=Particle(), Vector r=Vector(), Vector P=Vector()):Particle(p),m_r(r),m_p(P){}
  MatPoint(double massa, double carica, Vector r, Vector P):MatPoint(Particle(massa,carica),r,P){}
  
  Vector R();    
  Vector P();
  void   R(Vector);
  void   P(Vector);
  
  double E();
  
  Vector GravField(Vector);
  
  
 private:
  Vector m_r;
  Vector m_p;
  double m_E;
};

#endif
