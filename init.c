/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:25:40 by tlamarch          #+#    #+#             */
/*   Updated: 2024/06/25 02:55:16 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct t_common	init_common(int ac, char **av)
{
	t_common	common;

	common.nb = ft_atoi(*(av[1]));

}

struct t_philo	*init_philo(int ac, char **av)
{
	int				i;
	int				nb_philo;
	struct t_philo	*tab_philo;

	i = 0;
	nb_philo = ft_atoi(*(av[1]));
	common.nb_char = ft_itoa();
	tab_philo = malloc(nb_philo * (sizeof(t_philo)));
	if (!tab_philo)
		return (perror("Malloc tab_philo"), NULL);
}
