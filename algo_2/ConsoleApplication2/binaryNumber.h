#pragma once


class BinaryNumber {
private:
    static const int maxSize;
    int* value;


    //складывает два чилса и возвращает новое
    BinaryNumber summator(const BinaryNumber& arg1, const BinaryNumber& arg2);

    //добавляет к объекту this число other
    void adder(const BinaryNumber& other);

    //увеличивает this на один
    void incrementor();

    //инвертирует this 
    void invertor();

    //побитово сдвигает this на 1 влево
    void shiftLeft();

public:
    //дефолтный конструктор, все нули
    BinaryNumber();

    //конструктор копия без которой не работает равно
    BinaryNumber(const BinaryNumber& other);

    //конструктор с десятичным числом-инициализатором
    BinaryNumber(int n);


    BinaryNumber& operator=(const BinaryNumber& other);

    BinaryNumber& operator+=(const BinaryNumber& other);

    BinaryNumber operator+(const BinaryNumber& other);

    //по значению, чтобы не изменять другое число
    BinaryNumber operator-(BinaryNumber other);

    BinaryNumber operator*(const BinaryNumber& other);

    int& operator[](size_t i);
    const int& operator[](size_t i) const;

    int* getBinaryValue();

    int getDecimalValue();

    ~BinaryNumber();
};