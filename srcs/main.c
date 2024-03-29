# include "../includes/philosophers.h"

static void	dinner_start(t_rules *rules)
{
	// printf("dinner_start\n");//
	// fflush(stdout);//
	int	i;
	t_philo	*philos;

	philos = rules->philos;
	i = -1;
	rules->ts_start = get_ms_timestamp();
	while(++i < rules->nb_phil)
	{
		philos[i].ts_lastmeal = rules->ts_start; //tant que le thread n' est pas cree pas besoin de mutex
		safe_thread_handle(&philos[i] , CREATE);
		philos[i].thread.is_init = true;
	}
	printf("%ld DINNER START\n", get_ms_elapsed(rules->ts_start));//
	fflush(stdout);//
	setter_bool(&rules->rules_lock, DINNER_READY, true);
}

// destroy_initialized_mtx(t_rules *rules, t_mutex *mutex)
// {
// 	if(mutex->mtx_is_init == true)
// 		safe_mutex_handle(rules, &(mutex->mtx), DESTROY);
// }

void    dinner_end(t_rules *rules) //etape de clean 
{
    printf("%ld DINNER END\n", get_ms_elapsed(rules->ts_start));//
	fflush(stdout);//
	int i;
	t_philo	*philos;
	t_mutex 	*forks;

    // stopper les actions de tous les threads
	// setter_bool(&rules->rules_lock, DINNER_ENDED, true);// je l'ai mis des la detection de died
	philos = rules->philos;
	forks = rules->forks;
    //join tous les threads
	if(philos)
	{
		i = -1;
		while(++i < rules->nb_phil && philos[i].thread.is_init == true)
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
		while(++i < rules->nb_phil && forks[i].is_init)
			safe_mutex_handle(&(forks[i]), DESTROY);
		free(forks);
	}
	if(rules->write_lock.is_init)
		safe_mutex_handle(&(rules->write_lock), DESTROY);
	if(rules->rules_lock.is_init)
		safe_mutex_handle(&(rules->rules_lock), DESTROY);
}

void    close_error(t_rules * rules, char *strerr)
{
    print_error(rules, strerr);
    dinner_end(rules);
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