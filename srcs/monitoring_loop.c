# include "../includes/philosophers.h"

void	end_simulation(t_rules *p_rules)
{
	p_rules->end_simulation = true;
}

void	*monitoring_loop(void *void_p_rules)
{
	t_rules	*p_rules;
	t_philo *philos;
	int		i;

	p_rules = (t_rules *)void_p_rules;
	philos = p_rules->philos;
	while(p_rules->end_simulation == false)
	{
		i = 0;
		while(i < p_rules->philos_nbr)
		{
			if(philos[i].is_eating == false && philos[i].time_since_meal > p_rules->time_to_die)
			{
				print_msg_mutex()
				end_simulation();
			}

			if(philos[i].full == true)
		}
		if (p_rules->philos_full_nbr == p_rules->philos_nbr)
		{

		}
	}
}