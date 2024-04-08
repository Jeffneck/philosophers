# include "../includes/philosophers.h"


void	*lone_philo(void *p)
{
	printf("lone \n");//
	fflush(stdout);//
	t_rules	*rules;
	t_philo *philo;

	philo = (t_philo *)p; 
	rules = philo->rules;
	//on attend que tous les philos soient crees pour commencer le dinner
	while (getter_bool(&rules->rules_lock, DINNER_READY) == false) 
		ms_sleep(2);
	// setter_tslastmeal(philo, getter_tsstart(philo));//philo_lock et rules_lock ?? //getter_ts_start semble inutile
	safe_mutex_handle(philo->fst_fork, LOCK);
	print_philo(philo, TOOK_FORK_MSG);
	safe_mutex_handle(philo->fst_fork, UNLOCK);
	while (getter_bool(&rules->rules_lock, DINNER_ENDED) == false)
	{
		ms_sleep(1);
	}
	return(NULL); //inutile de retourner qq chose ? la fonction doit avoir ce prototype
}