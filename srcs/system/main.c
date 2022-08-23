/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "system.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (ready(&data, argc, argv) != 0)
		return (1);
	launch(&data);
	debug_write("launched!\n");
	pthread_mutex_lock(&data.system_active);
	pthread_mutex_unlock(&data.system_active);
	cleanup(&data);
	debug_write("checking leaks...\n");
	return (0);
}