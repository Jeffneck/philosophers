# include "../includes/philosophers.h"


bool	is_end_condition(t_rules *p_rules)
{
	int		i;
	t_philo	*philos;
	int		nb_full;
	bool	is_dead;

	i = -1;
	philos = p_rules->philos;
	nb_full = 0;
	is_dead = false;
	while(++i < p_rules->philos_nbr && is_dead == false)
	{
		safe_mutex_handle(&(philos[i].philo_lock), LOCK);
		is_dead = (get_elapsed_time_ms(philos[i].lastmeal) > p_rules->time_to_die);
		if (philos[i].full == true)
			nb_full++;
		safe_mutex_handle(&(philos[i].philo_lock), LOCK);
	}
		if(is_dead == true) //time to die est accessible sans mutex ?
			philo_msg_mutex(p_rules, philos[i], DIED_MSG);
	return (is_dead || (nb_full == p_rules->philos_nbr));
}

void	monitor_dinner(t_rules	*p_rules)
{
	while(is_end_condition(p_rules) == false)
		ms_sleep(2);
}

// bool	one_philo_died(t_rules *p_rules)
// {
// 	bool	is_dead;
// 	int		i;
// 	t_philo *philos;

// 	i = -1;
// 	is_dead = false;
// 	philos = p_rules->philos;
// 	while(++i < p_rules->philos_nbr && is_dead == false)
// 	{
// 		// printf("lastmeal %ld, start %ld, time die %ld\n",philo.timestamp_lastmeal,  p_rules->timestamp_start, p_rules->time_to_die);
// 		// printf("%ld  %d DIED ? %ld\n", get_elapsed_time_ms(p_rules->timestamp_start),philo.id, get_elapsed_time_ms(philo.timestamp_lastmeal));
// 		// if(philo.is_eating == false && (philo.timestamp_lastmeal - p_rules->timestamp_start) > p_rules->time_to_die / 1e3)
// 		// if((philo.timestamp_lastmeal - p_rules->timestamp_start) > p_rules->time_to_die / 1e3)
// 		// if((get_curr_timestamp() - philo.timestamp_lastmeal) > p_rules->time_to_die )
// 		safe_mutex_handle(&(philos[i].philo_lock), LOCK);
// 		if(get_elapsed_time_ms(philos[i].lastmeal) > p_rules->time_to_die) //time to die est accessible sans mutex ?
// 		{
// 			// write(1, "a\n", 2);//
// 			philo_msg_mutex(p_rules, philos[i], DIED_MSG);
// 			is_dead = true;
// 		}
// 		safe_mutex_handle(&(philos[i].philo_lock), LOCK);
// 	}
// 	return (is_dead);
// }

// bool	everyone_is_full(t_rules *p_rules)
// {
// 	int		i;
// 	int		nb_full;
// 	t_philo	*philos;

// 	i = -1;
// 	nb_full = 0;
// 	philos = p_rules->philos;
// 	while(++i < p_rules->philos_nbr)
// 	{
// 		// if (p_rules->philos[i].full == true)
// 		if (get_locked_bool(&(philos[i].philo_lock), &(philos[i].full)) == true)
// 			nb_full++;
// 	}
// 	if (nb_full == p_rules->philos_nbr)
// 		return (true);
// 	return (false);
// }