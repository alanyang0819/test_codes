#include<iostream>
using namespace std;

class Student {
    private:
        int marks[5];
    public:
        void setMarks() {
            for (int i = 0; i < 5; i++) {
                cin >> marks[i];
            }
        }

        double calculateAverage() {
            double avg = 0;
            for (int i = 0; i < 5; i++) {
                avg += marks[i] / 5;
            }
            return avg;
        }

        void displayMarks() {
            for (int i = 0; i < 5; i++) {
                cout << marks[i] << " ";
            }
            cout << "\n";
        }
};

int main() {
    Student stu;
    cout << "Input Marks: ";
    stu.setMarks();
    cout << "Marks: ";
    stu.displayMarks();
    cout << "Average: " << stu.calculateAverage() << endl;
}