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

int	set_start_delay(t_data *data, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		if (num_philo % 2 == 0)
		{
			if (i * 2 < num_philo)
				data->philo[i].start_delay = 0;
			else
				data->philo[i].start_delay = 800 * data->arg.time_to_eat;
		}
		else
		{
			data->philo[i].start_delay = \
				1000 * data->arg.time_to_eat * 2 * i / num_philo;
		}
		i++;
	}
	return (0);
}

int	launch_philo(t_data *data, int num_philo)
{
	int				i;
	t_philo			*philo;
	unsigned long	now;

	now = get_time();
	i = 0;
	while (i < num_philo)
	{
		philo = &(data->philo[i]);
		philo->state = ALIVE;
		philo->start_time = now;
		philo->pid = fork();
		if (philo->pid == 0)
			philo_loop(philo);
		if (philo->pid < 0)
		{
			philo->state = UNLAUNCHED;
			break ;
		}
		i++;
	}
	if (i == num_philo)
		return (0);
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
