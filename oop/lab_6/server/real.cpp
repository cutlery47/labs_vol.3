
#include "real.h"

Real::Real()
{

}

Real::Real(double val) {
    this->val = val;
}

Real Real::abs()
{
    if (this->val > 0)
    {
        return *this;
    }

    return Real(-1 * this->val);
}

Real Real::operator*(Real num)
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

Real Real::operator-()
{
    this->val *= -1;
    return *this;
}

