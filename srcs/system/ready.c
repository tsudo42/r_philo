/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

long	get_num(char *str, int min, int max, int *is_error)
{
	long	num;
	char	*endptr;

	if (*is_error)
		return (-1);
	num = ft_strtol(str, &endptr, 10);
	if (num < min || max < num || *endptr != '\0')
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": ", ft_strlen(": "));
		if (num > max)
			write(STDERR_FILENO, ERRMSG_TOOBIG, ft_strlen(ERRMSG_TOOBIG));
		else
			write(STDERR_FILENO, ERRMSG_INVAL, ft_strlen(ERRMSG_INVAL));
		*is_error = 1;
		return (-1);
	}
	return (num);
}

int	set_arg(t_arg *arg, int argc, char **argv)
{
	int	is_error;

	if (argc < 5 || 6 < argc)
	{
		write(STDERR_FILENO, ERRMSG_INVAL, ft_strlen(ERRMSG_INVAL));
		return (-1);
	}
	is_error = 0;
	arg->num_philo = get_num(argv[1], 1, MAX_PHILO, &is_error);
	arg->time_to_die = get_num(argv[2], 0, INT_MAX / 100000, &is_error);
	arg->time_to_eat = get_num(argv[3], 0, INT_MAX / 100000, &is_error);
	arg->time_to_sleep = get_num(argv[4], 0, INT_MAX / 100000, &is_error);
	if (argc == 6)
		arg->num_to_eat = get_num(argv[5], 0, INT_MAX / 100000, &is_error);
	else
		arg->num_to_eat = -1;
	if (is_error)
		exit(1);
	return (0);
}

int	ready_sem(t_data *data)
{
	int	num_philo;

	num_philo = data->arg.num_philo;
	errno = 0;
	data->sem.sem_state = sem_open(SEM_STATE_NAME, O_CREAT, 0644, 0);
	data->sem.sem_fork = sem_open(SEM_FORK_NAME, O_CREAT, 0644, num_philo);
	data->sem.sem_printer = sem_open(SEM_PRINTER_NAME, O_CREAT, 0644, 1);
	if (errno != 0)
	{
		write(STDERR_FILENO, ERRMSG_SEM, ft_strlen(ERRMSG_SEM));
		cleanup_sem(data);
		exit(1);
	}
	return (0);
}

void	setup_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.num_philo)
	{
		data->philo[i].index = i + 1;
		data->philo[i].state = UNLAUNCHED;
		data->philo[i].arg = &data->arg;
		data->philo[i].sem = &data->sem;
		i++;
	}
}

int	ready(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	set_arg(&data->arg, argc, argv);
	ready_sem(data);
	setup_philo(data);
	return (0);
}
