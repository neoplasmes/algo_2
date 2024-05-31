#pragma once


class BinaryNumber {
private:
    static const int maxSize;
    int* value;


    //���������� ��� ����� � ���������� �����
    BinaryNumber summator(const BinaryNumber& arg1, const BinaryNumber& arg2);

    //��������� � ������� this ����� other
    void adder(const BinaryNumber& other);

    //����������� this �� ����
    void incrementor();

    //����������� this 
    void invertor();

    //�������� �������� this �� 1 �����
    void shiftLeft();

public:
    //��������� �����������, ��� ����
    BinaryNumber();

    //����������� ����� ��� ������� �� �������� �����
    BinaryNumber(const BinaryNumber& other);

    //����������� � ���������� ������-���������������
    BinaryNumber(int n);


    BinaryNumber& operator=(const BinaryNumber& other);

    BinaryNumber& operator+=(const BinaryNumber& other);

    BinaryNumber operator+(const BinaryNumber& other);

    //�� ��������, ����� �� �������� ������ �����
    BinaryNumber operator-(BinaryNumber other);

    BinaryNumber operator*(const BinaryNumber& other);

    int& operator[](size_t i);
    const int& operator[](size_t i) const;

    int* getBinaryValue();

    int getDecimalValue();

    ~BinaryNumber();
};