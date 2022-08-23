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

int	join_philo(t_data *data)
{
	int	i;
	int	state;

	debug_write("joining philo...\n");
	i = 0;
	while (i < data->arg.num_philo)
	{
		if (data->philo[i].state != UNLAUNCHED && data->philo[i].pid > 0)
			kill(data->philo[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	while (i < data->arg.num_philo)
	{
		if (data->philo[i].state != UNLAUNCHED)
		{
			waitpid(data->philo[i].pid, &state, WUNTRACED);
			data->philo[i].state = state;
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
	if (data->sem.sem_state)
		ret |= sem_close(data->sem.sem_state);
	if (data->sem.sem_fork)
		ret |= sem_close(data->sem.sem_fork);
	if (data->sem.sem_printer)
		ret |= sem_close(data->sem.sem_printer);
	ret |= sem_unlink(SEM_STATE_NAME);
	ret |= sem_unlink(SEM_FORK_NAME);
	ret |= sem_unlink(SEM_PRINTER_NAME);
	return (ret);
}

int	print_error(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.num_philo)
	{
		if (data->philo[i].state == PTHREAD_ERR)
		{
			write(STDERR_FILENO, ERRMSG_PTHREAD, ft_strlen(ERRMSG_PTHREAD));
			return (-1);
		}
		i++;
	}
	return (0);
}

int	cleanup(t_data *data)
{
	join_philo(data);
	cleanup_sem(data);
	return (print_error(data));
}
