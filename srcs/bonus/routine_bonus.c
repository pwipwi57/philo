/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:07 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/30 11:12:20 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	take_fork(t_common *common)
{
	sem_wait(common->sem_eat);
	(sem_wait(common->sem_fork), sem_wait(common->sem_fork));
	if (test_die(common))
	{
		(sem_post(common->sem_eat), sem_post(common->sem_fork), sem_post(common->sem_fork));
		return;
	}
	write_message(common, "has taken a fork\n");
	write_message(common, "has taken a fork\n");
	sem_post(common->sem_eat);
	return ;
}

static void	philo_sleep(t_common *common)
{
	if (test_die(common))
		return ;
	write_message(common, "is sleeping\n");
	my_usleep(common->time_to_sleep, common);
	if (test_die(common))
		return ;
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
	sem_wait(common->sem_write_read);
	common->end = 1;
	sem_post(common->sem_write_read);
	return (0);
}

static size_t	create_thread_end(t_common *common)
{
	pthread_t thread;

	if (pthread_create(&thread,
			NULL, thread_monitoring, (void *)common))
	{
		perror(__func__);
		close_all_sem_exit(common, 3);
	}
	return (thread);
}

static int	philo_eat(t_common *common)
{
	take_fork(common);
	if (test_die(common))
		return (sem_post(common->sem_fork), sem_post(common->sem_fork), 1);
	common->last_eat = (get_time());
	if (!common->last_eat)
		close_all_sem_exit(common, 1);
	write_message(common, "is eating\n");
	my_usleep(common->time_to_eat, common);
	sem_post(common->sem_fork);
	sem_post(common->sem_fork);
	return (0);
}

void	routine(t_common *common)
{
	pthread_t thread;

	if (common->nb % 2)
		my_usleep(1, common);
	thread = create_thread_end(common);
	sem_wait(common->sem_write_read);
	while (!common->end)
	{
		sem_post(common->sem_write_read);
		philo_eat(common);
		common->meal_eaten = (common->meal_eaten) + 1;
		if (common->meal_eaten == common->nb_meal)
			sem_post(common->sem_meal);
		philo_sleep(common);
		usleep(10);
		sem_wait(common->sem_write_read);
	}
	sem_post(common->sem_write_read);
	pthread_join(thread, NULL);
	if (!common->die)
		close_all_sem_exit(common, 0);
	close_all_sem_exit(common, 5);
}
