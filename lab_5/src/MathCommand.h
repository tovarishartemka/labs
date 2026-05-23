#pragma once
#include "Command.h"
#include <iostream>
//enum перечисление
enum class MathType {
    ADD,
    SUB,
    MUL,
    DIV
};

class MathCommand : public Command {
private:
    double a;
    double b;
    MathType type;

public:
    MathCommand(double x,
                double y,
                MathType t)
        : a(x), b(y), type(t) {}

    void execute() override {

        double result = 0;

        switch (type) {

        case MathType::ADD:
            result = a + b;
            break;

        case MathType::SUB:
            result = a - b;
            break;

        case MathType::MUL:
            result = a * b;
            break;

        case MathType::DIV:
            result = a / b;
            break;
        }

        std::cout << "Result: "
                  << result << std::endl;
    }
};