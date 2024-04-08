# include "../../includes/philosophers.h"

bool	check_rules_max_values(t_rules *rules)
{
	if(rules->nb_phil > MAX_PHILO_NBR)
		return(ft_putstr_fd("<Philo_nbr> is too high, " \
				"re_make and redefine macro if necessary\n", 2), false);
	if(rules->ms_to_die < MIN_TIME
		|| rules->ms_to_eat < MIN_TIME
		|| rules->ms_to_sleep < MIN_TIME
		)
		return(ft_putstr_fd("One argument has a time(ms) too low, " \
			"re_make and redefine macro if necessary\n", 2), false);
	return(true);
}
