#include "forces_and_moments.h"

#include <cassert>
#include <iostream>

#include "balk.h"

namespace
{

constexpr int factorial(int n) noexcept
{
    if (n <= 1)
    {
        return 1;
    }
    int res = 1;
    while (n > 1)
    {
        res *= (n--);
    }
    return res;
}

constexpr double power(double value, int pow) noexcept
{
    double res = 1;
    while (pow-- > 0)
    {
        res *= value;
    }
    return res;
}

} // namespace

constexpr Term::Term(int shift, double segment_length, bool is_unknown)
    : shift(shift), segment_length(segment_length), is_unknown(is_unknown)
{
}

constexpr double Term::calculatePolinomAtPoint(double x, double scalar, int degree) const
{
    if (degree < 0)
    {
        return 0;
    }
    return scalar * power(x, degree) / factorial(degree);
}

HingeSupport::HingeSupport(int shift, double segment_length)
    : Term(shift, segment_length, true)
{
}

double HingeSupport::calculate(double x, int degree) const
{
    if (x < shift * segment_length)
    {
        return 0;
    }
    return calculatePolinomAtPoint(x - shift * segment_length, 1, 3 - degree);
}

void HingeSupport::addAnEquation(Balk &balk) const
{
    balk.func(0, shift * segment_length);
    if (shift == 0 || shift == balk.getBalkSize())
    {
        balk.func(2, shift * segment_length);
    }
}

ElasticSupport::ElasticSupport(int shift, double segment_length, double k)
    : Term(shift, segment_length, true), k(k)
{
}

double ElasticSupport::calculate(double x, int degree) const
{
    if (x < shift * segment_length)
    {
        return 0;
    }
    return calculatePolinomAtPoint(x - shift * segment_length, 1, 3 - degree);
}

double ElasticSupport::get_k() const noexcept
{
    return k;
}

void ElasticSupport::addAnEquation(Balk &balk) const
{
    balk.func(0, shift * segment_length);
    int ind_in_A = 0;
    auto it = balk.getTerms().begin();
    while (this != it->get())
    {
        if (it->get()->isUnknown())
        {
            ++ind_in_A;
        }
        ++it;
    }
    assert(it != balk.getTerms().end());
    balk.getA().back()[ind_in_A] -= 1 / (k * balk.getEJ());
}

HardPinching::HardPinching(int shift, double segment_length)
    : Term(shift, segment_length, true)
{
}

double HardPinching::calculate(double x, int degree) const
{
    if (x < shift * segment_length)
    {
        return 0;
    }
    return calculatePolinomAtPoint(x - shift * segment_length, 1, 2 - degree);
}

void HardPinching::addAnEquation(Balk &balk) const
{
    balk.func(0, shift * segment_length);
    balk.func(1, shift * segment_length);
}

ConcentratedPower::ConcentratedPower(int shift, double segment_length, double force)
    : Term(shift, segment_length, false), force(force)
{
}

double ConcentratedPower::calculate(double x, int degree) const
{
    if (x < shift * segment_length)
    {
        return 0;
    }
    return calculatePolinomAtPoint(x - shift * segment_length, force, 3 - degree);
}

Moment::Moment(int shift, double segment_length, double moment)
    : Term(shift, segment_length, false), moment(moment)
{
}

double Moment::calculate(double x, int degree) const
{
    if (x < shift * segment_length)
    {
        return 0;
    }
    return calculatePolinomAtPoint(x - shift * segment_length, moment, 2 - degree);
}

UniformLoad::UniformLoad(int shift, double segment_lengths, double force)
    : Term(shift, segment_length, false), force(force)
{
}

double UniformLoad::calculate(double x, int degree) const
{
    if (x < shift * segment_length)
    {
        return 0;
    }
    return calculatePolinomAtPoint(x - shift * segment_length, force, 4 - degree);
}

InitShift::InitShift(double EJ)
    : Term(0, 0, true), force(EJ)
{
    initial_variable = true;
}

double InitShift::calculate(double x, int degree) const
{
    // Added IJ as a force for easier counting
    return calculatePolinomAtPoint(x, force, -degree);
}

InitAngle::InitAngle(double EJ)
    : Term(0, 0, true), force(EJ)
{
    initial_variable = true;
}

double InitAngle::calculate(double x, int degree) const
{
    // Added IJ as a force for easier counting
    return calculatePolinomAtPoint(x, force, 1 - degree);
}

InitMoment::InitMoment()
    : Term(0, 0, true)
{
    initial_variable = true;
}

double InitMoment::calculate(double x, int degree) const
{
    return calculatePolinomAtPoint(x, 1, 2 - degree);
}

InitForce::InitForce()
    : Term(0, 0, true)
{
    initial_variable = true;
}

double InitForce::calculate(double x, int degree) const
{
    return calculatePolinomAtPoint(x, 1, 3 - degree);
}
