#include "Parser.h"

#include "PrintCommand.h"
#include "FileCommand.h"
#include "MathCommand.h"

#include <sstream>

std::vector<Command*> Parser::parse(
    const std::string& line)
{
    std::vector<Command*> commands;

    std::stringstream ss(line);

    std::string cmd;

    while (ss >> cmd) { // записать в cmd  из ss слово

        if (cmd == "PRINT") {

            std::string text;
            getline(ss, text);

            commands.push_back(
                new PrintCommand(text));
        }

        else if (cmd == "ADD") {

            double a, b;
            ss >> a >> b;

            commands.push_back(
                new MathCommand(a, b,
                MathType::ADD));
        }

        else if (cmd == "SUB") {

            double a, b;
            ss >> a >> b;

            commands.push_back(
                new MathCommand(a, b,
                MathType::SUB));
        }

        else if (cmd == "MUL") {

            double a, b;
            ss >> a >> b;

            commands.push_back(
                new MathCommand(a, b,
                MathType::MUL));
        }

        else if (cmd == "DIV") {

            double a, b;
            ss >> a >> b;

            commands.push_back(
                new MathCommand(a, b,
                MathType::DIV));
        }
    }

    return commands;
}
