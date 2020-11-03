#pragma once

#include <iostream>
#include <string>

#include "balk.h"

class Parser
{
public:
    Balk get_balk_from_file(const std::string &file_name);
};