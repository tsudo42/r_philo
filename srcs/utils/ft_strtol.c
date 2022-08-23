/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/07 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <errno.h>

/* ************************************************************************** */
/*  Determine base if base is 0(automatically configured), and read prefix.   */
/*  Status: 0 means read nothing, 1 means successfully reading, -1 means OVF  */
/*  In order to recognize 0 as valid value, status is set to 1.               */
/* ************************************************************************** */
static int	strtol_read_base(const char **str_ptr, int base, int *status)
{
	const char	*str;

	*status = 0;
	str = *str_ptr;
	if (base == 0 || base == 16)
	{
		if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X') && \
			ft_isxdigit(str[2]))
		{
			*str_ptr += 2;
			return (16);
		}
	}
	if (base == 0)
	{
		if (str[0] == '0')
		{
			*str_ptr += 1;
			*status = 1;
			return (8);
		}
		return (10);
	}
	return (base);
}

/* ************************************************************************** */
/*  If (prev_val * base + next_d > LONG_MAX or abs(LONG_MIN)), returns -1.    */
/* ************************************************************************** */
static int	strtol_check_overflow( \
	unsigned long prev_val, unsigned int next_d, int base, int sign)
{
	unsigned long	max_div;
	unsigned long	max_mod;

	if (sign > 0)
	{
		max_div = LONG_MAX / base;
		max_mod = LONG_MAX % base;
	}
	else
	{
		max_div = -(unsigned long)LONG_MIN / base;
		max_mod = -(unsigned long)LONG_MIN % base;
	}
	if (prev_val > max_div)
		return (-1);
	if (prev_val == max_div && next_d > max_mod)
		return (-1);
	return (1);
}

/* ************************************************************************** */
/*  Returns read value. If read alnum is equal to/more than base, break ;.    */
/*  Status: 0 means read nothing, 1 means successfully reading, -1 means OVF  */
/* ************************************************************************** */
static unsigned long	strtol_read_value( \
	const char **str, int base, int sign, int *status)
{
	unsigned long	val;
	unsigned int	d;

	val = 0;
	while (**str != '\0')
	{
		if (ft_isdigit(**str))
			d = **str - '0';
		else if (ft_islower(**str))
			d = **str - 'a' + 10;
		else if (ft_isupper(**str))
			d = **str - 'A' + 10;
		else
			break ;
		if ((int)d >= base)
			break ;
		if (*status != -1)
			*status = strtol_check_overflow(val, d, base, sign);
		if (*status != -1)
			val = val * base + d;
		(*str)++;
	}
	return (val);
}

/* ************************************************************************** */
/*  Status: 0 means read nothing, 1 means successfully reading, -1 means OVF  */
/*  If read any alnum, endptr points to the next char after alnum string.     */
/* ************************************************************************** */
static long	ft_strtol_helper(const char *str, char **endptr, int base)
{
	int				sign;
	unsigned long	val;
	int				status;

	while (ft_isspace((unsigned char)*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	base = strtol_read_base(&str, base, &status);
	val = strtol_read_value(&str, base, sign, &status);
	if (status != 0)
		*endptr = (char *)str;
	if (status == -1)
	{
		errno = ERANGE;
		if (sign > 0)
			return (LONG_MAX);
		return (LONG_MIN);
	}
	else if (sign == -1)
		return (-val);
	return (val);
}

/* ************************************************************************** */
/*  This function mimics the original strtol (c.f. man 3 strtol).             */
/*  If str points to NULL or base is invalid (other than 0=auto or 2~36),     */
/*  errno is set to EINVAL.                                                   */
/* ************************************************************************** */
long	ft_strtol(const char *str, char **endptr, int base)
{
	long	val;
	char	*endptr_tmp;

	if (str == NULL || base < 0 || base == 1 || 36 < base)
	{
		errno = EINVAL;
		return (0);
	}
	endptr_tmp = (char *)str;
	val = ft_strtol_helper(str, &endptr_tmp, base);
	if (endptr_tmp == str)
		errno = EINVAL;
	if (endptr != NULL)
		*endptr = endptr_tmp;
	return (val);
}
