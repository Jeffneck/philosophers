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

typedef struct s_mutex
{
    t_mtx	mtx;
	bool	mtx_is_init;
}   t_mutex;

typedef struct s_philo
{
    int				id;
	// bool			is_eating;
    int				meals_counter;
    bool			full; //meal_lock
    long			timestamp_lastmeal; //meal lock
    t_mutex			*first_fork;
    t_mutex			*second_fork;
    pthread_t		thread_id; //un philosophe = un thread
	bool			thread_is_init;
    t_rules			*rules;
}   t_philo;


struct s_rules
{
	int		philos_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nbr_limit_meals; //-1 si aucune limite
	//mutex et threads
	t_philo			*philos; //tableau de structure contenant tous les philosophes
	t_mutex			*forks; //tableau de structure contenant toutes les fourchettes
	//utils
	long	timestamp_start; //heure precise du debut de la simulation
    //monitoring
	bool	ready_to_eat; //doit etre mutex si je l'utilise, tester sans quand tout sera ok
	t_mutex end_lock;
	bool	end_simulation; //mort philo ou tous les philo sont full
	t_mutex meal_lock; //verif full et timestamp_lastmeal;
	//mutex || struct synchronise
	t_mutex	write;
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
void    exit_error(char *strerr);
void    close_error(t_rules *p_rules, char *strerr);

//threads & mutex
void	safe_thread_handle(t_rules *p_rules, pthread_t *philo_thread, void *philo_data, t_trdcode trdcode);
void	safe_mutex_handle(t_rules *p_rules, t_mtx *mutex, t_mtxcode mtxcode);


//time utils
long	get_curr_timestamp(void);
void	ft_usleep(long u_towait);
long	get_elapsed_time_ms(long timestamp_start);

void	*dinner_loop(void *philo_data);
void	monitor_dinner(t_rules	*p_rules);
void    dinner_end(t_rules *p_rules);

//init 
void    init_structs(t_rules *p_rules, char ** av);

//init utils
void	check_rules_max_values(t_rules *p_rules);
void	transform_rules_times_to_ms(t_rules *p_rules);







#endif //PHILOSOPHERS_H