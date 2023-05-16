/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barbizu- <barbizu-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:15:26 by barbizu-          #+#    #+#             */
/*   Updated: 2022/12/28 11:15:29 by barbizu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	philo_write(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->print);
	if (!philo_dead(data))
		printf("%lld %d %s\n", (get_time() - data->t_start), id, str);
	pthread_mutex_unlock(&data->print);
}

int	left_handed(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->left_fork]) != 0)
		return (0);
	philo_write(philo->data, philo->id, FORK);
	if (pthread_mutex_lock(&philo->data->forks[philo->right_fork]) != 0)
		return (0);
	philo_write(philo->data, philo->id, FORK);
	return (1);
}

int	right_handed(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->right_fork]) != 0)
		return (0);
	philo_write(philo->data, philo->id, FORK);
	if (pthread_mutex_lock(&philo->data->forks[philo->left_fork]) != 0)
		return (0);
	philo_write(philo->data, philo->id, FORK);
	return (1);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(50);
	if (philo->data->n_times_eat >= 0)
	{
		while ((philo->data->n_times_eat > philo->n_eat)
			&& !philo_dead(philo->data))
			philo_eat(philo);
	}
	else
	{
		while (!philo_dead(philo->data))
			philo_eat(philo);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!left_handed(philo))
			return (0);
	}
	else
	{
		if (!right_handed(philo))
			return (0);
	}
	philo_write(philo->data, philo->id, EAT);
	philo->last_eat = (get_time() - philo->data->t_start);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	philo->n_eat++;
	philo_write(philo->data, philo->id, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	philo_write(philo->data, philo->id, THINK);
	return (1);
}
