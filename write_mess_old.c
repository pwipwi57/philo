/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 02:00:57 by tlamarch          #+#    #+#             */
/*   Updated: 2024/06/25 02:49:19 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strcat_philo(char *nb, char *time, char *str)
{
	char	*new;
	int		i;
	int		j;

	i = (ft_strlen(time) + ft_strlen(nb) + ft_strlen(str) + 3);
	new = malloc(i);
	if (!new)
		return (free(nb), free(time), perror("strcat malloc"), NULL);
	i = -1;
	j = 0;
	while (time[++i])
		new[i] = time[i];
	free(time);
	new[i++] = ' ';
	while (nb[j])
		new[i++] = nb[j++];
	free(nb);
	new[i++] = ' ';
	while (*str)
		new[i++] = *str++;
	new[i] = 0;
	return (new);
}

char	*create_message(size_t time, int n, char *str)
{
	char	*mess;
	char	*time_char;
	char	*number;

	mess = NULL;
	time_char = ft_itoa(time);
	if (!time_char)
		return (perror("time_char :"), NULL);
	number = ft_itoa(n);
	if (!number)
		return (perror("number :"), free(time_char), NULL);
	mess = ft_strcat_philo(number, time_char, str);
	if (!mess)
		return (NULL);
	return (mess);
}

int	write_message(t_common *common, t_philo philo, char *str)
{
	size_t	timenow;
	size_t	time_since_start;
	char	*mess;
	int		leng;

	time_since_start = common->time_begin - get_current_time();
	if (time_since_start == common->time_begin)
		return (perror("Getimeofday"), 1);
	mess = create_message(time_since_start, philo.n, str);
	if (!mess)
		return (perror("Malloc mess :"), 1);
	write(1, mess, ft_strlen(mess));
	free(mess);
	return (0);
}
