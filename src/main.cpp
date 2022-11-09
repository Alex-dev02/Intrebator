#include <iostream>

#include <db/include/Database.hpp>

int main() {
    auto storage = Database::DB();
    std::cout << "Hello world!";
}
