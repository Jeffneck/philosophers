# include "../../includes/philosophers.h"

void    exit_error(char *strerr)
{
    ft_printf(R"%s\n"RS, strerr);
    exit(EXIT_FAILURE);
}

void    close_error(t_rules *p_rules, char *strerr)
{
    clean(p_rules);
    exit_error(strerr);
}