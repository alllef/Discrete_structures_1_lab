#include <iostream>
#include<vector>
#include <Windows.h>
#include <iomanip>


using namespace std;

void initializeGraph(int &picks, int &ribs, vector<int> &start, vector<int> &end, vector<int> &powerVector);

void makeContiguityMatrix(vector<int> start, vector<int> end, int picks, int ribs);

void makeIncidenceUnOrientedMatrix(vector<int> start, vector<int> end, int picks, int ribs);

void definePowerOfPicks(vector<int> start, vector<int> end, int picks, int ribs, vector<int> &vectorPower);

void defineIsolatedAndHangingPicks(vector<int> &vectorPower);

void makeIncidenceOrientedMatrix(vector<int> start, vector<int> end, int picks, int ribs);

void defineHalfPowers(vector<int> start, vector<int> end, int picks, int ribs);

void menu(vector<int> &start, vector<int> &end, int &picks, int &ribs, vector<int> &powerVector, bool &isOriented);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    vector<int> startVector = {};
    vector<int> endVector = {};
    vector<int> vectorOfPower = {};
    int n = 0, m = 0;

    initializeGraph(n, m, startVector, endVector, vectorOfPower);

    return 0;
}

void initializeGraph(int &picks, int &ribs, vector<int> &start, vector<int> &end, vector<int> &powerVector) {
    int middleNumber = 0, otherNumber = 0;
    bool isOriented;
    bool b;
    cout << "Введите количество вершин " << endl;
    cin >> picks;
    cout << "Введите количество ребер " << endl;
    cin >> ribs;
    cout << "Если это неориентированный граф, нажмите 0, если ориентированный, нажмите 1" << endl;
    cin >> isOriented;

    if (isOriented == 0)cout << "Введите ребра графа " << endl;
    if (isOriented == 1)cout << "Введите начало и конец каждого ребра " << endl;

    for (int i = 0; i < ribs; i++) {
        if (isOriented == 1) cout << "Начало ребра";

        do {
            cin >> middleNumber;
            if (middleNumber < 1 || middleNumber > picks) cout << "Неправильно. введите значение от 1 до " << picks;
        } while (middleNumber < 1 || middleNumber > picks);

        if (isOriented == 1) cout << "Конец ребра";

        do {
            cin >> otherNumber;
            if (otherNumber < 1 || otherNumber > picks) cout << "Неправильно. введите значение от 1 до " << picks;
        } while (otherNumber < 1 || otherNumber > picks);

        for (int j = 0; j < start.size(); j++) {
            if (middleNumber == start[j] && otherNumber == end[j]) {
                b = true;
                while (b) {
                    cout << "Такое ребро уже есть введите другие значения" << endl;

                    do {
                        cin >> middleNumber;
                        if (middleNumber < 1 || middleNumber > picks) cout << "Неправильно. введите значение от 1 до " << picks;
                    } while (middleNumber < 1 || middleNumber > picks);

                    do {
                        cin >> otherNumber;
                        if (otherNumber < 1 || otherNumber > picks) cout << "Неправильно. введите значение от 1 до " << picks;
                    } while (otherNumber < 1 || otherNumber > picks);

                    for (int k = 0; k < start.size(); k++) {
                        if (middleNumber != start[k] || otherNumber != end[k]) b = false;
                    }

                }
            }
        }


        start.push_back(middleNumber);
        end.push_back(otherNumber);


        if (isOriented == 0 && i < ribs - 1) cout << "Следующее ребро" << endl;
    }
    menu(start, end, picks, ribs, powerVector, isOriented);
}


