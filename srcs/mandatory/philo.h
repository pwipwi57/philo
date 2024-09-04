/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:21 by tlamarch          #+#    #+#             */
/*   Updated: 2024/08/30 16:44:09 by tlamarch         ###   ########.fr       */
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
	char			*nb_char;
	size_t			last_eat;
}	t_philo;

typedef struct s_common
{
	int				nb_philo;
	pthread_t		*philo_thread;
	pthread_mutex_t	*mutex;	
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_write;
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
int			calclen(int n);
char		*rev(int size, char *res);
char		*ft_itoa(int n);

// create_philo.c
void		*routine(void *arg);
t_arg		*create_philo(t_common *common);

// init.c
int			init_mutex(t_common *common);
t_common	*init_common(t_common *common, int ac, char **av);
t_philo		*init_philo(t_common *co, int i);

// utils.c
void		unlock_mutex(t_common *co, t_philo *ph);
size_t		ft_strlen(const char *s);
size_t		get_current_time(void);
void		free_philo(t_philo **tab, int nb_philo);
void		destroy_free_all(t_arg *arg, t_common *common);

// write_mess.c
void		ft_strcat_philo(char *nb, char *time, char *str, char *new);
int			create_message(size_t time, char *nb, char *str, char *mess);
int			write_message(t_common *common, t_philo *philo, char *str);

#endif