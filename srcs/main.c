# include "../includes/philosophers.h"

static void	dinner_start(t_rules *p_rules)
{
	int	i;
	t_philo	*philos;

	philos = p_rules->philos;
	i = -1;
	p_rules->timestamp_start = get_curr_timestamp(MILLISECONDS);
	while(++i < p_rules->philos_nbr)
	{
		philos[i].timestamp_lastmeal = p_rules->timestamp_start;
		safe_thread_handle(&(p_rules->philos[i].thread_id), dinner_loop, &philos[i], CREATE);
		philos[i].thread_is_init = true;
	}
	p_rules->ready_to_eat = true;
}

void    dinner_end(t_rules *p_rules)
{
    int i;

    // stopper les actions de tous les threads
    p_rules->end_simulation = true;
    //join tous les threads
    i = -1;
    while(++i < p_rules->philos_nbr && p_rules->philos[i].thread_is_init == true)
        safe_thread_handle(p_rules, p_rules->philos[i].thread_id, &(p_rules->philos[i]), JOIN);
    //destroy tous les mutex
    i = -1;
    while(++i < p_rules->philos_nbr && p_rules->forks[i].mtx_is_init == true)
        safe_mutex_handle(p_rules, &(p_rules->forks[i].mtx), DESTROY);
    safe_mutex_handle(p_rules, &(p_rules->write.mtx), DESTROY);
    free(p_rules->philos);
    free(p_rules->forks);
}

int     main(int ac, char **av) //penser au philo seul ! et au cas impossible des le debut ?
{
    t_rules rules;

	if (ac != 5 && ac != 6)
        exit_error("Wrong input\n");
    init_structs(&rules, av);
    dinner_start(&rules);
	monitor_dinner(&rules);
	dinner_end(&rules);
    return(EXIT_SUCCESS);
}