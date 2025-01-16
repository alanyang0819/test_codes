#include<iostream>
#include<vector>
using namespace std;

class Matrix {
  private:
    vector<vector<int>> mtx;

  public:
    void setMatrix(int rows, int cols) {
      mtx.resize(rows, vector<int>(cols));
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          cin >> mtx[i][j];
        }
      }
    }

    void transpose() {
      vector<vector<int>> transposed;
      transposed.resize(mtx[0].size(), vector<int>(mtx.size()));
      for (size_t i = 0; i < mtx.size(); i++) {
        for (size_t j = 0; j < mtx[0].size(); j++) {
          transposed[j][i] = mtx[i][j];
        }
      }
      mtx = transposed;
    }

    void displayMatrix() {
     for (const auto& row: mtx) {
      for (const auto& val : row){
        cout << val << " ";
      }
      cout << endl;
     }
    }
};

int main() {
  Matrix mtx;
  int rows, cols;
  cout << "Please input rows and cols: ";
  cin >> rows >> cols;
  mtx.setMatrix(rows, cols);
  cout << "Matrix:" << endl;
  mtx.displayMatrix();
  mtx.transpose();
  cout << "Transposed Matrix:" << endl;
  mtx.displayMatrix();
}