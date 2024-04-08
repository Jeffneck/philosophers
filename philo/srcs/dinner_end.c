#include "../includes/philosophers.h"

static void	close_philos(t_rules *rules)
{
	int		i;
	t_philo	*philos;

	philos = rules->philos;
	if(philos)
	{
		i = -1;
		while(++i < rules->nb_phil && philos[i].thread.is_init == true)
		{
			safe_thread_handle(&philos[i], JOIN);
			safe_mutex_handle(&(philos[i].philo_lock), DESTROY);
		}
		free(philos);
	}
}

static void	close_forks(t_rules *rules)
{
	int		i;
	t_mutex	*forks;

	forks = rules->forks;
	if(forks)
	{
		i = -1;
		while(++i < rules->nb_phil && forks[i].is_init)
			safe_mutex_handle(&(forks[i]), DESTROY);
		free(forks);
	}
}


void    close_error(t_rules * rules, char *strerr)
{
    print_error(rules, strerr);
    dinner_end(rules);
}

void	dinner_end(t_rules *rules)
{
	close_philos(rules);
	close_forks(rules);
	rules->dinner_ended = true;// pour stopper en cas d' err d' args	
	if(rules->write_lock.is_init)
		safe_mutex_handle(&(rules->write_lock), DESTROY);
	if(rules->rules_lock.is_init)
		safe_mutex_handle(&(rules->rules_lock), DESTROY);
}