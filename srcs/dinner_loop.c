# include "../includes/philosophers.h"

static void	philo_think(t_rules	*p_rules, t_philo *philo)
{
	if(p_rules->end_simulation == true)
		return ;
	philo_msg_mutex(p_rules, *philo, THINK_MSG);
}

static void	philo_sleep(t_rules	*p_rules, t_philo *philo)
{
	// long timestamp_start_sleep;
	if(p_rules->end_simulation == true)
		return ;
	philo_msg_mutex(p_rules, *philo, SLEEP_MSG);
	ft_usleep(p_rules->time_to_sleep);
}

static void	philo_eat(t_rules	*p_rules, t_philo *philo)
{
	if(p_rules->end_simulation == true || philo->full == true)
		return ;
	safe_mutex_handle(p_rules, &(philo->first_fork->mtx), LOCK);
	philo_msg_mutex(p_rules, *philo, TOOK_FORK_MSG);
	safe_mutex_handle(p_rules, &(philo->second_fork->mtx), LOCK);
	philo_msg_mutex(p_rules, *philo, TOOK_FORK_MSG);
	//verifier ici s' il est dead ?
	philo->is_eating = 1;
	philo_msg_mutex(p_rules, *philo, EAT_MSG);
	philo->timestamp_lastmeal = get_curr_timestamp(MILLISECONDS);//tout mettre en microsec plutot ?
	ft_usleep(p_rules->time_to_eat);//si en microsec, calcul non necessaire
	philo->is_eating = 0;
	safe_mutex_handle(p_rules, &(philo->first_fork->mtx), UNLOCK);
	safe_mutex_handle(p_rules, &(philo->second_fork->mtx), UNLOCK);
	philo->meals_counter++;
	if(philo->meals_counter == p_rules->nbr_limit_meals)
		philo->full = true;
}

void	*dinner_loop(void *philo_data)
{
	t_rules	*p_rules;
	t_philo *philo;

	philo = (t_philo *)philo_data; 
	p_rules = philo->rules;
	while (p_rules->ready_to_eat == false)
		ft_usleep(50);//on attend que tous les philos soient crees pour commencer le dinner
	philo->timestamp_lastmeal = p_rules->timestamp_start; //retirer cette ligne du monitoring
	while (p_rules->end_simulation == false)
	{
		philo_eat(p_rules, philo); 
		philo_sleep(p_rules, philo);
		philo_think(p_rules, philo);
	}
	return(NULL); //inutile de retourner qq chose ? la fonction doit avoir ce prototype
}

// void	dinner_start