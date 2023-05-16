/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:59:09 by barbizu-          #+#    #+#             */
/*   Updated: 2022/12/28 11:59:13 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	start_philo(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, start_routine,
				&(data->philo[i])))
		{
			printf("Error en los hilos");
			return (0);
		}
		i++;
	}
	if (pthread_create(&data->dead, NULL, checker, (void *)data))
	{
		printf("Error en los hilos");
		return (0);
	}
	if (!join_philo(data))
		return (0);
	return (1);
}

int	join_philo(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->n_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
		{
			printf("Error en los hilos");
			return (0);
		}
		i++;
	}
	if (pthread_join(data->dead, NULL))
	{
		printf("Error en los hilos");
		return (0);
	}
	return (1);
}

int	one_philo(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[1]) != 0)
		return (0);
	philo_write(philo->data, 1, FORK);
	usleep(philo->data->time_to_die * 1000);
	printf("%lld %d %s\n", (get_time() - philo->data->t_start), 1, DIE);
	return (1);
}
