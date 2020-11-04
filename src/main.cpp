#include <iostream>
#include <filesystem>

#include "balk.h"
#include "parser.h"

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    try
    {
        Balk balk = Parser().get_balk_from_file(argv[1]);
        // create folder "outputs" for saving results of the solve_balk();
        fs::create_directory("outputs");
        balk.solve_balk();
    }
    catch (const ParseError &e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}