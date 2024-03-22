# include "../../includes/philosophers.h"

//en cas d' erreur avant la creation des mutex .., on peut utiliser directement putstr_fd

// static bool	is_dinner_over(t_rules *rules)
// {
// 	bool	ret;
// 	safe_mutex_handle(p_ru&(rules->rules_lock), LOCK);
// 	if(rules->end_simulation == true)
// 		ret = true;
// 	else 
// 		ret = false;
// 	safe_mutex_handle(rules, &(rules->end_lock.mtx), UNLOCK);
// 	return (ret);
// }

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, strlen(s));
}

void	print_philo(t_philo *philo, char *msg)
{
	t_rules *rules;

	rules = philo->rules;
	safe_mutex_handle(&(rules->write_lock), LOCK);
	if(getter_bool(&rules->rules_lock, DINNER_ENDED) == false)
		printf(msg, get_ms_elapsed(rules->ts_start), philo->id);
	safe_mutex_handle(&(rules->write_lock), UNLOCK);
	
}

void	print_philo_died(t_philo *philo)
{
	t_rules *rules;

	rules = philo->rules;
	safe_mutex_handle(&(rules->write_lock), LOCK);
	printf(DIED_MSG, get_ms_elapsed(rules->ts_start), philo->id);
	setter_bool(&rules->rules_lock, DINNER_ENDED, true);
	safe_mutex_handle(&(rules->write_lock), UNLOCK);
}

void	print_error(t_rules *rules, char *strerr) //utilisable que par le main thread donc on peut regarder is_init ?
{
	if(rules->write_lock.is_init) // && rules->rules_lock.is_init)
	{
		safe_mutex_handle(&(rules->write_lock), LOCK);
			ft_putstr_fd(strerr, 2);
		safe_mutex_handle(&(rules->write_lock), UNLOCK);
	}
	else
		ft_putstr_fd(strerr, 2);
}
