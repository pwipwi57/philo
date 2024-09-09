/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:47:28 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/08 23:23:37 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_common *common, int i)
{
	int	j;

	j = 0;
	if (i >= 0)
		pthread_mutex_destroy(&common->mutex_write);
	if (i >= 1)
		pthread_mutex_destroy(&common->mutex_dead);
	if (i >= 2)
		pthread_mutex_destroy(&common->mutex_count_meal);
	if (i >= 3)
	{
		while (j < common->nb_philo)
			pthread_mutex_destroy(&common->mutex_fork[j++]);
		free(common->mutex_fork);
	}
	if (i >= 4)
		while (--j >= 0)
			pthread_mutex_destroy(&common->philo[j].mutex_last_eat);
	if (i >= 5)
		return ;
	exit (1);
}

void	destroy_free_all(t_arg *arg, t_common *common)
{
	destroy_mutex(common, 5);
	pthread_mutex_destroy(&arg->mutex_i);
	free(common->philo);
	free(common->philo_thread);
}

