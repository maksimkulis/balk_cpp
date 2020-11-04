#pragma once

#include <string>
#include <stdexcept>

#include "balk.h"


class ParseError : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};


class Parser
{
public:
    Balk get_balk_from_file(const std::string &file_name);
};