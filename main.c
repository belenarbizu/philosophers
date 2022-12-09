#include "philo.h"

void	*start_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = data->n_thread;
	if (data->n_times_eat >= 0)
	{
		while ((data->n_times_eat > data->philo[i].n_eat)) //&& philo_dead
		{
			philo_eat(data, i);
		}
	}
	/*else
    {
        while (!philo->data->dead)
        {
            philo_eat(philo);
        }
    }*/
	return (NULL);
}

int	philo_eat(t_data *data, int i)
{
	if (grab_fork(data, data->philo[i].right_fork, data->philo[i].id))
		return (1);
	if (grab_fork(data, data->philo[i].left_fork, data->philo[i].id))
		return (1);
	printf("timestamp_in_ms %d %s\n", data->philo[i].id, EAT);
	usleep(data->time_to_eat);
	down_fork(data, data->philo[i].right_fork, data->philo[i].left_fork);
	//philo.last_eat = (get_time() - philo->data->t_start);
	//printf("tiempo last eat:%d\n", philo.last_eat);
	printf("timestamp_in_ms %d %s\n", data->philo[i].id, SLEEP);
	usleep(data->time_to_sleep);
	printf("timestamp_in_ms %d %s\n", data->philo[i].id, THINK);
	return (0);
}

int	grab_fork(t_data *data, int i, int id)
{
	if (pthread_mutex_lock(&data->forks[i]) != 0)
		return (1);
	printf("timestamp_in_ms %d %s %d\n", id, FORK, i);
	return (0);
}

void	down_fork(t_data *data, int i, int j)
{
	pthread_mutex_unlock(&data->forks[i]);
	pthread_mutex_unlock(&data->forks[j]);
	data->philo[i].n_eat++;
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc < 5 || argc > 6)
		write(1, "El numero de argumentos debe ser 4 ó 5\n", 40);
	else
	{
		data = malloc(sizeof(t_data));
		if (init(argc, argv, data))
		{
			if (init_fork(data))
				init_philo(data);
		}
	}
}
