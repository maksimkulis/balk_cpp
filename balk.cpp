#include "balk.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

#include "lu_solver.h"

const int NUM_OF_POINTS = 1000;

Balk::Balk(int balk_size, double segment_length, double E, double J)
    : balk_size(balk_size), segment_length(segment_length), E(E), J(J)
{
    terms.push_back(std::make_shared<InitShift>(E * J));
    terms.push_back(std::make_shared<InitAngle>(E * J));
    terms.push_back(std::make_shared<InitMoment>());
    terms.push_back(std::make_shared<InitForce>());
}

void Balk::add_hinge_support(int shift, double segment_length)
{
    terms.push_back(std::make_shared<HingeSupport>(shift, segment_length));
}

void Balk::add_elastic_support(int shift, double segment_length, double value)
{
    terms.push_back(std::make_shared<ElasticSupport>(shift, segment_length, value));
}

void Balk::add_hard_pinching(int shift, double segment_length)
{
    terms.push_back(std::make_shared<HardPinching>(shift, segment_length));
}

void Balk::add_concentrated_power(int shift, double segment_length, double value)
{
    terms.push_back(std::make_shared<ConcentratedPower>(shift, segment_length, value));
}

void Balk::add_moment(int shift, double segment_length, double value)
{
    terms.push_back(std::make_shared<Moment>(shift, segment_length, value));
}

void Balk::add_uniform_load(int shift, double segment_length, double value)
{
    terms.push_back(std::make_shared<UniformLoad>(shift, segment_length, value));
}

// Solve this God damn balk
void Balk::solve_balk(const std::string &file_output)
{
    // Count a number of unknown elements. Init with 4 because of initial variables.
    size_t unknown_num = 4;
    for (const auto &el : terms)
    {
        unknown_num += ((el->isUnknown()) && (el->getShift() != 0) && (el->getShift() != balk_size));
    }

    std::shared_ptr<Term> first = nullptr;
    std::shared_ptr<Term> last = nullptr;
    auto it = terms.begin();
    for (; it != terms.end(); ++it) {
        if ((it->get()->getShift() == 0) && !(it->get()->initial_variable))
        {
            first = *it;
            break;
        }
    }
    if (first == nullptr) { // Free begin
        func(2, 0);
        func(3, 0);
    } else {
        first->addAnEquation(*this);
        terms.erase(it);
    }

    it = terms.begin();
    for (; it != terms.end(); ++it) {
        if ((it->get()->getShift() == balk_size) && !(it->get()->initial_variable))
        {
            last = *it;
            break;
        }
    }
    if (last == nullptr) { // Free end
        func(2, segment_length * balk_size);
        func(3, segment_length * balk_size);
    } else {
        last->addAnEquation(*this);
        terms.erase(it);
    }

    for (const auto &el : terms)
    {
        if (el->isUnknown())
        {
            el->addAnEquation(*this);
        }
    }


    const std::vector<double> x = solve(A, b);
    std::vector<std::string> outputs = {"outputs/out1.txt", "outputs/out2.txt", "outputs/out3.txt", "outputs/out4.txt"};
    for (int num = 0; num < outputs.size(); ++num) {
        std::ofstream file;
        file.open(outputs[num]);

        for (int i = 0; i < NUM_OF_POINTS; ++i) {
            double res = 0;
            int ind = 0;
            for (const auto& el: terms) {
                if (!(el->isUnknown())) {
                    res += el->calculate(i * balk_size * segment_length / NUM_OF_POINTS, num);
                // } else if (!((el->isUnknown()) && (!el->initial_variable) && (el->getShift() == 0) || (el->getShift() != balk_size))) {
                } else {
                    res += el->calculate(i * balk_size * segment_length / NUM_OF_POINTS, num) * x[ind++];
                }
            }
            file << res / (E * J) << std::endl;
        }
        file.close();
    }
}

void Balk::func(int degree, double value)
{
    std::vector<double> vec;
    double right_part = 0;
    for (auto &el : terms)
    {
        if ((el->isUnknown()) && (el->initial_variable || ((el->getShift() != 0) && (el->getShift() != balk_size)))) {
            vec.push_back(el->calculate(value, degree));
        } else {
            right_part += el->calculate(value, degree);
        }
    }
    A.push_back(std::move(vec));
    b.push_back(-right_part);
}