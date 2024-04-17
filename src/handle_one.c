/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okrahl <okrahl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:44:29 by okrahl            #+#    #+#             */
/*   Updated: 2024/04/17 16:39:48 by okrahl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	handle_solo(t_philosopher *philosopher)
{
	if (philosopher->data->num_philosophers == 1)
	{
		pthread_mutex_lock(&philosopher->data->print_mutex);
		printf("%ld %i has taken a fork\n", \
			get_timestamp_ms(philosopher->start_time), philosopher->index);
		pthread_mutex_unlock(&philosopher->data->print_mutex);
		return (-1);
	}
	return (1);
}
