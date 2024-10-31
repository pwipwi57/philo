/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:25:40 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/31 18:19:57 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	init_fork(t_common *common)
{
	int	i;

	i = -1;
	common->mutex_fork = malloc(common->nb_philo * (sizeof(pthread_mutex_t)));
	if (!common->mutex_fork)
		(perror("malloc fork"), destroy_mutex(common, 2));
	while (++i < common->nb_philo)
	{
		if (pthread_mutex_init(&common->mutex_fork[i], NULL))
		{
			perror("mutex init");
			while (i >= 0)
				pthread_mutex_destroy(&common->mutex_fork[i--]);
			free(common->mutex_fork);
			destroy_mutex(common, 2);
		}
	}
	return ;
}

static void	init_mutex(t_common *common)
{
	if (pthread_mutex_init(&common->mutex_write, NULL))
		(perror("mutex init"), exit(1));
	if (pthread_mutex_init(&common->mutex_end, NULL))
		(perror("mutex init"), destroy_mutex(common, 0));
	if (pthread_mutex_init(&common->mutex_meal_counter, NULL))
		(perror("mutex init"), destroy_mutex(common, 1));
	init_fork(common);
	return ;
}

static void	init_philo(t_common *common)
{
	int		i;

	i = -1;
	common->philo = malloc(common->nb_philo * (sizeof(t_philo)));
	if (!common->philo)
		(perror("Philo\n"), destroy_mutex(common, 3));
	while (++i < common->nb_philo)
	{
		common->philo[i].n = i;
		if (i + 1 < common->nb_philo)
			common->philo[i].next = i + 1;
		else
			common->philo[i].next = 0;
		common->philo[i].last_eat = common->time_begin;
		if (pthread_mutex_init(&common->philo[i].mutex_last_eat, NULL))
			break ;
	}
	if (i < common->nb_philo)
	{
		while (i >= 0)
			pthread_mutex_destroy(&common->philo[i--].mutex_last_eat);
		free(common->philo);
		destroy_mutex(common, 3);
	}
	return ;
}

static void	init_const(t_common *common, int ac, char **av)
{
	common->nb_philo = ft_atoi(av[1]);
	common->time_begin = get_time();
	common->time_to_die = ft_atoi(av[2]);
	common->time_to_eat = ft_atoi(av[3]);
	common->time_to_sleep = ft_atoi(av[4]);
	common->meal_counter = 0;
	common->end = 0;
	if (common->nb_philo % 2 && common->time_to_sleep <= common->time_to_eat)
		common->time_think = (common->time_to_eat - common->time_to_sleep) * 2;
	else if (common->time_to_sleep <= common->time_to_eat)
		common->time_think = (common->time_to_eat - common->time_to_sleep) + 2;
	else
		common->time_think = 0;
	if (ac == 6)
		common->nb_meal = ft_atoi(av[5]);
	else
		common->nb_meal = (long)INT_MAX + 1;
	return ;
}

t_common	*init_common(t_common *common, int ac, char **av)
{
	init_const(common, ac, av);
	init_mutex(common);
	init_philo(common);
	common->philo_thread = malloc(common->nb_philo * (sizeof(pthread_t *)));
	if (!common->philo_thread)
		return (free(common->mutex_fork), free(common->philo),
			destroy_mutex(common, 4), NULL);
	memset(common->philo_thread, 0, common->nb_philo);
	return (common);
}
