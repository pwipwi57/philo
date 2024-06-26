/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:11:03 by tlamarch          #+#    #+#             */
/*   Updated: 2024/06/25 02:40:31 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_pos(const char *nptr)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb);
}

int	calclen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*rev(int size, char *res)
{
	int	i;
	int	exc;

	if (!res || size < 1)
		return (NULL);
	i = 0;
	res[size--] = '\0';
	while (i <= (size))
	{
		exc = res[i];
		res[i] = res[size];
		res[size] = exc;
		i++;
		size--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		i;
	char	*res;

	nbr = n;
	i = 0;
	res = malloc(calclen(nbr) + 1);
	if (res == NULL)
		return (NULL);
	if (nbr == 0)
		res[i++] = '0';
	while (nbr > 0)
	{
		res[i++] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	res = rev(i, res);
	return (res);
}
