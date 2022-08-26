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
	arg->time_to_die = get_num(argv[2], 0, INT_MAX / 10, &is_error);
	arg->time_to_eat = get_num(argv[3], 0, INT_MAX / 10, &is_error);
	arg->time_to_sleep = get_num(argv[4], 0, INT_MAX / 10, &is_error);
	if (argc == 6)
		arg->num_to_eat = get_num(argv[5], 0, INT_MAX / 10, &is_error);
	else
		arg->num_to_eat = -1;
	return (is_error);
}

void	setup_philo_fork(t_data *data, int i, int num_philo)
{
	if (num_philo % 2)
	{
		if (i == 0)
		{
			data->philo[i].fork_first = &(data->fork[0]);
			data->philo[i].fork_second = &(data->fork[num_philo - 1]);
		}
		else
		{
			data->philo[i].fork_first = &(data->fork[i - 1]);
			data->philo[i].fork_second = &(data->fork[i]);
		}
		return ;
	}
	if (i % 2)
	{
		data->philo[i].fork_first = &(data->fork[(i + 1) % num_philo]);
		data->philo[i].fork_second = &(data->fork[i]);
	}
	else
	{
		data->philo[i].fork_first = &(data->fork[i]);
		data->philo[i].fork_second = &(data->fork[i + 1]);
	}
}

void	setup_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg.num_philo)
	{
		data->philo[i].index = i + 1;
		data->philo[i].state = UNLAUNCHED;
		data->philo[i].state_lock = &(data->philo_state[i]);
		\
		setup_philo_fork(data, i, data->arg.num_philo);
		\
		data->philo[i].printer = &data->printer;
		data->philo[i].arg = &data->arg;
		i++;
	}
}

int	ready(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	if (set_arg(&data->arg, argc, argv) != 0)
		return (-1);
	if (ready_mutex(data) != 0)
	{
		write(STDERR_FILENO, ERRMSG_MUTEX, ft_strlen(ERRMSG_MUTEX));
		return (-1);
	}
	setup_philo(data);
	return (0);
}
