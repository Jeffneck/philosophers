# include "../../includes/philosophers.h"

//en cas d' erreur avant la creation des mutex .., on peut utiliser directement putstr_fd

// static bool	is_dinner_over(t_rules *p_rules)
// {
// 	bool	ret;
// 	safe_mutex_handle(p_ru&(p_rules->rules_lock), LOCK);
// 	if(p_rules->end_simulation == true)
// 		ret = true;
// 	else 
// 		ret = false;
// 	safe_mutex_handle(p_rules, &(p_rules->end_lock.mtx), UNLOCK);
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

	rules = &(philo->rules);
	safe_mutex_handle(&(rules->write_lock), LOCK);
	// if(is_dinner_over(p_rules) == false)
	if(false == get_mtxbool(&rules->rules_lock, &rules->dinner_ended))
		printf(msg, get_ms_elapsed(rules->ts_start), philo->id);
	safe_mutex_handle(&(rules->write_lock), UNLOCK);
	
}

void	print_error(t_rules *p_rules, char *strerr) //utilisable que par le main thread donc on peut regarder is_init ?
{
	if(p_rules->write_lock.is_init) // && p_rules->rules_lock.is_init)
	{
		safe_mutex_handle(&(p_rules->write_lock), LOCK);
			ft_putstr_fd(strerr, 2);
		safe_mutex_handle(&(p_rules->write_lock), UNLOCK);
	}
	else
		ft_putstr_fd(strerr, 2);
}
