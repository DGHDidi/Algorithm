struct Matrix {
    int x = 0, y = 0;
    vector<vector<int>> mat;
    Matrix(int x, int y) : x(x), y(y) {
        mat.assign(x, vector<int>(y, 0));
    }
    Matrix operator*(const Matrix &other) const {
        assert(y == other.x);
        Matrix res(x, y);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                for (int k = 0; k < y; k++) {
                    res.mat[i][j] = mat[i][k] * other.mat[k][j];
                }
            }
        }
        return res;
    }
    void print() {
        cout << "-------------------------\n";
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << "-------------------------\n";
    }
};
