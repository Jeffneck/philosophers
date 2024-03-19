# include "../includes/philosophers.h"

bool	one_philo_died(t_rules *p_rules)
{
	
	int		i;
	t_philo philo;

	i = -1;
	while(++i < p_rules->philos_nbr)
	{
		philo = p_rules->philos[i];
		// printf("lastmeal %ld, start %ld, time die %ld\n",philo.timestamp_lastmeal,  p_rules->timestamp_start, p_rules->time_to_die);
		// printf("%ld  %d DIED ? %ld\n", get_elapsed_time_ms(p_rules->timestamp_start),philo.id, get_elapsed_time_ms(philo.timestamp_lastmeal));
		// if(philo.is_eating == false && (philo.timestamp_lastmeal - p_rules->timestamp_start) > p_rules->time_to_die / 1e3)
		// if((philo.timestamp_lastmeal - p_rules->timestamp_start) > p_rules->time_to_die / 1e3)
		// if((get_curr_timestamp() - philo.timestamp_lastmeal) > p_rules->time_to_die )
		if(get_elapsed_time_ms(philo.timestamp_lastmeal) > p_rules->time_to_die )
		{
			// write(1, "a\n", 2);//
			philo_msg_mutex(p_rules, philo, DIED_MSG);
			return (1);
		}
	}
	return (0);
}

bool	everyone_is_full(t_rules *p_rules)
{
	int		i;
	int		nb_full;

	i = -1;
	nb_full = 0;
	while(++i < p_rules->philos_nbr)
	{
		if (p_rules->philos[i].full == true)
			nb_full++;
	}
	if (nb_full == p_rules->philos_nbr)
		return (1);
	return (0);
}

void	monitor_dinner(t_rules	*p_rules)
{
	while(true)
	{
		//si on souhaite un monitoring plus efficace on peut faire un thread pour chaque verification.
		safe_mutex_handle(p_rules, &(p_rules->meal_lock.mtx), LOCK);
		
		if(one_philo_died(p_rules) || everyone_is_full(p_rules))
		{
			safe_mutex_handle(p_rules, &(p_rules->end_lock.mtx), LOCK);
			p_rules->end_simulation = true;
			safe_mutex_handle(p_rules, &(p_rules->end_lock.mtx), UNLOCK);
			safe_mutex_handle(p_rules, &(p_rules->meal_lock), UNLOCK);
			return ;
		}
		safe_mutex_handle(p_rules, &(p_rules->meal_lock), UNLOCK);
		ft_usleep(1e3);//entre 1 et 10e3
	}
}