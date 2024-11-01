/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:45:51 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/31 16:53:40 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	test_die(t_common *co, t_philo *ph)
{
	pthread_mutex_lock(&co->mutex_end);
	if (co->end == 1)
		return (pthread_mutex_unlock(&co->mutex_end), 1);
	pthread_mutex_unlock(&co->mutex_end);
	pthread_mutex_lock(&ph->mutex_last_eat);
	if ((get_time() - ph->last_eat) >= co->time_to_die)
	{
		pthread_mutex_unlock(&ph->mutex_last_eat);
		return (1);
	}
	pthread_mutex_unlock(&ph->mutex_last_eat);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	write_message(t_common *common, t_philo *philo, char *str)
{
	size_t	time_since_start;

	pthread_mutex_lock(&common->mutex_write);
	time_since_start = get_time() - common->time_begin;
	printf("%zu %d %s", time_since_start, (philo->n) + 1, str);
	pthread_mutex_unlock(&common->mutex_write);
	return (0);
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
		if (milliseconds > 10 && elapsed <= milliseconds - 10)
			usleep(10000);
		else if (milliseconds > 1 && elapsed <= milliseconds - 1)
			usleep(1000);
		else
			usleep(100);
		if (test_die(co, ph))
			return (1);
	}
	return (0);
}
