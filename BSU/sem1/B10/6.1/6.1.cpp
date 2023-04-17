#include <iostream>
#include <iomanip>

using namespace std;

enum class Gender {
    Male,
    Female
};

struct Student {
    char fullname[1000];
    int age;
    int course;
    Gender gender;
    double subj[10];
};

void input(Student data[], int n, int m) {
    cout << "Введите записи (ФИО возраст курс пол(m/f)):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Запись #" << i + 1 << ": ";
        Student st;
        char gen_char;
        cin >> st.fullname >> st.age >> st.course >> gen_char;
        st.gender = gen_char == 'm' ? Gender::Male : Gender::Female;

        cout << "Баллы по предметам: ";
        for (int j = 0; j < m; j++)
            cin >> st.subj[j];

        data[i] = st;
    }
    cout << endl;
}

void output(Student data[100], int n, int m) {
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

    cout<<setfill(' ');

    for (int i = 0; i < n; i++) {
        cout << "| " << setw(30) << data[i].fullname << " | " << setw(7) << data[i].age;
        cout << " | " << setw(4) << data[i].course << " | " << setw(3) << (data[i].gender == Gender::Male ? "муж" : "жен") << " | ";
        for (int j = 0; j < m; j++)
            cout << setw(4) << data[i].subj[j] << " | ";
        cout << endl;
    }
}

int func(Student data[], int n, int N, int M) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (data[i].course != N) continue;
        if (data[i].subj[M - 1] >= 4) continue;

        res++;
    }

    return res;
}

int main(){
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
    } else {
        n = 10;
        m = 4;
        data[0] = { "Student 1", 16, 6, Gender::Female, {6, 4, 2, 3} };
        data[1] = { "Student 2", 17, 5, Gender::Male, {4, 6, 2, 5} };
        data[2] = { "Student 3", 18, 7, Gender::Female, {5, 2, 4, 4} };
        data[3] = { "Student 4", 16, 6, Gender::Female, {6, 4, 6, 2} };
        data[4] = { "Student 5", 20, 4, Gender::Male, {7, 4, 2, 8} };
        data[5] = { "Student 6", 21, 5, Gender::Male, {2, 4, 7, 3} };
        data[6] = { "Student 7", 18, 4, Gender::Female, {8, 2, 6, 5} };
        data[7] = { "Student 8", 22, 5, Gender::Male, {6, 4, 6, 2} };
        data[8] = { "Student 9", 23, 5, Gender::Female, {4, 5, 2, 3} };
        data[9] = { "Student 10", 17, 6, Gender::Male, {3, 1, 6, 9} };
    }

    cout << "Введённые данные: " << endl;
    output(data, n, m);

    int N;
    cout << "Введите курс: ";
    cin >> N;

    int M;
    cout << "Введите номер предмета (от 1 до " << m << "): ";
    cin >> M;

    cout << "Ответ: " << func(data, n, N, M) << endl;


    return 0;
}