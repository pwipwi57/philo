/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:21 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/07 20:47:03 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	t_philo			**philo;
	size_t			time_begin;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_meal;
	int				dead;
}	t_common;

typedef struct s_arg
{
	t_common		*common;
	int				i;
	pthread_mutex_t	mutex_i;	
}	t_arg;

// action.c
int			test_die(t_common *co, t_philo *ph);
int			take_left_fork_first(t_common *co, t_philo *ph);
int			take_right_fork_first(t_common *co, t_philo *ph);
int			philo_sleep(t_common *common, t_philo *philo);
int			philo_eat(t_common *common, t_philo *philo);

// atoi_itoa.c
int			ft_atoi_pos(const char *nptr);

// create_philo.c
void		*routine(void *arg);
t_arg		*create_philo(t_common *common);

void		destroy_mutex(t_common *common, int i);

// init.c
int			init_mutex(t_common *common);
t_common	*init_common(t_common *common, int ac, char **av);
t_common	*init_common_2(t_common *common, int ac, char **av);
t_philo		*init_philo(t_common *co, int i);
t_philo		*init_philo2(t_common *co, t_philo *philo, int i);

// utils.c
void		unlock_mutex(t_common *co, t_philo *ph);
size_t		ft_strlen(const char *s);
size_t		get_current_time(void);
void		free_philo(t_philo **tab, int nb_philo);
int			my_usleep(unsigned int milliseconds, t_common *co, t_philo *ph);
void		destroy_free_all(t_arg *arg, t_common *common);

int			write_message(t_common *common, t_philo *philo, char *str);

#endif
