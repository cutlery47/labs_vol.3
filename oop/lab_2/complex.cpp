#include "complex.h"

Complex::Complex()
{

}

double Complex::getReal() {
    return real;
}

double Complex::getImag() {
    return imag;
}

Complex::Complex(const double& val) {
    real = val;
    imag = 0;
}

std::ostream& operator << (std::ostream& os, Complex val) {
    os << "(" << val.getReal() << ") + (" << val.getImag() << " * i)";
    return os;
}

std::istream& operator >> (std::istream& is, Complex& val) {
    is >> val.real >> val.imag;
    return is;
}

Complex Complex::operator * (Complex val) {
    Complex tmp;
    tmp.real = real * val.real - imag * val.imag;
    tmp.imag = real * val.imag + imag * val.real;
    return tmp;
}

bool Complex::operator == (Complex val) {
    if (real == val.real and imag == val.imag) {
        return true;
    } else {
        return false;
    }
}

bool Complex::operator != (Complex val) {
    if (real != val.real or imag != val.imag) {
        return true;
    } else {
        return false;
    }
}

Complex Complex::operator + (Complex val) {
    Complex tmp;
    tmp.real = real + val.real;
    tmp.imag = imag + val.imag;
    return tmp;
}

Complex Complex::operator - (Complex val) {
    Complex tmp;
    tmp.real = real - val.real;
    tmp.imag = imag - val.imag;
    return tmp;
}

Complex Complex::operator / (Complex val) {
    Complex tmp;
    tmp.real = (real * val.real + imag * val.imag) / (val.real * val.real + val.imag * val.imag);
    tmp.imag = (val.real * imag - real * val.imag) / (val.real * val.real + val.imag * val.imag);
    return tmp;
}

Complex Complex::operator - () {
    Complex tmp;
    tmp.real = -real;
    tmp.imag = -imag;
    return tmp;
}
