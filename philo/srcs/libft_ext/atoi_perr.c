# include "../../includes/philosophers.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

static const char	*valid_input(const char *str, int *p_err)
{
	int			len;
	const char	*number;

	len = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
    {
        *p_err = -2;
		++str;
    }
	if (!ft_isdigit(*str))
        *p_err = -3;
	number = str;
	while (ft_isdigit(*str++))
		++len;
	if (len > 10)
        *p_err = -1;
	return (number);
}

int  atoi_perr_positive_only(const char *str, int *p_err)
{
	long	num;
    
	num = 0;
    *p_err = 0;
	str = valid_input(str, p_err);
    if (*p_err != 0)
	{
        return (0);
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str++ - '0');
	}
	if (num > INT_MAX || num == 0)
    {
        *p_err = -1;
		return(0);
    }
	return ((int)num);
}

int  atoi_perr(const char *str, int *p_err)
{
    long	num;

	num = 0;
    *p_err = 0;
	str = valid_input(str, p_err);
    if (*p_err == -1 || *p_err == -3)
        return (0);
    *p_err = 0;
	while (ft_isdigit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
    {
        *p_err = -1;
		return(0);
    }
	return ((int)num);
}