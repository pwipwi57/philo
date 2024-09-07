/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:47:28 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/07 20:45:42 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_common *common, int i)
{
	if (i >= 0)
		pthread_mutex_destroy(&common->mutex_write);
	if (i >= 1)
		pthread_mutex_destroy(&common->mutex_dead);
	if (i >= 2)
		pthread_mutex_destroy(&common->mutex_count_meal);
	exit (1);
}

void	destroy_free_all(t_arg *arg, t_common *common)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&common->mutex_dead);
	pthread_mutex_destroy(&arg->mutex_i);
	pthread_mutex_destroy(&common->mutex_write);
	while (i < common->nb_philo)
		pthread_mutex_destroy(&common->mutex_fork[i++]);
	free_philo(common->philo, common->nb_philo);
	free(common->mutex_fork);
	free(common->philo_thread);
	free(arg);
}

void	free_philo(t_philo **tab, int nb_philo)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (i < nb_philo && tab[i])
		free(tab[i++]);
	free(tab);
	return ;
}

