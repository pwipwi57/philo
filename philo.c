/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:05 by tlamarch          #+#    #+#             */
/*   Updated: 2024/06/30 21:54:35 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_common		common;

	if (ac < 5 || ac > 6)
		return (printf("Mauvais nombre d'arguments. ac = %d", ac), 1);
	common = init_common(ac, av);
	if (!common)
		return (1);
	tab_mutex = malloc(common.nb * (sizeof(pthread_mutex_t)));
	
}