/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:05 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/11 21:50:39 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_common *common)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < common->nb_philo)
		{
			pthread_mutex_lock(&common->philo[i].mutex_last_eat);
			if (get_time() - common->philo[i].last_eat >= common->time_to_die)
			{
				pthread_mutex_unlock(&common->philo[i].mutex_last_eat);
				pthread_mutex_lock(&common->mutex_dead);
				common->dead = 1;
				pthread_mutex_unlock(&common->mutex_dead);
				write_message(common, &common->philo[i], "died\n");
				return ;
			}
			pthread_mutex_unlock(&common->philo[i].mutex_last_eat);
		}
		usleep(1000);
	}
}

static void	routine_one_philo(char *av)
{
	printf("0 1 has taken a fork\n");
	usleep(ft_atoi_pos(av));
	printf("%d 1 died\n", ft_atoi_pos(av));
	exit(0);
}

static void	join_pthread(t_common *common)
{
	int	i;

	i = -1;
	while (++i < common->nb_philo)
	{
		if ((common->philo_thread)[i])
		{
			if (pthread_join((common->philo_thread)[i], NULL))
			{
				perror("Pthread join");
				return ;
			}
		}
	}
	return ;
}

int	main(int ac, char **av)
{
	t_common		common;
	t_arg			arg;

	if (test_arg(ac, av))
		return (1);
	if (ft_atoi_pos(av[1]) == 1)
		routine_one_philo(av[2]);
	if (!init_common(&common, ac, av))
		return (printf("Erreur initialisation\n"), 1);
	if (!create_philo(&arg, &common))
		return (1);
	monitoring(&common);
	join_pthread(&common);
	destroy_free_all(&arg, &common);
	return (0);
}
