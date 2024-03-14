# include "../../includes/philosophers.h"
//utiliser print_error_mutex dans exit error
// void    exit_error(char *strerr)
// {
//     ft_printf(R"%s\n"RS, strerr);
//     exit(EXIT_FAILURE);
// }

void    close_error(t_rules *p_rules, char *strerr) //close clean car pas forcement d' erreur
{
    int i;

    // stopper les actions de tous les threads
    p_rules->end_simulation = true;
    //join tous les threads
    i = -1;
    while(++i < p_rules->philos_nbr && p_rules->philos[i].is_init == true)// != -1 est une bonne verif ?
        handle_thread_error(pthread_join(p_rules->philos[i].thread_id, NULL), JOIN); //que se passe t il s' il y a une erreur la dedans
    i = -1;
    while(++i < p_rules->philos_nbr && p_rules->forks[i].is_init == true)
        handle_mutex_error(pthread_mutex_destroy(&(p_rules->forks[i].fork_mtx)), DESTROY);
    if(strerr)
        print_error_mutex(p_rules, strerr);
    //destroy tous les mutex (end_simulation)

    free(p_rules->philos);
    free(p_rules->forks);
    exit_error(strerr);
}