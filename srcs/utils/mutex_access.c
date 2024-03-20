# include "../../includes/philosophers.h"

bool	get_mtxbool(t_mutex *mutex, bool *to_get)
{
	bool ret;
	safe_mutex_handle(mutex, LOCK);
	ret = *to_get;
	safe_mutex_handle(mutex, UNLOCK);
	return(ret);
}

void	set_mtxbool(t_mutex *mutex, bool *to_set, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*to_set = value;
	safe_mutex_handle(mutex, LOCK);
}


long	get_mtxlong(t_mutex *mutex, long *to_get)
{
	long ret;
	safe_mutex_handle(mutex, LOCK);
	ret = *to_get;
	safe_mutex_handle(mutex, UNLOCK);
	return(ret);
}

void	set_mtxlong(t_mutex *mutex, long *to_set, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*to_set = value;
	safe_mutex_handle(mutex, LOCK);
}
