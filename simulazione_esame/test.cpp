#include <iostream>
#include "poly.h"

using namespace std;
int main(){

  poly p1(1,2,3,4); //1+2x+3x^2+4x^3
  poly p2(0,0,0,5);

  poly p3=p1+p2;
    
  for(int i=0;i<p3.size();i++){
    cout << p3[i] << endl;
			      
    }
  cout << p2.eval(2) << endl;

}


