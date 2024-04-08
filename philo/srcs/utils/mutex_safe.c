# include "../../includes/philosophers.h"

//utiliser close error plutot que exit error pour liberer la memoire allouee
// sous entent que cette fonction aurait soit : 
// la possibilite de vider le gc
// la possibilite d' acceder a la struct t_rules pour liberer toutes les allocations


static void	handle_mtx_err(t_rules *rules, int ret, t_mtxcode mtxcode)
{
	// printf("handle_mtx_err\n");//
	// fflush(stdout);//
	if (0 == ret || EPERM == ret || EBUSY == ret
			|| (EINVAL == ret && (LOCK == mtxcode || UNLOCK == mtxcode)))
		return ;
	else if (EINVAL == ret && INIT == mtxcode)
		close_error(rules, EINVAL_MTX_E);
	else if (EDEADLK == ret)
		close_error(rules, EDEADLK_MTX_E);
	else if (ENOMEM == ret)
		close_error(rules, ENOMEM_MTX_E);
}

void	safe_mutex_handle(t_mutex *mutex, t_mtxcode mtxcode) //retirer rules car contenu dans mutex et donner t_mutex au lieu de t_mtx
{
	// printf("safe_mutex_handle code = %d\n", mtxcode);//
	// fflush(stdout);//
	if(!mutex) //protege dans certains cas de closing
		return;
	else if (LOCK == mtxcode)
		handle_mtx_err(mutex->rules, pthread_mutex_lock(&mutex->mtx_id), mtxcode);
	else if (UNLOCK == mtxcode)
		handle_mtx_err(mutex->rules, pthread_mutex_unlock(&mutex->mtx_id), mtxcode);
	else if (INIT == mtxcode)
	{
		handle_mtx_err(mutex->rules, pthread_mutex_init(&mutex->mtx_id, NULL), mtxcode);//ajouter mutex.is_init = true ici est + smart
		mutex->is_init = true; //variable uniquement touchee par main_thd mais potentiellement inutile
	}
	else if (DESTROY == mtxcode && mutex->is_init)
	{
		mutex->is_init = false; //variable uniquement touchee par main_thd
		handle_mtx_err(mutex->rules, pthread_mutex_destroy(&mutex->mtx_id), mtxcode);
	}
	else//
		close_error(mutex->rules, "this messge should not be printed : safe_mutex_handle\n"); //retirer apres debug
}








// static void	handle_mtx_err(t_rules *rules, int funct_return, t_mtxcode mtxcode)
// {
// 	if (0 == funct_return)
// 		return ;
// 	if (EINVAL == funct_return && (LOCK == mtxcode || UNLOCK == mtxcode))
// 		return ; close_error(rules, "The value specified by mutex is invalid\n");
// 	else if (EINVAL == funct_return && INIT == mtxcode)
// 		close_error(rules, "The value specified by attr is invalid.\n");
// 	else if (c == funct_return)
// 		close_error(rules, "A deadlock would occur if the thread "
// 			"blocked waiting for mutex.\n");
// 	else if (EPERM == funct_return)
// 		close_error(rules, "The current thread does not hold a lock on mutex.\n");
// 	else if (ENOMEM == funct_return)
// 		close_error(rules, "The process cannot allocate enough memory"
// 			" to create another mutex.\n");
// 	else if (EBUSY == funct_return)
// 		close_error(rules, "Mutex is locked\n");

// 	//ne pas mettre close error ici
// }

// void	safe_mutex_handle(t_mutex *mutex, t_mtxcode mtxcode) //retirer rules car contenu dans mutex et donner t_mutex au lieu de t_mtx
// {
// 	int	ret;
// 	if(!mutex) //protege dans certains cas de closing
// 		return;
// 	else if (INIT == mtxcode)
// 	{
// 		handle_mtx_err(mutex->rules, pthread_mutex_init(mutex, NULL), mtxcode);//ajouter mutex.is_init = true ici est + smart
// 		mutex->is_init = true; //variable uniquement touchee par main_thd
// 	}
// 	else if (LOCK == mtxcode && mutex->is_init)
// 	{
// 		handle_mtx_err(mutex->rules, pthread_mutex_lock(mutex), mtxcode);
// 		mutex->is_lock = true;
// 	}
// 	else if (UNLOCK == mtxcode && mutex->is_init && mutex->is_lock)
// 	{
// 		mutex->is_lock == false;
// 		handle_mtx_err(mutex->rules, pthread_mutex_unlock(mutex), mtxcode);
// 	}
// 	else if (DESTROY == mtxcode && mutex->is_lock == false && mutex->is_init) //verifier ici si  mutex.is_init = true ici est + smart
// 	{
// 		mutex->is_init = false; //variable uniquement touchee par main_thd
// 		if(mutex->is_lock)
// 			safe_mutex_handle(mutex, UNLOCK);
// 		handle_mtx_err(mutex->rules, pthread_mutex_destroy(mutex), mtxcode);
// 	}
// 	else
// 		close_error(mutex->rules, "this messge should not be printed : safe_mutex_handle\n"); //retirer apres debug
// }

