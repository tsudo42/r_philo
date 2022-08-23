/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int set_start_delay(t_data *data, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (num_philo % 2 == 0)
		{
			if (i % 2 == 0)
				data->philo[i].start_delay = 0;
			else
				data->philo[i].start_delay = 500;
		}
		else
		{
			if (i % 2 == 0)
				data->philo[i].start_delay = \
					1000 * data->arg.time_to_eat * (i / 2) / (num_philo / 2);
			else
				data->philo[i].start_delay = \
					1000 * data->arg.time_to_eat + 500;
		}
		i++;
	}
	return (0);
}

int	launch_philo(t_data *data, int num_philo)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < num_philo)
	{
		philo = &(data->philo[i]);
		philo->state = ALIVE;
		if (pthread_create(&philo->thread, NULL, philo_loop, philo) != 0)
			break ;
		i++;
	}
	if (i == num_philo)
		return (0);
	data->philo[i].state = UNLAUNCHED;
	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_lock(data->philo[i].state_lock);
		if (data->philo[i].state != UNLAUNCHED)
			data->philo[i].state = PTHREAD_ERR;
		pthread_mutex_unlock(data->philo[i].state_lock);
		i++;
	}
	return (-1);
}

int	launch(t_data *data)
{
	if (data->arg.num_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->arg.time_to_die * 1000);
		printf("%ld 1 died\n", data->arg.time_to_die);
		return (0);
	}
	set_start_delay(data, data->arg.num_philo);
	return (launch_philo(data, data->arg.num_philo));
}
