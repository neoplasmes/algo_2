#include <iostream>

#include "ExpressionReader.h"

using namespace std;

void printBinaryNumber(const BinaryNumber& n) {
    for (size_t i = 0; i < 8; i++) {
        cout << n[i];
    }

    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");
    
    ExpressionReader reader;
    cout << reader.calculateFromPostfix("  665 5 *  75 +").getDecimalValue() << endl;
    

    return 0;
}