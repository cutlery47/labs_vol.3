
#include "real.h"

Real::Real()
{

}

Real::Real(const double& val) {
    this->val = val;
}

Real::Real(const Real& num) {
    this->val = num.val;
}

Real::Real(QString str) {
    this->val = str.toDouble();
}

double Real::value() {
    return this->val;
}

QString Real::toQString() {
    return QString::number(this->val);
}

Real Real::abs()
{
    if (this->val > 0)
    {
        return this->val;
    }

    return Real(-1 * this->val);
}

Real Real::operator * (Real num)
{
    Real temp;
    temp.val = this->val * num.val;
    return temp;
}

Real Real::operator+(Real num)
{
    Real temp;
    temp.val = this->val + num.val;
    return temp;
}

Real Real::operator/(Real num)
{
    Real temp;
    temp.val = this->val / num.val;
    return temp;
}

Real Real::operator-(Real num)
{
    Real temp;
    temp.val = this->val - num.val;
    return temp;
}

bool Real::operator==(Real num)
{
    return this->val == num.val;
}

bool Real::operator>(Real num)
{
    return this->val > num.val;
}

bool Real::operator<(Real num)
{
    return this->val < num.val;
}

bool Real::operator!=(Real num)
{
    return this->val != num.val;
}

void Real::operator=(Real num) {
    this->val = num.val;
}

Real Real::operator-() {
    this->val = -this->val;
    return *this;
}





