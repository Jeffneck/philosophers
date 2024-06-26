# include "../includes/philosophers.h"

static void	pre_desynchronize(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ms_sleep(0.9 * philo->rules->ms_to_eat);
}

static void	keep_desynchronize(t_philo *philo)
{
	long t_die;
	long t_loop;

	t_die = philo->rules->ms_to_die; 
	t_loop = philo->rules->ms_to_eat + philo->rules->ms_to_sleep;
	
	// if (philo->id % 2 == 0)
	// 	ms_sleep(0.9 *
	if (t_die > t_loop)
		ms_sleep((t_die - t_loop) - 5);
}

static void	philo_think(t_philo *philo)
{
	print_philo(philo, THINK_MSG);
}

static void	philo_sleep(t_philo *philo)
{
	print_philo(philo, SLEEP_MSG);
	ms_sleep(philo->rules->ms_to_sleep);
}

static void	philo_eat(t_philo *philo)
{
	safe_mutex_handle(philo->fst_fork, LOCK);
	print_philo(philo, TOOK_FORK_MSG);
	safe_mutex_handle(philo->scd_fork, LOCK);
	print_philo(philo, TOOK_FORK_MSG);
	// safe_mutex_handle(&(philo->philo_lock), LOCK);
	setter_tslastmeal(philo, get_ms_timestamp());
	// philo->ts_lastmeal = get_ms_timestamp();//tout mettre en microsec plutot ?
	print_philo(philo, EAT_MSG);
	ms_sleep(philo->rules->ms_to_eat);
	if(++philo->nb_meals == philo->rules->max_meals)
		setter_isfull(philo, true);
		// philo->is_full = true;
	// safe_mutex_handle(&(philo->philo_lock), UNLOCK);
	safe_mutex_handle(philo->fst_fork, UNLOCK);
	safe_mutex_handle(philo->scd_fork, UNLOCK);
}


void	*dinner_loop(void *p)
{
	printf("dinner loop\n");//
	fflush(stdout);//
	t_rules	*rules;
	t_philo *philo;

	philo = (t_philo *)p; 
	rules = philo->rules;
	//on attend que tous les philos soient crees pour commencer le dinner
	while (getter_bool(&rules->rules_lock, DINNER_READY) == false) 
		ms_sleep(2);
	// setter_tslastmeal(philo, getter_tsstart(philo));//philo_lock et rules_lock ?? //getter_ts_start semble inutile
	setter_tslastmeal(philo, rules->ts_start);//philo_lock et rules_lock ??
	pre_desynchronize(philo);
	while (getter_bool(&rules->rules_lock, DINNER_ENDED) == false)
	{
		philo_eat(philo); 
		philo_sleep(philo);
		philo_think(philo);
		keep_desynchronize(philo);
	}
	return(NULL); //inutile de retourner qq chose ? la fonction doit avoir ce prototype
}


// void	dinner_start