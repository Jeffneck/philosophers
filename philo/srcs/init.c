# include "../includes/philosophers.h"

static void	assign_forks(t_philo *philo, t_mutex *forks)
{
	if (philo->id % 2 == 0)
	{
		printf("pair philo id = %d first fork id %d second fork id %d\n", philo->id, philo->id % philo->rules->nb_phil, philo->id - 1);/////
		philo->fst_fork = &(forks[philo->id % philo->rules->nb_phil]);
		philo->scd_fork = &(forks[philo->id - 1]);
	}
	else
	{
		printf(" philo id = %d first fork id %d second fork id %d\n", philo->id, philo->id - 1, philo->id);/////
		// printf(" second fork addr %p\n", &forks[philo->id % philo->rules->nb_phil]);/////
		philo->fst_fork = &(forks[philo->id - 1]);
		if(philo->rules->nb_phil >= 1)//lonephilo
			philo->scd_fork = &(forks[philo->id % philo->rules->nb_phil]);

	}
}

static void    init_mutex(t_rules *rules, t_mutex *mutex)
{

		mutex->is_init = false;
		mutex->rules = rules;
		safe_mutex_handle(mutex, INIT);
		mutex->is_init = true;
}

static void    init_philos(t_rules *rules, t_philo *philos)
{
	int	i;

	i = -1;

	while(++i < rules->nb_phil)
	{
		philos[i].id = i + 1;
		philos[i].rules = rules;
		philos[i].nb_meals = 0;//inutile ac calloc
		philos[i].is_full = false;//inutile ac calloc
		init_mutex(rules, &(philos[i].philo_lock));
		assign_forks(&philos[i], rules->forks);
	}
}

static void    init_forks(t_rules *rules, t_mutex *forks)
{
	int	i;

	i = -1;
	while(++i < rules->nb_phil)
		init_mutex(rules, &forks[i]);
}


static bool    init_rules_from_av(t_rules *rules, char ** av)
{
    int		err;

	memset(rules, 0, sizeof(t_rules));
	// printf("dinner end bool = %d", rules->dinner_ended);//test
	rules->nb_phil = atoi_perr_positive_only(av[1], &err);
	// printf("philo nbr = %d\n", rules->nb_phil);//
	if (err != 0)
		return (ft_putstr_fd("Arg 1 :<Philo_nbr> is not valid\n", 2), false);
	rules->ms_to_die = atoi_perr_positive_only(av[2], &err);
	if (err != 0)
		return (ft_putstr_fd("Arg 2 :<time_to_die> is not valid\n", 2), false);
	rules->ms_to_eat = atoi_perr_positive_only(av[3], &err);
	if (err != 0)
		return (ft_putstr_fd("Arg 3 :<time_to_eat> is not valid\n", 2), false);
	rules->ms_to_sleep = atoi_perr_positive_only(av[4], &err);
	if (err != 0)
		return (ft_putstr_fd("Arg 4 :<time_to_sleep> is not valid\n", 2), false);
	rules->max_meals = -1;
	if(av[5])
		rules->max_meals = atoi_perr_positive_only(av[5], &err);
	if (err != 0)
		return (ft_putstr_fd("Arg 5 :<nbr_limit_meals> is not valid\n", 2), false);
	return (true);

}

//mettre dans main
bool    init_structs(t_rules *rules, char ** av)
{
	int	nb;

	if (!init_rules_from_av(rules, av))
		return (false);
	nb = rules->nb_phil;
	rules->philos = ft_calloc(nb, sizeof(t_philo));
	rules->forks = ft_calloc(nb, sizeof(t_mutex));
	if (!rules->philos || !rules->forks)
		return (ft_putstr_fd(MALLOC_E, 2), false);
	init_mutex(rules, &rules->write_lock);
	init_mutex(rules, &rules->rules_lock);
	init_forks(rules, rules->forks);
	if (!check_rules_max_values(rules))
		return (false);
	init_philos(rules, rules->philos);
	return (true);
}