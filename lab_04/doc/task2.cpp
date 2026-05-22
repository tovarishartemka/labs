#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct CalcResult {
    double value;
    double time_sec;
};

CalcResult f1(long long iters) {
    auto start = high_resolution_clock::now();
    double sum = 0;
    for (long long x = 0; x < iters; ++x) {
        sum += (x * x) - (x * x) + (x * 4) - (x * 5) + x + x;
    }
    auto end = high_resolution_clock::now();
    return {sum, duration<double>(end - start).count()};
}

CalcResult f2(long long iters) {
    auto start = high_resolution_clock::now();
    double sum = 0;
    for (long long x = 0; x < iters; ++x) {
        sum += x + x;
    }
    auto end = high_resolution_clock::now();
    return {sum, duration<double>(end - start).count()};
}

CalcResult f3(double res1, double res2) {
    auto start = high_resolution_clock::now();
    double res3 = res1 + res2 - res1;
    auto end = high_resolution_clock::now();
    return {res3, duration<double>(end - start).count()};
}

void run_threads(long long iters) {
    cout << "Итераций: " << iters << endl;
    CalcResult r1, r2;
    auto start_total = high_resolution_clock::now();

    thread t1([&]() { r1 = f1(iters); }); // 1  в 1 поток
    thread t2([&]() { r2 = f2(iters); }); // 2 в 2 поток

    t1.join();
    t2.join(); 

    CalcResult r3 = f3(r1.value, r2.value);

    auto end_total = high_resolution_clock::now();
    double total_time = duration<double>(end_total - start_total).count();

    cout << "Результат Ф3: " << r3.value << endl;
    cout << "Шаг 1: " << fixed << setprecision(6) << r1.time_sec << " сек." << endl;
    cout << " Шаг 2 : " << r2.time_sec << " сек." << endl;
    cout <<  "Шаг 3 : " << r3.time_sec << " сек." << endl;
    cout << "Общая длительность : " << total_time << " сек.\n" << endl;
}

int main() {
    vector<long long> iterations = {10000, 100000};
    for (long long iters : iterations) {
        run_threads(iters);
    }
    return 0;
}