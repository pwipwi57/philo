/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:45:51 by tlamarch          #+#    #+#             */
/*   Updated: 2024/10/29 18:51:37 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

int	test_die(t_common *common)
{
	sem_wait(common->sem_write_read);
	if (common->end || common->die)
		return(sem_post(common->sem_write_read), 1);
	sem_post(common->sem_write_read);
	if ((get_time() - common->last_eat) < common->time_to_die)
		return (0);
	sem_post(common->sem_dead);
	common->die = 1;
	return (1);
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
		return(write(2, "gettimeofday() error\n", 22), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	write_message(t_common *common, char *str)
{
	size_t	time_since_start;

	sem_wait(common->sem_write_read);
	if ((common->end) && !(common->die) && (str[0] == 'd'))
		return(sem_post(common->sem_write_read), 1);
	sem_post(common->sem_write_read);
	sem_wait(common->sem_write);
	time_since_start = get_time() - common->time_begin;
	if (time_since_start == -(common->time_begin))
		close_all_sem_exit(common, 1);
	printf("%zu %d %s", time_since_start, (common->nb) + 1, str);
	sem_post(common->sem_write);
	return (0);
}

int	my_usleep(unsigned int milliseconds, t_common *co)
{
	struct timeval	start;
	struct timeval	end;
	unsigned int	elapsed;

	if (!co)
		return (1);
	if (gettimeofday(&start, NULL) == -1)
		return(write(2, "gettimeofday() error\n", 22), 1);
	if (gettimeofday(&end, NULL) == -1)
		return(write(2, "gettimeofday() error\n", 22), 1);
	elapsed = (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000;
	while (elapsed <= milliseconds)
	{
		gettimeofday(&end, NULL);
		elapsed = (end.tv_sec - start.tv_sec) * 1000
			+ (end.tv_usec - start.tv_usec) / 1000;
		if (milliseconds > 10 && elapsed <= milliseconds - 10)
			usleep(9000);
		else
			usleep(1000);
		if (test_die(co))
			break ;
	}
	return (0);
}
