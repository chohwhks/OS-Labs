#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "creator: нужно 2 аргумента - имя файла и число записей\n";
        return 1;
    }

    const char* binFileName = argv[1];
    int n = std::atoi(argv[2]);

    std::ofstream out(binFileName, std::ios::binary);
    if (!out) {
        std::cerr << "creator: не удалось открыть файл " << binFileName << "\n";
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        employee emp{};

        std::cout << "Сотрудник " << (i + 1) << " из " << n << ":\n";

        std::cout << "  Номер: ";
        std::cin >> emp.num;

        std::cout << "  Имя: ";
        std::string name;
        std::cin >> name;
        std::strncpy(emp.name, name.c_str(), sizeof(emp.name) - 1);
        emp.name[sizeof(emp.name) - 1] = '\0';

        std::cout << "  Часы: ";
        std::cin >> emp.hours;

        out.write(reinterpret_cast<char*>(&emp), sizeof(employee));
    }

    out.close();
    return 0;
}