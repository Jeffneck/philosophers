# include "../includes/philosophers.h"


bool	is_end_condition(t_rules *rules)
{
	printf("is_end_condition\n");//
	fflush(stdout);//
	int		i;
	t_philo	*philos;
	int		nb_full;
	bool	is_dead;

	i = -1;
	philos = rules->philos;
	nb_full = 0;
	is_dead = false;
	while(++i < rules->nb_phil && is_dead == false)
	{
		is_dead = (get_ms_elapsed(getter_tslastmeal(&philos[i])) > rules->ms_to_die); //philo_lock deja unlocke
		if (getter_isfull(&philos[i]) == true)
			nb_full++;
	}
		if(is_dead == true) //time to die est accessible sans mutex ?
			print_philo(&philos[i], DIED_MSG);
	return (is_dead || (nb_full == rules->nb_phil));
}

void	monitor_dinner(t_rules	*rules)
{
	printf("monitor_dinner\n");//
	fflush(stdout);//
	while(is_end_condition(rules) == false)
		ms_sleep(2);
}

// bool	one_philo_died(t_rules *rules)
// {
// 	bool	is_dead;
// 	int		i;
// 	t_philo *philos;

// 	i = -1;
// 	is_dead = false;
// 	philos = rules->philos;
// 	while(++i < rules->philos_nbr && is_dead == false)
// 	{
// 		// printf("lastmeal %ld, start %ld, time die %ld\n",philo.timestamp_lastmeal,  rules->timestamp_start, rules->time_to_die);
// 		// printf("%ld  %d DIED ? %ld\n", get_ms_elapsed(rules->timestamp_start),philo.id, get_ms_elapsed(philo.timestamp_lastmeal));
// 		// if(philo.is_eating == false && (philo.timestamp_lastmeal - rules->timestamp_start) > rules->time_to_die / 1e3)
// 		// if((philo.timestamp_lastmeal - rules->timestamp_start) > rules->time_to_die / 1e3)
// 		// if((get_curr_timestamp() - philo.timestamp_lastmeal) > rules->time_to_die )
// 		safe_mutex_handle(&(philos[i].philo_lock), LOCK);
// 		if(get_ms_elapsed(philos[i].lastmeal) > rules->time_to_die) //time to die est accessible sans mutex ?
// 		{
// 			// write(1, "a\n", 2);//
// 			philo_msg_mutex(rules, philos[i], DIED_MSG);
// 			is_dead = true;
// 		}
// 		safe_mutex_handle(&(philos[i].philo_lock), LOCK);
// 	}
// 	return (is_dead);
// }

// bool	everyone_is_full(t_rules *rules)
// {
// 	int		i;
// 	int		nb_full;
// 	t_philo	*philos;

// 	i = -1;
// 	nb_full = 0;
// 	philos = rules->philos;
// 	while(++i < rules->philos_nbr)
// 	{
// 		// if (rules->philos[i].full == true)
// 		if (get_locked_bool(&(philos[i].philo_lock), &(philos[i].full)) == true)
// 			nb_full++;
// 	}
// 	if (nb_full == rules->philos_nbr)
// 		return (true);
// 	return (false);
// }