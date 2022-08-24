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
# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <signal.h>

# define MAX_PHILO 256

# define ERRMSG_INVAL	"invalid argument\n"
# define ERRMSG_TOOBIG	"argument too big\n"
# define ERRMSG_SEM		"error on semaphore\n"
# define ERRMSG_ANY		"fatal error\n"

# define MY_DEBUG 1

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
	OVER		= 2,
	KILLED		= 3,
	NOT_RUNNING	= 4,
	ANY_ERROR	= 5
}	t_state;

typedef struct s_arg{
	int		num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		num_to_eat;
}	t_arg;

# define SEM_STATE_NAME		"/sem_state"
# define SEM_FORK_NAME		"/sem_fork"
# define SEM_PRINTER_NAME	"/sem_printer"

typedef struct s_sem_set {
	sem_t			*sem_state;
	sem_t			*sem_fork;
	sem_t			*sem_printer;
}	t_sem_set;

typedef struct s_philo
{
	int				index;
	pid_t			pid;
	unsigned long	start_time;
	unsigned long	start_delay;
	long			think_delay;
	int				eat_count;
	long			starve_time;
	long			last_eat;
	t_state			state;
	t_arg			*arg;
	t_sem_set		*sem;
}	t_philo;

typedef struct s_data
{
	t_arg		arg;
	t_philo		philo[MAX_PHILO];
	t_sem_set	sem;
}	t_data;

#endif /* DEFS_H */
