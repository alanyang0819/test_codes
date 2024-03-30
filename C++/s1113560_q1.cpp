#include<iostream>
using namespace std;

int main()
{
  int a[] = {61, 16, 45, 7, 58, 96, 82, 56, 75, 73};
  int length = 10;
  cout << "Sort the list by using a Bubble sort:" << endl;
  cout << " ";
  for(int i = 0; i < length; i++)
  {
    cout << a[i] << " ";
  }
  cout << endl;
  for(int n = 0; n < length; n++)
  {
    bool swapped = false;
    for(int j = 0; j < length - n - 1; j++) 
    {
      if(a[j] > a[j + 1])
      {
        swap(a[j], a[j + 1]);
        swapped = true;
      }
    }
    if(!swapped)
      break;
    cout << " ";
    for(int m = 0; m < length; m++)
    {
      cout << a[m] << " ";
    }
    cout << endl;
  }
  return 0;
}
