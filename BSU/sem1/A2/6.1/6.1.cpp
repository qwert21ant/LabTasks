#include <iostream>
#include <iomanip>

using namespace std;

enum {
    Male = 1,
    Female = 2
};

struct Student {
    char fullname[1000];
    int age;
    int course;
    int gender;
    double subj[10];
};

void input(Student data[], int n, int m) {
    cout << "Введите записи (ФИО возраст курс пол(m/f)):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Запись #" << i + 1 << ": ";
        Student st;
        char gen_char;
        cin >> st.fullname >> st.age >> st.course >> gen_char;
        st.gender = gen_char == 'm' ? Male : Female;

        cout << "Баллы по предметам: ";
        for (int j = 0; j < m; j++)
            cin >> st.subj[j];

        data[i] = st;
    }
    cout << endl;
}

void output(Student data[], int n, int m) {
    cout << "| " << setw(30) << "ФИО" << " | " << setw(7) << "Возраст";
    cout << " | " << setw(4) << "Курс" << " | " << setw(3) << "Пол" << " | ";
    for (int i = 0; i < m; i++)
        cout << setw(4) << i + 1 << " | ";
    cout << endl;

    cout << "+" << setfill('-') << setw(33) << "+" << setw(10) << "+";
    cout << setw(7) << "+" << setw(6) << "+";
    for (int i = 0; i < m; i++)
        cout << setw(7) << "+";
    cout << endl;

    cout << setfill(' ');

    for (int i = 0; i < n; i++) {
        cout << "| " << setw(30) << data[i].fullname << " | " << setw(7) << data[i].age;
        cout << " | " << setw(4) << data[i].course << " | " << setw(3) << (data[i].gender == Male ? "муж" : "жен") << " | ";
        for (int j = 0; j < m; j++)
            cout << setw(4) << data[i].subj[j] << " | ";
        cout << endl;
    }
}

int func(Student data[], int n, int N) {
    int ind = -1;
    int min_age = 10000000;
    for (int i = 1; i < n; i++) {
        if (data[i].course != N) continue;

        if (data[i].age < min_age) {
            min_age = data[i].age;
            ind = i;
        }
    }

    return ind;
}

int main() {
    setlocale(LC_ALL, "rus");

    Student data[100];

    int mode;
    cout << "Выберите способ ввода (1 - ввод, 2 - стандартные значения): ";
    cin >> mode;

    int n, m;
    if (mode == 1) {
        int n;
        cout << "Введите количество записей (до 100): ";
        cin >> n;

        int m;
        cout << "Введите количество предметов (до 10): ";
        cin >> m;

        input(data, n, m);
    }
    else {
        n = 10;
        m = 4;
        data[0] = { "Student 1", 24, 6, Female, {6, 4, 2, 3} };
        data[1] = { "Student 2", 17, 5, Male, {4, 6, 2, 5} };
        data[2] = { "Student 3", 18, 7, Female, {5, 2, 4, 4} };
        data[3] = { "Student 4", 16, 6, Female, {6, 4, 6, 2} };
        data[4] = { "Student 5", 20, 4, Male, {7, 4, 2, 8} };
        data[5] = { "Student 6", 21, 5, Male, {2, 4, 7, 3} };
        data[6] = { "Student 7", 18, 4, Female, {8, 2, 6, 5} };
        data[7] = { "Student 8", 22, 5, Male, {6, 4, 6, 2} };
        data[8] = { "Student 9", 23, 5, Female, {4, 5, 2, 3} };
        data[9] = { "Student 10", 17, 6, Male, {3, 1, 6, 9} };
    }

    cout << "Введённые данные: " << endl;
    output(data, n, m);

    int N;
    cout << "Введите курс: ";
    cin >> N;

    int res = func(data, n, N);
    if (res == -1)
        cout << "На этом курсе нет сутдентов" << endl;
    else
        cout << "Ответ: " << data[res].fullname << endl;

    return 0;
}