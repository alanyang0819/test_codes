#include<iostream>
#include<cmath>
using namespace std;

int main()
{
  int ori;
  cout << "Input your number: ";
  cin >> ori;
  int num = ori;
  int par1 = ori % 10;
  ori /= 10;
  int par2 = ori % 10;
  ori /= 10;
  int par3 = ori % 10;
  if(pow(par1, 3) + pow(par2, 3 ) + pow(par3, 3) == num){
    cout << "Armstrong number !" << endl; 
  }
  else{
    cout << "Error !" << endl;
  }
  return 0;


}