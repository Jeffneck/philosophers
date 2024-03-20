# include "../../includes/philosophers.h"

//utiliser close error plutot que exit error pour liberer la memoire allouee
// sous entent que cette fonction aurait soit : 
// la possibilite de vider le gc
// la possibilite d' acceder a la struct t_rules pour liberer toutes les allocations

static void	handle_mutex_error(t_rules *p_rules, int funct_return, t_mtxcode mtxcode)
{
	if (0 == funct_return)
		return ;
	if (EINVAL == funct_return && (LOCK == mtxcode || UNLOCK == mtxcode))
		close_error(p_rules, "The value specified by mutex is invalid\n");
	else if (EINVAL == funct_return && INIT == mtxcode)
		close_error(p_rules, "The value specified by attr is invalid.\n");
	else if (EDEADLK == funct_return)
		close_error(p_rules, "A deadlock would occur if the thread "
			"blocked waiting for mutex.\n");
	else if (EPERM == funct_return)
		close_error(p_rules, "The current thread does not hold a lock on mutex.\n");
	else if (ENOMEM == funct_return)
		close_error(p_rules, "The process cannot allocate enough memory"
			" to create another mutex.\n");
	else if (EBUSY == funct_return)
		close_error(p_rules, "Mutex is locked\n");
		// remplacer les exit par une autre fonction, soit cleanclose soit print msg
	// (void)p_rules;//remplacer par une bonne gestion d' erreurs
}

bool	get_locked_bool(t_mutex *mutex, bool *to_get)
{
	bool ret;
	safe_mutex_handle(mutex, LOCK);
	ret = *to_get;
	safe_mutex_handle(mutex, UNLOCK);
	return(ret);
}

void	set_locked_bool(t_mutex *mutex, bool *to_set, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*to_set = value;
	safe_mutex_handle(mutex, LOCK);
}

void	safe_mutex_handle(t_mutex *mutex, t_mtxcode mtxcode) //retirer p_rules car contenu dans mutex et donner t_mutex au lieu de t_mtx
{
	if (LOCK == mtxcode)
		handle_mutex_error(mutex->rules, pthread_mutex_lock(mutex), mtxcode);
	else if (UNLOCK == mtxcode)
		handle_mutex_error(mutex->rules, pthread_mutex_unlock(mutex), mtxcode);
	else if (INIT == mtxcode)
		handle_mutex_error(mutex->rules, pthread_mutex_init(mutex, NULL), mtxcode);//ajouter mutex.is_init = true ici est + smart
	else if (DESTROY == mtxcode) //verifier ici si  mutex.is_init = true ici est + smart
		handle_mutex_error(mutex->rules, pthread_mutex_destroy(mutex), mtxcode);
}

