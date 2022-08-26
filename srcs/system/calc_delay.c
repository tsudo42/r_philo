/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_delay.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

void	calc_delay_even(t_data *data, int num_philo)
{
	unsigned long	start_delay;
	unsigned long	think_delay;
	int				i;

	start_delay = 1000 * data->arg.time_to_eat / 2;
	if (data->arg.time_to_eat > data->arg.time_to_sleep)
		think_delay = 1000 * (data->arg.time_to_eat - data->arg.time_to_sleep);
	else
	{
		think_delay = 0;
		if (data->arg.time_to_sleep - data->arg.time_to_eat < 500)
			think_delay = 500;
	}
	if (think_delay > 10)
		think_delay -= 10;
	i = 0;
	while (i < num_philo)
	{
		if (i % 2)
			data->philo[i].start_delay = start_delay;
		data->philo[i].think_delay = think_delay;
		i++;
	}
}

/* num_philo should not be 1! */
void	calc_delay_odd(t_data *data, int num_philo)
{
	long	time_unit;
	long	think_delay;
	int		i;

	time_unit = data->arg.time_to_eat / (num_philo / 2);
	if (num_philo == 3)
		think_delay = time_unit * 3 / 2;
	else
		think_delay = time_unit * ((num_philo / 2) + 1) / 2;
	if (time_unit / 2 < 10)
		think_delay -= time_unit / 2;
	else
		think_delay -= 10;
	think_delay -= data->arg.time_to_sleep;
	if (think_delay < 0)
		think_delay = 0;
	i = 0;
	while (i < num_philo)
	{
		data->philo[(2 * i) % num_philo].start_delay = 1000 * i * time_unit;
		data->philo[i].think_delay = 1000 * think_delay;
		i++;
	}
}

void	calc_delay(t_data *data, int num_philo)
{
	if (num_philo == 1)
		return ;
	if (num_philo % 2)
		calc_delay_odd(data, num_philo);
	else
		calc_delay_even(data, num_philo);
}
