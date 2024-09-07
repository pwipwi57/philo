/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:45:51 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/07 19:48:29 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_mutex(t_common *co, t_philo *philo)
{
	if (&co->mutex_fork[philo->n] < &co->mutex_fork[philo->next])
	{
		pthread_mutex_unlock(&co->mutex_fork[philo->n]);
		pthread_mutex_unlock(&co->mutex_fork[philo->next]);
	}
	else
	{
		pthread_mutex_unlock(&co->mutex_fork[philo->next]);
		pthread_mutex_unlock(&co->mutex_fork[philo->n]);
	}
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

int	write_message(t_common *common, t_philo *philo, char *str)
{
	size_t	time_since_start;

	pthread_mutex_lock(&common->mutex_write);
	time_since_start = get_current_time() - common->time_begin;
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
		if (elapsed <= milliseconds - 10)
			usleep(9000);
		else
		usleep(1000); // voir pour ralonger
		if (test_die(co, ph))
			return (1);
	}
	return (0);
}
