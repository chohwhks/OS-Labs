#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include "employee.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "reporter: нужно 3 аргумента - бинарник, файл отчета, ставка\n";
        return 1;
    }

    const char* binFileName = argv[1];
    const char* reportFileName = argv[2];
    double rate = std::stod(argv[3]);

    std::ifstream in(binFileName, std::ios::binary);
    if (!in) {
        std::cerr << "reporter: не удалось открыть " << binFileName << "\n";
        return 1;
    }

    std::ofstream out(reportFileName);
    if (!out) {
        std::cerr << "reporter: не удалось создать " << reportFileName << "\n";
        return 1;
    }

    out << "Отчет по файлу \"" << binFileName << "\"\n\n";
    out  << "Номер   Имя         Часы      Зарплата\n";

    employee emp;
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        double salary = emp.hours * rate;
        out << std::left << std::setw(8) << emp.num
            << std::setw(12) << emp.name
            << std::setw(10) << emp.hours
            << std::setw(12) << std::fixed << std::setprecision(2) << salary
            << "\n";
    }

    in.close();
    out.close();
    return 0;
}