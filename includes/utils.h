/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "defs.h"

int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isspace(int c);
int				ft_isupper(int c);
int				ft_isxdigit(int c);
long			ft_strtol(const char *str, char **endptr, int base);
size_t			ft_strlen(const char *s);

#endif /* UTILS_H */
