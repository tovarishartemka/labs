#pragma once
#include <vector>
#include <string>
#include "Command.h"

class Parser {
public: //принимаем строку
    static std::vector<Command*> parse(
        const std::string& line);
};
