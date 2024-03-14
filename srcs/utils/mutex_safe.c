# include "../../includes/philosophers.h"

//utiliser close error plutot que exit error pour liberer la memoire allouee
// sous entent que cette fonction aurait soit : 
// la possibilite de vider le gc
// la possibilite d' acceder a la struct t_rules pour liberer toutes les allocations

void	handle_mutex_error(int status, t_mtxcode mtxcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == mtxcode || UNLOCK == mtxcode))
		exit_error("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == mtxcode)
		exit_error("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		exit_error("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		exit_error("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		exit_error("The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == status)
		exit_error("Mutex is locked");
}

//on pourrait techniquement se passer de cette fonction
// void	safe_mutex_handle(t_rules *p_rules, t_mtx *mutex, t_mtxcode mtxcode)
// {
// 	if (LOCK == mtxcode)
// 		handle_mutex_error(pthread_mutex_lock(mutex), mtxcode);
// 	else if (UNLOCK == mtxcode)
// 		handle_mutex_error(pthread_mutex_unlock(mutex), mtxcode);
// 	else if (INIT == mtxcode)
// 		handle_mutex_error(pthread_mutex_init(mutex, NULL), mtxcode);
// 	else if (DESTROY == mtxcode)
// 		handle_mutex_error(pthread_mutex_destroy(mutex), mtxcode);
// 	else
// 		exit_error("Wrong mtxcode for mutex_handle:"
// 			"use <LOCK> <UNLOCK> <INIT> <DESTROY>");
// }
