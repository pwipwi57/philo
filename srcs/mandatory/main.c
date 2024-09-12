/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:05 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/12 23:48:06 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	test_end(t_common *common)
{
	int	i;
	
	i = 1;
	pthread_mutex_lock(&common->mutex_end);
	if (common->end == 1)
		i = 0;
	pthread_mutex_unlock(&common->mutex_end);
	return (i);
}

static t_arg	*create_philo(t_arg *arg, t_common *common)
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

static void	monitoring(t_common *common)
{
	int	i;

	while (1 && test_end(common))
	{
		i = -1;
		while (++i < common->nb_philo)
		{
			pthread_mutex_lock(&common->philo[i].mutex_last_eat);
			if (get_time() - common->philo[i].last_eat >= common->time_to_die)
			{
				pthread_mutex_unlock(&common->philo[i].mutex_last_eat);
				pthread_mutex_lock(&common->mutex_end);
				common->end = 1;
				pthread_mutex_unlock(&common->mutex_end);
				usleep(2000);
				write_message(common, &common->philo[i], "died\n");
				return ;
			}
			pthread_mutex_unlock(&common->philo[i].mutex_last_eat);
		}
		usleep(1000);
	}
}

static void	join_pthread(t_common *common)
{
	int	i;

	i = -1;
	while (++i < common->nb_philo)
		if ((common->philo_thread)[i])
			if (pthread_join((common->philo_thread)[i], NULL))
				perror("Pthread join");
	return ;
}

int	main(int ac, char **av)
{
	t_common		common;
	t_arg			arg;

	if (test_arg(ac, av))
		return (1);
	if (!init_common(&common, ac, av))
		return (printf("Erreur initialisation\n"), 1);
	if (!create_philo(&arg, &common))
		return (1);
	monitoring(&common);
	join_pthread(&common);
	destroy_free_all(&arg, &common);
	return (0);
}
