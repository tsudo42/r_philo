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

void	print_state(t_philo *philo, t_action action)
{
	static long	start_time = -1;
	static int	is_end = 0;
	const char	*strs[] = {
		"%lu %d has taken a fork\n",
		"%lu %d is eating\n",
		"%lu %d is sleeping\n",
		"%lu %d is thinking\n",
		"%lu %d died\n",
	};

	pthread_mutex_lock(philo->printer);
	if (philo->state == STARVED || philo->state == PTHREAD_ERR)
		is_end = 1;
	if (!is_end)
	{
		if (start_time < 0)
			start_time = get_time();
		printf(strs[action], get_time() - start_time, philo->index);
		if (action == DIED)
			is_end = 1;
	}
	else
		philo->state = END;
	pthread_mutex_unlock(philo->printer);
}

static int	check_end(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->state_lock);
	ret = (philo->state != ALIVE);
	pthread_mutex_unlock(philo->state_lock);
	return (ret);
}

static int	eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->fork_first);
	print_state(philo, TAKE_FORK);
	pthread_mutex_lock(philo->fork_second);
	print_state(philo, TAKE_FORK);
	pthread_mutex_lock(philo->state_lock);
	time = get_time();
	philo->last_eat = time + philo->arg->time_to_eat;
	philo->starve_time = time + philo->arg->time_to_die;
	philo->eat_count++;
	print_state(philo, EAT);
	pthread_mutex_unlock(philo->state_lock);
	my_sleep(philo->arg->time_to_eat);
	pthread_mutex_unlock(philo->fork_second);
	pthread_mutex_unlock(philo->fork_first);
	return (0);
}

void	*philo_loop(void *ptr)
{
	t_philo		*philo;
	pthread_t	monitor_thread;

	philo = ptr;
	philo->last_eat = get_time();
	philo->starve_time = philo->last_eat + philo->arg->time_to_die;
	print_state(philo, THINKING);
	if (pthread_create(&monitor_thread, NULL, monitor, philo) != 0)
	{
		philo->state = PTHREAD_ERR;
		print_state(philo, DIED);
		return (NULL);
	}
	while (!check_end(philo))
	{
		eat(philo);
		print_state(philo, SLEEP);
		my_sleep(philo->arg->time_to_sleep);
		print_state(philo, THINKING);
	}
	pthread_join(monitor_thread, NULL);
	return (NULL);
}
