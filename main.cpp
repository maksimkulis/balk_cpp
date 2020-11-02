#include "balk.h"
#include "parser.h"
#include "lu_solver.h"

int main(int argc, char **argv)
{
    Parser pars;
    Balk balk = pars.get_balk_from_file(argv[1]);
    balk.solve_balk("output.txt");
    return 0;
}