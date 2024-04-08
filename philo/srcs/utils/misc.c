# include "../../includes/philosophers.h"

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

void	print_error(t_rules *rules, char *strerr)
{
	if(rules->write_lock.is_init)
	{
		safe_mutex_handle(&(rules->write_lock), LOCK);
			ft_putstr_fd(strerr, 2);
		safe_mutex_handle(&(rules->write_lock), UNLOCK);
	}
	else
		ft_putstr_fd(strerr, 2);
}
