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

int	cleanup_sem(t_data *data)
{
	int	ret;

	ret = 0;
	if (data->sem.sem_fork)
		ret |= sem_close(data->sem.sem_fork);
	if (data->sem.sem_printer)
		ret |= sem_close(data->sem.sem_waiter);
	if (data->sem.sem_printer)
		ret |= sem_close(data->sem.sem_printer);
	ret |= sem_unlink(SEM_FORK_NAME);
	ret |= sem_unlink(SEM_WAITER_NAME);
	ret |= sem_unlink(SEM_PRINTER_NAME);
	return (ret);
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
