# include "../includes/philosophers.h"

bool	one_philo_died(t_rules *p_rules)
{
	
	int		i;
	t_philo philo;

	i = -1;
	while(++i < p_rules->philos_nbr)
	{
		philo = p_rules->philos[i];
		if(philo.is_eating == false 
			&& philo.timestamp_lastmeal - p_rules->timestamp_start > p_rules->time_to_die)
		{
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
	if (nb_full == p_rules->philos_full_nbr)
		return (1);
	return (0);
}

void	monitor_dinner(t_rules	*p_rules)
{
	while(true)
	{
		//si on souhaite un monitoring plus efficace on peut faire un thread pour chaque verification.
		if(one_philo_died || everyone_is_full)
			return ;
	}
}