/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:50:53 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/11 21:58:04 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	test_negativ(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi_pos(av[i++]) < 0)
		{
			printf("Nombre negatif non autorise.\n");
			return (1);
		}
	}
	return (0);
}

static int	test_overflow(int ac, char **av)
{
	int	i;

	i = 1;
	if (ft_strlen(av[i]) > 12 || (av[i++]) > INT_MAX)	{
		printf("Nombre negatif non autorise.\n");
		return (1);
	}
	return (0);
}

int	test_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Mauvais nombre d'arguments. ac = %d\n", ac), 1);
	if (test_overflow(ac, av));
		return (1);
	if (test_negativ(ac, av))
		return (1);
	if (av[1] == 0)
		return (1);
	if (ac == 6 && av[5] == 0)
		return (1);
	return (0);
}