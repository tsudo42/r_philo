/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	launch_philo(t_data *data, int num_philo)
{
	int				i;
	t_philo			*philo;
	unsigned long	now;

	now = get_time();
	i = 0;
	while (i < num_philo)
	{
		philo = &(data->philo[i]);
		philo->state = ALIVE;
		philo->start_time = now;
		philo->pid = fork();
		if (philo->pid == 0)
			philo_loop(philo);
		if (philo->pid < 0)
		{
			philo->state = NOT_RUNNING;
			break ;
		}
		i++;
	}
	if (i == num_philo)
		return (0);
	return (-1);
}

void	waiter(t_data *data)
{
	int	i;

	debug_write("waiter activated\n");
	i = 0;
	while (i < data->arg.num_philo)
	{
		if (sem_wait(data->sem.sem_waiter))
		{
			write(STDERR_FILENO, ERRMSG_ANY, ft_strlen(ERRMSG_ANY));
			exit(1);
		}
		i++;
	}
	debug_write("waiter finished\n");
	exit(0);
}

int	launch(t_data *data)
{
	pid_t	waiter_pid;
	int		i;

	waiter_pid = fork();
	if (waiter_pid < 0)
	{
		write(STDERR_FILENO, ERRMSG_ANY, ft_strlen(ERRMSG_ANY));
		cleanup_sem(data);
		exit(1);
	}
	if (waiter_pid == 0)
		waiter(data);
	i = 0;
	while (i < data->arg.num_philo)
	{
		data->philo[i].waiter_pid = waiter_pid;
		i++;
	}
	calc_delay(data, data->arg.num_philo);
	if (launch_philo(data, data->arg.num_philo) != 0)
		kill(waiter_pid, SIGTERM);
	debug_write("launched!\n");
	waitpid(waiter_pid, NULL, WUNTRACED);
	return (0);
}
