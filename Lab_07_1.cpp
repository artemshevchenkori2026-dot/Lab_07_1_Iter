#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Формування матриці за допомогою випадкових чисел
void Create(int** q, const int rowCount, const int colCount, const int Low, const int High) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            q[i][j] = Low + rand() % (High - Low + 1);
        }
    }
}

// Виведення матриці на екран
void Print(int** q, const int rowCount, const int colCount) {
    cout << endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            cout << setw(5) << q[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// Обмін двох рядків місцями
void Change(int** q, const int row1, const int row2, const int colCount) {
    for (int j = 0; j < colCount; j++) {
        int tmp = q[row1][j];
        q[row1][j] = q[row2][j];
        q[row2][j] = tmp;
    }
}

// Сортування рядків матриці за ключами (col 0 - спадання, col 1 - спадання, col 3 - зростання)
void Sort(int** q, const int rowCount, const int colCount) {
    for (int i0 = 0; i0 < rowCount - 1; i0++) {
        for (int i1 = 0; i1 < rowCount - i0 - 1; i1++) {
            if ((q[i1][0] < q[i1 + 1][0]) ||
                (q[i1][0] == q[i1 + 1][0] && q[i1][1] < q[i1 + 1][1]) ||
                (q[i1][0] == q[i1 + 1][0] && q[i1][1] == q[i1 + 1][1] && q[i1][3] > q[i1 + 1][3])) {
                Change(q, i1, i1 + 1, colCount);
            }
        }
    }
}

// Обчислення суми S, кількості k та обнулення елементів за критерієм
void Calc(int** q, const int rowCount, const int colCount, int& S, int& k) {
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            // Критерій: додатні, крім випадків коли обидва індекси (i та j) є парними
            if (q[i][j] > 0 && !(i % 2 == 0 && j % 2 == 0)) {
                S += q[i][j];
                k++;
                q[i][j] = 0;
            }
        }
    }
}

int main() {
    srand((unsigned)time(0));

    const int Low = -8;
    const int High = 42;
    const int rowCount = 8;
    const int colCount = 7;

    // Створення динамічної матриці
    int** q = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        q[i] = new int[colCount];
    }

    // 1. Створення та виведення початкової матриці
    Create(q, rowCount, colCount, Low, High);
    cout << "Initial matrix:" << endl;
    Print(q, rowCount, colCount);

    // 2. Сортування рядків та виведення
    Sort(q, rowCount, colCount);
    cout << "Sorted matrix:" << endl;
    Print(q, rowCount, colCount);

    // 3. Обчислення та обнулення за критерієм
    int S = 0;
    int k = 0;
    Calc(q, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix:" << endl;
    Print(q, rowCount, colCount);

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++) {
        delete[] q[i];
    }
    delete[] q;

    return 0;
}