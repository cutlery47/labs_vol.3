#include "complex.h"

Complex::Complex()
{

}

Complex::Complex(const double& val) {
    this->real = val;
    this->imag = 0;
}

Complex::Complex(QString str) {
    QString real_str;
    QString imag_str;
    str.chop(1);
    int index = str.indexOf('+');

    real_str = str.left(index + 1);
    imag_str = str.right(str.length() - index);

    this->real = real_str.toDouble();
    this->imag = imag_str.toDouble();
}

double Complex::getReal() {
    return real;
}

double Complex::getImag() {
    return imag;
}

QString Complex::toQString() {
    return QString::number(this->real) + " + " + QString::number(this->imag) + "i";
}


int Complex::abs() {
    return (this->real * this->real + this->imag * this->imag);
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

void Complex::operator=(QString str) {
    QString real_str;
    QString imag_str;
    str.chop(1);
    int index = str.indexOf('+');

    real_str = str.left(index);
    imag_str = str.right(str.length() - index - 1);

    this->real = real_str.toDouble();
    this->imag = imag_str.toDouble();
}

void Complex::operator=(int num) {
    this->real = num;
    this->imag = 0;
}

