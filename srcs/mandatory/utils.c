/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:45:51 by tlamarch          #+#    #+#             */
/*   Updated: 2024/07/21 19:50:54 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_mutex(t_common *co, t_philo *philo)
{
	// printf("unlock / philo->n = %d\n", philo->n);
		pthread_mutex_unlock(&co->mutex[philo->n]);
		pthread_mutex_unlock(&co->mutex[philo->next]);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	free_philo(t_philo **tab, int nb_philo)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (i < nb_philo)
	{
		free(tab[i]->nb_char);
		free(tab[i++]);
	}
	free(tab);
	return ;
}

int	my_usleep(unsigned int milliseconds, t_common *co, t_philo *ph)
{
	struct timeval	start;
	struct timeval	end;
	unsigned int	elapsed;

	if (!co && !ph)
		return (1);
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000;
	while (elapsed <= milliseconds)
	{
		gettimeofday(&end, NULL);
		elapsed = (end.tv_sec - start.tv_sec) * 1000
			+ (end.tv_usec - start.tv_usec) / 1000;
		usleep(100);
		// if (test_die(co, ph))
		// 	return (1);
	}
	return (0);
}
