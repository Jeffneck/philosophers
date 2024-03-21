# include "../includes/philosophers.h"

static void	assign_forks(t_philo *philo, t_mutex *forks)
{
	//meilleure strat d' inverser l' assignation en fonction des nb pairs ?
	fflush(stdout); //
	if (philo->id % 2 == 0)
	{
		printf("philo id = %d first fork id %d second fork id %d\n", philo->id, philo->id % philo->rules->nb_phil, philo->id - 1);/////
		philo->fst_fork = &(forks[philo->id % philo->rules->nb_phil]);
		philo->scd_fork = &(forks[philo->id - 1]);
	}
	else
	{
		printf("philo id = %d first fork id %d second fork id %d\n", philo->id - 1, philo->id, philo->id % philo->rules->nb_phil);/////
		philo->fst_fork = &(forks[philo->id - 1]);
		philo->scd_fork = &(forks[philo->id]);
	}
}

static void    init_mutex(t_rules *p_rules, t_mutex *mutex)
{

		mutex->is_init = false;
		safe_mutex_handle(mutex, INIT);
		mutex->is_init = true;
}

static void    init_philos(t_rules *p_rules, t_philo *philos)
{
	int	i;

	i = -1;
	// printf("philo nbr = %d\n", p_rules->philos[0].rules->philos_nbr);//
	// fflush(stdout);//
	// printf("philo nbr = %d\n", p_rules->philos_nbr);//
	// fflush(stdout); //
	while(++i < p_rules->nb_phil)
	{
		philos[i].id = i + 1;
		philos[i].rules = p_rules;
		philos[i].nb_meals = 0;//inutile ac calloc
		philos[i].full = false;//inutile ac calloc
		init_mutex(p_rules, &(philos[i].philo_lock));
		assign_forks(&philos[i], p_rules->forks);
	}
}

static void    init_forks(t_rules *p_rules, t_mutex *forks)
{
	int	i;

	i = -1;
	while(++i < p_rules->nb_phil)
		init_mutex(p_rules, &forks[i]);
}


static void    init_rules_from_av(t_rules *p_rules, char ** av)
{
    int		err;

	memset(p_rules, 0, sizeof(t_rules)); // peut ne pas fonctionner
	p_rules->nb_phil = atoi_perr_positive_only(av[1], &err);
	printf("philo nbr = %d\n", p_rules->nb_phil);//
	if (err != 0)
		close_error(p_rules, "Arg 1 :<Philo_nbr> is not valid");
	p_rules->ms_to_die = atoi_perr_positive_only(av[2], &err);
	if (err != 0)
		close_error(p_rules, "Arg 2 :<time_to_die> is not valid");//mettre tous les times directement en microsec
	p_rules->ms_to_eat = atoi_perr_positive_only(av[3], &err);
	if (err != 0)
		close_error(p_rules, "Arg 3 :<time_to_eat> is not valid");
	p_rules->ms_to_sleep = atoi_perr_positive_only(av[4], &err);
	if (err != 0)
		close_error(p_rules, "Arg 4 :<time_to_sleep> is not valid");
	p_rules->max_meals = -1;
	if(av[5])
		p_rules->max_meals = atoi_perr_positive_only(av[5], &err);
	if (err != 0)
		close_error(p_rules, "Arg 5 :<nbr_limit_meals> is not valid");
}

//mettre dans main
void    init_structs(t_rules *p_rules, char ** av)
{
	int	nb;

	init_rules_from_av(p_rules, av);
	nb = p_rules->nb_phil;
	check_rules_max_values(p_rules);
	// transform_rules_times_to_ms(p_rules);//on les met en microsec ce qui n' est pas utile 
	p_rules->philos = ft_calloc(nb, sizeof(t_philo)); //ajouter un philo == NULL pour marquer la fin du tableau de struct ?
	p_rules->forks = ft_calloc(nb, sizeof(t_mutex)); //ajouter un philo == NULL pour marquer la fin du tableau de struct ?
	if (!p_rules->philos || !p_rules->forks)
		close_error(p_rules, MALLOC_E);
	init_mutex(p_rules, &p_rules->write_lock);
	init_mutex(p_rules, &p_rules->rules_lock);
	init_forks(p_rules, p_rules->forks);
	init_philos(p_rules, p_rules->philos);
}