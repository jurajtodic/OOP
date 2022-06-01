#include <iostream>
#include <cmath>
using namespace std;

class Triangle;
class Point {
public:
    double x, y;
    
    Point(){
        x = 0.0;
        y = 0.0;
    }

    Point (double a, double b){
        x = a;
        y = b;
    }

    ~Point(){}

    bool isInsideTriangle(const Triangle&);
    void print (){
        cout << "(x,y) = (" << x << "," << y <<")";
    }
};


class Triangle {
public:
    Point A, B, C; 
    Triangle (const Point& _A, const Point& _B, const Point& _C){
        A=_A;
        B=_B;
        C=_C;
    }
    ~Triangle(){};
    void print(){
        cout << "Trokut sa vrhovima (x1,y1),(x2,y2),(x3,y3) = (" << A.x << "," << A.y << "),(" << B.x << "," << B.y << "),(" << C.x << "," << C.y << ")" << endl;
    }
};

double area (const Point& p1, const Point& p2, const Point& p3) {
    return abs((p1.x*(p2.y-p3.y) + p2.x*(p3.y-p1.y)+ p3.x*(p1.y-p2.y))/2.0); 
} 
  

bool isInsideTriangle(const Triangle& T, const Point& p) 
{    
/* Calculate area of triangle ABC */
   double wholearea = area (T.A, T.B, T.C); 
  
   /* Calculate area of triangle PBC */   
   double area1 = area (p, T.B, T.C); 
  
   /* Calculate area of triangle PAC */   
   double area2 = area (T.A, p, T.C); 
  
   /* Calculate area of triangle PAB */    
   double area3 = area (T.A, T.B, p); 
    
   /* Check if sum of A1, A2 and A3 is same as A */ 
    return (wholearea == area1 + area2 + area3);
} 


int main ()
{
    // PR 1.
    Point *p11 = new Point(0,0);
    Point *p12 = new Point(20,0);
    Point *p13 = new Point(10,30);
    Point *p14 = new Point(10,15);
    Triangle *T1 = new Triangle (*p11,*p12,*p13);
    T1->print();
    if (isInsideTriangle (*T1,*p14) == 1) {
        cout << "Tocka ";
        p14->print(); 
        cout << " je u trokutu" << endl;
        cout << endl;
    }
    else{
        cout << "Tocka ";
        p14->print(); 
        cout << " nije u trokutu" << endl;
        cout << endl;
    }

    // PR 2.
    Point *p21 = new Point(6,0);
    Point *p22 = new Point(12,1);
    Point *p23 = new Point(9,9);
    Point *p24 = new Point(9,3);
    Triangle *T2 = new Triangle (*p21,*p22,*p23);
    T2->print();
    if (isInsideTriangle (*T2,*p24) == 1) {
        cout << "Tocka ";
        p24->print(); 
        cout << " je u trokutu" << endl;
        cout << endl;
    }
    else{
        cout << "Tocka ";
        p24->print(); 
        cout << " nije u trokutu" << endl;
        cout << endl;
    }    

    // PR 3.
    Point *p31 = new Point(-5,0);
    Point *p32 = new Point(-1,2);
    Point *p33 = new Point(-3,-6);
    Point *p34 = new Point(-6,1);
    Triangle *T3 = new Triangle (*p31,*p32,*p33);
    T3->print();
    if (isInsideTriangle (*T3,*p34) == 1) {
        cout << "Tocka ";
        p34->print(); 
        cout << " je u trokutu" << endl;
    }
    else{
        cout << "Tocka ";
        p34->print(); 
        cout << " nije u trokutu" << endl;
    } 
    
    delete p11;
    delete p12;
    delete p13;   
    delete p14;
    delete p21;
    delete p22;
    delete p23;   
    delete p24;
    delete p31;
    delete p32;
    delete p33;   
    delete p34;
    delete T1;
    delete T2;   
    delete T3;
    return 0;
}