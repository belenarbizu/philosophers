#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_philo
{
    int         id;
    int         last_eat; //ultima vez que ha comido
    int         n_eat; //numero de veces que ha comido
    int         right_fork; //id del tenedor de la derecha del philo
    int         left_fork; //id del tenedor de la izquierda del philo
    int         is_dead;
    pthread_t   thread;
    struct s_data      *data;
}               t_philo;

typedef struct s_data
{
    int             n_philo;
    long long       t_start; //iniciar tiempo
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             n_times_eat;
    t_philo         *philo;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_t       dead;
}                   t_data;

/*MAIN*/
void	free_data(t_data *data);
int     check_death(t_data *data, int *i);
int     philo_dead(t_data *data);
void	*checker(void *arg);

/*ROUTINE*/
void	philo_write(t_data *data, int id, char *str);
int     left_handed(t_philo *philo);
int     right_handed(t_philo *philo);
void    *start_routine(void *arg);
int     philo_eat(t_philo *philo);

/*INIT*/
int     init(int argc, char **argv, t_data *data);
int     init_fork(t_data *data);
int     init_philo(t_data *data);
void    fill_philo(t_data *data, int i);

/*START*/
int     start_philo(t_data *data);
int     join_philo(t_data *data);
int     one_philo(t_philo *philo);

/*UTILS*/
int	        ft_atoi(const char *str);
int	        ft_isdigit(int c);
int         check_num(char **str);
long long   get_time(void);

//pthread_mutex_init INICIA
//pthread_mutex_destroy DESTRUYE
//pthread_mutex_lock BLOQ
//pthread_mutex_unlock LIBERA

//hacer un usleep propio porque se para MÍNIMO el numero que le pasas

//COMER -> DORMIR -> PENSAR

#endif
