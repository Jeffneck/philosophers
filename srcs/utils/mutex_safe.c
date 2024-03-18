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
		close_error(p_rules, "The value specified by mutex is invalid");
	else if (EINVAL == funct_return && INIT == mtxcode)
		close_error(p_rules, "The value specified by attr is invalid.");
	else if (EDEADLK == funct_return)
		close_error(p_rules, "A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == funct_return)
		close_error(p_rules, "The current thread does not hold a lock on mutex.");
	else if (ENOMEM == funct_return)
		close_error(p_rules, "The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == funct_return)
		close_error(p_rules, "Mutex is locked");
		// remplacer les exit par une autre fonction, soit cleanclose soit print msg
	(void)p_rules;//remplacer par une bonne gestion d' erreurs
}

//on pourrait techniquement se passer de cette fonction
void	safe_mutex_handle(t_rules *p_rules, t_mtx *mutex, t_mtxcode mtxcode)
{
	if (LOCK == mtxcode)
		handle_mutex_error(p_rules, pthread_mutex_lock(mutex), mtxcode);
	else if (UNLOCK == mtxcode)
		handle_mutex_error(p_rules, pthread_mutex_unlock(mutex), mtxcode);
	else if (INIT == mtxcode)
		handle_mutex_error(p_rules, pthread_mutex_init(mutex, NULL), mtxcode);
	else if (DESTROY == mtxcode)
		handle_mutex_error(p_rules, pthread_mutex_destroy(mutex), mtxcode);
}
