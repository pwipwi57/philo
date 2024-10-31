/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_take_fork_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:35:14 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/31 15:40:49 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	take_fork(t_common *common)
{
	sem_wait(common->sem_eat);
	(sem_wait(common->sem_fork), sem_wait(common->sem_fork));
	if (test_die(common))
	{
		sem_post(common->sem_eat);
		sem_post(common->sem_fork);
		sem_post(common->sem_fork);
		return ;
	}
	write_message(common, "has taken a fork\n");
	write_message(common, "has taken a fork\n");
	sem_post(common->sem_eat);
	return ;
}
