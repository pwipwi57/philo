/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:37:25 by tlamarch          #+#    #+#             */
/*   Updated: 2024/08/29 19:28:22 by tlamarch         ###   ########.fr       */
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
	pthread_mutex_lock(&arg->mutex_i); //  a proteger
	nb_philo = arg->i;
	((t_arg *)args)->i++;
	pthread_mutex_unlock(&arg->mutex_i); //  a proteger
	((t_arg *)args)->common->philo[nb_philo]->n = nb_philo;
	// while (!test_die(arg->common, arg->common->philo[nb_philo])
	// 	&& i + 1 <= arg->common->nb_meal)
	if (nb_philo % 2)
		(usleep(5000));
	while (i + 1 <= arg->common->nb_meal)
	{
		if (philo_eat(arg->common, arg->common->philo[nb_philo]))
			return (NULL);
		if (philo_sleep(arg->common, arg->common->philo[nb_philo]))
			return (NULL);
		i++;
		usleep(10);
	}
	return ((void *)1);
}

t_arg	*create_philo(t_common *common)
{
	t_arg	*arg;
	int		i;

	i = 0;
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->common = common;
	arg->i = 0;
	arg->common->time_begin = get_current_time();
	pthread_mutex_init(&arg->mutex_i, NULL); //  a proteger
	while (i < common->nb_philo)
	{
		if (pthread_create(&(common->philo_thread[i]),
				NULL, routine, (void *)arg))
			return (NULL);
		i++;
	}
	return (arg);
}
