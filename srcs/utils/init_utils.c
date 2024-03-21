# include "../../includes/philosophers.h"

void	check_rules_max_values(t_rules *rules)
{
	if(rules->nb_phil > MAX_PHILO_NBR)
		close_error(rules, "<Philo_nbr> is too high, re_make and redefine macro if necessary");
	if(rules->ms_to_die < MIN_TIME
		|| rules->ms_to_eat < MIN_TIME
		|| rules->ms_to_sleep < MIN_TIME
		)
		close_error(rules, "One argument has a time(ms) too low, re_make and redefine macro if necessary");
}

// void	transform_rules_times_to_ms(t_rules *rules) // inutile puisque tout est en microsecondes apres a part impression
// {
// 	rules->ms_to_die *= 1000;
// 	rules->ms_to_eat *= 1000;
// 	rules->ms_to_sleep *= 1000;
// }