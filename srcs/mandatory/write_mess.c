/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:51:31 by tlamarch          #+#    #+#             */
/*   Updated: 2024/07/07 20:55:22 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_strcat_philo(char *nb, char *time, char *str, char *new)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (time[++i])
		new[i] = time[i];
	free(time);
	new[i++] = ' ';
	while (nb[j])
		new[i++] = nb[j++];
	new[i++] = ' ';
	while (*str)
		new[i++] = *str++;
	new[i] = 0;
}

int	create_message(size_t time, char *nb, char *str, char *mess)
{
	char	*time_char;

	time_char = ft_itoa((int)time);
	if (!time_char)
		return (perror("time_char :"), 1);
	ft_strcat_philo(nb, time_char, str, mess);
	return (0);
}

int	write_message(t_common *common, t_philo *philo, char *str)
{
	size_t	time_since_start;
	char	mess[64];

	memset(mess, 0, 64);
	time_since_start = get_current_time() - common->time_begin;
	if (time_since_start == common->time_begin)
		return (perror("Getimeofday"), 1);
	if (create_message(time_since_start, philo->nb_char, str, mess))
		return (1);
	pthread_mutex_lock(&common->mutex_write);
	write(1, mess, ft_strlen(mess));
	pthread_mutex_unlock(&common->mutex_write);
	return (0);
}
