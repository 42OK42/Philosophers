/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:18:23 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/17 16:39:41 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	input_check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (-1);
	if (ft_atoi(argv[1]) <= 0)
		return (-1);
	if (ft_atoi(argv[2]) < 0)
		return (-1);
	if (ft_atoi(argv[3]) < 0)
		return (-1);
	if (ft_atoi(argv[4]) < 0)
		return (-1);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			*data;

	if (input_check(argc, argv) != 1)
		return (printf("Usage: ./philosophers number_of_philosophers time_to_die tim\
e_to_eat time_to_sleep\
[number_of_times_each_philosopher_must_eat]\n"), -1);
	data = fill_data(argc, argv);
	start_philosophers(data);
	clean_up(data);
	return (1);
}
