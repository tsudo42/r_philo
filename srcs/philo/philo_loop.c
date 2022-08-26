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
	else if (philo->state == ALIVE)
		philo->state = END;
	pthread_mutex_unlock(philo->printer);
}

static int	start(t_philo *philo)
{
	pthread_mutex_lock(philo->state_lock);
	philo->last_eat = get_time();
	philo->starve_time = philo->last_eat + philo->arg->time_to_die;
	pthread_mutex_unlock(philo->state_lock);
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

	pthread_mutex_lock(philo->state_lock);
	ret = (philo->state == ALIVE);
	pthread_mutex_unlock(philo->state_lock);
	return (ret);
}

static int	eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->fork_first);
	pthread_mutex_lock(philo->state_lock);
	print_state(philo, TAKE_FORK);
	pthread_mutex_unlock(philo->state_lock);
	\
	pthread_mutex_lock(philo->fork_second);
	pthread_mutex_lock(philo->state_lock);
	print_state(philo, TAKE_FORK);
	pthread_mutex_unlock(philo->state_lock);
	\
	pthread_mutex_lock(philo->state_lock);
	time = get_time();
	philo->last_eat = time + philo->arg->time_to_eat;
	philo->starve_time = time + philo->arg->time_to_die;
	philo->eat_count++;
	print_state(philo, EAT);
	pthread_mutex_unlock(philo->state_lock);
	\
	my_usleep(philo->arg->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_second);
	pthread_mutex_unlock(philo->fork_first);
	return (0);
}

void	*philo_loop(void *ptr)
{
	t_philo		*philo;

	philo = ptr;
	if (start(philo) != 0)
		return (NULL);
	while (1)
	{
		if (!check_alive(philo))
			return (NULL);
		eat(philo);
		if (!check_alive(philo))
			return (NULL);
		pthread_mutex_lock(philo->state_lock);
		print_state(philo, SLEEP);
		pthread_mutex_unlock(philo->state_lock);
		my_usleep(philo->arg->time_to_sleep * 1000);
		if (!check_alive(philo))
			return (NULL);
		pthread_mutex_lock(philo->state_lock);
		print_state(philo, THINKING);
		pthread_mutex_unlock(philo->state_lock);
		if (philo->think_delay)
			my_usleep(philo->think_delay);
	}
	return (NULL);
}
