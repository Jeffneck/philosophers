# include "../../includes/philosophers.h"

//utiliser close error plutot que exit error pour liberer la memoire allouee et destroy tous les mutex + modif une variable qui mettrait fin a tous les threads
// sous entent que cette fonction aurait soit : 
// la possibilite de vider le gc
// la possibilite d' accerder a la struct t_rules pour liberer toutes les allocations

static void	handle_thd_err(t_rules *rules, int status, t_trdcode trdcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		close_error(rules, EAGAIN_THD_E); 
	else if (EPERM == status)
		close_error(rules, EPERM_THD_E);
	else if (EINVAL == status && CREATE == trdcode)
		close_error(rules, EINVAL_THD_C_E);
	else if (EINVAL == status && (JOIN == trdcode || DETACH == trdcode))
		close_error(rules, EINVAL_THD_J_E);
	else if (ESRCH == status)
		close_error(rules, ESRCH_THD_E);
	else if (EDEADLK == status)
		close_error(rules, EDEADLK_THD_E);
}

// //on pourrait techniquement se passer de cette fonction
// void	safe_thread_handle(t_rules *rules, pthread_t *philo_thread, void *philo, t_trdcode trdcode)
void	safe_thread_handle(t_philo *philo, t_trdcode trdcode)
{
	// printf("nb philos = ")
	if(!philo)
		return;
	if (CREATE == trdcode && philo->rules->nb_phil == 1)
		handle_thd_err(philo->rules, pthread_create(&(philo->thread.thd_id), NULL, lone_philo, philo), trdcode);
	else if (CREATE == trdcode)
		handle_thd_err(philo->rules, pthread_create(&(philo->thread.thd_id), NULL, dinner_loop, philo), trdcode);
	else if (JOIN == trdcode)
		handle_thd_err(philo->rules, pthread_join(philo->thread.thd_id, NULL), trdcode);
	else if (DETACH == trdcode)
		handle_thd_err(philo->rules, pthread_detach(philo->thread.thd_id), trdcode);
	else//
		close_error(philo->rules, "this messge should not be printed : safe_mutex_handle\n");
}