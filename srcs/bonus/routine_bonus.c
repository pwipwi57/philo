/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:07 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/29 15:40:24 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	take_fork(t_common *common)
{
	sem_wait(common->sem_eat);
	(sem_wait(common->sem_fork), sem_wait(common->sem_fork));
	test_die(common);
	write_message(common, "has taken a fork\n");
	write_message(common, "has taken a fork\n");
	sem_post(common->sem_eat);
	return ;
}

static void	philo_sleep(t_common *common)
{
	test_die(common);
	write_message(common, "is sleeping\n");
	my_usleep(common->time_to_sleep, common);
	test_die(common);
	write_message(common, "is thinking\n");
	if (common->nb_philo % 2)
		my_usleep(common->time_to_think, common);
	return ;
}

static void	*thread_monitoring(void *arg)
{
	t_common	*common;

	common = (t_common *)arg;
	sem_wait(common->sem_end);
	close_all_sem_exit(common, 0);
	exit(0);
	return (0);
}

static int	create_thread_end(t_common *common)
{
	pthread_t thread;

	if (pthread_create(&thread,
			NULL, thread_monitoring, (void *)common))
		close_all_sem_exit(common, 1);
	return (0);
}

static int	philo_eat(t_common *common)
{
	take_fork(common);
	test_die(common);
	common->last_eat = (get_time());
	if (!common->last_eat)
		close_all_sem_exit(common, 1);
	write_message(common, "is eating\n");
	my_usleep(common->time_to_eat, common);
	sem_post(common->sem_fork);
	sem_post(common->sem_fork);
	return (0);
}

void	routine(t_common *common) // i num philo
{
	if (common->nb % 2)
		my_usleep(1, common);
	create_thread_end(common);
	while (1)
	{
		philo_eat(common);
		common->meal_eaten = (common->meal_eaten) + 1;
		if (common->meal_eaten == common->nb_meal)
			sem_post(common->sem_meal);
		philo_sleep(common);
		usleep(10);
	}
	return ;
}
