#include "third_party/crow_all.h"
#include <iostream>

int main() {
    std::cout << "Crow test build OK!\n";
    // Можно запустить минимальный сервер:
    crow::SimpleApp app;
    app.port(8080).multithreaded().run();
    return 0;
}