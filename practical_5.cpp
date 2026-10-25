#include <iostream>
using namespace std;

class Rectangle
{
private:
    float length, width;

public:
    // Constructor
    Rectangle(float l, float w)
    {
        length = l;
        width = w;
    }

    // Function to calculate area
    float area()
    {
        return length * width;
    }

    // Function to calculate perimeter
    float perimeter()
    {
        return 2 * (length + width);
    }

    // Destructor
    ~Rectangle()
    {
        cout << "Rectangle object destroyed." << endl;
    }
};

int main()
{
    float length, width;

    cout << "Enter length of rectangle: ";
    cin >> length;

    cout << "Enter width of rectangle: ";
    cin >> width;

    Rectangle r(length, width);

    cout << "Area = " << r.area() << endl;
    cout << "Perimeter = " << r.perimeter() << endl;

    return 0;
}