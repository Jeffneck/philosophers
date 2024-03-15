# include "../includes/philosophers.h"

/*
input attendu ./philosophers <nb philos> <time_to_die> <time_to_eat> <time_to_sleep> <[nbr_limit_meals]>


*/

void	assign_fork_pairs(int philo_nbr, int philo_id, t_philo *philos, t_fork *forks)
{
	if (2 % philo_id == 0)
	{
		philos[i].first_fork = &(forks[philo_id]);
		philos[i].second_fork = &(forks[(i + 1) % philo_nbr]);
	}
	else
	{

	}

}

void    init_philos(t_rules *p_rules, t_philo *philos)
{
	int	i;

	i = -1;
	while(++i < p_rules->philos_nbr)
	{
		philos[i].id = i + 1;
		philos[i].meals_counter = 0;
		philos[i].full = false;
		assign_forks(p_rules->philos_nbr, i + 1, philos, p_rules->forks);
	}
}
void    init_forks(t_rules *p_rules, t_mutex *forks)
{
	int	i;

	i = -1;
	while(++i < p_rules->philos_nbr)
	{
		forks[i].mtx_is_init = false;
		safe_mutex_handle(p_rules, &(forks[i].mtx), INIT);
		forks[i].mtx_is_init = true;
		forks[i].id = i;
	}
}
void    init_rules_from_av(t_rules *p_rules, char ** av)
{
    int		err;

	p_rules->philos_nbr = atoi_perr_positive_only(av[1], &err);
	if (err != 0)
		close_error(p_rules, "Arg 1 :<Philo_nbr> is not valid");
	p_rules->time_to_die = atoi_perr_positive_only(av[2], &err);
	if (err != 0)
		close_error(p_rules, "Arg 2 :<time_to_die> is not valid");
	p_rules->time_to_eat = atoi_perr_positive_only(av[3], err);
	if (err != 0)
		close_error(p_rules, "Arg 3 :<time_to_eat> is not valid");
	p_rules->time_to_sleep = atoi_perr_positive_only(av[4], err);
	if (err != 0)
		close_error(p_rules, "Arg 4 :<time_to_sleep> is not valid");
	p_rules->nbr_limit_meals = -1;
	if(av[5])
		p_rules->nbr_limit_meals = atoi_perr_positive_only(av[5], err);
	if (err != 0)
		close_error(p_rules, "Arg 5 :<nbr_limit_meals> is not valid");

}

void	check_rules_max_values(t_rules *p_rules)
{
	if(p_rules->philos_nbr > MAX_PHILO_NBR)
		close_error(p_rules, "<Philo_nbr> is too high, re_make and redefine macro if necessary");
	if(p_rules->time_to_die < MIN_TIME
		|| p_rules->time_to_eat < MIN_TIME
		|| p_rules->time_to_sleep < MIN_TIME
		)
		close_error(p_rules, "One argument has a time(ms) too low, re_make and redefine macro if necessary");
}

void	transform_rules_times_to_ms(t_rules *p_rules) // inutile puisque tout est en microsecondes apres a part impression
{
	p_rules->time_to_die *= 1000;
	p_rules->time_to_eat *= 1000;
	p_rules->time_to_sleep *= 1000;
}

void    init_structs(t_rules *p_rules, char ** av)
{
	int	nb;

	memset(p_rules, 1, sizeof(t_rules));
	init_rules_from_av(p_rules, av);
	nb = p_rules->philos_nbr;
	check_rules_max_values(p_rules);
	transform_rules_times_to_ms(p_rules);
	p_rules->end_simulation = false;
	p_rules->philos = malloc_safe(nb * sizeof(t_philo), p_rules, MALLOC_E, close_error); //ajouter un philo == NULL pour marquer la fin du tableau de struct ?
	p_rules->forks = malloc_safe(nb * sizeof(t_mutex), p_rules, MALLOC_E, close_error); //ajouter un philo == NULL pour marquer la fin du tableau de struct ?
    init_forks(p_rules->forks);
	
}

// void	dinner_start(t_rules *p_rules)
// {
// 	init_monitoring();//pas besoin car notre monitoring loop est assure par notre main thread
// 	init_philos(p_rules->philos);

// }


void	dinner_start(t_rules *p_rules)
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

void    dinner_end(t_rules *p_rules) //close clean car pas forcement d' erreur
{
    int i;

    // stopper les actions de tous les threads
    p_rules->end_simulation = true;
    //join tous les threads
    i = -1;
    while(++i < p_rules->philos_nbr && p_rules->philos[i].is_init == true)// != -1 est une bonne verif ?
        safe_thread_handle(p_rules, p_rules->philos[i].thread_id, &(p_rules->philos[i]), JOIN);
    //destroy tous les mutex (end_simulation)
    i = -1;
    while(++i < p_rules->philos_nbr && p_rules->forks[i].mtx_is_init == true)
        safe_mutex_handle(p_rules, &(p_rules->forks[i].mtx), DESTROY);
    safe_mutex_handle(p_rules, &(p_rules->write.mtx), DESTROY);
    free(p_rules->philos);
    free(p_rules->forks);
}

int     main(int ac, char **av)
{
    t_rules rules;

	if (ac != 5 && ac != 6)
        exit_error("Wrong input\n");
    init_structs(&rules, av);
    dinner_start(&rules);//c' est init philos
	monitor_dinner(&rules);
	dinner_end(&rules);
    return(0);
}