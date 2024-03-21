# include "../includes/philosophers.h"

static void	dinner_start(t_rules *p_rules)
{
	// printf("dinner_start\n");//
	// fflush(stdout);//
	int	i;
	t_philo	*philos;

	philos = p_rules->philos;
	i = -1;
	p_rules->ts_start = get_ms_timestamp();
	while(++i < p_rules->nb_phil)
	{
		philos[i].ts_lastmeal = p_rules->ts_start; //tant que le thread n' est pas cree pas besoin de mutex
		safe_thread_handle(&philos[i] , CREATE);
		philos[i].thread.is_init = true;
	}
	printf("%ld DINNER START\n", get_elapsed_time_ms(p_rules->ts_start));//
	fflush(stdout);//
	set_mtxbool(&p_rules->rules_lock, &p_rules->dinner_ready, true);
}

// destroy_initialized_mtx(t_rules *p_rules, t_mutex *mutex)
// {
// 	if(mutex->mtx_is_init == true)
// 		safe_mutex_handle(p_rules, &(mutex->mtx), DESTROY);
// }

void    dinner_end(t_rules *p_rules) //etape de clean 
{
    printf("%ld DINNER END\n", get_elapsed_time_ms(p_rules->ts_start));//
	fflush(stdout);//
	int i;
	t_philo	*philos;
	t_mutex 	*forks;

    // stopper les actions de tous les threads
	set_mtxbool(&p_rules->rules_lock, &p_rules->dinner_ended, true);
	philos = p_rules->philos;
	forks = p_rules->forks;
    //join tous les threads
	if(philos)
	{
		i = -1;
		while(++i < p_rules->nb_phil && philos[i].thread.is_init == true)
		{
			safe_thread_handle(&philos[i], JOIN);
			safe_mutex_handle(&(philos[i].philo_lock), DESTROY);
		}
		free(philos);
	}
    //destroy tous les mutex
	if(forks)
	{
		i = -1;
		while(++i < p_rules->nb_phil && forks[i].is_init)
			safe_mutex_handle(&(forks[i]), DESTROY);
		free(forks);
	}
	if(&p_rules->write_lock && p_rules->write_lock.is_init)
		safe_mutex_handle(&(p_rules->write_lock), DESTROY);
	if(&p_rules->rules_lock && p_rules->rules_lock.is_init)
		safe_mutex_handle(&(p_rules->rules_lock), DESTROY);
}

void    close_error(t_rules * p_rules, char *strerr)
{
    print_error(p_rules, strerr);
    dinner_end(p_rules);
    // exit(EXIT_FAILURE); //interdit : utiliser dinner end pour mettre fin a tout et rassembler les threads
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