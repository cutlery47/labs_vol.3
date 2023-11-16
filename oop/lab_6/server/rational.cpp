#include "rational.h"

Rational::Rational()
{
    numerator = 0;
    denominator = 1;
}

Rational::Rational(const int& val) {
    numerator = val;
    denominator = 1;
}

Rational::Rational(QString str) {
    QString str_num;
    QString str_den;
    int flag = 0;

    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '/') {
            flag = 1;
        } else {
            if (flag == 0) {
                str_num.append(str[i]);
            } else {
                str_den.append(str[i]);
            }
        }
    }

    // если знаменателя не было при вводе - добавляем единицу
    if (str_den.size() == 0) {
        str_den.append('1');
    }

    this->setDenominator(str_den.toInt());
    this->setNumerator(str_num.toInt());
}

int Rational::getNumerator() {
    return numerator;
}

int Rational::getDenominator() {
    return denominator;
}

void Rational::setNumerator(int val) {
    numerator = val;
}

void Rational::setDenominator(int val) {
    denominator = val;
}

QString Rational::toQString() {
    return QString::number(this->numerator) + "/" + QString::number(this->denominator);
}

int Rational::getGCD(Rational val) {
    int gcd = 0;

    if (denominator < val.denominator) {
        gcd = denominator;
    } else {
        gcd = val.denominator;
    }

    while (gcd > 0) {
        if (denominator % gcd == 0 and val.denominator % gcd == 0) {
            break;
        }
        gcd -= 1;
    }

    return gcd;
}

Rational Rational::simplify()
{
    //сначала знаки
    if(this->denominator < 0)
    {
        this->numerator *= -1;
        this->denominator *= -1;
    }
    // теперь сокращаем дробь
    int MAX = std::max(this->denominator, std::abs(this->numerator));
    for(int i = MAX; i > 1; i--)
    {
        if(this->numerator % i == 0 && this->denominator % i == 0)
        {
            this->numerator /= i;
            this->denominator /= i;
        }
    }

    return *this;
}

std::ostream& operator << (std::ostream& os, Rational val) {
    os << val.getNumerator() << " / " << val.getDenominator();
    return os;
}

std::istream& operator >> (std::istream& is, Rational& val) {
    is >> val.numerator >> val.denominator;
    return is;
}

Rational Rational::abs() {
    Rational tmp;
    tmp.setNumerator(std::abs(this->numerator));
    tmp.setDenominator(std::abs(this->denominator));

    return tmp;
}

bool Rational::operator == (Rational val) {
    int gcd = getGCD(val);

    // if new numerators are equal -> pog
    if (numerator * (val.denominator / gcd) == val.numerator * (denominator / gcd)) {
        return true;
    } else {
        return false;
    }
}

bool Rational::operator > (Rational val) {
    int gcd = getGCD(val);

    if (numerator * (val.denominator / gcd) > val.numerator * (denominator / gcd)) {
        return true;
    } else {
        return false;
    }
}

bool Rational::operator < (Rational val) {
    int gcd = getGCD(val);

    if (numerator * (val.denominator / gcd) < val.numerator * (denominator / gcd)) {
        return true;
    } else {
        return false;
    }
}

bool Rational::operator != (Rational val) {
    int gcd = getGCD(val);

    if (numerator * (val.denominator / gcd) != val.numerator * (denominator / gcd)) {
        return true;
    } else {
        return false;
    }
}

Rational Rational::operator + (Rational val) {
    Rational tmp;
    int gcd = this->getGCD(val);

    int new_num = numerator * (val.denominator / gcd) + val.numerator * (denominator / gcd);
    int new_den = denominator * (val.denominator / gcd);

    tmp.numerator = new_num;
    tmp.denominator = new_den;

    return tmp;
}

Rational Rational::operator - (Rational val) {
    Rational tmp;
    int gcd = this->getGCD(val);

    int new_num = numerator * (val.denominator / gcd) - val.numerator * (denominator / gcd);
    int new_den = denominator * (val.denominator / gcd);

    tmp.numerator = new_num;
    tmp.denominator = new_den;
    return tmp;
}

Rational Rational::operator / (Rational val) {
    Rational tmp;
    tmp.numerator = numerator * val.denominator;
    tmp.denominator = denominator * val.numerator;

    if (tmp.getDenominator() < 0 and tmp.getNumerator() < 0) {
        tmp.setDenominator(tmp.getDenominator() * -1);
        tmp.setNumerator(tmp.getNumerator() * -1);
    }

    return tmp;
}

Rational Rational::operator * (Rational val) {
    Rational tmp;
    tmp.numerator = numerator * val.numerator;
    tmp.denominator = denominator * val.denominator;

    if (tmp.getDenominator() < 0 and tmp.getNumerator() < 0) {
        tmp.setDenominator(tmp.getDenominator() * -1);
        tmp.setNumerator(tmp.getNumerator() * -1);
    }

    return tmp;
}


Rational Rational::operator - () {
    Rational tmp;
    tmp.numerator = -numerator;
    tmp.denominator = denominator;
    return tmp;
}
