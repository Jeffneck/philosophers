# include "../../includes/philosophers.h"

long	get_timestamp(t_timecode timecode)
{
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	if(timecode == MICROSECONDS)
		return (timestamp.tv_sec * 1e6 + timestamp.tv_usec);
	if(timecode == MILLISECONDS)
		return (timestamp.tv_sec * 1e3 + timestamp.tv_usec / 1e3);
	if(timecode == SECONDS)
		return (timestamp.tv_sec + timestamp.tv_usec / 1e6);
}

void	ft_usleep(long time_towait, t_rules *p_rules)
{
	long	start;
	long	time_remaining;

	start = get_timestamp(MICROSECONDS);
	while(get_timestamp(MICROSECONDS) - start < time_towait)
	{
		
		time_remaining = get_timestamp(MICROSECONDS) - start;
		if(time_remaining > 1e4)
			usleep(time_remaining / 2);
		while(get_timestamp(MICROSECONDS) - start < time_towait)
				;
	}
}

long	get_simulation_time_ms(long timestamp_start)
{
	return(get_timestamp(MILLISECONDS) - timestamp_start);
}