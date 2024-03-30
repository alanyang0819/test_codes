#include<iostream>
using namespace std;

int main()
{
  int a[] = {8, 2, 4, 9, 3, 6};
  int length = 6;
  for(int i = 0; i < length; i++)
  {
    cout << a[i] << " ";
  }
  cout << endl;
  for(int n = 1; n < length; n++)
  {
    int numToInsert = a[n];
    int j = n - 1;
    while(j >= 0 && a[j] > numToInsert)
    {
      a[j + 1] = a[j];
      j = j - 1;
    }
    a[j + 1] = numToInsert;
    for(int k = 0; k < length; k++)
    {
      cout << a[k] << " ";
    }
    cout << endl;
  }
  return 0;
}