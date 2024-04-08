# include "../includes/philosophers.h"

bool	is_end_condition(t_rules *rules)
{
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
		is_dead = (get_ms_elapsed(getter_tslastmeal(&philos[i])) > rules->ms_to_die);
		if(is_dead == true)
			print_philo_died(&philos[i]);
		if (getter_isfull(&philos[i]) == true)
			nb_full++;
	}
	if(nb_full == rules->nb_phil)
		setter_bool(&rules->rules_lock, DINNER_ENDED, true);
	return (is_dead || (nb_full == rules->nb_phil));
}

void	monitor_dinner(t_rules	*rules)
{
	while(getter_bool(&rules->rules_lock, DINNER_READY) == false)
		ms_sleep(2);
	ms_sleep(5);
	while(is_end_condition(rules) == false)
		ms_sleep(2);
}
