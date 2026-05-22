#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct CalcResult {
    double value;
    double time_sec;
};

CalcResult compute_f1(long long iters) {
    auto start = high_resolution_clock::now();
    double sum = 0;
    for (long long x = 0; x < iters; ++x) {
        sum += (x * x) - (x * x) + (x * 4) - (x * 5) + x + x;
    }
    auto end = high_resolution_clock::now();
    return {sum, duration<double>(end - start).count()};
}

CalcResult compute_f2(long long iters) {
    auto start = high_resolution_clock::now();
    double sum = 0;
    for (long long x = 0; x < iters; ++x) {
        sum += x + x;
    }
    auto end = high_resolution_clock::now();
    return {sum, duration<double>(end - start).count()};
}

CalcResult compute_f3(double res1, double res2) {
    auto start = high_resolution_clock::now();
    double res3 = res1 + res2 - res1;
    auto end = high_resolution_clock::now();
    return {res3, duration<double>(end - start).count()};
}

    // fd1[0] —  для чтения из первого канала
    // fd1[1] —  для записи в первый канал
    // fd2 аналогично для второго канала

void run_processes(long long iters) {
    cout << " Итераций: " << iters << endl;

    int fd1[2], fd2[2];
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        cerr << "Ошибка создания pipe" << endl;
        return;
    }

    auto start_total = high_resolution_clock::now();

    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(fd1[0]); // Закрываем чтение
        CalcResult r1 = compute_f1(iters);
        write(fd1[1], &r1, sizeof(CalcResult));
        close(fd1[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        close(fd2[0]); // Закрываем чтение
        CalcResult r2 = compute_f2(iters);
        write(fd2[1], &r2, sizeof(CalcResult));
        close(fd2[1]);
        exit(0);
    }

    // Родительский процесс
    close(fd1[1]); // Закрываем запись
    close(fd2[1]);

    CalcResult r1, r2;
    waitpid(pid1, NULL, 0);
    read(fd1[0], &r1, sizeof(CalcResult));
    close(fd1[0]);

    waitpid(pid2, NULL, 0);
    read(fd2[0], &r2, sizeof(CalcResult));
    close(fd2[0]);

    CalcResult r3 = compute_f3(r1.value, r2.value);

    auto end_total = high_resolution_clock::now();
    double total_time = duration<double>(end_total - start_total).count();

    cout << "Результат Ф3: " << r3.value << endl;
    cout << "Время  1 : " << fixed << setprecision(6) << r1.time_sec << " сек." << endl;
    cout << "Время  2 : " << r2.time_sec << " сек." << endl;
    cout << "Время  3  " << r3.time_sec << " сек." << endl;
    cout << "Общее: " << total_time << " сек.\n" << endl;
}

int main() {
    vector<long long> iterations = {10000, 100000};
    for (long long iters : iterations) {
        run_processes(iters);
    }
    return 0;
}