#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h> // mutex init destroy lock unlock && threads create join detach 
# include <errno.h>
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX INT_MIN
# include "../libft/libft.h"


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


typedef struct s_fork
{
    t_mtx fork_mtx;
    int     fork_id;
}   t_fork;


typedef struct s_philo
{
    int				id; 
    int				meals_counter;
    bool			full; //=repus
    long			time_since_meal;
    t_fork			*first_fork;
    t_fork			*second_fork;
    pthread_t		thread_id; //un philosophe = un thread
    t_rules			*rules;
}   t_philo;

struct s_rules
{
    int    philo_nbr;
    int    time_to_die;
    int    time_to_eat;
    int    time_to_sleep;
    long            nbr_limit_meals; //-1 si aucune limite
    long            timestamp_start; //heure precise du debut de la simulation
    bool            end_simulation; //mort philo ou tous les philo sont full
	t_philo			*philos; //tableau de structure contenant tous les philosophes
	t_fork			*forks; //tableau de structure contenant toutes les fourchettes
};

// **libft_extension**
int  atoi_perr_positive_only(const char *str, int *p_err);
int  atoi_perr(const char *str, int *p_err);
void	*malloc_safe(size_t bytes, void *tofree, char *strerr, void (*f_cleanclose)(void *, char *));


void    exit_error(char *strerr);
void    close_error(t_rules *p_rules, char *strerr);


void	safe_thread_handle(pthread_t *thread, void *(*routine)(void *),
		void *data, t_trdcode trdcode);

void	safe_mutex_handle(t_mtx *mutex, t_mtxcode mtxcode);












#endif //PHILOSOPHERS_H