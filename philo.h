/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:21 by tlamarch          #+#    #+#             */
/*   Updated: 2024/07/03 03:53:41 by tlamarch         ###   ########.fr       */
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

typedef struct s_philo
{
	int				n;
	int				next;
	char			*nb_char;
	time_t			last_eat;
}	t_philo;

typedef struct s_common
{
	int				nb_philo;
	pthread_mutex_t	*mutex;	
	pthread_mutex_t	mutex_dead;	
	t_philo			*philo;
	size_t			time_begin;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
}	t_common;

// action.c
int			philo_sleep(t_common *common, t_philo philo);
int			philo_eat(t_common *common, t_philo *philo);

// atoi_itoa.c
int			ft_atoi_pos(const char *nptr);
int			calclen(int n);
char		*rev(int size, char *res);
char		*ft_itoa(int n);

// init.c
t_common	init_common(int ac, char **av);
t_philo		*init_philo(int ac, char **av);

// philo.c

// utils.c
size_t		ft_strlen(const char *s);
size_t		get_current_time(void);

// write_message_old.c
// char		*ft_strcat_philo(char *nb, char *time, char *str);
// char		*create_message(size_t time, int n, char *str);
// int		write_message(t_common *common, t_philo philo, char *str);

// write_mess.c
void		ft_strcat_philo(char *nb, char *time, char *str, char *mess);
void		create_message(size_t time, int n, char *str, char *mess);
int			write_message(t_common *common, t_philo philo, char *str);

#endif