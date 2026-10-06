#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include "employee.h"

void runChildWith2Args(const char* path, const std::string& a1, const std::string& a2) {
    pid_t pid = fork();
    if (pid == 0) {
        execl(path, path, a1.c_str(), a2.c_str(), (char*)NULL);
        std::cerr << "Ошибка запуска " << path << "\n";
        _exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        std::cerr << "fork() не удался\n";
    }
}

void runChildWith3Args(const char* path, const std::string& a1, const std::string& a2, const std::string& a3) {
    pid_t pid = fork();
    if (pid == 0) {
        execl(path, path, a1.c_str(), a2.c_str(), a3.c_str(), (char*)NULL);
        std::cerr << "Ошибка запуска " << path << "\n";
        _exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        std::cerr << "fork() не удался\n";
    }
}

int main() {
    std::string binFileName;
    int n;
    std::cout << "Введите имя бинарного файла: ";
    std::cin >> binFileName;
    std::cout << "Введите количество записей: ";
    std::cin >> n;

    runChildWith2Args("./creator", binFileName, std::to_string(n));

    std::cout << "\nСодержимое файла " << binFileName << ":\n";
    std::ifstream in(binFileName, std::ios::binary);
    employee emp;
    while (in.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << emp.num << " | " << emp.name << " | " << emp.hours << "\n";
    }
    in.close();

    std::string reportFileName;
    std::string rate;
    std::cout << "\nВведите имя файла отчета: ";
    std::cin >> reportFileName;
    std::cout << "Введите оплату за час: ";
    std::cin >> rate;

    runChildWith3Args("./reporter", binFileName, reportFileName, rate);

    std::cout << "\n--- Отчет ---\n";
    std::ifstream reportIn(reportFileName);
    std::string line;
    while (std::getline(reportIn, line)) {
        std::cout << line << "\n";
    }
    reportIn.close();

    return 0;
}