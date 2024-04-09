/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:25:16 by okrahl            #+#    #+#             */
/*   Updated: 2024/03/26 13:25:23 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	assign_first_fork(t_philosopher *philosopher)
{
	int		first_fork;

	if (philosopher->index % 2 == 0)
		first_fork = philosopher->fork_r;
	else
		first_fork = philosopher->fork_l;
	return (first_fork);
}

int	assign_second_fork(t_philosopher *philosopher)
{
	int		second_fork;

	if (philosopher->index % 2 == 0)
		second_fork = philosopher->fork_l;
	else
		second_fork = philosopher->fork_r;
	return (second_fork);
}

int	one_finished(t_data *data)
{
	t_philosopher	*philosophers;
	int				max_meals;
	int				counter;

	counter = 0;
	philosophers = data->philosopher;
	pthread_mutex_lock(&data->max_meals_mutex);
	max_meals = data->max_meals;
	pthread_mutex_unlock(&data->max_meals_mutex);
	while (philosophers)
	{
		pthread_mutex_lock(&philosophers->meals_eaten_mutex_p);
		if (philosophers->meals_eaten >= max_meals)
			counter++;
		pthread_mutex_unlock(&philosophers->meals_eaten_mutex_p);
		philosophers = philosophers->next;
	}
	if (data->num_philosophers == counter)
		return (-1);
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	min_counter;
	int	result;

	result = 0;
	i = 0;
	min_counter = 1;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min_counter = (-1 * min_counter);
		i++;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		result = ((result * 10) + (str[i] - '0'));
		i++;
	}
	return (result * min_counter);
}

void	change_all_here(t_data *data)
{
	t_philosopher	*philosopher_start;

	philosopher_start = data->philosopher;
	while (philosopher_start)
	{
		pthread_mutex_lock(&philosopher_start->all_here_mutex_p);
		philosopher_start->all_here = -1;
		pthread_mutex_unlock(&philosopher_start->all_here_mutex_p);
		philosopher_start = philosopher_start->next;
	}
}
