#include <iostream>
#include <ctime>

double calculate(double x)
{
    return x * x - x * x + x * 4 - x * 5 + x + x;
}

int main()
{
    long long n;
    double res = 0;
    double x = 10.0;

    while (true)
    {
        std::cout << "Input number of iterations: ";

        if (!(std::cin >> n))
        {
            std::cout << "Input is not a number. Program finished.\n";
            break;
        }

        clock_t start = clock();

        for (long long i = 0; i < n; ++i)
        {
            res = calculate(x);
        }

        clock_t end = clock();

        double elapsed_time =
            static_cast<double>(end - start) / CLOCKS_PER_SEC;

        std::cout << "Time = " << elapsed_time
            << " sec; Result(x = 10) = "
            << res << "\n\n";
    }

    return 0;
}
