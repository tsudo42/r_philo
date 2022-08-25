/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	cleanup_mutex(t_data *data)
{
	int	i;

	debug_write("cleaning mutex up...\n");
	i = 0;
	while (i < data->arg.num_philo)
	{
		pthread_mutex_destroy(&(data->philo_state[i]));
		pthread_mutex_destroy(&(data->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->printer));
	debug_write("cleaned!\n");
	return (0);
}

int	ready_mutex(t_data *data)
{
	int	i;

	errno = 0;
	i = 0;
	while (i < data->arg.num_philo)
	{
		pthread_mutex_init(&(data->philo_state[i]), NULL);
		pthread_mutex_init(&(data->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&data->printer, NULL);
	if (errno != 0)
	{
		cleanup_mutex(data);
		return (-1);
	}
	return (0);
}
