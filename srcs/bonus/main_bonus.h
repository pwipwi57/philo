/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:10:25 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/31 02:43:13 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:21 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/17 01:39:17 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <limits.h>

// typedef struct s_philo
// {
// 	int				n;
// 	int				next;
// 	sem_t			*sem_last_eat;
// 	size_t			last_eat;
// }	t_philo;

typedef struct s_common
{
	int				nb_philo;
	int				nb;
	sem_t			*sem_dead;
	sem_t			*sem_end;
	sem_t			*sem_eat;
	sem_t			*sem_fork;
	sem_t			*sem_meal;
	sem_t			*sem_write;
	sem_t			*sem_wr_rd;
	pid_t			*philo;
	size_t			time_begin;
	size_t			last_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_think;
	long			nb_meal;
	long			meal_eaten;
	int				end;
	int				die;
}	t_common;

// typedef struct s_arg
// {
// 	t_common		*common;
// 	int				i;
// }	t_arg;

// free.c 1/5
void	close_sem_init_err(t_common *common, char *str, int mod);
void		close_all_sem_exit(t_common *common, int i);
void		wait_all_and_exit(t_common *common, int exit_code, int mod);

// init.c 5/5
t_common	*init_common(t_common *common, int ac, char **av);

// routine.c 5/5
void		routine(t_common *common);

// test_arg.c 5/5
long		ft_atoi(const char *nptr);
int			test_arg(int ac, char **av);

// utils.c 5/5
int			test_die(t_common *co);
size_t		ft_strlen(const char *s);
size_t		get_time(void);
int			write_message(t_common *common, char *str);
int			my_usleep(unsigned int milliseconds, t_common *co);

#endif
