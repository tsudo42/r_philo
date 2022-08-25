/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

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

int	ready_sem(t_data *data)
{
	int	num_philo;

	cleanup_sem(data);
	num_philo = data->arg.num_philo;
	errno = 0;
	data->sem.sem_fork = \
		sem_open(SEM_FORK_NAME, O_CREAT | O_EXCL, 0644, num_philo / 2);
	data->sem.sem_waiter = \
		sem_open(SEM_WAITER_NAME, O_CREAT | O_EXCL, 0644, 0);
	data->sem.sem_printer = \
		sem_open(SEM_PRINTER_NAME, O_CREAT | O_EXCL, 0644, 1);
	if (errno != 0)
	{
		write(STDERR_FILENO, ERRMSG_SEM, ft_strlen(ERRMSG_SEM));
		cleanup_sem(data);
		exit(1);
	}
	return (0);
}
