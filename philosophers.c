/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:42:38 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/26 13:25:41 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	no_one_dead(t_data	*data)
{
	long			current_time_in_ms;
	t_philosopher	*philosopher;
	long			time_to_die;

	time_to_die = data->time_to_die;
	philosopher = data->philosopher;
	while (philosopher)
	{
		pthread_mutex_lock(&philosopher->start_time_mutex_p);
		current_time_in_ms = get_timestamp_ms(philosopher->start_time);
		pthread_mutex_unlock(&philosopher->start_time_mutex_p);
		pthread_mutex_lock(&philosopher->last_meal_mutex_p);
		if (current_time_in_ms - philosopher->last_meal > time_to_die)
		{
			pthread_mutex_unlock(&philosopher->last_meal_mutex_p);
			return (philosopher->index);
		}
		pthread_mutex_unlock(&philosopher->last_meal_mutex_p);
		philosopher = philosopher->next;
	}
	return (-1);
}

int	create_philosopher_threads(t_data *data)
{
	t_philosopher		*philosopher;

	philosopher = data->philosopher;
	while (philosopher)
	{
		if (pthread_create(&philosopher->tid, NULL, &routine, philosopher) != 0)
		{
			pthread_mutex_lock(&data->print_mutex);
			return (printf("Failed to create thread"), -1);
			pthread_mutex_unlock(&data->print_mutex);
		}
		philosopher = philosopher->next;
	}
	update_starttimes(data);
	pthread_mutex_lock(&data->all_created_mutex);
	data->all_created = 1;
	pthread_mutex_unlock(&data->all_created_mutex);
	return (1);
}

int	join_philosopher_threads(t_data *data)
{
	t_philosopher		*philosopher;	

	philosopher = data->philosopher;
	while (philosopher)
	{
		if (pthread_join(philosopher->tid, NULL) != 0)
		{
			pthread_mutex_lock(&data->print_mutex);
			return (printf("Failed to join thread"), -1);
			pthread_mutex_unlock(&data->print_mutex);
		}
		philosopher = philosopher->next;
	}
	return (1);
}

void	monitor_philosophers(t_data *data)
{
	long			current_time_in_ms;
	int				dead_philo;

	while (check_all_here(data->philosopher) == 1)
	{
		usleep(100);
		dead_philo = no_one_dead(data);
		if (dead_philo != -1)
		{
			pthread_mutex_lock(&data->start_time_mutex);
			current_time_in_ms = get_timestamp_ms(data->start_time);
			pthread_mutex_unlock(&data->start_time_mutex);
			change_all_here(data);
			pthread_mutex_lock(&data->print_mutex);
			printf("%ld %i died\n", current_time_in_ms, dead_philo);
			pthread_mutex_unlock(&data->print_mutex);
		}
		if (data->max_meals != -1)
		{
			if (one_finished(data) != 1)
				change_all_here(data);
		}
	}
}

int	start_philosophers(t_data *data)
{
	if (create_philosopher_threads(data) == -1)
		return (-1);
	monitor_philosophers(data);
	if (join_philosopher_threads(data) == -1)
		return (-1);
	return (1);
}
