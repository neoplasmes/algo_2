#include <iostream>
#include <string>
#include <math.h>
#include "binaryNumber.h"

using namespace std;



const int BinaryNumber::maxSize = 32;


//добавляет к объекту this число other
void BinaryNumber::adder(const BinaryNumber& other) {
    int initialSignLeft = this->value[0];
    int initialSignRight = other.value[0];

    //temp хранит знак для переноса
    int temp = 0;
    for (int i = maxSize - 1; i >= 0; i--) {
        //bitsum хранит результат текущего сложения двух битов + бит из temp
        int bitSum = this->value[i] + other.value[i] + temp;
        this->value[i] = bitSum % 2;
        temp = bitSum / 2;
    }

    //проверка на знак
    int finalSign = this->value[0];
    if ((initialSignLeft != finalSign) && (initialSignRight != finalSign)) {
        throw overflow_error("переполнение при вычислении, введите другие аргументы");
    }
}

//увеличивает this на один
void BinaryNumber::incrementor() {

    int initialSign = value[0];
    int temp = 1;
    for (int i = maxSize - 1; i >= 0; i--) {
        int bitSum = value[i] + temp;
        value[i] = bitSum % 2;
        temp = bitSum / 2;
        if (temp == 0) {
            break;
        }
    }
    int finalSign = value[0];
    if (initialSign != finalSign) {
        throw overflow_error("переполнение при вычислении, введите другие аргументы");
    }
}

//инвертирует this 
void BinaryNumber::invertor() {
    for (int i = 0; i < maxSize; i++) {
        value[i] = !value[i];
    }
}

//побитово сдвигает this на 1 влево
void BinaryNumber::shiftLeft() {
    for (int i = 0; i < maxSize - 1; i++) {
        value[i] = value[i + 1];
    }
    value[maxSize - 1] = 0;
}




//конструктор без инициализатора. создаёт число 0
BinaryNumber::BinaryNumber() {
    value = new int[maxSize];
    for (int i = 0; i < maxSize; i++) {
        value[i] = 0;
    }
}

//конструктор-копирщик, без которого не сработает оператор присваивания
BinaryNumber::BinaryNumber(const BinaryNumber& other) {
    this->value = new int[maxSize];
    for (int i = 0; i < maxSize; i++) {
        this->value[i] = other.value[i];
    }
}

//конструктор с десятичным числом-инициализатором
BinaryNumber::BinaryNumber(int n) {
    int at = maxSize - 1;
    int initializingValue = n;
    value = new int[maxSize];
    
    if (n >= 0) {
        value[0] = 0;

        while (n >= 1) {
            value[at--] = n % 2;
            n = n / 2;

            if (at < 0) {
                throw invalid_argument("десятичное число " + to_string(initializingValue) + " вне допустимого диапазона, введите другие аргументы");
            }
        }

        for (int i = 1; i <= at; i++) {
            value[i] = 0;
        }
    }
    else {
        value[0] = 1;
        //реверс числа из отрицательного в положительное с вычитанием единицы, чего требует дополнительный код
        n = 0 - n - 1;

        while (n >= 1) {
            value[at--] = !(n % 2);
            n = n / 2;
        }

        for (int i = 1; i <= at; i++) {
            value[i] = 1;
        }

        if (at < 0) {
            throw invalid_argument("десятичное число " + to_string(initializingValue) + " вне допустимого диапазона, введите другие аргументы");
        }
    }  
}

//оператор взятия одного конкретного бита
int& BinaryNumber::operator[](size_t i) {
    return value[i];
}

const int& BinaryNumber::operator[](size_t i) const{
    return value[i];
}

//оператор присваивания
BinaryNumber& BinaryNumber::operator=(const BinaryNumber& other) {
    for (int i = 0; i < maxSize; i++) {
        this->value[i] = other.value[i];
    }

    return (*this);
}

//оператор добавления, НЕ создаёт новый объект. По сути нужен для комфортной реализации умножения
BinaryNumber& BinaryNumber::operator+=(const BinaryNumber& other) {
    int initialSignLeft = this->value[0];
    int initialSignRight = other.value[0];

    //temp хранит знак для переноса
    int temp = 0;
    for (int i = maxSize - 1; i >= 0; i--) {
        //bitsum хранит результат текущего сложения двух битов + бит из temp
        int bitSum = this->value[i] + other.value[i] + temp;
        this->value[i] = bitSum % 2;
        temp = bitSum / 2;
    }

    //проверка на знак
    int finalSign = this->value[0];
    if ((initialSignLeft != finalSign) && (initialSignRight != finalSign)) {
        throw overflow_error("переполнение при вычислении, введите другие аргументы");
    }

    return (*this);
}

//оператор сложения, создаёт новый объект
BinaryNumber BinaryNumber::operator+(const BinaryNumber& other) {
    BinaryNumber leftCopy = (*this);
    leftCopy += other;
    return leftCopy;
}

//оператор вычитания. создаёт новый объект. 
BinaryNumber BinaryNumber::operator-(BinaryNumber other) {
    other.invertor();
    other.incrementor();
    return (*this) + other;
}


//оператор умножения, создаёт новый объект.
BinaryNumber BinaryNumber::operator*(const BinaryNumber& other) {
    BinaryNumber result;
    //копия левого члена выражения, которая будет сдвигаться и прибавляться к результату
    BinaryNumber temp = (*this);
    for (int i = maxSize - 1; i >= 0; i--) {
        if (other.value[i] == 1) {
            result += temp;
        }

        temp.shiftLeft();
    }

    return result;
}


//возвращает указатель на массив с битами
int* BinaryNumber::getBinaryValue() {
    return value;
}

//функкция, чтобы получить десятичное значение числа
int BinaryNumber::getDecimalValue() {
    int result = 0;
    if (value[0] == 0) {
        for (int i = 1; i < maxSize; i++) {
            if (value[i] == 1) {
                result += pow(2, (maxSize - 1) - i);
            }
        }
    }
    else {
        for (int i = 1; i < maxSize; i++) {
            if (value[i] == 0) {
                result -= pow(2, (maxSize - 1) - i);
            }
        }

        result -= 1;
    }

    return result;
}

//деконструктор, очищающий память
BinaryNumber::~BinaryNumber() {
    delete[] value;
}
