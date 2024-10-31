/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:47:28 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/31 02:51:13 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	close_sem_init_err(t_common *common, char *str, int mod)
{
	perror(str);
	if (mod > 0)
		(sem_close(common->sem_write), sem_unlink("sem_write"));
	if (mod > 1)
		(sem_close(common->sem_end), sem_unlink("sem_end"));
	if (mod > 2)
		(sem_close(common->sem_eat), sem_unlink("sem_eat"));
	if (mod > 3)
		(sem_close(common->sem_meal), sem_unlink("sem_meal"));
	if (mod > 4)
		(sem_close(common->sem_fork), sem_unlink("sem_fork"));
	if (mod > 5)
		(sem_close(common->sem_dead), sem_unlink("sem_dead"));
	exit(1);
}

void	close_all_sem_exit(t_common *common, int i)
{
	sem_post(common->sem_dead);
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
		if (!mod && WIFEXITED(retu) && WEXITSTATUS(retu) == 5)
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
