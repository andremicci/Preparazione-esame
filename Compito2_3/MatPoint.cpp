#include "MatPoint.h"
#include "Vector.h"
#include <cmath>




Vector MatPoint::R(){
  return m_r;
}

Vector MatPoint::P(){
  return m_p;
}

void MatPoint::R(Vector r){
  m_r = r;
}

void MatPoint::P(Vector p){
  m_p = p;
}

double MatPoint :: E(){

  m_E=sqrt(pow(m_p.Mod()*consts::c,2)+pow((*this).Mass()*consts::c,2));
  return m_E;
}

Vector MatPoint::GravField(Vector r){
  
  Vector r0   = m_r;
  Vector dist = r-r0;

  Vector val  = -consts::G*Mass()/pow(dist.Mod(),2)*dist.Vers();

  return val;
  
  
}


