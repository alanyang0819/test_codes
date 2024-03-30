#include<iostream>
using namespace std;

int binarySearch(int a[], int length, int target)
{
  int left = 0;
  int right = length - 1;
  int mid;
  while(right >= left)
  {
    mid = (left + right) / 2;
    if(target == a[mid])
      return mid;
    else if(target > a[mid])
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}

int main()
{
  int arr[] = {0, 4, 7, 10, 14, 23, 45, 47, 53};
  int arrLength = 9;
  int targetValue = 47;
  cout << "Search for " << targetValue << endl;
  int index = binarySearch(arr, arrLength, targetValue);
  
  for(int i = 0; i < arrLength; i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
  if(index != -1)
      cout << arr[index] << " is at index " << index << endl;
  else
      cout << "Target Value is not found !" << endl;
  return 0;
}