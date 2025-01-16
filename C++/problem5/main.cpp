#include<iostream>
using namespace std;
const int N=4;
const int M=4;
class MatrixOperation{
    private:
    int mat[N][M];
    public:
    void setMatrix(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                cin>>mat[i][j];
            }
        }
    }
    void swapRows(int row1,int row2){
            for(int i=0;i<4;i++){
                int tmp=mat[row1][i];
                mat[row1][i]=mat[row2][i];
                mat[row2][i]=tmp;
            }
    }
    void swapCols(int col1,int col2){
            for(int i=0;i<4;i++){
                int tmp=mat[i][col1];
                mat[i][col1]=mat[i][col2];
                mat[i][col2]=tmp;
            }
    }
    void displayMatrix(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};
int main(){
    MatrixOperation m;
    m.setMatrix();
    m.swapRows(1,3);
    //m.swapCols(1,3);
    m.displayMatrix();
}