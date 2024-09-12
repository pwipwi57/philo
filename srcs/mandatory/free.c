/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:47:28 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/12 22:27:54 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	unlock_mutex(t_common *co, t_philo *philo)
{
	if (&co->mutex_fork[philo->n] < &co->mutex_fork[philo->next])
	{
		pthread_mutex_unlock(&co->mutex_fork[philo->n]);
		pthread_mutex_unlock(&co->mutex_fork[philo->next]);
	}
	else
	{
		pthread_mutex_unlock(&co->mutex_fork[philo->next]);
		pthread_mutex_unlock(&co->mutex_fork[philo->n]);
	}
}

void	destroy_mutex(t_common *common, int i)
{
	int	j;

	j = 0;
	if (i >= 0)
		pthread_mutex_destroy(&common->mutex_write);
	if (i >= 1)
		pthread_mutex_destroy(&common->mutex_end);
	if (i >= 2)
		pthread_mutex_destroy(&common->mutex_meal_counter);
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

