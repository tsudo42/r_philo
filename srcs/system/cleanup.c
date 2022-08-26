/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	join_philo(t_data *data)
{
	int	i;

	debug_write("joining philo...\n");
	i = 0;
	while (i < data->arg.num_philo)
	{
		pthread_mutex_lock(data->philo[i].state_lock);
		if (data->philo[i].state == UNLAUNCHED)
		{
			i++;
			continue ;
		}
		pthread_mutex_unlock(data->philo[i].state_lock);
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	debug_write("joined!\n");
	return (0);
}

int	print_error(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.num_philo)
	{
		if (data->philo[i].state == PTHREAD_ERR)
		{
			write(STDERR_FILENO, ERRMSG_PTHREAD, ft_strlen(ERRMSG_PTHREAD));
			return (-1);
		}
		i++;
	}
	return (0);
}

int	cleanup(t_data *data)
{
	join_philo(data);
	if (data->monitor_launched)
		pthread_join(data->monitor_thread, NULL);
	cleanup_mutex(data);
	return (print_error(data));
}
