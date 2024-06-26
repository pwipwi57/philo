/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:07 by tlamarch          #+#    #+#             */
/*   Updated: 2024/06/25 02:37:15 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_sleep(t_common *common, t_philo philo)
{
	write_message(common, philo, " is sleeping\n");
	if (usleep(common.time_to_sleep * 1000))
		return (perror("Usleep sleep"), 1);
	return (0);
}

int	philo_eat(t_common *common, t_philo *philo)
{
	if (philo->n % 2)
		take_left_fork_first(common, philo);
	else
		take_right_fork_first(common, philo);
	write_message(common, philo, " is eating\n");
	if (usleep(common.time_to_eat * 1000))
		return (perror("Usleep eat"), 1);
	return (0);
}


