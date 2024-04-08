# include "../../includes/philosophers.h"

long	get_ms_timestamp(void)
{
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1e3 + timestamp.tv_usec / 1e3);
}

void	ms_sleep(long ms)
{
	usleep(ms * 1000);
}

long	get_ms_elapsed(long ts_init)
{
	return(get_ms_timestamp() - ts_init);
}

/*
void	ms_sleep(long to_wait)
{
	long	start;
	long	time_remaining;

	start = get_ms_timestamp();
	while(get_ms_timestamp() - start < to_wait)
	{
		time_remaining = get_ms_timestamp() - start;
		if(time_remaining > 1e4)
			usleep(time_remaining * 1e3 / 2);
		while(get_ms_timestamp() - start < to_wait)
				;
	}
}
*/
