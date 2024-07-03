/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 02:27:46 by tlamarch          #+#    #+#             */
/*   Updated: 2024/06/27 14:25:46 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	char	mess[64];

	memset(mess, 0, 64);
	create_message(999999999, 2, "a manger une bite\n", mess);
	write(1, mess, ft_strlen(mess));

	return (0);
}
