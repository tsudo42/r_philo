/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* philo->state_lock should be locked upon print_state() call. */
void	print_state(t_philo *philo, t_action action)
{
	const char	*strs[] = {
		"%lu %d has taken a fork\n",
		"%lu %d is eating\n",
		"%lu %d is sleeping\n",
		"%lu %d is thinking\n",
		"%lu %d died\n",
	};

	sem_wait(philo->sem->sem_printer);
	printf(strs[action], get_time() - philo->start_time, philo->index);
	if (action == DIED)
	{
		kill(philo->waiter_pid, SIGTERM);
		exit(0);
	}
	sem_post(philo->sem->sem_printer);
}

static int	start(t_philo *philo)
{
	philo->last_eat = get_time();
	philo->starve_time = philo->last_eat + philo->arg->time_to_die;
	if (philo->arg->num_philo == 1)
	{
		if (philo->arg->num_to_eat == 0)
			sem_post(philo->sem->sem_waiter);
		print_state(philo, TAKE_FORK);
		while (1)
			monitoring_usleep(philo, philo->arg->time_to_die);
	}
	if (philo->start_delay != 0)
	{
		print_state(philo, THINKING);
		monitoring_usleep(philo, philo->start_delay);
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	long	time;

	sem_wait(philo->sem->sem_fork);
	print_state(philo, TAKE_FORK);
	sem_wait(philo->sem->sem_fork);
	print_state(philo, TAKE_FORK);
	\
	time = get_time();
	if (philo->last_eat < time && philo->starve_time < time)
		print_state(philo, DIED);
	philo->last_eat = time + philo->arg->time_to_eat;
	philo->starve_time = time + philo->arg->time_to_die;
	philo->eat_count++;
	if (philo->arg->num_to_eat > 0 && \
		philo->arg->num_to_eat <= philo->eat_count)
	{
		sem_post(philo->sem->sem_waiter);
		philo->arg->num_to_eat = -1;
	}
	print_state(philo, EAT);
	\
	monitoring_usleep(philo, philo->arg->time_to_eat * 1000);
	sem_post(philo->sem->sem_fork);
	sem_post(philo->sem->sem_fork);
	return (0);
}

void	philo_loop(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	start(philo);
	while (1)
	{
		eat(philo);
		print_state(philo, SLEEP);
		monitoring_usleep(philo, philo->arg->time_to_sleep * 1000);
		print_state(philo, THINKING);
		if (philo->think_delay)
			monitoring_usleep(philo, philo->think_delay * 1000);
	}
}
