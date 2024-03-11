#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Chaque thread comptera TIMES_TO_COUNT fois
#define TIMES_TO_COUNT 21000

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"


typedef	struct s_data
{
	pthread_mutex_t mutex;
	unsigned int	count;
}	t_data;


void	*thread_routine(void *data)
{
	// Chaque thread commence ici
	pthread_t	tid;
	unsigned int	i;
	t_data *p_data;

	tid = pthread_self();
	p_data = (t_data *)data;
	// On imprime le compte avant que ce thread commence a itérer
	pthread_mutex_lock(&(p_data->mutex));
	printf("%sThread [%ld]: compte au depart = %u.%s\n", YELLOW, tid, p_data->count, NC);
	pthread_mutex_unlock(&(p_data->mutex));

	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		// On itere TIMES_TO_COUNT fois
		// On incremente le compte a chaque iteration
		pthread_mutex_lock(&(p_data->mutex));
		(p_data->count)++;
		pthread_mutex_unlock(&(p_data->mutex));
		i++;
	}
	// On imprime le compte final au moment ou ce thread
	// a termine son propre compte
	printf("%sThread [%ld]: Compte final = %u.%s\n", BYELLOW, tid, p_data->count, NC);
	return (NULL); // Thread termine ici.
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	// Variable pour contenir le compte des deux threads :
	t_data data;

	data.count = 0;
	if (pthread_mutex_init(&(data.mutex), NULL) != 0)
	{
        fprintf(stderr, "Erreur lors de l'initialisation du mutex\n");
        return 1;
    }
	// Vu que chaque thread va compter TIMES_TO_COUNT fois et qu'on va
	// avoir 2 threads, on s'attend a ce que le compte final soit
	// 2 * TIMES_TO_COUNT :
	printf("Main: Le compte attendu est de %s%u%s\n", GREEN, 2 * TIMES_TO_COUNT, NC);
	// Creation des threads :
	if (pthread_create(&tid1, NULL, thread_routine, &data) != 0)
	{
        fprintf(stderr, "Erreur lors de la creation d'un thread\n");
        return 1;
    }

	printf("Main: Creation du premier thread [%ld]\n", tid1);
	if(pthread_create(&tid2, NULL, thread_routine, &data) != 0)
	{
        fprintf(stderr, "Erreur lors de la creation d'un thread\n");
        return 1;
    }
	printf("Main: Creation du second thread [%ld]\n", tid2);
	// Recuperation des threads :
	if (pthread_join(tid1, NULL) != 0)
	{
        fprintf(stderr, "Erreur lors de la jointure d'un thread\n");
        return 1;
    }
	printf("Main: Union du premier thread [%ld]\n", tid1);
	if (pthread_join(tid2, NULL) != 0)
	{
        fprintf(stderr, "Erreur lors de la jointure d'un thread\n");
        return 1;
    }
	printf("Main: Union du second thread [%ld]\n", tid2);
	
	if(pthread_mutex_destroy(&(data.mutex)))
	{
        fprintf(stderr, "Erreur lors de la destruction du mutex\n");
        return 1;
    }

	// Evaluation du compte final :
	if (data.count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERREUR ! Le compte est de %u%s\n", RED, data.count, NC);
	else
		printf("%sMain: OK. Le compte est de %u%s\n", GREEN, data.count, NC);
	return (0);
}

// gcc -pthread 'bacasable/4.threads_mutex.c' -o 'bacasable/4.threads_mutex' ; 'bacasable/4.threads_mutex' ; rm 'bacasable/4.threads_mutex'