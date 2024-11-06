#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

// Single-threaded matrix multiplication
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size(), n = B.size(), p = B[0].size();
    vector<vector<int>> result(m, vector<int>(p, 0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Multithreaded matrix multiplication (one thread per row)
void multiplyRow(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& result, int row) {
    int p = B[0].size(), n = B.size();
    for (int j = 0; j < p; ++j) {
        for (int k = 0; k < n; ++k) {
            result[row][j] += A[row][k] * B[k][j];
        }
    }
}

vector<vector<int>> matrixMultiplyRow(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int m = A.size();
    vector<vector<int>> result(m, vector<int>(B[0].size(), 0));
    vector<thread> threads;

    for (int i = 0; i < m; ++i) {
        threads.push_back(thread(multiplyRow, cref(A), cref(B), ref(result), i));
    }
    for (auto& th : threads) th.join();
    return result;
}

// Utility function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) cout << value << " ";
        cout << endl;
    }
}

int main() {
    int option;
    while (true) {
        cout << "\nMenu:\n1. Single-threaded\n2. Multithreaded (one thread per row)\n3. Exit\nChoose an option: ";
        cin >> option;
        if (option == 3) break;

        int m, n, p;
        cout << "Enter rows for Matrix A: "; cin >> m;
        cout << "Enter columns for Matrix A / rows for Matrix B: "; cin >> n;
        cout << "Enter columns for Matrix B: "; cin >> p;

        vector<vector<int>> A(m, vector<int>(n)), B(n, vector<int>(p));

        cout << "Enter Matrix A:\n";
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) cin >> A[i][j];

        cout << "Enter Matrix B:\n";
        for (int i = 0; i < n; ++i) for (int j = 0; j < p; ++j) cin >> B[i][j];

        vector<vector<int>> result;
        auto start = chrono::high_resolution_clock::now();

        if (option == 1) {
            result = matrixMultiply(A, B);
            cout << "Single-threaded result:\n";
        } else if (option == 2) {
            result = matrixMultiplyRow(A, B);
            cout << "Multithreaded (one thread per row) result:\n";
        } else {
            cout << "Invalid option\n";
            continue;
        }

        auto end = chrono::high_resolution_clock::now();
        printMatrix(result);
        chrono::duration<double, milli> duration = end - start;
        cout << "Time: " << duration.count() << " ms\n";
    }

    return 0;
}
