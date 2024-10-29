/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:47:28 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/29 15:33:26 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	close_all_sem_exit(t_common *common, int i)
{
	sem_wait(common->sem_write);
	sem_post(common->sem_dead);
	sem_close(common->sem_write);
	sem_close(common->sem_dead);
	sem_close(common->sem_eat);
	sem_close(common->sem_meal);
	sem_close(common->sem_fork);
	exit(i);
}

void	wait_all_and_exit(t_common *common, int exit_code)
{
	int	i;
	
	i = -1;
	while (++i < common->nb_philo)
	{
		if (common->philo[i] < 1)
			continue ;
		waitpid(common->philo[i], NULL, 0);
	}
	free(common->philo);
	common->philo = NULL;
	close_all_sem_exit(common, exit_code);
	return ;
}
