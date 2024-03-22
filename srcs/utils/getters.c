# include "../../includes/philosophers.h"

static bool	getter_mtxbool(t_mutex *mutex, bool *to_get)
{
	bool	ret;
	safe_mutex_handle(mutex, LOCK);
	ret = *to_get;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

static long	getter_mtxlong(t_mutex *mutex, long *to_get)
{
	printf("getter_mtxlong\n");//
	fflush(stdout);//
	long	ret;
	safe_mutex_handle(mutex, LOCK);
	ret = *to_get;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	getter_bool(t_mutex *mutex, t_varcode varcode)
{
	if(DINNER_READY == varcode)
		return (getter_mtxbool(mutex, &(mutex->rules->dinner_ready)));
	return (getter_mtxbool(mutex, &(mutex->rules->dinner_ended)));
}

bool	getter_isfull(t_philo *philo)
{
	return (getter_mtxbool(&philo->philo_lock, &(philo->is_full)));
}

long	getter_tslastmeal(t_philo *philo)
{
	return (getter_mtxlong(&philo->philo_lock, &(philo->ts_lastmeal)));
}

long	getter_tsstart(t_philo *philo)
{
	return (getter_mtxlong(&philo->rules->rules_lock, &(philo->rules->ts_start)));
}