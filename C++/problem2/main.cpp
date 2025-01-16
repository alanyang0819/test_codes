#include<iostream>
#include<queue>
using namespace std;

class QueueOperations {
  private:
    queue<int> q;
  public:
    void enqueue() {
      int num;
      cin >> num;
      q.push(num);
    }

    void dequeue() {
      q.pop();
    }

    void displayQueue() {
      while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
      }
    }
};

int main() {
  QueueOperations q_op;
  for (int i = 0; i < 5; i++) {
    cout << "Please inpuut numbers: ";
    q_op.enqueue();
  }
  for (int i = 0; i < 2; i++) {
    q_op.dequeue();
  }

  cout << "Remaining elements: ";
  q_op.displayQueue();
}