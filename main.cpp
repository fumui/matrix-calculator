#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

class Matrix{
    vector<vector<int>> data;

    static int AddOperation(Matrix& m1,Matrix& m2,int i,int j ){
        return m1.GetDataAt(i,j) + m2.GetDataAt(i,j);
    }
    static int SubtractOperation(Matrix& m1,Matrix& m2,int i,int j ){
        return m1.GetDataAt(i,j) - m2.GetDataAt(i,j);
    }

    bool DoMatrixOperations(Matrix m, int(*op)(Matrix&, Matrix&, int, int)){
        auto ordo = GetOrdo();
        for (int i = 0; i < get<0>(ordo); i++){
            for (int j = 0; j < get<1>(ordo); j++){
                int newValue = op(*this, m,i,j);
                SetDataAt(i,j,newValue);
            }
        }
        return true;
    }
    public:
    Matrix(){ }
    
    Matrix(int x, int y){
        data = vector<vector<int>>(x);
        for (int i = 0; i < x; i++){
            cout << "input data for row "<<i+1<<endl;
            data[i] = vector<int>(y);
            for (int j = 0; j < y; j++){
                cout << "column "<<j+1<< ": ";
                cin >> data[i][j];
            }
        }
        cout << "Matrix created, data: \n";
        Print();
    }
    tuple<int, int> GetOrdo(){
        return tuple<int, int>{data.size(), data[0].size()};
    }
    void Print(){
        auto ordo = GetOrdo();

        for (int i = 0; i < get<0>(ordo); i++){
            cout << "| ";
            for (int j = 0; j < get<1>(ordo); j++){
                cout << data[i][j] <<" ";
            }
            cout << "|\n";
        }
    }
    
    int GetDataAt(int x, int y){
        return data[x][y];
    }
    void SetDataAt(int x, int y, int value){
        data[x][y] = value;
    }
    
    bool Subtract(Matrix& m){
        auto ordo = GetOrdo();
        if (m.GetOrdo() != ordo){
            return false;
        }
        return DoMatrixOperations(m,SubtractOperation);
    }
    bool Add(Matrix& m){
        auto ordo = GetOrdo();
        if (m.GetOrdo() != ordo){
            return false;
        }
        return DoMatrixOperations(m,AddOperation);
    }

    static Matrix CreateMatrix(){
        int row, column;
        cout << "Input ordo matrix to create\n";
        cout << "row: ";
        cin >> row;
        cout << "column: ";
        cin >> column;
        cout << "input matrix data:\n";
        return Matrix(row, column);
    }
};

int main() {
    bool again = false;
    Matrix a,b;
    do {
        system("clear");
        cout << "Simple Matrix Calculator\n";
        cout << "Create the first matrix\n";
        a = Matrix::CreateMatrix();
        cout << "\nCreate the second matrix\n";
        b = Matrix::CreateMatrix();
        cout << endl;
        int opt;
        cout << "Choose operation:\n";
        cout << "1. Addition\n";
        cout << "2. Substraction\n";
        cout << "3. Exit\n";
        cin >> opt;
        bool success;
        switch (opt){
        case 1:
            success = a.Add(b);
            break;
        case 2:
            success = a.Subtract(b);
            break;
        default:
            return 0;
        }
        if (success) {
            cout << "output: \n";
            a.Print();
        } else {
            cout << "Operation failed\n";
        }
        string query;
        cout << "again? [Y/n] ";
        cin >> query;
        again = query == "Y";
    }while (again);
}