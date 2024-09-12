/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:21 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/12 21:42:07 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				n;
	int				next;
	pthread_mutex_t	mutex_last_eat;
	size_t			last_eat;
}	t_philo;

typedef struct s_common
{
	int				nb_philo;
	pthread_t		*philo_thread;
	pthread_mutex_t	*mutex_fork;	
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_count_meal;
	t_philo			*philo;
	size_t			time_begin;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_think;
	int				nb_meal;
	int				dead;
}	t_common;

typedef struct s_arg
{
	t_common		*common;
	int				i;
	pthread_mutex_t	mutex_i;	
}	t_arg;

// free.c
void		unlock_mutex(t_common *co, t_philo *philo);
void		destroy_mutex(t_common *common, int i);
void		destroy_free_all(t_arg *arg, t_common *common);

// init.c
t_common	*init_common(t_common *common, int ac, char **av);

// routine.c
void		*routine(void *args);

// test_arg.c
long		ft_atoi(const char *nptr);
int			test_arg(int ac, char **av);

// utils.c
int			test_die(t_common *co, t_philo *ph);
size_t		ft_strlen(const char *s);
size_t		get_time(void);
int			write_message(t_common *common, t_philo *philo, char *str);
int			my_usleep(unsigned int milliseconds, t_common *co, t_philo *ph);

#endif
