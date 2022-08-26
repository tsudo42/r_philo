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

int	launch_error(t_data *data, int num_philo)
{
	int	i;

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
		{
			philo->state = UNLAUNCHED;
			break ;
		}
		i++;
	}
	if (i == num_philo)
	{
		if (pthread_create(&data->monitor_thread, NULL, monitor, data) == 0)
		{
			data->monitor_launched = 1;
			return (0);
		}
	}
	return (launch_error(data, num_philo));
}

int	launch(t_data *data)
{
	if (data->arg.num_philo == 1)
	{
		if (data->arg.num_to_eat == 0)
			return (0);
		printf("0 1 has taken a fork\n");
		usleep(data->arg.time_to_die * 1000);
		printf("%ld 1 died\n", data->arg.time_to_die);
		return (0);
	}
	calc_delay(data, data->arg.num_philo);
	return (launch_philo(data, data->arg.num_philo));
}
