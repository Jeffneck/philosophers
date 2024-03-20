# include "../includes/philosophers.h"

static void	philo_think(t_rules	*p_rules, t_philo *philo)
{
	philo_msg_mutex(p_rules, *philo, THINK_MSG);
	keep_desynchronised();
}

static void	philo_sleep(t_rules	*p_rules, t_philo *philo)
{
	philo_msg_mutex(p_rules, *philo, SLEEP_MSG);
	ft_usleep(p_rules->time_to_sleep * 1e3);
}

// static void	update_n_check_end_conditions(t_rules	*p_rules, t_philo *philo)//plus besoin de is_eating
// {
// 	if(philo->meals_counter == p_rules->nbr_limit_meals)
// 	{
		
// 	}
// 	safe_mutex_handle(p_rules, &(p_rules->end_conditions), LOCK);
// 	p_rules->dead_condition == true;
// 	p_rules->dead_condition == true;

// 	safe_mutex_handle(p_rules, &(p_rules->end_conditions), UNLOCK);
// }

static void	philo_eat(t_rules	*p_rules, t_philo *philo)
{
	philo->meals_counter++;
	safe_mutex_handle(p_rules, &(philo->first_fork->mtx), LOCK);
	philo_msg_mutex(p_rules, *philo, TOOK_FORK_MSG);
	safe_mutex_handle(p_rules, &(philo->second_fork->mtx), LOCK);
	philo_msg_mutex(p_rules, *philo, TOOK_FORK_MSG);
	safe_mutex_handle(p_rules, &(p_rules->meal_lock.mtx), LOCK);

	// philo->is_eating = 1; //inutile avec meal lock
	philo_msg_mutex(p_rules, *philo, EAT_MSG);
	philo->timestamp_lastmeal = get_curr_timestamp();//tout mettre en microsec plutot ?
	ft_usleep(p_rules->time_to_eat * 1e3);
	if(philo->meals_counter == p_rules->nbr_limit_meals)
		philo->full = true;
	// philo->is_eating = 0;//inutile avec meal lock
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