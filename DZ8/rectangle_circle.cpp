#include<iostream>
#include<cmath>
using namespace std;

class Shapes {
public:
    virtual double area() const = 0;
};

class Rectangle : public Shapes {
private:
    double width, height;
public:
    Rectangle(double width, double height): width{width}, height{height} {}
    double area() const override { return width * height; }
};

class Circle : public Shapes {
private:
    double radius;
public:
    Circle(double radius): radius{radius} {}
    double area() const override { return radius*radius*M_PI; }
};


int main()
{
    Rectangle r1{5.5, 7.2};
    Rectangle r2{0.2, 1.5};
    Rectangle r3{8.9, 9.8};
    Circle c1{1.5};
    Circle c2{2.6};
    Circle c3{2.7};

    // Shapes* arr[6] = {&r1, &r2, &r3, &c1, &c2, &c3};

    Shapes* o1 = &r1;
    Shapes* o2 = &r2;
    Shapes* o3 = &r3;
    Shapes* o4 = &c1;
    Shapes* o5 = &c2;
    Shapes* o6 = &c3;

    Shapes* arr[6] = { o1, o2, o3, o4, o5, o6};

    double s{0.0};
    for(Shapes* shape : arr) {
        s += (*shape).area() ;
    }
    cout << s;

    return 0;
}