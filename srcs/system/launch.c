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

int	launch_philo(t_data *data, t_philo *philo)
{
	static int	is_error = 0;
	int			i;

	if (is_error)
		return (-1);
	philo->state = ALIVE;
	if (pthread_create(&(philo->thread), NULL, philo_loop, philo) == 0)
		return (0);
	is_error = 1;
	philo->state = UNLAUNCHED;
	i = 0;
	while (i < data->arg.num_philo)
	{
		pthread_mutex_lock(data->philo[i].state_lock);
		if (data->philo[i].state != UNLAUNCHED)
			data->philo[i].state = PTHREAD_ERR;
		pthread_mutex_unlock(data->philo[i].state_lock);
		i++;
	}
	return (-1);
}

int	launch_even(t_data *data, int num_philo)
{
	int		i;

	i = 0;
	while (i < num_philo)
	{
		launch_philo(data, &(data->philo[i]));
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < num_philo)
	{
		launch_philo(data, &(data->philo[i]));
		i += 2;
	}
	return (0);
}

long	calc_wait_time(int num_philo, t_arg arg)
{
	return (1000 * arg.time_to_eat / (num_philo / 2));
}

int	launch_odd(t_data *data, int num_philo)
{
	int		i;
	long	time_to_wait;

	time_to_wait = calc_wait_time(num_philo, data->arg);
	i = 0;
	while (i < num_philo)
	{
		launch_philo(data, &(data->philo[i]));
		my_usleep(time_to_wait);
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < num_philo)
	{
		launch_philo(data, &(data->philo[i]));
		i += 2;
	}
	return (0);
}

int	launch(t_data *data)
{
	int	ret;

	if (data->arg.num_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data->arg.time_to_die * 1000);
		printf("%ld 1 died\n", data->arg.time_to_die);
		return (0);
	}
	if (data->arg.num_philo % 2 == 0)
		ret = launch_even(data, data->arg.num_philo);
	else
		ret = launch_odd(data, data->arg.num_philo);
	return (ret);
}
