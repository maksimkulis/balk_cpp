#include "parser.h"

#include <fstream>
#include <sstream>

Balk Parser::get_balk_from_file(const std::string &file_name)
{
    std::ifstream file{file_name};
    if (!file) {
        throw ParseError("Cannot open Input file");
    }

    std::string line;
    std::getline(file, line);
    std::stringstream stream(line);

    int balk_size;
    double segment_length;
    double E, J;
    stream >> balk_size;
    stream >> segment_length;
    stream >> E >> J;
    Balk balk(balk_size, segment_length, E, J);

    // Parse conditions
    while (std::getline(file, line))
    {
        stream.clear();
        stream.str(line);

        char type;
        int shift, shift_end;
        double value;

        // Read the type of expression
        stream >> type >> shift;

        switch (type)
        {
        case 'R':
            balk.add_hinge_support(shift, segment_length);
            break;
        case 'K':
            stream >> value;
            balk.add_elastic_support(shift, segment_length, value);
            break;

        case 'Z':
            balk.add_hard_pinching(shift, segment_length);
            break;

        case 'P':
            stream >> value;
            balk.add_concentrated_power(shift, segment_length, value);
            break;

        case 'M':
            stream >> value;
            balk.add_moment(shift, segment_length, value);
            break;

        case 'Q':
            stream >> shift_end >> value;
            balk.add_uniform_load(shift, segment_length, value);
            if (shift_end != balk_size)
            {
                balk.add_uniform_load(shift_end, segment_length, -value);
            }
            break;

        default:
            throw ParseError("Unknown term");
        }
    }
    file.close();
    return balk;
}