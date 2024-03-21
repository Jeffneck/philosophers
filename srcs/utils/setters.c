# include "../../includes/philosophers.h"

void	set_mtxbool(t_mutex *mutex, bool *to_set, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*to_set = value;
	safe_mutex_handle(mutex, LOCK);
}

void	set_mtxlong(t_mutex *mutex, long *to_set, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*to_set = value;
	safe_mutex_handle(mutex, LOCK);
}

void set_bool(t_mutex *mutex, t_varcode varcode, bool value)
{
	if(DINNER_READY == varcode)
		set_mtxbool(mutex, &(mutex->rules->dinner_ready), value);
	else if(DINNER_ENDED == varcode)
		set_mtxbool(mutex, &(mutex->rules->dinner_ended), value);
}

void philo_is_full(t_philo *philo, bool value)
{
	set_mtxbool(&philo->philo_lock, &(philo->is_full), value);
}

void philo_lastmeal(t_philo *philo, long ts_meal)
{
	set_mtxlong(&philo->philo_lock, &(philo->), value);
}
