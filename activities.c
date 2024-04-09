/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:35:11 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/01 18:15:36 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_philosopher *philosopher, long start_time)
{
	long			timestamp_in_ms;

	if (check_all_here(philosopher) == 1)
	{
		pthread_mutex_lock(&philosopher->data->print_mutex);
		timestamp_in_ms = get_timestamp_ms(start_time);
		pthread_mutex_lock(&philosopher->last_meal_mutex_p);
		philosopher->last_meal = timestamp_in_ms;
		pthread_mutex_unlock(&philosopher->last_meal_mutex_p);
		if (check_all_here(philosopher) == 1)
			printf("%ld %i is eating\n", timestamp_in_ms, philosopher->index);
		pthread_mutex_unlock(&philosopher->data->print_mutex);
		pthread_mutex_lock(&philosopher->meals_eaten_mutex_p);
		philosopher->meals_eaten++;
		pthread_mutex_unlock(&philosopher->meals_eaten_mutex_p);
		usleep(philosopher->time_to_eat * 1000);
		return (1);
	}
	else
		return (-1);
}

int	ft_sleep(t_philosopher *philosopher, long start_time)
{
	long			timestamp_in_ms;

	if (check_all_here(philosopher) == 1)
	{
		pthread_mutex_lock(&philosopher->data->print_mutex);
		timestamp_in_ms = get_timestamp_ms(start_time);
		if (check_all_here(philosopher) == 1)
			printf("%ld %i is sleeping\n", timestamp_in_ms, philosopher->index);
		pthread_mutex_unlock(&philosopher->data->print_mutex);
		usleep(philosopher->time_to_sleep * 1000);
		return (1);
	}
	else
		return (-1);
}

int	think(t_philosopher *philosopher, long start_time)
{
	long			timestamp_in_ms;

	if (check_all_here(philosopher) == 1)
	{
		pthread_mutex_lock(&philosopher->data->print_mutex);
		timestamp_in_ms = get_timestamp_ms(start_time);
		if (check_all_here(philosopher) == 1)
			printf("%ld %i is thinking\n", timestamp_in_ms, philosopher->index);
		pthread_mutex_unlock(&philosopher->data->print_mutex);
		usleep((philosopher->time_to_die * 1000 - \
			(philosopher->time_to_eat * 1000 + philosopher->time_to_sleep \
			* 1000)) * 0.9);
		return (1);
	}
	else
		return (-1);
}
