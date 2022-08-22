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

void	*monitor(void *ptr)
{
	t_philo	*philo;
	long	time;

	philo = ptr;
	usleep(philo->arg->time_to_die * 500);
	while (1)
	{
		pthread_mutex_lock(philo->state_lock);
		if (philo->state)
			break ;
		time = get_time();
		if (philo->last_eat < time && philo->starve_time < time)
		{
			print_state(philo, DIED);
			philo->state = STARVED;
		}
		if (philo->arg->num_to_eat > 0 && \
			philo->arg->num_to_eat <= philo->eat_count)
			philo->state = END;
		pthread_mutex_unlock(philo->state_lock);
		usleep(5000);
	}
	philo->state = END;
	pthread_mutex_unlock(philo->state_lock);
	return (NULL);
}
