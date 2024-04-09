/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:48:40 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/22 16:48:02 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_timestamp_ms(long start_time)
{
	struct timeval	current_time;
	long			timestamp_in_ms;

	gettimeofday(&current_time, NULL);
	timestamp_in_ms = (current_time.tv_sec * 1000) + \
		(current_time.tv_usec / 1000);
	return (timestamp_in_ms - start_time);
}

void	update_starttimes(t_data *data)
{
	t_philosopher	*philosopher;
	struct timeval	current_time;

	philosopher = data->philosopher;
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(&data->start_time_mutex);
	data->start_time = (current_time.tv_sec * 1000) + \
		(current_time.tv_usec / 1000);
	pthread_mutex_unlock(&data->start_time_mutex);
	while (philosopher)
	{
		pthread_mutex_lock(&philosopher->start_time_mutex_p);
		philosopher->start_time = (current_time.tv_sec * 1000) + \
			(current_time.tv_usec / 1000);
		philosopher->last_meal = get_timestamp_ms(philosopher->start_time);
		pthread_mutex_unlock(&philosopher->start_time_mutex_p);
		philosopher = philosopher->next;
	}
	return ;
}
