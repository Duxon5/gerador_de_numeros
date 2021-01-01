#include <string>
#include <iostream>

int main() {
  int arr[] = {10,20,30,40,50,60,10,20,30,40,50,60};
  int arrSize = sizeof(arr)/sizeof(arr[0]);
  std::cout << "The size of the array is: " << arrSize;
  return 0;
}
