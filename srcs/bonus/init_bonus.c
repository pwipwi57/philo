/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:25:40 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/29 15:39:58 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	init_sem(t_common *common)
{
	common->sem_write = sem_open("sem_write", O_CREAT, 0777, 1);
	if (common->sem_write == SEM_FAILED)
		(perror("sem_write open"), exit(1));
	sem_unlink("sem_write");
	common->sem_end = sem_open("sem_end", O_CREAT, 0777, 0);
	if (common->sem_end == SEM_FAILED)
		(perror("sem_end open :"), sem_close(common->sem_write), exit(1));
	sem_unlink("sem_end");
	common->sem_meal = sem_open("sem_meal", O_CREAT, 0777, 0);
	if (common->sem_meal == SEM_FAILED)
		(perror("sem_meal open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), exit(1));
	sem_unlink("sem_meal");
	common->sem_eat = sem_open("sem_eat", O_CREAT, 0777, 1);
	if (common->sem_eat == SEM_FAILED)
		(perror("sem_eat open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), sem_close(common->sem_meal), exit(1));
	sem_unlink("sem_eat");
	common->sem_fork = sem_open("sem_fork", O_CREAT, 0777, common->nb_philo);
	if (common->sem_fork == SEM_FAILED)
		(perror("sem_fork open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), sem_close(common->sem_eat),
			sem_close(common->sem_meal), exit(1));
	sem_unlink("sem_fork");
	common->sem_dead = sem_open("sem_dead", O_CREAT, 0777, 0);
	if (common->sem_dead == SEM_FAILED)
		(perror("sem_dead open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), sem_close(common->sem_eat),
			sem_close(common->sem_meal), sem_close(common->sem_meal), exit(1));
	sem_unlink("sem_dead");
	return ;
}

static void	init_philo(t_common *common)
{
	common->philo = malloc(common->nb_philo * (sizeof(pid_t)));
	if (!common->philo)
		(perror("malloc Philo\n"), close_all_sem_exit(common, 1));
	memset(common->philo, 0, common->nb_philo * (sizeof(pid_t)));
	return ;
}

static void	init_const(t_common *common, int ac, char **av)
{
	common->nb_philo = ft_atoi(av[1]);
	common->nb = -1;
	common->time_begin = get_time();
	common->last_eat = common->time_begin;
	common->time_to_die = ft_atoi(av[2]);
	common->time_to_eat = ft_atoi(av[3]);
	common->time_to_sleep = ft_atoi(av[4]);
	common->meal_eaten = 0;
	common->end = 0;
	if (common->nb_philo % 2 && common->time_to_sleep <= common->time_to_eat)
		common->time_to_think = common->time_to_eat - common->time_to_sleep;
	else
		common->time_to_think = 0;
	if (ac == 6)
		common->nb_meal = ft_atoi(av[5]);
	else
		common->nb_meal = INT_MAX;
	return ;
}

t_common	*init_common(t_common *common, int ac, char **av)
{
	init_const(common, ac, av);
	init_sem(common);
	init_philo(common);
	return (common);
}
