/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:05 by tlamarch          #+#    #+#             */
/*   Updated: 2024/07/04 12:57:24 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{
	t_common		*common;
	int				i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("Mauvais nombre d'arguments. ac = %d", ac), 1);
	common = init_common(ac, av);
	if (!common)
		return (1);
	while (i < common->nb_philo)
		create_philo(common, i);
}
