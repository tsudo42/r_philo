/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_usleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring_usleep(t_philo *philo, unsigned long us)
{
	struct timeval	now;
	struct timeval	end;
	long			time;

	gettimeofday(&end, NULL);
	end.tv_usec += us;
	if (end.tv_usec >= 1000000)
	{
		end.tv_sec += (end.tv_usec / 1000000);
		end.tv_usec = end.tv_usec % 1000000;
	}
	while (1)
	{
		gettimeofday(&now, NULL);
		if (now.tv_sec > end.tv_sec || \
		(now.tv_sec == end.tv_sec && now.tv_usec >= end.tv_usec))
			return ;
		time = now.tv_sec * 1000UL + now.tv_usec / 1000;
		if (philo->last_eat < time && philo->starve_time < time)
			print_state(philo, DIED);
		usleep(50);
	}
}
