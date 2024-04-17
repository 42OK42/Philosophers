/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:46:24 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/17 16:39:51 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_forks(t_philosopher *philos, long start_time)
{
	int	first_fork;
	int	second_fork;

	if (philos->num_philosophers == 1)
		return (-1);
	second_fork = assign_second_fork(philos);
	first_fork = assign_first_fork(philos);
	if (take_first_fork(philos, start_time, first_fork) == -1)
		return (-1);
	if (take_second_fork(philos, start_time, first_fork, second_fork) == -1)
		return (-1);
	return (1);
}

int	take_first_fork(t_philosopher *philos, long start_time, int first_fork)
{
	pthread_mutex_lock(&philos->data->fork_mutex[first_fork]);
	pthread_mutex_lock(&philos->data->print_mutex);
	usleep(20);
	if (check_all_here(philos) != 1)
	{
		pthread_mutex_unlock(&philos->data->print_mutex);
		pthread_mutex_unlock(&philos->data->fork_mutex[first_fork]);
		return (-1);
	}
	printf("%ld %i has taken a fork\n", get_timestamp_ms(start_time), \
		philos->index);
	pthread_mutex_unlock(&philos->data->print_mutex);
	return (1);
}

int	take_second_fork(t_philosopher *philos, long start_time, \
	int first_fork, int second_fork)
{
	pthread_mutex_lock(&philos->data->fork_mutex[second_fork]);
	pthread_mutex_lock(&philos->data->print_mutex);
	if (check_all_here(philos) != 1)
	{
		pthread_mutex_unlock(&philos->data->fork_mutex[first_fork]);
		pthread_mutex_unlock(&philos->data->fork_mutex[second_fork]);
		pthread_mutex_unlock(&philos->data->print_mutex);
		return (-1);
	}
	printf("%ld %i has taken a fork\n", get_timestamp_ms(start_time), \
		philos->index);
	pthread_mutex_unlock(&philos->data->print_mutex);
	return (1);
}

int	give_forks_back(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->data->fork_mutex[philosopher->fork_l]);
	pthread_mutex_unlock(&philosopher->data->fork_mutex[philosopher->fork_r]);
	return (1);
}
