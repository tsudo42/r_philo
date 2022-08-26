/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_philo(t_philo *philo, int *min_eat_count)
{
	long	time;

	pthread_mutex_lock(philo->state_lock);
	if (philo->state == ALIVE && philo->last_eat != 0)
	{
		time = get_time();
		if (philo->last_eat < time && philo->starve_time < time)
		{
			print_state(philo, DIED);
			philo->state = STARVED;
			pthread_mutex_unlock(philo->state_lock);
			return (1);
		}
		if (*min_eat_count > philo->eat_count)
			*min_eat_count = philo->eat_count;
	}
	pthread_mutex_unlock(philo->state_lock);
	return (0);
}

void	*set_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.num_philo)
	{
		pthread_mutex_lock(data->philo[i].state_lock);
		data->philo[i].state = END;
		pthread_mutex_unlock(data->philo[i].state_lock);
		i++;
	}
	return (NULL);
}

void	*monitor(void *ptr)
{
	t_data	*data;
	int		i;
	int		min_eat_count;

	data = ptr;
	i = 0;
	min_eat_count = 0;
	while (1)
	{
		if (data->arg.num_to_eat >= 0 && \
			data->arg.num_to_eat <= min_eat_count)
			break ;
		min_eat_count = data->arg.num_to_eat;
		i = 0;
		while (i < data->arg.num_philo)
		{
			if (monitor_philo(&(data->philo[i]), &min_eat_count))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (set_end(data));
}
