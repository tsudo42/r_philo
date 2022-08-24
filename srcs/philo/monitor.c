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
		sem_wait(philo->sem->sem_monitor);
		time = get_time();
		if (philo->last_eat < time && philo->starve_time < time)
		{
			print_state(philo, DIED);
			philo->state = STARVED;
			break ;
		}
		if (philo->arg->num_to_eat > 0 && \
			philo->arg->num_to_eat < philo->eat_count)
		{
			philo->state = END;
			break ;
		}
		sem_post(philo->sem->sem_monitor);
		usleep(5000);
	}
	sem_post(philo->sem->sem_state);
	return (NULL);
}
