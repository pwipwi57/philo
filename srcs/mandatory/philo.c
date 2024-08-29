/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:05 by tlamarch          #+#    #+#             */
/*   Updated: 2024/08/29 19:55:20 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("Mauvais nombre d'arguments. ac = %d", ac), 1);
	while (i < ac)
	{
		if (ft_atoi_pos(av[i++]) < 0)
			return (1);
	}
	return (0);
}

void	destroy_free_all(t_arg *arg, t_common *common)
{
	int	i;

	i = 0;
	while (i < common->nb_philo)
		pthread_mutex_destroy(&common->mutex[i++]);
	free(common->mutex);
	pthread_mutex_destroy(&common->mutex_dead);
	pthread_mutex_destroy(&arg->mutex_i);
	pthread_mutex_destroy(&common->mutex_write);
	free_philo(common->philo, common->nb_philo);
	free(common->philo_thread);
	free(arg);
}

int	main(int ac, char **av)
{
	t_common		*common;
	t_common		sub_common;
	t_arg			*arg;
	int				i;

	if (test_arg(ac, av))
		return (1);
	common = &sub_common;
	if (ft_atoi_pos(av[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(ft_atoi_pos(av[2]) * 1000);
		printf("%d 1 died\n", ft_atoi_pos(av[2]));
		return (0);
	}
	common = init_common(common, ac, av);
	if (!common)
		return (1);
	arg = create_philo(common);
	if (!arg)
		return (1);
	i = 0;
	while (i < common->nb_philo)
	{
		if ((common->philo_thread)[i])
			pthread_join((common->philo_thread)[i], NULL);
		i++;
	}
	destroy_free_all(arg, common);
	return (0);
}
