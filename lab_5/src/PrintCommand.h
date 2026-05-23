//писать итог команды
#pragma once
#include "Command.h"
#include <iostream>

class PrintCommand : public Command {
private:
    std::string text;

public:
    PrintCommand(const std::string& txt) : text(txt) {}

    void execute() override {
        std::cout << text << std::endl;
    }
};
