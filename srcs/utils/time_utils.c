# include "../../includes/philosophers.h"

long	get_ms_timestamp(void)
{
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	// if(timecode == MICROSECONDS)
	// 	return (timestamp.tv_sec * 1e6 + timestamp.tv_usec);
	// if(timecode == MILLISECONDS)
	return (timestamp.tv_sec * 1e3 + timestamp.tv_usec / 1e3);
	// return (timestamp.tv_sec + timestamp.tv_usec / 1e6);
}

void	ms_sleep(long ms)
{
	// long	start;
	// long	time_remaining;

	// start = get_curr_timestamp(MICROSECONDS);
	// while(get_curr_timestamp(MICROSECONDS) - start < u_towait)
	// {
		
	// 	time_remaining = get_curr_timestamp(MICROSECONDS) - start;
	// 	if(time_remaining > 1e4)
	// 		usleep(time_remaining / 2);
	// 	while(get_curr_timestamp(MICROSECONDS) - start < u_towait)
	// 			;
	// }
	usleep(ms * 1000);
}

long	get_ms_elapsed(long ts_init)
{
	return(get_ms_timestamp() - ts_init);
}