void makeContiguityMatrix(vector<int> start, vector<int> end, int picks, int ribs) {
    cout << "Матрица смежности" << endl;
    int *contiguityMatrix = new int[picks * picks];
    for (int i = 0; i < picks; i++) {
        for (int j = 0; j < picks; j++) {
            *(contiguityMatrix + i * picks + j) = 0;
        }
    }

    for (int i = 0; i < ribs; i++) {

        *(contiguityMatrix + (start[i] - 1) * picks + (end[i] - 1)) = 1;
    }
    for (int i = 0; i < picks; i++) {
        for (int j = 0; j < picks; j++) {

            cout << *(contiguityMatrix + i * picks + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void makeIncidenceUnOrientedMatrix(vector<int> start, vector<int> end, int picks, int ribs) {
    cout << "Матрица инцидентности:" << endl;
    int *incidenceMatrix = new int[picks * ribs];
    for (int i = 0; i < picks; i++) {
        for (int j = 0; j < ribs; j++) {
            *(incidenceMatrix + i * ribs + j) = 0;


            *(incidenceMatrix + (start[j] - 1) * ribs + j) = 1;
            *(incidenceMatrix + (end[j] - 1) * ribs + j) = 1;
            cout << *(incidenceMatrix + i * ribs + j) << " ";

        }
        cout << endl;

    }

}


void definePowerOfPicks(vector<int> start, vector<int> end, int picks, int ribs, vector<int> &vectorPower) {


    int counterOfPower = 0;

    for (int i = 0; i < picks; i++) {
        for (int j = 0; j < ribs; j++) {
            if (start[j] == end[j]) {
                counterOfPower++;
                break;
            }
            if ((start[j] - 1) == i)counterOfPower++;
            if ((end[j] - 1) == i)counterOfPower++;
        }
        vectorPower.push_back(counterOfPower);
        counterOfPower = 0;
        cout << "Степень вершины " << (i + 1) << " " << vectorPower[i] << endl;

    }
    for (int i = 0; i < vectorPower.size() - 1; i++) {
        if (vectorPower[i] == vectorPower[i + 1]) counterOfPower++;
        if (counterOfPower == vectorPower.size() - 1)
            cout << "Этот граф однородный со степенью " << vectorPower[i] << endl;
    }
}

void defineIsolatedAndHangingPicks(vector<int> &vectorPower) {
    for (int i = 0; i < vectorPower.size(); i++) {
        if (vectorPower[i] == 0) cout << "Вершина " << i + 1 << " изоллированая" << endl;
        if (vectorPower[i] == 1) cout << "Вершина " << i + 1 << " висячая" << endl;
    }
}

void makeIncidenceOrientedMatrix(vector<int> start, vector<int> end, int picks, int ribs) {
    cout << "Матрица инцидентности:" << endl;
    int *incidenceMatrix = new int[picks * ribs];
    for (int i = 0; i < picks; i++) {
        for (int j = 0; j < ribs; j++) {
            *(incidenceMatrix + i * ribs + j) = 0;


            *(incidenceMatrix + (start[j] - 1) * ribs + j) = -1;
            *(incidenceMatrix + (end[j] - 1) * ribs + j) = 1;
            if (start[j] == end[j]) *(incidenceMatrix + (end[j] - 1) * ribs + j) = 2;
            cout << setw(2) << *(incidenceMatrix + i * ribs + j) << " ";

        }
        cout << endl;
    }
}

void defineHalfPowers(vector<int> start, vector<int> end, int picks, int ribs) {
    int halfExitPower = 0, halfEnterPower = 0;
    for (int i = 0; i < picks; i++) {
        for (int j = 0; j < ribs; j++) {
            if ((start[j] - 1) == i) halfExitPower++;
            if ((end[j] - 1) == i) halfEnterPower++;
        }
        cout << "Полустепень выхода вершины " << i + 1 << " " << halfExitPower << endl;
        cout << "Полустепень захода вершины " << i + 1 << " " << halfEnterPower << endl;
        cout << endl;
        halfExitPower = 0;
        halfEnterPower = 0;
    }
}

void menu(vector<int> &start, vector<int> &end, int &picks, int &ribs, vector<int> &powerVector, bool &isOriented) {
    int number;
    bool b = true;
    if (isOriented == 0) {

        cout << endl;
        while (b) {
            cout
                    << "1 - матрица инцидентности и матрица смежности. 2 - посмотреть степень вершин. 3 - посмотреть изоллированные и"
                    << endl;
            cout << "висячие вершины. -1 - закончить программу ";
            cin >> number;
            cout << endl;
            switch (number) {
                case -1:
                    b = false;
                    break;
                case 1:
                    makeContiguityMatrix(start, end, picks, ribs);
                    makeIncidenceUnOrientedMatrix(start, end, picks, ribs);
                    break;
                case 2:
                    definePowerOfPicks(start, end, picks, ribs, powerVector);
                    break;
                case 3:
                    defineIsolatedAndHangingPicks(powerVector);
                    break;
                default:
                    cout << "Неправильный ввод" << endl;
                    break;
            }
        }
    }
    if (isOriented == 1) {
        cout << endl;
        while (b) {
            cout
                    << "1 - матрица инцидентности и матрица смежности. 2 - найти полустепени выхода и захода. -1 - закончить программу";
            cin >> number;
            cout << endl;
            switch (number) {
                case 0:
                    cout << "Нажмите 1, чтобы вывести матрицы смежности и инцидентности" << endl;
                    cout << "Нажмите 2, чтобы посмотреть степени вершин." << endl;
                    cout << "Нажмите 3, чтобы посмотреть изоллированные и висячие вершины." << endl;
                    cout << "Нажмите -1, чтобы закончить работу программы " << endl;
                    break;
                case -1:
                    b = false;
                    break;
                case 1:
                    makeContiguityMatrix(start, end, picks, ribs);
                    makeIncidenceOrientedMatrix(start, end, picks, ribs);
                    break;
                case 2:
                    defineHalfPowers(start, end, picks, ribs);
                    break;
                default:
                    cout << "Неправильный ввод" << endl;
                    break;
            }
        }
    }
}