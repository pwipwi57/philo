/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:25:40 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/07 20:44:57 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_common	*init_common(t_common *common, int ac, char **av)
{
	common->philo = NULL;
	common->philo_thread = NULL;
	common->mutex_fork = NULL;
	common->nb_philo = ft_atoi_pos(av[1]);
	if (init_mutex(common))
		return (perror("init_mutex"), NULL);
	common->philo = malloc(common->nb_philo * (sizeof(t_philo *)));
	if (!common->philo)
		return (free(common->mutex_fork), NULL); // destroy_mutex;
	memset(common->philo, 0, common->nb_philo);
	common->philo_thread = malloc(common->nb_philo * (sizeof(pthread_t *)));
	if (!common->philo_thread)
		return (free(common->mutex_fork), free(common->philo), NULL);
	memset(common->philo_thread, 0, common->nb_philo);
	common->time_begin = get_current_time();
	common->time_to_die = ft_atoi_pos(av[2]);
	common->time_to_eat = ft_atoi_pos(av[3]);
	common->time_to_sleep = ft_atoi_pos(av[4]);
	common->dead = 0;
	if (!init_common_2(common, ac, av))
		return (NULL);
	return (common);
}

t_common	*init_common_2(t_common *common, int ac, char **av)
{
	int			i;

	i = -1;
	while (++i < common->nb_philo)
	{
		(common->philo)[i] = init_philo(common, i);
		if (!(common->philo)[i])
			return (free(common->mutex_fork), free(common->philo_thread),
				free_philo(common->philo, common->nb_philo), NULL);
	}
	if (ac == 6)
		common->nb_meal = ft_atoi_pos(av[5]);
	else
		common->nb_meal = INT_MAX;
	return (common);
}

int	init_mutex(t_common *common)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&common->mutex_write, NULL))
		(perror("mutex init"), exit(1));
	if (pthread_mutex_init(&common->mutex_dead, NULL))
		(perror("mutex init"), destroy_mutex(common, 0));
	if (pthread_mutex_init(&common->mutex_count_meal, NULL))
		(perror("mutex init"), destroy_mutex(common, 1));
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
	return (0);
}

t_philo	*init_philo(t_common *co, int i)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (perror("malloc philo"), NULL);
	philo->n = i;
	if (i + 1 < co->nb_philo)
		philo->next = i + 1;
	else
		philo->next = 0;
	philo->last_eat = co->time_begin;
	return (philo);
}
