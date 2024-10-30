/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:05 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/30 19:34:07 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	*thread_dead(void *arg)
{
	int			i;
	t_common	*common;

	i = 0;
	common = (t_common *)arg;
	sem_wait(common->sem_dead);
	while (i++ < common->nb_philo)
		(sem_post(common->sem_meal));
	while (i++ < common->nb_philo)
		(sem_post(common->sem_end));
	return (0);
}

static void	*thread_meal(void *arg)
{
	int			i;
	t_common	*common;

	i = 0;
	common = (t_common *)arg;
	while (i++ < common->nb_philo)
		sem_wait(common->sem_meal);
	i = 0;
	while (i++ < common->nb_philo)
		sem_post(common->sem_end);
	sem_post(common->sem_dead);
	return (0);
}

static void	pthread_monitoring(t_common *common)
{
	pthread_t	pthread_dead;
	pthread_t	pthread_meal;

	if (pthread_create(&pthread_dead,
			NULL, thread_dead, (void *)common))
		wait_all_and_exit(common, 1, 0);
	if (pthread_create(&pthread_meal,
			NULL, thread_meal, (void *)common))
		wait_all_and_exit(common, 1, 0);
	// pthread_join(pthread_dead, NULL);
	// pthread_join(pthread_meal, NULL);
	return ;
}

static void	init_sem_child(t_common *common)
{
	sem_close(common->sem_write);
	sem_close(common->sem_dead);
	sem_close(common->sem_eat);
	sem_close(common->sem_meal);
	sem_close(common->sem_fork);
	sem_close(common->sem_end);
	sem_close(common->sem_wr_rd);
	common->sem_write = sem_open("sem_write", 1);
	if (common->sem_write == SEM_FAILED)
		(perror("sem_write open"), exit(1));
	common->sem_end = sem_open("sem_end", 0);
	if (common->sem_end == SEM_FAILED)
		(perror("sem_end open :"), sem_close(common->sem_write), exit(1));
	common->sem_meal = sem_open("sem_meal", 0);
	if (common->sem_meal == SEM_FAILED)
		(perror("sem_meal open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), exit(1));
	common->sem_eat = sem_open("sem_eat", 1);
	if (common->sem_eat == SEM_FAILED)
		(perror("sem_eat open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), sem_close(common->sem_meal), exit(1));
	common->sem_fork = sem_open("sem_fork", (common->nb_philo));
	if (common->sem_fork == SEM_FAILED)
		(perror("sem_fork open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), sem_close(common->sem_eat),
			sem_close(common->sem_meal), exit(1));
	common->sem_dead = sem_open("sem_dead", 0);
	if (common->sem_dead == SEM_FAILED)
		(perror("sem_dead open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), sem_close(common->sem_eat),
			sem_close(common->sem_meal), sem_close(common->sem_fork), exit(1));
	common->sem_wr_rd = sem_open("sem_wr_rd", 1);
	if (common->sem_wr_rd == SEM_FAILED)
		(perror("sem_wr_rd open :"), sem_close(common->sem_write),
			sem_close(common->sem_end), sem_close(common->sem_eat),
			sem_close(common->sem_meal), sem_close(common->sem_fork),
			sem_close(common->sem_dead), exit(1));
	return ;
}

static int	create_philo(t_common *common)
{
	while (++(common->nb) < common->nb_philo)
	{
		common->philo[common->nb] = fork();
		if (common->philo[common->nb] == -1)
			return (perror("fork"), 1);
		else if (common->philo[common->nb] == 0)
		{
			free(common->philo);
			init_sem_child(common);
			routine(common);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_common		common;

	if (test_arg(ac, av))
		return (1);
	if (!init_common(&common, ac, av))
		return (printf("Erreur initialisation\n"), 1);
	create_philo(&common);
	pthread_monitoring(&common);
	wait_all_and_exit(&common, 0, 0);
	return (0);
}
