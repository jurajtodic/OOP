#include <iostream>
using namespace std;

class SquareMatrix {
public:
/*
*pokazivač na dimanički alocirano polje duljine M čiji su elementi
*pokazivači na dinamički alocirana polja duljine M (retci u matrici)
*/
    double** container;
    unsigned int M;

    SquareMatrix() = delete;
    // inicijaliziraj sve ćelije na 0.0
    SquareMatrix(unsigned int);
    SquareMatrix(const SquareMatrix&);
    ~SquareMatrix();

    double* operator[](unsigned int);
    const double* operator[](unsigned int) const;

    SquareMatrix& operator=(const SquareMatrix&);
    SquareMatrix& operator+=(const SquareMatrix&);
    SquareMatrix& operator-=(const SquareMatrix&);
    SquareMatrix& operator*=(const SquareMatrix&);

    // postavi sve celije na isti skalar
    SquareMatrix& operator=(double);
    // svim celijama nadodaj isti skalar
    SquareMatrix& operator+=(double);
    // od svih ćelija oduzmi isti skalar
    SquareMatrix& operator-=(double);
    // svaku ćeliju pomnoži sa skalarom
    SquareMatrix& operator*=(double);
    // svaku ćeliju podijeli sa skalarom
    SquareMatrix& operator/=(double);

    SquareMatrix operator+(const SquareMatrix&) const;
    SquareMatrix operator-(const SquareMatrix&) const;
    SquareMatrix operator*(const SquareMatrix&) const;

    SquareMatrix operator+(double) const;
    SquareMatrix operator-(double) const;
    SquareMatrix operator*(double) const;
    SquareMatrix operator/(double) const;

    bool operator==(const SquareMatrix&) const;
    bool operator!=(const SquareMatrix&) const;
};

double* SquareMatrix :: operator[] (unsigned int i) {
    return container[i]; // vraca i-ti redak u matrici
}

const double* SquareMatrix :: operator[] (unsigned int i) const {
    return container[i]; // vraca i-ti redak u matrici
}

SquareMatrix :: SquareMatrix (unsigned int n) : M{M}, container{new double* [M]} {
    for (unsigned int i = 0; i<M; ++i)
        container[i] = new double [M]; // stvoriti redke u matrici
    for (unsigned int i = 0; i<M; ++i)
        for (unsigned int j = 0; j<M; ++j)
            (*this)[i][j] = 0.0; // za i-ti redak dohvatimo j-ti element
                                 // overloadali smo operator dohvacanja 
}

SquareMatrix :: SquareMatrix (const SquareMatrix& m): M{M}, container{new double* [m.M]} {
    for(int i = 0; i<M ; i++)
        container[i] = new double [M];
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j]=m[i][j];
}

SquareMatrix :: ~SquareMatrix() {
    for (int i = 0; i< M; i++)
        delete[] container[i]; // brisemo redke
    delete [] container; // obrisemo cijelu matricu
}

SquareMatrix& SquareMatrix :: operator=(const SquareMatrix& m) {
    // izbrisemo matricu koja je pozvala = ...
    this->~SquareMatrix(); 
    // pa napravimo drugu...
    container = new double* [m.M];
    for (int i = 0; i<M; i++)
        container [i] = new double [M];
    // i pridruzimo joj vrijednosti desne matrice
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j]=m[i][j];
    return (*this);
}

SquareMatrix& SquareMatrix :: operator+=(const SquareMatrix& m) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j] +=m [i][j];
    return (*this);
}

SquareMatrix& SquareMatrix :: operator-=(const SquareMatrix& m) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j] -= m[i][j];
    return (*this);
}


// ovo ne valja -> treba primjeniti matricno mnozenje
SquareMatrix& SquareMatrix :: operator *= (const SquareMatrix& m) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j] *= m[i][j];
    return (*this);
}

SquareMatrix& SquareMatrix :: operator=(double val) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j]=val;
    return (*this);
}

SquareMatrix& SquareMatrix :: operator+=(double val) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j]+=val;
    return (*this);
}

SquareMatrix& SquareMatrix :: operator-=(double val) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j]-=val;
    return (*this);
}

SquareMatrix& SquareMatrix :: operator*=(double val) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j]*=val;
    return (*this);
}

SquareMatrix& SquareMatrix :: operator/=(double val) {
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            (*this)[i][j]/=val;
    return (*this);
}

SquareMatrix SquareMatrix :: operator+(const SquareMatrix& m) const {
    SquareMatrix w{*this};
    return w+=m;
    /*
    SquareMatrix w{M};
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            w[i][j] = (*this)[i][j] + m[i][j];
    return w;
    */
}

SquareMatrix SquareMatrix :: operator-(const SquareMatrix& m) const {
    SquareMatrix w{*this};
    return w-=m;
    /*
    SquareMatrix w{M};
    for (int i = 0; i<M; i++)
        for (int j = 0; j<M; j++)
            w[i][j] = (*this)[i][j] - m[i][j];
    return w;
    */
}

SquareMatrix SquareMatrix :: operator*(const SquareMatrix& m) const {
    SquareMatrix w{M};
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < M; ++j)
            for(int k = 0; k < M; ++k)
                w[i][j] += (*this)[i][k] * m[k][j];
    return w;
}

SquareMatrix SquareMatrix :: operator+(double val) const {
    return SquareMatrix{*this} += val;
}

SquareMatrix SquareMatrix :: operator-(double i) const {
    return SquareMatrix{*this} -= i;
}

SquareMatrix SquareMatrix :: operator*(double i) const {
    return SquareMatrix{*this} *= i;
}

SquareMatrix SquareMatrix :: operator/(double i) const {
    return SquareMatrix{*this} /= i;
}

bool SquareMatrix :: operator==(const SquareMatrix& m) const {
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < M; ++j)
            if ((*this)[i][j] != m[i][j]) 
                return false;
    return true;
}

bool SquareMatrix :: operator!=(const SquareMatrix& m ) const {
    return !((*this)==m);
}

// PREOPTERECENI OPERATOR ISPISA 
ostream& operator << (ostream& os, const SquareMatrix& m) {
    for (int i=0; i< m.M;i++) {
        for (int j=0; j< m.M;j++) 
            os << "[" << m[i][j] << "] ";
        os << endl;
    }
    os << endl;
}

int main ()
{
    SquareMatrix m1{10};
    cout << m1;
    /*
    double br=1.0;
    for (int i=0; i< 10;i++)
        for (int j=0; j< 10;j++)
            if (i == j) {
                m1[i][j]=br;
                br++;
            }
    */
    m1 += 1.0;
    cout <<m1;
    
    SquareMatrix m2{m1};
    m2 /= 10;
    cout << m2;
    return 0;
}