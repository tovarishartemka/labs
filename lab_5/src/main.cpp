#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "Parser.h"

void executeLine(std::string line,
                 int threadId)
{
    auto start =
        std::chrono::system_clock::now();

    std::cout << "[THREAD "
              << threadId
              << "] START\n";

    auto commands = Parser::parse(line);

    for (auto cmd : commands) {
        cmd->execute();
    }

    for (auto cmd : commands) {
        delete cmd;
    }

    auto end =
        std::chrono::system_clock::now();

    std::cout << "[THREAD "
              << threadId
              << "] FINISH\n";
}

int main()
{
    std::vector<std::string> lines;

    std::cout
        << "Enter commands.\n";
    std::cout
        << "Type END to finish.\n";

    while (true) {

        std::string line;

        getline(std::cin, line);

        if (line == "END")
            break;

        lines.push_back(line);
    }

    std::vector<std::thread> threads;

    for (int i = 0;
         i < lines.size();
         i++)
    {
        threads.push_back(
            std::thread(
                executeLine,
                lines[i],
                i + 1
            )
        );
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}