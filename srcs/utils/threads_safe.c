# include "../../includes/philosophers.h"

//utiliser close error plutot que exit error pour liberer la memoire allouee et destroy tous les mutex + modif une variable qui mettrait fin a tous les threads
// sous entent que cette fonction aurait soit : 
// la possibilite de vider le gc
// la possibilite d' accerder a la struct t_rules pour liberer toutes les allocations

static void	handle_thread_error(t_rules *p_rules, int status, t_trdcode trdcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		close_error(p_rules, "No resources to create another thread"); 
	else if (EPERM == status)
		close_error(p_rules, "The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == trdcode)
		close_error(p_rules, "The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == trdcode || DETACH == trdcode))
		close_error(p_rules, "The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		close_error(p_rules, "No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		close_error(p_rules, "A deadlock was detected or the value of"
			"thread specifies the calling thread.");
	//tout remplacer par print_msg pas de exit
}


// //on pourrait techniquement se passer de cette fonction
void	safe_thread_handle(t_rules *p_rules, pthread_t *philo_thread, void *philo, t_trdcode trdcode)
{
	if (CREATE == trdcode)
		handle_thread_error(p_rules, pthread_create(philo_thread, NULL, dinner_loop, philo), trdcode);
	else if (JOIN == trdcode)
		handle_thread_error(p_rules, pthread_join(*philo_thread, NULL), trdcode);
	else if (DETACH == trdcode)
		handle_thread_error(p_rules, pthread_detach(*philo_thread), trdcode);
}