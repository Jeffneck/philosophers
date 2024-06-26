#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h> // mutex init destroy lock unlock && threads create join detach 
# include <errno.h>
# include <string.h>
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX INT_MIN
// # include "../libft/libft.h"


# ifndef MAX_PHILO_NBR
#  define MAX_PHILO_NBR 200
# endif
# ifndef MIN_TIME
#  define MIN_TIME 60
# endif



/*
** ANSI Escape Sequences for Bold Text Colors
** Usage: 
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** Remember to use RS to reset the color after setting it.
*/

# define RS		"\033[0m"      /* Reset to default color */
# define R		"\033[1;31m"   /* Bold Red */
# define G		"\033[1;32m"   /* Bold Green */
# define Y		"\033[1;33m"   /* Bold Yellow */
# define B		"\033[1;34m"   /* Bold Blue */
# define M		"\033[1;35m"   /* Bold Magenta */
# define C		"\033[1;36m"   /* Bold Cyan */
# define W		"\033[1;37m"   /* Bold White */

typedef pthread_mutex_t t_mtx;
typedef struct s_rules t_rules;

# define MALLOC_E "memory allocation error detected, program ended\n"
# define EINVAL_MTX_E "The value specified by attr is invalid.\n"
# define EDEADLK_MTX_E "A deadlock would occur if the thread blocked waiting for mutex.\n"
# define ENOMEM_MTX_E "The process cannot allocate enough memory to create another mutex.\n"

# define EINVAL_THD_C_E "The value specified by attr is invalid.\n"
# define EINVAL_THD_J_E "The value specified by thread is not joinable\n"
# define EAGAIN_THD_E "No resources to create another thread\n"
# define EPERM_THD_E "The caller does not have appropriate permission\n"
# define EDEADLK_THD_E "A deadlock was detected or the value of thread specifies the calling thread.\n"
# define ESRCH_THD_E "No thread could be found corresponding to that specified by the given thread ID, thread.\n"


# define TOOK_FORK_MSG "%ld %d has taken a fork\n"
# define EAT_MSG Y"%ld %d is eating\n"RS
# define SLEEP_MSG B"%ld %d is sleeping\n"RS
# define THINK_MSG "%ld %d is thinking\n"
# define DIED_MSG R"%ld %d died\n"RS


typedef enum e_timecode
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}			t_timecode;

typedef enum e_varcode
{
	DINNER_READY,
	DINNER_ENDED,
}			t_varcode;

typedef enum e_mtxcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
}			t_mtxcode;

typedef enum e_trdcode
{
	CREATE,
	JOIN,
	DETACH,
}			t_trdcode;

//remplacer par structure t_mutex, qui pourrait aussi etre utilisee par write !
// typedef struct s_fork
// {
//     t_mtx fork_mtx;
//     int     fork_id;
// 	bool	is_init;
// }   t_fork;
/*
ts = timestamp
th = thread
*/
typedef struct s_mutex
{
    pthread_mutex_t	mtx_id;
	// bool			is_lock;
	bool			is_init;
	t_rules			*rules;
}   t_mutex;

typedef struct s_thread
{
    pthread_t	thd_id;
	bool		is_init;
	t_rules 	*rules;
}   t_thread;

typedef struct s_philo
{
    int			id;
	//
	// long		ms_to_die;
	// long		ms_to_eat;
	// long		ms_to_sleep;
	//
	int			nb_meals;
	// int			max_meals; 
	//
	t_mutex		*fst_fork;
	t_mutex		*scd_fork;
	//locked
	t_mutex		philo_lock;
	long		ts_lastmeal;
	bool		is_full;
	//locked
	t_thread	thread;
	t_rules		*rules;
}   t_philo;


struct s_rules
{
	int		nb_phil;
	long	ms_to_die;
	long	ms_to_eat;
	long	ms_to_sleep;
	int		max_meals; //-1 si aucune limite
	//mutex et threads
	t_philo			*philos; //tableau de structure contenant tous les philosophes
	t_mutex			*forks; //tableau de structure contenant toutes les fourchettes
	//utils
	long	ts_start; //heure precise du debut de la simulation
    //monitoring
	t_mutex rules_lock; // var dinner_ready && dinner_end
	bool	dinner_ready;
	bool	dinner_ended; //mort philo ou tous les philo sont full
	t_mutex	write_lock; //acces a stdout
};

// **libft_extension**
int		atoi_perr_positive_only(const char *str, int *p_err);
int		atoi_perr(const char *str, int *p_err);
void	*ft_calloc(size_t nmemb, size_t size);

//print
void	ft_putstr_fd(char *s, int fd);
void	print_philo(t_philo *philo, char *msg);
void	print_philo_died(t_philo *philo);
void	print_error(t_rules *p_rules, char *strerr);

//error
void    close_error(t_rules *p_rules, char *strerr);

//threads & mutex
void	safe_thread_handle(t_philo *philo, t_trdcode trdcode);

void	safe_mutex_handle(t_mutex *mutex, t_mtxcode mtxcode);

//mutex access 
void setter_bool(t_mutex *mutex, t_varcode varcode, bool new_value);
void setter_isfull(t_philo *philo, bool new_value);
void setter_tslastmeal(t_philo *philo, long new_value);

bool	getter_bool(t_mutex *mutex, t_varcode varcode);
bool	getter_isfull(t_philo *philo);
long	getter_tslastmeal(t_philo *philo);
long	getter_tsstart(t_philo *philo);

//time utils
long	get_ms_timestamp(void);
void	ms_sleep(long ms);
long	get_ms_elapsed(long ts_init);

void	*dinner_loop(void *philo_data);
void	monitor_dinner(t_rules	*p_rules);
void    dinner_end(t_rules *p_rules);

//init 
bool    init_structs(t_rules *p_rules, char ** av);

//init utils
bool	check_rules_max_values(t_rules *p_rules);
// void	transform_rules_times_to_ms(t_rules *p_rules);

void	*lone_philo(void *p);





#endif //PHILOSOPHERS_H