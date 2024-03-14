# include "../../includes/philosophers.h"

static void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

// static void	ft_putnbr_fd(int n, int fd)
// {
// 	char	nbr[1];

// 	if (n == -2147483648)
// 	{
// 		write(fd, "-2147483648", 11);
// 		return ;
// 	}
// 	if (n < 0)
// 	{
// 		n = -n;
// 		write(fd, "-", 1);
// 	}
// 	if (n > 9)
// 	{
// 		ft_putnbr_fd(n / 10, fd);
// 		ft_putnbr_fd(n % 10, fd);
// 	}
// 	else
// 	{
// 		nbr[0] = n + 48;
// 		write(fd, nbr, 1);
// 	}
// }

void	philo_msg_mutex(t_rules *p_rules, t_philo philo, char *msg)
{
	safe_mutex_handle((&p_rules->write_mtx), LOCK);
	if(philo.rules->end_simulation == false)
	{
		printf(msg, get_timestamp(MILLISECONDS) - p_rules->timestamp_start, philo.id);
	}
	safe_mutex_handle((&p_rules->write_mtx), UNLOCK);
}

void	print_error_mutex(t_rules *p_rules, char *strerr)
{
		if(p_rules->write.mtx_is_init) ////


		ft_putstr_fd(strerr, 2);
}
