/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:47:28 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/30 19:35:09 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	close_all_sem_exit(t_common *common, int i)
{
	// sem_post(common->sem_dead);
	sem_close(common->sem_write);
	sem_close(common->sem_dead);
	sem_close(common->sem_eat);
	sem_close(common->sem_meal);
	sem_close(common->sem_fork);
	sem_close(common->sem_end);
	sem_close(common->sem_wr_rd);
	sem_unlink("sem_write");
	sem_unlink("sem_dead");
	sem_unlink("sem_eat");
	sem_unlink("sem_meal");
	sem_unlink("sem_fork");
	sem_unlink("sem_end");
	sem_unlink("sem_wr_rd");
	exit(i);
}

void	wait_all_and_exit(t_common *common, int exit_code, int mod)
{
	int	i;
	int	retu;

	i = -1;
	retu = 0;
	while (++i < common->nb_philo)
	{
		if (common->philo[i] < 1)
			continue ;
		waitpid(common->philo[i], &retu, 0);
		if (retu == 1280 && !mod)
		{
			common->nb = i;
			write_message(common, "died\n");
			wait_all_and_exit(common, exit_code, 1);
		}
	}
	free(common->philo);
	common->philo = NULL;
	close_all_sem_exit(common, exit_code);
	return ;
}
