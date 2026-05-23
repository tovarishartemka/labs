#pragma once
#include "Command.h"
#include <fstream>

class FileCommand : public Command {
private:
    std::string filename; //здесь имя файла
    std::string text; // тут его содержимое

public: //конструктор
    FileCommand(const std::string& file,
                const std::string& txt)
        : filename(file), text(txt) {} //кладу значение сюда 

    void execute() override {           //перезапись
        std::ofstream out(filename, std::ios::app); // std::ios::app - запись в конец

        if (out.is_open()) {
            out << text << std::endl; //ofstream работа с файлами
        }
    }
};
