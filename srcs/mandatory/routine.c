/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:07 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/17 01:19:44 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	take_left_fork_first(t_common *co, t_philo *ph)
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

static int	take_right_fork_first(t_common *co, t_philo *ph)
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

static int	philo_sleep(t_common *common, t_philo *philo)
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
	if (common->nb_philo % 2)
		if (my_usleep(common->time_to_think, common, philo))
			return (1);
	return (0);
}

static int	philo_eat(t_common *common, t_philo *philo)
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

void	*routine(void *args)
{
	int		nb_meal_eaten;
	int		nb_philo;
	t_arg	*arg;

	arg = (t_arg *)args;
	pthread_mutex_lock(&arg->mutex_i);
	nb_philo = arg->i;
	arg->i++;
	pthread_mutex_unlock(&arg->mutex_i);
	arg->common->philo[nb_philo].n = nb_philo;
	if (nb_philo % 2)
		my_usleep(1, arg->common, &arg->common->philo[nb_philo]);
	nb_meal_eaten = 0;
	while (1)
	{
		if (philo_eat(arg->common, &arg->common->philo[nb_philo]))
			return (NULL);
		nb_meal_eaten = nb_meal_eaten + 1;
		if (nb_meal_eaten == arg->common->nb_meal)
			add_meal_count(arg->common);
		if (philo_sleep(arg->common, &arg->common->philo[nb_philo]))
			return (NULL);
		usleep(10);
	}
	return ((void *)1);
}
