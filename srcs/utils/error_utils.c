# include "../../includes/philosophers.h"
//utiliser print_error_mutex dans exit error
void    close_error(t_rules * p_rules, char *strerr)
{
    print_error_mutex(p_rules, strerr);
    dinner_end(p_rules);
    exit(EXIT_FAILURE); //interdit
}

