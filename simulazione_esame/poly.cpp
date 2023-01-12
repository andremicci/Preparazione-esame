#include "poly.h"

poly poly::operator+(poly pol){

  poly sum;

  for(int i=0;i<pol.size();i++){
    sum[i]=(*this)[i]+pol[i];
  }

 return sum;
  
 
}

double poly:: eval(double x){

  int n=(*this).size();
  double val=0;

  for(int i=0;i<n;i++){
    val=val+(*this)[i]*std::pow(x,i);
  }

  return val;
}
