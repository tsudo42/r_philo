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
		return ;
	sem_post(philo->sem->sem_printer);
}

static int	start(t_philo *philo)
{
	pthread_t	monitor_thread;

	philo->last_eat = get_time();
	philo->starve_time = philo->last_eat + philo->arg->time_to_die;
	if (pthread_create(&monitor_thread, NULL, monitor, philo) != 0 || \
		pthread_detach(monitor_thread) != 0)
	{
		exit(PTHREAD_ERR);
	}
	if (philo->start_delay != 0)
	{
		print_state(philo, THINKING);
		my_usleep(philo->start_delay);
	}
	return (0);
}

static int	check_alive(t_philo *philo)
{
	int	ret;

	ret = (philo->state == ALIVE);
	return (ret);
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
	philo->last_eat = time + philo->arg->time_to_eat;
	philo->starve_time = time + philo->arg->time_to_die;
	philo->eat_count++;
	print_state(philo, EAT);
	\
	my_usleep(philo->arg->time_to_eat * 1000);
	sem_post(philo->sem->sem_fork);
	sem_post(philo->sem->sem_fork);
	return (0);
}

void	philo_loop(void *ptr)
{
	t_philo		*philo;

	philo = ptr;
	start(philo);
	while (check_alive(philo))
	{
		eat(philo);
		print_state(philo, SLEEP);
		my_usleep(philo->arg->time_to_sleep * 1000);
		print_state(philo, THINKING);
	}
	exit(END);
}
