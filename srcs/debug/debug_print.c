/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	debug_write(const char *str)
{
	if (MY_DEBUG)
	{
		return (write(STDERR_FILENO, str, ft_strlen(str)));
	}
	return (0);
}

int	debug_locked_write(const char *str, pthread_mutex_t *mutex)
{
	int	ret;

	if (MY_DEBUG)
	{
		pthread_mutex_unlock(mutex);
		ret = write(STDERR_FILENO, str, ft_strlen(str));
		pthread_mutex_lock(mutex);
		return (ret);
	}
	return (0);
}
