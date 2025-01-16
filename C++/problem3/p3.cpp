#include<iostream>
#include<stack>
using namespace std;

class StackOperations {
  private:
    stack<int>sk;
  public:
  void push() {
    int num;
    cin >> num;
    sk.push(num);
  }
  void pop() {
    sk.pop();
  }
  void displayStack() {
    while (!sk.empty()) {
      cout << sk.top() << " ";
      sk.pop();
    }
    cout << "\n";
  }
};

int main() {
  StackOperations sk_op;
  for (int i = 0; i < 5; i++) {
    cout << "Please input numbers: ";
    sk_op.push();
  }

  for (int i =0 ; i < 2; i++) {
    sk_op.pop();
  }

  sk_op.displayStack();
}