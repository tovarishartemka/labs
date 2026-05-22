#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// f(x) = x^2-x^2+x*4-x*5+x+x
double f1(long long iters) {
    double sum = 0;
    for (long long x = 0; x < iters; ++x) {
        sum += (x * x) - (x * x) + (x * 4) - (x * 5) + x + x;
    }
    return sum;
}

// f(x) = x+x
double f2(long long iters) {
    double sum = 0;
    for (long long x = 0; x < iters; ++x) {
        sum += x + x;
    }
    return sum;
}

//  3
double f3(double res1, double res2) {
    return res1 + res2 - res1;
}

void run_sequence(long long iters) {
    cout << " Итераций: " << iters  << endl;
    auto start_total = high_resolution_clock::now();

    double r1 = f1(iters);
    double r2 = f2(iters);
    double r3 = f3(r1, r2);

    auto end_total = high_resolution_clock::now();
    double total_time = duration<double>(end_total - start_total).count();

    cout << "Результат Ф3: " << r3 << endl;
    cout << "время выполнения: " << fixed << setprecision(6) << total_time << " сек.\n" << endl;
}

int main() {
    vector<long long> iterations = {10000, 100000};
    for (long long iters : iterations) {
        run_sequence(iters);
    }
    return 0;
}