# include "../includes/philosophers.h"

static void	dinner_start(t_rules *p_rules)
{
	// printf("dinner_start\n");//
	// fflush(stdout);//
	int	i;
	t_philo	*philos;

	philos = p_rules->philos;
	i = -1;
	p_rules->timestamp_start = get_curr_timestamp();
	while(++i < p_rules->philos_nbr)
	{
		philos[i].timestamp_lastmeal = p_rules->timestamp_start;
		safe_thread_handle(p_rules, &(philos[i].thread_id), &philos[i] , CREATE);
		philos[i].thread_is_init = true;
	}
	p_rules->ready_to_eat = true;
}

destroy_initialized_mtx(t_rules *p_rules, t_mutex *mutex)
{
	if(mutex->mtx_is_init == true)
		safe_mutex_handle(p_rules, &(mutex->mtx), DESTROY);
}

void    dinner_end(t_rules *p_rules) //etape de clean 
{
    printf("%ld dinner_end\n", get_elapsed_time_ms(p_rules->timestamp_start));//
	fflush(stdout);//
	int i;
	t_philo	*philos;
	t_mutex 	*forks;

	philos = p_rules->philos;
	forks = p_rules->forks;
    // stopper les actions de tous les threads
    // p_rules->end_simulation = true;
    //join tous les threads
	if(philos)
	{
		i = -1;
		while(++i < p_rules->philos_nbr && philos[i].thread_is_init == true)
			safe_thread_handle(p_rules, &(philos[i].thread_id), &philos[i], JOIN);
		free(philos);
	}
    //destroy tous les mutex
	if(forks)
	{
		i = -1;
		while(++i < p_rules->philos_nbr && forks[i].mtx_is_init == true)
			destroy_initialized_mtx(p_rules, &forks[i]);
		free(forks);
	}
		destroy_initialized_mtx(p_rules, &write_lock);
		destroy_initialized_mtx(p_rules, &meal_lock);
		destroy_initialized_mtx(p_rules, &end_lock);
}

int     main(int ac, char **av) //penser au philo seul ! et au cas impossible des le debut ?
{
    t_rules rules;

	// memset(&rules, 1, sizeof(t_rules));
	if (ac != 5 && ac != 6)
        close_error(&rules, "Wrong input\n");
    init_structs(&rules, av);
    dinner_start(&rules);
	monitor_dinner(&rules);
	dinner_end(&rules);
    return(EXIT_SUCCESS);
}