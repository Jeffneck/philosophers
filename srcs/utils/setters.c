# include "../../includes/philosophers.h"

static void	setter_mtxbool(t_mutex *mutex, bool *to_set, bool new_value)
{
	safe_mutex_handle(mutex, LOCK);
	*to_set = new_value;
	safe_mutex_handle(mutex, UNLOCK);
}

static void	setter_mtxlong(t_mutex *mutex, long *to_set, long new_value)
{
	safe_mutex_handle(mutex, LOCK);
	*to_set = new_value;
	safe_mutex_handle(mutex, UNLOCK);
}

void setter_bool(t_mutex *mutex, t_varcode varcode, bool new_value)
{
	if(DINNER_READY == varcode)
		setter_mtxbool(mutex, &(mutex->rules->dinner_ready), new_value);
	else if(DINNER_ENDED == varcode)
		setter_mtxbool(mutex, &(mutex->rules->dinner_ended), new_value);
}

void setter_isfull(t_philo *philo, bool new_value)
{
	setter_mtxbool(&philo->philo_lock, &(philo->is_full), new_value);
}

void setter_tslastmeal(t_philo *philo, long new_value)
{
	setter_mtxlong(&philo->philo_lock, &(philo->ts_lastmeal), new_value);
}