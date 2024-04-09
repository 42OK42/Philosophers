/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:17:36 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/22 16:55:15 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_up(t_data *data)
{
	t_philosopher	*current_philosopher;

	if (data == NULL)
		return ;
	current_philosopher = data->philosopher;
	while (current_philosopher)
	{
		pthread_mutex_destroy(&data->fork_mutex \
			[current_philosopher->index - 1]);
		current_philosopher = current_philosopher->next;
	}
	free(data->fork_mutex);
	current_philosopher = data->philosopher;
	clean_philosohers(current_philosopher);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->all_here_mutex);
	pthread_mutex_destroy(&data->all_created_mutex);
	pthread_mutex_destroy(&data->max_meals_mutex);
	pthread_mutex_destroy(&data->start_time_mutex);
	free(data);
}

void	clean_philosohers(t_philosopher *current_philosopher)
{
	t_philosopher	*temp_philosopher;

	while (current_philosopher != NULL)
	{
		pthread_mutex_destroy(&current_philosopher->start_time_mutex_p);
		pthread_mutex_destroy(&current_philosopher->all_here_mutex_p);
		pthread_mutex_destroy(&current_philosopher->last_meal_mutex_p);
		pthread_mutex_destroy(&current_philosopher->meals_eaten_mutex_p);
		temp_philosopher = current_philosopher;
		current_philosopher = current_philosopher->next;
		free(temp_philosopher);
	}
}
