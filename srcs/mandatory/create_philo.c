/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:37:25 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/11 20:59:33 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	int		i;
	int		nb_philo;
	t_arg	*arg;

	i = 0;
	arg = (t_arg *)args;
	pthread_mutex_lock(&arg->mutex_i);
	nb_philo = arg->i;
	arg->i++;
	pthread_mutex_unlock(&arg->mutex_i);
	arg->common->philo[nb_philo].n = nb_philo;
	if (nb_philo % 2)
		my_usleep(1, arg->common, &arg->common->philo[nb_philo]);
	while (i++ < arg->common->nb_meal)
	{
		if (philo_eat(arg->common, &arg->common->philo[nb_philo]))
			return (NULL);
		if (philo_sleep(arg->common, &arg->common->philo[nb_philo]))
			return (NULL);
		usleep(10);
	}
	return ((void *)1);
}

t_arg	*create_philo(t_arg *arg, t_common *common)
{
	int		i;

	i = 0;
	arg->common = common;
	arg->i = 0;
	common->time_begin = get_time();
	if (pthread_mutex_init(&arg->mutex_i, NULL))
		return (perror("mutex init create philo"), NULL);
	while (i < common->nb_philo)
		if (pthread_create(&(common->philo_thread[i++]),
				NULL, routine, (void *)arg))
			return (NULL);
	return (arg);
}
