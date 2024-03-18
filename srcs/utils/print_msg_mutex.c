# include "../../includes/philosophers.h"

//en cas d' erreur avant la creation des mutex .., on peut utiliser directement putstr_fd
void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void	philo_msg_mutex(t_rules *p_rules, t_philo philo, char *msg)
{
	// if(!msg)
	// 	return ;
	safe_mutex_handle(p_rules, &(p_rules->write.mtx), LOCK);
	printf(msg, get_timestamp(MILLISECONDS) - p_rules->timestamp_start, philo.id);
	safe_mutex_handle(p_rules, &(p_rules->write.mtx), LOCK);
	
}

void	print_error_mutex(t_rules *p_rules, char *strerr)
{
	// if(!strerr)
	// 	return ;
	if(p_rules->write.mtx_is_init)
	{
		safe_mutex_handle(p_rules, &(p_rules->write.mtx), LOCK);
			ft_putstr_fd(strerr, 2);
		safe_mutex_handle(p_rules, &(p_rules->write.mtx), UNLOCK);
	}
	else
		ft_putstr_fd(strerr, 2);
}
