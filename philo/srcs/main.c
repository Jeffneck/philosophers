# include "../includes/philosophers.h"

static void	dinner_start(t_rules *rules)
{
	int	i;
	t_philo	*philos;

	philos = rules->philos;
	i = -1;
	rules->ts_start = get_ms_timestamp();
	while(++i < rules->nb_phil)
	{
		philos[i].ts_lastmeal = rules->ts_start;
		safe_thread_handle(&philos[i] , CREATE);
		philos[i].thread.is_init = true;
	}
	setter_bool(&rules->rules_lock, DINNER_READY, true);
}

int	main(int ac, char **av) //penser au philo seul ! et au cas impossible des le debut ?
{
	t_rules rules;

	if (ac != 5 && ac != 6)
		close_error(&rules, "Wrong input\n");
	if (init_structs(&rules, av))// pour stopper en cas d' err d' args	
	{
		dinner_start(&rules);
		monitor_dinner(&rules);
	}
	dinner_end(&rules);
	return(EXIT_SUCCESS);
}