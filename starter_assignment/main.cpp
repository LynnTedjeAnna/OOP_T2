#include <iostream>
#include "administration.hpp"

int main() {
    // Providing a seed value
    srand((unsigned) time(NULL));
    Administration Administration;
    Administration.start();
    return 0;
}
