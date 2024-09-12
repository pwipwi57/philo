/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 21:50:53 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/12 21:34:51 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	ft_atoi(const char *nptr)
{
	int				i;
	long			nbl;

	i = 0;
	nbl = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+')
		i++;
	while ('0' <= nptr[i] && nptr[i] <= '9')
		nbl = nbl * 10 + (nptr[i++] - 48);
	return (nbl);
}

static int	test_negativ(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if ((av[i++][0]) == '-')
		{
			printf("Nombres negatifs non autorises.\n");
			return (1);
		}
	}
	return (0);
}

static int	test_overflow(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strlen(av[i]) > 12 || ft_atoi(av[i++]) > INT_MAX)
		{
			printf("T'abuses pas un peu la ?\n");
			return (1);
		}
	}
	return (0);
}

static void	routine_one_philo(char *av)
{
	printf("0 1 has taken a fork\n");
	usleep(ft_atoi(av));
	printf("%ld 1 died\n", ft_atoi(av));
	exit(0);
}

int	test_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Mauvais nombre d'arguments. ac = %d\n", ac), 1);
	if (test_negativ(ac, av))
		return (1);
	if (test_overflow(ac, av))
		return (1);
	if (av[1] == 0)
		return (1);
	if (ac == 6 && av[5] == 0)
		return (1);
	if (ft_atoi(av[1]) == 1)
		routine_one_philo(av[2]);
	return (0);
}