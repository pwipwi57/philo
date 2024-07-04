/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:25:40 by tlamarch          #+#    #+#             */
/*   Updated: 2024/07/03 18:04:08 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_common	*init_common(int ac, char **av)
{
	t_common	common;
	int			i;

	i = -1;
	common.nb_philo = ft_atoi(*(av[1]));
	common.mutex = malloc(common.nb_philo * (sizeof(pthread_mutex_t)));
	if (!common.mutex)
		return (NULL);
	common.philo = malloc(common.nb_philo * (sizeof(t_philo *)));
	if (!common.philo)
		return (free(common.mutex), 1);
	common.time_begin = get_current_time();
	common.time_to_die = ft_atoi(*(av[2]));
	common.time_to_eat = ft_atoi(*(av[3]));
	common.time_to_sleep = ft_atoi(*(av[4]));
	common.dead = 0;
	while (++i < common.nb_philo)
	{
		((common.philo)[i]) = init_philo(ac, av, &common, i);
		if (!(common.philo)[i])
			return (free(common.mutex), ftab((void *)common.philo), NULL);
	}
	return (&common);
}

t_philo	*init_philo(int ac, char **av, t_common *co, int i)
{
	int				i;
	t_philo			*philo;

	i = 0;
	philo = malloc(sizeof(t_philo));
	philo->n = i;
	if (i + 1 < co->nb_philo)
		philo->next = i + 1;
	else
		philo->next = 0;
	philo->nb_char = ft_itoa(i + 1);
	if (!philo->nb_char)
		return (perror("Itoa nb_char_philo"), NULL);
	philo->last_eat = get_current_time() - co->time_begin;
	return (philo);
}
