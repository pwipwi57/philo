/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:11:03 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/11 21:44:54 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi_pos(const char *nptr)
{
	int				i;
	int				sign;
	long			nbl;
	unsigned long	unbl;

	i = 0;
	sign = 1;
	unbl = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -sign;
	while ('0' <= nptr[i] && nptr[i] <= '9')
		unbl = unbl * 10 + (nptr[i++] - 48);
	nbl = unbl * sign;
	return (nbl);
}
