/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:07 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/12 13:09:14 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	test_die(t_common *co, t_philo *ph)
{
	pthread_mutex_lock(&co->mutex_dead);
	if (co->dead == 1)
		return (pthread_mutex_unlock(&co->mutex_dead), 1);
	pthread_mutex_unlock(&co->mutex_dead);
	pthread_mutex_lock(&ph->mutex_last_eat);
	if ((get_time() - ph->last_eat) >= co->time_to_die)
	{
		pthread_mutex_unlock(&ph->mutex_last_eat);
		pthread_mutex_lock(&co->mutex_dead);
		// write_message(co, ph, "died\n");
		co->dead = 1;
		pthread_mutex_unlock(&co->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->mutex_last_eat);
	return (0);
}

int	take_left_fork_first(t_common *co, t_philo *ph)
{
	pthread_mutex_lock(&co->mutex_fork[ph->n]);
	if (test_die(co, ph))
	{
		pthread_mutex_unlock(&co->mutex_fork[ph->n]);
		return (1);
	}
	write_message(co, ph, "has taken a fork\n");
	pthread_mutex_lock(&co->mutex_fork[ph->next]);
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
	pthread_mutex_lock(&co->mutex_fork[ph->next]);
	if (test_die(co, ph))
	{
		pthread_mutex_unlock(&co->mutex_fork[ph->next]);
		return (1);
	}
	write_message(co, ph, "has taken a fork\n");
	pthread_mutex_lock(&co->mutex_fork[ph->n]);
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
	if (my_usleep(common->time_to_sleep, common, philo))
		return (1);
	if (test_die(common, philo))
		return (1);
	if (write_message(common, philo, "is thinking\n"))
		return (1);
	usleep(1500);
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
	{
		unlock_mutex(common, philo);
		return (1);
	}
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = (get_time());
	pthread_mutex_unlock(&philo->mutex_last_eat);
	if (write_message(common, philo, "is eating\n"))
		return (unlock_mutex(common, philo), 1);
	if (my_usleep(common->time_to_eat, common, philo))
		return (unlock_mutex(common, philo), 1);
	unlock_mutex(common, philo);
	return (0);
}
