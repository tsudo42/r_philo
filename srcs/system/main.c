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

#if DEBUG

int	debug_check_leak(void)
{
	debug_write("checking leaks...\n");
	return (system("leaks philo"));
}

#else /* DEBUG*/

int	debug_check_leak(void)
{
	return (0);
}

#endif /* DEBUG*/

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	if (ready(&data, argc, argv) != 0)
		return (1);
	launch(&data);
	debug_write("launched!\n");
	ret = cleanup(&data);
	debug_check_leak();
	return (ret);
}
