# include "../../includes/philosophers.h"

//en cas d' erreur avant la creation des mutex .., on peut utiliser directement putstr_fd

static bool	is_dinner_over(t_rules *p_rules)
{
	bool	ret;
	safe_mutex_handle(p_rules, &(p_rules->end.mtx), LOCK);
	if(p_rules->end_simulation == true)
		ret = true;
	else 
		ret = false;
	safe_mutex_handle(p_rules, &(p_rules->end.mtx), UNLOCK);
	return (ret);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, strlen(s));
}

void	philo_msg_mutex(t_rules *p_rules, t_philo philo, char *msg)
{
	safe_mutex_handle(p_rules, &(p_rules->write.mtx), LOCK);
	//eviter d' afficher un message de mort puis un message de philo qui mange
	// ft_usleep(100);
	if(is_dinner_over(p_rules) == false)
		printf(msg, get_elapsed_time_ms(p_rules->timestamp_start), philo.id);
	safe_mutex_handle(p_rules, &(p_rules->write.mtx), UNLOCK);
	
}

void	print_error_mutex(t_rules *p_rules, char *strerr)
{
	// if(!strerr)
	// 	return ;
	if(p_rules->write.mtx_is_init && p_rules->end.mtx_is_init)
	{
		safe_mutex_handle(p_rules, &(p_rules->write.mtx), LOCK);
			ft_putstr_fd(strerr, 2);
		safe_mutex_handle(p_rules, &(p_rules->write.mtx), UNLOCK);
	}
	else
		ft_putstr_fd(strerr, 2);
}
