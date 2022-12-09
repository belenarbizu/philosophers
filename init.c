#include "philo.h"

int    init(int argc, char **argv, t_data *data)
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
    if (argc == 6)
        data->n_times_eat = ft_atoi(argv[5]);
    else
        data->n_times_eat = -1;
    return (1);
}

int    init_philo(t_data *data)
{
    int i;

    i = 0;
    data->t_start = get_time();
    data->philo = malloc(sizeof(t_philo) * data->n_philo);
    while (i < data->n_philo)
    {
        data->philo[i].n_eat = 0;
        data->philo[i].last_eat = 0;
        data->philo[i].id = i + 1;
        data->philo[i].left_fork = i;
        data->philo[i].right_fork = i + 1;
        data->n_thread = i;
        if (i == 0)
            data->philo[i].left_fork = data->n_philo;
        if (pthread_create(&data->philo[i].thread, NULL, start_routine, (void *)data))
        {
            printf("Error en los hilos");
            return (0);
        }
        i++;
    }
    i = 0;
    while (i < data->n_philo)
    {
        if (pthread_join(data->philo[i].thread, NULL))
        {
            printf("Error en los hilos");
            return (0);
        }
        i++;
    }
    return (1);
}

int    init_fork(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
    while (i < data->n_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
        {
            printf("Error en los mutex");
            return (0);
        }
        i++;
    }
    return (1);
}
