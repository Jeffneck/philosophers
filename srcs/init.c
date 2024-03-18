# include "../includes/philosophers.h"

void	assign_fork_pairs(int philo_nbr, int philo_id, t_philo philo, t_mutex *forks)
{
	if (philo_id == philo_nbr)
	{
		philo.first_fork = &(forks[0]);
		philo.second_fork = &(forks[philo_id - 1]);
	}
	else
	{
		philo.first_fork = &(forks[philo_id - 1]);
		philo.second_fork = &(forks[philo_id]);
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
		close_error(p_rules, "Arg 2 :<time_to_die> is not valid");//mettre tous les times directement en microsec
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
    init_forks(p_rules, p_rules->forks);
}