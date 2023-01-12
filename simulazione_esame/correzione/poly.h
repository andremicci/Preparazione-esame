
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class poly: public vector<double>{

 public:
 poly(int=3):vector<double>(n){};
 poly(double p0,double p1,double p2=0,double p3=0):vector<double>{p0,p1,p2,p3};
 poly operator+(poly b);
 double eval(double);

 
};

poly poly::operator+(poly b){

  poly sum(b.size());
  for(int i=0;i<b.size();i++){
    sum[i]=(*this)[i]+b[i];
  }
  return sum;
}

double poly:: eval(double x){

  double sum=0;
  for(int i=0;i<size();i++){
    sum+=(*this)[i]*pow(x,i);
  }
  return sum;
}



int main(){
  poly a(1,2,3);
  poly b(2,2,3);
  poly sum(3);

  poly c;
  
  c[0]=1;
  c[1]=1
  c[2]=3

  sum=a+b;
  cout << sum(1) << endl;
}

