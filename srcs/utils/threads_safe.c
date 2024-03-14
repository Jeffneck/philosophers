# include "../../includes/philosophers.h"

//utiliser close error plutot que exit error pour liberer la memoire allouee et destroy tous les mutex + modif une variable qui mettrait fin a tous les threads
// sous entent que cette fonction aurait soit : 
// la possibilite de vider le gc
// la possibilite d' accerder a la struct t_rules pour liberer toutes les allocations

void	handle_thread_error(int status, t_trdcode trdcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		print("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == trdcode)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == trdcode || DETACH == trdcode))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that"
			"specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread.");
}


// //on pourrait techniquement se passer de cette fonction
// void	safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
// 		void *data, t_trdcode trdcode)
// {
// 	if (CREATE == trdcode)
// 		handle_thread_error(pthread_create(thread, NULL, routine, data), trdcode);
// 	else if (JOIN == trdcode)
// 		handle_thread_error(pthread_join(*thread, NULL), trdcode);
// 	else if (DETACH == trdcode)
// 		handle_thread_error(pthread_detach(*thread), trdcode);
// 	else
// 		error_exit("Wrong trdcode for thread_handle:"
// 			" use <CREATE> <JOIN> <DETACH>");
// }