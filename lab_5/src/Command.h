#pragma once
#include <string>

class Command {
public:
    virtual void execute() = 0; //vitrial дает менять функцию у наследников
    virtual ~Command() {} //деструктор
};
