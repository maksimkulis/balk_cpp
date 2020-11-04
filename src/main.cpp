#include <iostream>

#include "balk.h"
#include "parser.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] <<" \"<input_file_name>\" \"<output_folder_name>\"" << std::endl;
        return -1;
    }
    try
    {
        Balk balk = Parser().get_balk_from_file(argv[1]);
        balk.solve_balk();
        balk.save_result(argv[2]);
    }
    catch (const ParseError &e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}