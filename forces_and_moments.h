#pragma once

#include <vector>
#include <string>
#include <memory>

class Balk;

class Term
{
public:
    constexpr Term(int shift, double segment_length, bool is_unknown);

    virtual ~Term() = default;

    /// Calculate condition ad point x
    constexpr double calculatePolinomAtPoint(double x, double scalar, int degree) const;

    /// Degee 0 - shifts. 1 - angels, 2 - moments etc.
    /// Substitute the x
    virtual double calculate(double x, int degree) const = 0;

    /// This has to be overrided if the term corresponds to unknown value
    virtual void addAnEquation(Balk& balk) const { return; }

    [[nodiscard]]
    constexpr int getShift() const noexcept { return shift; }

    [[nodiscard]]
    constexpr bool isUnknown() const noexcept { return is_unknown; }

    // Dont touch this bool. It is true only for initial variables (w_0, M_0 etc).
    bool initial_variable = false;
protected:
    int shift;
    double segment_length;
    bool is_unknown;
};

// Sharnirnaya opora
class HingeSupport : public Term
{
public:
    HingeSupport(int shift, double segment_length);
    double calculate(double x, int degree) const override;
    void addAnEquation(Balk& balk) const override;
};

// Uprugaya opora
class ElasticSupport : public Term
{
public:
    ElasticSupport(int shift, double segment_length, double k);
    double calculate(double x, int degree) const override;
    // TODO 
    void addAnEquation(Balk& balk) const override;
    double get_k() const noexcept;

private:
    double k;
};

// Jostkogoe zashemleniya
class HardPinching : public Term
{
public:
    HardPinching(int shift, double segment_length);
    double calculate(double x, int degree) const override;
    void addAnEquation(Balk& balk) const override;
};

// Sosredotochennaya sila
class ConcentratedPower : public Term
{
public:
    ConcentratedPower(int shift, double segment_length, double force);
    double calculate(double x, int degree) const override;

private:
    double force;
};

// Moment
class Moment : public Term
{
public:
    Moment(int shift, double segment_length, double moment);
    double calculate(double x, int degree) const override;

private:
    double moment;
};

// Ravnomernaya nagruzka
class UniformLoad : public Term
{
public:
    UniformLoad(int shift, double segment_length, double force);
    double calculate(double x, int degree) const override;

private:
    double force;
};

// Initial variables (added for equations)
class InitShift : public Term
{
public:
    InitShift(double EJ);
    double calculate(double x, int degree) const override;

private:
    double force;
};

class InitAngle : public Term
{
public:
    InitAngle(double EJ);
    double calculate(double x, int degree) const override;

private:
    double force;
};

class InitMoment : public Term
{
public:
    InitMoment();
    double calculate(double x, int degree) const override;
};

class InitForce : public Term
{
public:
    InitForce();
    double calculate(double x, int degree) const override;
};
