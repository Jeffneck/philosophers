# include "../includes/philosophers.h"

static void	philo_think(t_philo *philo)
{
	print_philo(philo, THINK_MSG);
	keep_desynchronised();
}

static void	philo_sleep(t_philo *philo)
{
	print_philo(philo, SLEEP_MSG);
	ms_sleep(philo->ms_to_sleep);
	// ms_sleep(p_rules->ms_to_sleep); //si on copie ms_to_sleep dans chaque philo on pourait avoir une meilleure opti des timings
}

// static void	update_n_check_end_conditions(t_rules	*p_rules, t_philo *philo)//plus besoin de is_eating
// {
// 	if(philo->nb_meals == p_rules->nbr_limit_meals)
// 	{
		
// 	}
// 	safe_mutex_handle(p_rules, &(p_rules->end_conditions), LOCK);
// 	p_rules->dead_condition == true;
// 	p_rules->dead_condition == true;

// 	safe_mutex_handle(p_rules, &(p_rules->end_conditions), UNLOCK);
// }

static void	philo_eat(t_philo *philo)
{
	safe_mutex_handle(&(philo->fst_fork), LOCK);
	print_philo(philo, TOOK_FORK_MSG);
	safe_mutex_handle(&(philo->scd_fork), LOCK);
	print_philo(philo, TOOK_FORK_MSG);
	safe_mutex_handle(&(philo->philo_lock), LOCK);

	print_philo(philo, EAT_MSG);
	philo->ts_lastmeal = get_curr_timestamp();//tout mettre en microsec plutot ?
	ms_sleep(philo->rules->ms_to_eat);
	if(++philo->nb_meals == philo->rules->max_meals)
		philo->full = true;

	safe_mutex_handle(&(philo->philo_lock), LOCK);
	safe_mutex_handle(&(philo->fst_fork), UNLOCK);
	safe_mutex_handle(&(philo->scd_fork), UNLOCK);
}

void	pre_desynchronize(t_philo philo)
{
	if (philo.id % 2 == 0)
		ft_usleep(5e3);
}

void	keep_desynchronize(t_philo philo)
{
	if (philo.id % 2 == 0)
		ft_usleep(5e3);
}

void	*dinner_loop(void *p)
{
	t_rules	*rules;
	t_philo *philo;

	philo = (t_philo *)p; 
	rules = philo->rules;
	//on attend que tous les philos soient crees pour commencer le dinner
	while (get_locked_bool(&rules->rules_lock, &rules->dinner_ready) == false) 
		ms_sleep(1);
	philo->ts_lastmeal = rules->ts_start;//philo_lock et rules_lock ??
	pre_desynchronize(*philo);
	while (get_locked_bool(&rules->rules_lock, &rules->dinner_ended) == false)
	{
		philo_eat(rules, philo); 
		philo_sleep(rules, philo);
		philo_think(rules, philo);
	}
	return(NULL); //inutile de retourner qq chose ? la fonction doit avoir ce prototype
}

// void	dinner_start