#include <filesystem>

#include "balk.h"
#include "parser.h"
#include "lu_solver.h"

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    Parser pars;
    Balk balk = pars.get_balk_from_file(argv[1]);
    // create folder "outputs" for saving results of the solve_balk();
    fs::create_directory("outputs");
    balk.solve_balk();
    return 0;
}