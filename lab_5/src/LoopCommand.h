#pragma once   //это все команда на повторение
#include "Command.h"
#include <vector>

class LoopCommand : public Command {
private:
    int count;
    std::vector<Command*> commands; //адресса наследников

public:
    LoopCommand(int c,
                const std::vector<Command*>& cmds) //<Command*>& ссылка на вектор хранящий указатели Command  чтобы не копировать вектор
        : count(c), commands(cmds) {}

    void execute() override {

        for (int i = 0; i < count; i++) {

            for (auto cmd : commands) {
                cmd->execute(); //(*cmd).execute(); 
            }
        }
    }

    ~LoopCommand() {

        for (auto cmd : commands) {
            delete cmd;
        }
    }
};
