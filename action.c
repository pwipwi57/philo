/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:06:07 by tlamarch          #+#    #+#             */
/*   Updated: 2024/07/03 03:54:34 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	test_die(t_common *co, t_philo ph)
{
	pthread_mutex_lock(co->mutex_dead);
	if (common->dead == 1)
		return (1);
	if (get_current_time() - ph.last_eat >= co->time_to_die)
	{
		write_message(co, ph, " died\n");
		common->dead == 1;
		return (1);
	}
	return (0);
}

int	take_left_fork_first(t_common *co, t_philo ph)
{
	if (pthread_mutex_lock(co->mutex[ph.n]))
		return (perror("mutex"), 1);
	if (test_die(co, ph))
		return (pthread_mutex_unlock(co->mutex[ph.n]), 1);
	write_message(co, ph, " has taken a fork\n");
	if (pthread_mutex_lock(co->mutex[ph.next]))
		return (perror("mutex"), 1);
	if (test_die(co, ph))
		return (pthread_mutex_unlock(co->mutex[ph.n]),
			pthread_mutex_unlock(co->mutex[ph.next]), 1);
	write_message(co, ph, " has taken a fork\n");
	reutrn (0);
}

int	take_right_fork_first(t_common *co, t_philo ph)
{
	if (test_die(co, ph))
		return (1);
	if (pthread_mutex_lock(co->mutex[ph.next]))
		return (perror("mutex"), 1);
	if (test_die(co, ph))
		return (pthread_mutex_unlock(co->mutex[ph.next]), 1);
	write_message(co, ph, " has taken a fork\n");
	if (pthread_mutex_lock(co->mutex[ph.n]))
		return (perror("mutex"), pthread_mutex_unlock(co->mutex[ph.n], 1));
	if (test_die(co, ph))
		return (pthread_mutex_unlock(co->mutex[ph.n]),
			pthread_mutex_unlock(co->mutex[ph.next]), 1);
	write_message(co, ph, " has taken a fork\n");
	reutrn (0);
}

int	philo_sleep(t_common *common, t_philo philo)
{
	if (write_message(common, philo, " is sleeping\n"))
		return (1);
	if (usleep(common.time_to_sleep * 1000))
		return (perror("Usleep sleep"), 1);
	return (0);
}

int	philo_eat(t_common *common, t_philo *philo)
{
	if (write_message(common, *philo, " is thinking\n"))
		return (1);
	if (philo->n % 2)
		take_left_fork_first(common, *philo);
	else
		take_right_fork_first(common, philo);
	if (write_message(common, *philo, " is eating\n"))
		return (1);
	if (usleep(common.time_to_eat * 1000))
		return (perror("Usleep eat"), 1);
	common->last_eat = (get_current_time() - co->time_begin);
	pthread_mutex_unlock(co->mutex[philo.n]);
	pthread_mutex_unlock(co->mutex[philo.next]);
	return (0);
}
