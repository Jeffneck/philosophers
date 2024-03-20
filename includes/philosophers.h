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

# define TOOK_FORK_MSG "%ld %d has taken a fork\n"
# define EAT_MSG "%ld %d is eating\n"
# define SLEEP_MSG "%ld %d is sleeping\n"
# define THINK_MSG "%ld %d is thinking\n"
# define DIED_MSG "%ld %d died\n"


typedef enum e_timecode
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}			t_timecode;

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
	bool			is_lock;
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
    int				id;
    int				nb_meals;
    t_mutex			*fst_fork;
    t_mutex			*scd_fork;
	t_mutex			philo_lock; //lock : full / ts_lastmeal
    long			ts_lastmeal;
    bool			full;
    t_thread		thread;
    t_rules			*rules;
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
void	philo_msg_mutex(t_rules *p_rules, t_philo philo, char *msg);
void	print_error_mutex(t_rules *p_rules, char *strerr);

//error
void    exit_error(char *strerr);//pas le droit d'exit
void    close_error(t_rules *p_rules, char *strerr);

//threads & mutex
void	safe_thread_handle(t_philo *philo, t_trdcode trdcode);

void	safe_mutex_handle(t_mutex *mutex, t_mtxcode mtxcode);

//mutex access 
bool	get_mtxbool(t_mutex *mutex, bool *to_get);
void	set_mtxbool(t_mutex *mutex, bool *to_set, bool value);
long	get_mtxlong(t_mutex *mutex, long *to_get);
void	set_mtxlong(t_mutex *mutex, long *to_set, long value);

//time utils
long	get_ms_timestamp(void); //get_ms_timestamp
void	ms_sleep(long ms); //ms_sleep(long ms);
long	get_ms_elapsed(long ts_init); // get_ms_elapsed

void	*dinner_loop(void *philo_data);
void	monitor_dinner(t_rules	*p_rules);
void    dinner_end(t_rules *p_rules);

//init 
void    init_structs(t_rules *p_rules, char ** av);

//init utils
void	check_rules_max_values(t_rules *p_rules);
void	transform_rules_times_to_ms(t_rules *p_rules);







#endif //PHILOSOPHERS_H