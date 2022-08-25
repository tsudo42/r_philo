/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	wait_philo(t_data *data)
{
	int	i;
	int	state;

	debug_write("killing philo...\n");
	i = 0;
	while (i < data->arg.num_philo)
	{
		if (data->philo[i].state != NOT_RUNNING && data->philo[i].pid > 0)
			kill(data->philo[i].pid, SIGTERM);
		i++;
	}
	i = 0;
	debug_write("joining philo...\n");
	while (i < data->arg.num_philo)
	{
		if (data->philo[i].state == ALIVE)
		{
			data->philo[i].state = KILLED;
			if (waitpid(data->philo[i].pid, &state, WUNTRACED) < 0)
				data->philo[i].state = ANY_ERROR;
		}
		i++;
	}
	debug_write("joined!\n");
	return (0);
}

int	print_error(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.num_philo)
	{
		if (data->philo[i].state == ANY_ERROR)
		{
			write(STDERR_FILENO, ERRMSG_ANY, ft_strlen(ERRMSG_ANY));
			return (-1);
		}
		i++;
	}
	return (0);
}

int	cleanup(t_data *data)
{
	wait_philo(data);
	cleanup_sem(data);
	return (print_error(data));
}
