/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:42:35 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/17 16:39:43 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_philosopher	*init_philo(int index, t_data *data)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->tid = index;
	philosopher->index = index;
	philosopher->last_meal = get_timestamp_ms(data->start_time);
	philosopher->meals_eaten = 0;
	philosopher->start_time = data->start_time;
	philosopher->time_to_eat = data->time_to_eat;
	philosopher->time_to_sleep = data->time_to_sleep;
	philosopher->time_to_die = data->time_to_die;
	philosopher->max_meals = data->max_meals;
	philosopher->all_here = 1;
	philosopher->num_philosophers = data->num_philosophers;
	philosopher->next = NULL;
	philosopher->data = data;
	pthread_mutex_init(&philosopher->all_here_mutex_p, NULL);
	pthread_mutex_init(&philosopher->start_time_mutex_p, NULL);
	pthread_mutex_init(&philosopher->last_meal_mutex_p, NULL);
	pthread_mutex_init(&philosopher->meals_eaten_mutex_p, NULL);
	return (philosopher);
}

t_philosopher	*create_philos(int num_philos, t_data *data)
{
	t_philosopher	*philosopher;
	t_philosopher	*current_philosopher;
	int				i;

	i = 1;
	if (num_philos <= 0)
		return (NULL);
	current_philosopher = init_philo(i, data);
	philosopher = current_philosopher;
	while (i < num_philos)
	{
		i++;
		current_philosopher->next = init_philo(i, data);
		current_philosopher = current_philosopher->next;
	}
	current_philosopher = NULL;
	return (philosopher);
}

pthread_mutex_t	*init_forks(int count)
{
	pthread_mutex_t	*fork_mutex;
	int				i;

	i = 0;
	fork_mutex = malloc(count * sizeof(pthread_mutex_t));
	while (i < count)
	{
		pthread_mutex_init(&fork_mutex[i], NULL);
		i++;
	}
	return (fork_mutex);
}

void	assign_forks(t_data *data, int num_philosophers)
{
	t_philosopher	*philosopher;

	philosopher = data->philosopher;
	while (philosopher)
	{
		if (philosopher->index == 1)
			philosopher->fork_r = num_philosophers - 1;
		else
			philosopher->fork_r = philosopher->index - 2;
		philosopher->fork_l = philosopher->index - 1;
		philosopher = philosopher->next;
	}
}

t_data	*fill_data(int argc, char	**argv)
{
	t_data			*data;
	struct timeval	current_time;

	data = malloc(sizeof(t_data));
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	gettimeofday(&current_time, NULL);
	data->all_here = 1;
	data->all_created = 0;
	data->start_time = (current_time.tv_sec * 1000) + \
		(current_time.tv_usec / 1000);
	pthread_mutex_init(&data->all_here_mutex, NULL);
	pthread_mutex_init(&data->all_created_mutex, NULL);
	pthread_mutex_init(&data->max_meals_mutex, NULL);
	pthread_mutex_init(&data->start_time_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	data->fork_mutex = init_forks(data->num_philosophers);
	data->philosopher = create_philos(data->num_philosophers, data);
	return (assign_forks(data, data->num_philosophers), data);
}
