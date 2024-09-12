/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_counter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamarch <tlamarch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:21:02 by tlamarch          #+#    #+#             */
/*   Updated: 2024/09/12 22:31:28 by tlamarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	add_meal_count(t_common *common)
{
	pthread_mutex_lock(&common->mutex_meal_counter);
	(common->meal_counter)++;
	if (common->meal_counter == common->nb_meal)
	{
		pthread_mutex_unlock(&common->mutex_meal_counter);
		pthread_mutex_lock(&common->mutex_end);
		common->end = 1;
		pthread_mutex_unlock(&common->mutex_end);
	}
	pthread_mutex_unlock(&common->mutex_meal_counter);
	return ;
}
