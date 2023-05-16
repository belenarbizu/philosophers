/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:15:09 by barbizu-          #+#    #+#             */
/*   Updated: 2022/12/28 11:15:15 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = 1;
	pthread_detach(data->dead);
	pthread_mutex_destroy(&data->print);
	while (i <= data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_detach(data->philo[i].thread);
		i++;
	}
	free(data->philo);
	free(data->forks);
	free(data);
}

void	*checker(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 1;
	if (data->n_times_eat >= 0)
	{
		while (data->n_times_eat > data->philo[i].n_eat && !philo_dead(data))
		{
			if (check_death(data, &i))
				break ;
		}
	}
	else
	{
		while (!philo_dead(data))
		{
			if (check_death(data, &i))
				break ;
		}
	}
	return (NULL);
}

int	philo_dead(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->n_philo)
	{
		if (data->philo[i].is_dead)
			return (1);
		i++;
	}
	return (0);
}

int	check_death(t_data *data, int *i)
{
	if (*i == (data->n_philo + 1))
		*i = 1;
	if ((get_time() - data->t_start)
		- data->philo[*i].last_eat > data->time_to_die)
	{
		printf("%lld %d %s\n", (get_time() - data->t_start), data->philo[*i].id,
			DIE);
		data->philo[*i].is_dead = 1;
		return (1);
	}
	i++;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

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
		free_data(data);
	}
}
