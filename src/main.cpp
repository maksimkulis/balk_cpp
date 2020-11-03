#include <sys/stat.h>
#include "balk.h"
#include "parser.h"
#include "lu_solver.h"

int main(int argc, char **argv)
{
    Parser pars;
    Balk balk = pars.get_balk_from_file(argv[1]);
    // create folder "outputs" for saving results of the solve_balk();
    mkdir("./outputs", 0755);
    balk.solve_balk();
    return 0;
}