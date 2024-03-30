#include<iostream>
using namespace std;

int findMax(int arr[], int numofInt, int& maxIndex)
{
  maxIndex = 0;
  int maxVal = arr[0];
  for(int i = 1; i < numofInt; i++)
  {
    if(arr[i] > maxVal)
    {
      maxVal = arr[i];
      maxIndex = i;
    }
  }
  return maxVal;
}

void findMin(int arr[], int numofInt, int& minVal, int& minIndex)
{
  minIndex = 0;
  minVal = arr[0];
  for(int k = 1; k < numofInt; k++)
  {
    if(arr[k] < minVal)
    {
      minVal = arr[k];
      minIndex = k;
    }
  }
}

int main()
{
  int testcases;
  cin >> testcases;
  for(int j = 0; j < testcases; j++)
  {
    int length;
    cin >> length;
    int arr[100];
    for(int n = 0; n < length; n++)
    {
      cin >> arr[n];
    }
    for(int v = 0; v < length / 2 ; v++)
    {
      int maxIndex;
      findMax(arr, length - v, maxIndex);
      if(maxIndex != length - v -1)
      {
        swap(arr[maxIndex], arr[length - v - 1]);
      }
      int minIndex;
      int minVal;
      findMin(arr + v, length - v, minVal, minIndex);
      if(minIndex != 0)
      {
        swap(arr[minIndex + v], arr[v]);
      }
    }
      cout << "##" << " ";
      for(int m = 0; m < length; m++)
      {
        if(m % 10 == 0 && m / 10 > 0)
        {
          cout << endl << "#" << " ";
        }
        cout << arr[m] << " ";
      }
      cout << endl;
  }
}