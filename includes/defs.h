/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

# define MAX_PHILO 256

# define ERRMSG_INVAL	"invalid argument\n"
# define ERRMSG_TOOBIG	"argument too big\n"
# define ERRMSG_MUTEX	"error on mutex\n"
# define ERRMSG_PTHREAD	"error on pthread\n"

# define MY_DEBUG 0

typedef enum e_action {
	TAKE_FORK	= 0,
	EAT			= 1,
	SLEEP		= 2,
	THINKING	= 3,
	DIED		= 4,
}	t_action;

typedef enum e_state {
	ALIVE		= 0,
	STARVED		= 1,
	END			= 2,
	UNLAUNCHED	= 3,
	PTHREAD_ERR	= 4
}	t_state;

typedef struct s_arg{
	int		num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		num_to_eat;
}	t_arg;

typedef struct s_philo
{
	int				index;
	pthread_t		thread;
	unsigned long	start_delay;
	unsigned long	think_delay;
	int				eat_count;
	long			starve_time;
	long			last_eat;
	t_state			state;
	pthread_mutex_t	*state_lock;
	pthread_mutex_t	*fork_first;
	pthread_mutex_t	*fork_second;
	pthread_mutex_t	*printer;
	t_arg			*arg;
}	t_philo;

typedef struct s_data
{
	t_arg			arg;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	philo_state[MAX_PHILO];
	pthread_mutex_t	fork[MAX_PHILO];
	pthread_mutex_t	printer;
	pthread_t		monitor_thread;
	int				monitor_launched;
}	t_data;

#endif /* DEFS_H */
