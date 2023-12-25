#include<iostream>
#include<cassert>
using namespace std;

void foo(int *num1, int *num2, int *num3, int decimal)
{
  *num1 = decimal % 2;
  decimal = decimal / 2;
  *num2 = decimal % 2;
  decimal = decimal / 2;
  *num3 = decimal % 2;
}

int main()
{
  int x;
  int y;
  int z;

  for(int i = 0; i < 8; i++)
  {
    foo(&z, &y, &x, i);
    assert(x >= 0 && x <= 1 && y >= 0 && y <= 1 && z >= 0 && z <= 1);
    assert(z + y * 2 + x * 4 == i);
  }
  cout << "yes" << endl;
}