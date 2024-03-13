# include "../includes/philosophers.h"

/*
input attendu ./philosophers <nb philos> <time_to_die> <time_to_eat> <time_to_sleep> <[nbr_limit_meals]>


*/

void	assign_fork_pairs(int philo_nbr, int philo_id, t_philo *philos, t_fork *forks)
{
	if (2 % philo_id == 1)
	{
		philos[i/////].first_fork = &(forks[i]);
		philos[i].second_fork = &(forks[(i + 1) % philo_nbr]);
	}
	// else l'inverse//////////

}

void    init_philos(t_rules *p_rules)
{
	int	i;

	i = -1;
	while(++i < p_rules->philo_nbr)
	{
		p_rules->philos[i].id = i + 1;
		p_rules->philos[i].meals_counter = 0;
		p_rules->philos[i].full = false;
		p_rules->philos[i].time_since_meal = 0;
		assign_forks_pairs(p_rules->philo_nbr, i + 1, p_rules->philos, p_rules->forks);
		safe_thread_handle(&(p_rules->philos[i].thread_id), thread_routine, data, CREATE);
		p_rules->philos[i].right_fork = ;


	}
}
void    init_forks(t_forks *forks)
{

}
void    init_rules_from_av(t_rules *p_rules, char ** av)
{
    int		err;

	p_rules->philo_nbr = atoi_perr_positive_only(av[1], &err);
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
	if(p_rules->philo_nbr > MAX_PHILO_NBR)
		close_error(p_rules, "<Philo_nbr> is too high, re_make and redefine macro if necessary");
	if(p_rules->time_to_die < MIN_TIME
		|| p_rules->time_to_eat < MIN_TIME
		|| p_rules->time_to_sleep < MIN_TIME
		)
		close_error(p_rules, "One argument has a time(ms) too low, re_make and redefine macro if necessary");
}

void	transform_rules_times_to_ms(t_rules *p_rules)
{
	p_rules->time_to_die *= 1000;
	p_rules->time_to_eat *= 1000;
	p_rules->time_to_sleep *= 1000;
}

void    init_structs(t_rules *p_rules, char ** av)
{
	init_rules_from_av(p_rules, av);
	check_rules_max_values(p_rules);
	transform_rules_times_to_ms(p_rules);
	p_rules->end_simulation = false;
	p_rules->philos = malloc_safe(p_rules->philo_nbr * sizeof(t_philo), p_rules, MALLOC_E, close_error); //ajouter un philo == NULL pour marquer la fin du tableau de struct ?
	p_rules->forks = malloc_safe(p_rules->philo_nbr * sizeof(t_philo), p_rules, MALLOC_E, close_error); //ajouter un philo == NULL pour marquer la fin du tableau de struct ?
    init_forks(p_rules->forks);
    init_philos(p_rules->philos);
	
}

int     main(int ac, char **av)
{
    t_rules rules;

	if (ac != 5 && ac != 6)
        exit_error("Wrong input\n");
    init_structs(&rules, av);
    dinner_start();
    clean(&rules); //
    return(EXIT_SUCCESS);
}