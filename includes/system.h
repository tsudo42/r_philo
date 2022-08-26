/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_H
# define SYSTEM_H

# include "defs.h"
# include "philo.h"
# include "utils.h"
# include "debug.h"

int		ready(t_data *data, int argc, char **argv);
int		launch(t_data *data);
void	calc_delay(t_data *data, int num_philo);
int		cleanup(t_data *data);

int		ready_mutex(t_data *data);
int		cleanup_mutex(t_data *data);

#endif /* SYSTEM_H */
