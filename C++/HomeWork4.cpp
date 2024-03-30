#include<iostream>
#include<cassert>
using namespace std;

void foo(int result[], int length, int decimal, const int noChange[], int LENGTH)
{
  for(int k = 0; k < length; ++k)
  {
    result[k] = decimal % 3;
    decimal = decimal / 3;
  }
}

int main()
{
  const int LENGTH = 10;
  int ternary[LENGTH] = {};
  const int noChange[LENGTH] = {};
  int n;

  cin >> n;
  if(n > 0 && n <= 13)
  {
    foo(ternary, LENGTH, n, noChange, LENGTH);

    for(int i = 0; i < LENGTH; ++i)
    {
      assert(ternary[i] >= 0 && ternary[i] <= 2);
    }
    assert(ternary[0] * 1 + ternary[1] * 3 + ternary[2] * 9 == n);
    cout << "yes\n";
  }
  else
  {
    return 0;
  }
}
