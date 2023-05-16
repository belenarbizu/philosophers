/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:14:57 by barbizu-          #+#    #+#             */
/*   Updated: 2022/12/28 11:15:03 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	init(int argc, char **argv, t_data *data)
{
	if (check_num(argv))
	{
		printf("Arg no numericos\n");
		return (0);
	}
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	(void)argc;
	if (argc == 6)
		data->n_times_eat = ft_atoi(argv[5]);
	else
		data->n_times_eat = -1;
	return (1);
}

void	fill_philo(t_data *data, int i)
{
	data->philo[i].n_eat = 0;
	data->philo[i].last_eat = 0;
	data->philo[i].id = i;
	data->philo[i].right_fork = i;
	data->philo[i].left_fork = i + 1;
	data->philo[i].is_dead = 0;
	data->philo[i].data = data;
}

int	init_philo(t_data *data)
{
	int	i;

	i = 1;
	data->t_start = get_time();
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	while (i <= data->n_philo)
	{
		fill_philo(data, i);
		if (i == data->n_philo)
			data->philo[i].left_fork = 1;
		i++;
	}
	if (data->n_philo == 1)
	{
		if (!one_philo(&data->philo[1]))
			return (0);
		else
			return (1);
	}
	if (!start_philo(data))
		return (0);
	return (1);
}

int	init_fork(t_data *data)
{
	int	i;

	i = 1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while (i <= data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			printf("Error en los mutex");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
	{
		printf("Error en los mutex");
		return (0);
	}
	return (1);
}
