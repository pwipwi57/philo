/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:25:40 by tlamarch          #+#    #+#             */
/*   Updated: 2024/07/08 02:49:20 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_common *common)
{
	int	i;

	i = 0;
	common->mutex = malloc(common->nb_philo * (sizeof(pthread_mutex_t)));
	if (!common->mutex)
		return (1);
	pthread_mutex_init(&common->mutex_write, NULL);
	pthread_mutex_init(&common->mutex_dead, NULL); //  a proteger
	while (i < common->nb_philo)
	{
		pthread_mutex_init(&common->mutex[i], NULL); // A proteger
		i++;
	}
	return (0);
}

t_common	*init_common(t_common *common, int ac, char **av)
{
	int			i;

	i = -1;
	common->nb_philo = ft_atoi_pos(av[1]);
	if (init_mutex(common))
		return (perror("init_mutex"), NULL);
	common->philo = malloc(common->nb_philo * (sizeof(t_philo *)));
	if (!common->philo)
		return (free(common->mutex), NULL);
	memset(common->philo, 0, common->nb_philo);
	common->philo_thread = malloc(common->nb_philo * (sizeof(pthread_t *)));
	if (!common->philo_thread)
		return (free(common->mutex), free(common->philo), NULL);
	memset(common->philo_thread, 0, common->nb_philo);
	common->time_begin = get_current_time();
	common->time_to_die = ft_atoi_pos(av[2]);
	common->time_to_eat = ft_atoi_pos(av[3]);
	common->time_to_sleep = ft_atoi_pos(av[4]);
	common->dead = 0;
	while (++i < common->nb_philo)
	{
		((common->philo)[i]) = init_philo(common, i);
		if (!(common->philo)[i])
			return (free(common->mutex), free(common->philo_thread),
				free_philo(common->philo, common->nb_philo), NULL);
	}
	if (ac == 6)
		common->nb_meal = ft_atoi_pos(av[5]);
	else
		common->nb_meal = INT_MAX;
	return (common);
}

t_philo	*init_philo(t_common *co, int i)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	philo->n = i;
	if (i + 1 < co->nb_philo)
		philo->next = i + 1;
	else
		philo->next = 0;
	philo->nb_char = ft_itoa(i + 1);
	if (!philo->nb_char)
		return (perror("Itoa nb_char_philo"), NULL);
	philo->last_eat = co->time_begin;
	return (philo);
}
