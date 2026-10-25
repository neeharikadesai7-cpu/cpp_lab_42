#include <iostream>
using namespace std;

class Complex
{
private:
    int real, imag;

public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}

    // Addition
    Complex add(const Complex &x1, const Complex &x2)
    {
        Complex x3;
        x3.real = x1.real + x2.real;
        x3.imag = x1.imag + x2.imag;
        return x3;
    }

    // Subtraction
    Complex subtract(const Complex &c)
    {
        return Complex(real - c.real, imag - c.imag);
    }

    // Display
    void display() const
    {
        cout << real << " + i" << imag << endl;
    }
};

int main()
{
    Complex c1(4, 5), c2(8, 9);

    Complex sum;
    sum = sum.add(c1, c2);

    Complex diff = c1.subtract(c2);

    cout << "First Complex Number: ";
    c1.display();

    cout << "Second Complex Number: ";
    c2.display();

    cout << "Addition: ";
    sum.display();

    cout << "Subtraction: ";
    diff.display();

    return 0;
}