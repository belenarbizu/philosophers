#include "philo.h"

int	ft_atoi(const char *str)
{
	long long		n;
	int				cnt;
	int				sign;

	cnt = 0;
	n = 0;
	sign = 1;
	while (str[cnt] == ' ' || str[cnt] == '\t' || str[cnt] == '\n'
		|| str[cnt] == '\v' || str[cnt] == '\f' || str[cnt] == '\r')
		cnt++;
	if (str[cnt] == '-' || str[cnt] == '+')
	{
		if (str[cnt] == '-')
			sign *= -1;
		cnt++;
	}
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		n = n * 10 + str[cnt] - '0';
		cnt++;
	}
	n *= sign;
	if (n < INT_MIN || n > INT_MAX)
		return (0);
	return (n);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int check_num(char **str)
{
    int i;
    int j;

    i = 1;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

long long   get_time(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}