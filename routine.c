/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:26:10 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/25 20:56:12 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_here(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->all_here_mutex_p);
	if (philosopher->all_here != 1)
	{
		pthread_mutex_unlock(&philosopher->all_here_mutex_p);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->all_here_mutex_p);
	return (1);
}

int	check_all_created(t_data *data)
{
	pthread_mutex_lock(&data->all_created_mutex);
	if (data->all_created == 1)
	{
		pthread_mutex_unlock(&data->all_created_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->all_created_mutex);
		return (0);
	}
}

void	activities_loop(t_philosopher	*philosopher, long start_time)
{
	while (check_all_here(philosopher) == 1)
	{
		if (take_forks(philosopher, start_time) != 1)
			return ;
		if (check_all_here(philosopher) != 1)
		{
			give_forks_back(philosopher);
			return ;
		}
		if (eat(philosopher, start_time) != 1)
		{
			give_forks_back(philosopher);
			return ;
		}
		if (give_forks_back(philosopher) != 1)
			return ;
		if (check_all_here(philosopher) != 1)
			return ;
		if (ft_sleep(philosopher, start_time) != 1)
			return ;
		if (check_all_here(philosopher) != 1)
			return ;
		if (think(philosopher, start_time) != 1)
			return ;
	}
}

int	every_second_ate(int odd_or_even, t_data *data)
{
	t_philosopher	*philosopher;

	philosopher = data->philosopher;
	while (philosopher)
	{
		if (philosopher->index % 2 == odd_or_even)
		{
			pthread_mutex_lock(&philosopher->meals_eaten_mutex_p);
			if (philosopher->meals_eaten < 1)
			{
				pthread_mutex_unlock(&philosopher->meals_eaten_mutex_p);
				return (0);
			}
			pthread_mutex_unlock(&philosopher->meals_eaten_mutex_p);
		}
		philosopher = philosopher->next;
	}
	return (1);
}

void	*routine(void *arg)
{
	int				i;
	t_philosopher	*philos;
	t_data			*data;
	int				odd_or_even;
	long			start_time;

	odd_or_even = 0;
	philos = (t_philosopher *)arg;
	data = philos->data;
	i = philos->index;
	while (check_all_created(data) == 0)
		usleep(100);
	if (handle_solo(philos) != 1)
		return (NULL);
	pthread_mutex_lock(&data->start_time_mutex);
	start_time = data->start_time;
	pthread_mutex_unlock(&data->start_time_mutex);
	if (philos->index % 2 == odd_or_even && philos->num_philosophers > 1)
	{
		while (every_second_ate(1, data) != 1 \
			&& check_all_here(philos) != 1)
			usleep(100);
	}
	activities_loop(philos, start_time);
	return (NULL);
}
