/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(unsigned long us)
{
	struct timeval	now;
	struct timeval	end;

	gettimeofday(&end, NULL);
	end.tv_sec += us / 1000000;
	end.tv_usec += us % 1000000;
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
		usleep(50);
	}
}
