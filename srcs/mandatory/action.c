/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:07 by tlamarch          #+#    #+#             */
/*   Updated: 2024/08/30 16:14:39 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test_die(t_common *co, t_philo *ph)
{
	if (pthread_mutex_lock(&co->mutex_dead));
		return (perror("mutex"), 1);
	if (co->dead == 1)
		return (pthread_mutex_unlock(&co->mutex_dead), 1);
	pthread_mutex_unlock(&co->mutex_dead);
	if ((get_current_time() - ph->last_eat) >= co->time_to_die)
	{
		if (pthread_mutex_lock(&co->mutex_dead));
			return (perror("mutex"), 1);
		co->dead = 1;
		pthread_mutex_unlock(&co->mutex_dead);
		write_message(co, ph, "died\n");
		return (1);
	}
	return (0);
}

int	take_left_fork_first(t_common *co, t_philo *ph)
{
	if (pthread_mutex_lock(&co->mutex[ph->n]))
		return (perror("mutex"), 1);
	if (test_die(co, ph))
	{
		pthread_mutex_unlock(&co->mutex[ph->n]);
		return (1);
	}
	write_message(co, ph, "has taken a fork\n");
	if (pthread_mutex_lock(&co->mutex[ph->next]))
		return (pthread_mutex_unlock(&co->mutex[ph->n]), perror("mutex nxt"), 1);
	if (test_die(co, ph))
	{
		unlock_mutex(co, ph);
		return (1);
	}
	write_message(co, ph, "has taken a fork\n");
	return (0);
}

int	take_right_fork_first(t_common *co, t_philo *ph)
{
	if (pthread_mutex_lock(&co->mutex[ph->next]))
		return (perror("mutex next"), 1);
	if (test_die(co, ph))
	{
		pthread_mutex_unlock(&co->mutex[ph->next]);
		return (1);
	}
	write_message(co, ph, "has taken a fork\n");
	if (pthread_mutex_lock(&co->mutex[ph->n]))
		return (pthread_mutex_unlock(&co->mutex[ph->next]), perror("mutex"), 1);
	if (test_die(co, ph))
	{
		unlock_mutex(co, ph);
		return (1);
	}
	write_message(co, ph, "has taken a fork\n");
	return (0);
}

int	philo_sleep(t_common *common, t_philo *philo)
{
	if (test_die(common, philo))
		return (1);
	if (write_message(common, philo, "is sleeping\n"))
		return (1);
	if (usleep(common->time_to_sleep * 1000))
		return (1);
	if (test_die(common, philo))
		return (1);
	if (write_message(common, philo, "is thinking\n"))
		return (1);
	usleep(500);
	return (0);
}

int	philo_eat(t_common *common, t_philo *philo)
{
	if ((philo->n % 2))
	{
		if (take_right_fork_first(common, philo))
			return (1);
	}
	else
	{
		if (take_left_fork_first(common, philo))
			return (1);
	}
	if (test_die(common, philo))
		return (1);
	philo->last_eat = (get_current_time());
	if (write_message(common, philo, "is eating\n"))
		return (unlock_mutex(common, philo), 1);
	if (usleep(common->time_to_sleep * 1000))
		return (unlock_mutex(common, philo), 1);
	unlock_mutex(common, philo);
	return (0);
}
