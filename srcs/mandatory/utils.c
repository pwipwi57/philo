/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:45:51 by tlamarch          #+#    #+#             */
/*   Updated: 2024/08/30 16:06:29 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_mutex(t_common *co, t_philo *philo)
{
	if (&co->mutex[philo->n] < &co->mutex[philo->next])
	{
		pthread_mutex_unlock(&co->mutex[philo->n]);
		pthread_mutex_unlock(&co->mutex[philo->next]);
	}
	else
	{
		pthread_mutex_unlock(&co->mutex[philo->next]);
		pthread_mutex_unlock(&co->mutex[philo->n]);
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

