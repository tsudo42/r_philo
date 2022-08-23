/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:18:19 by tsudo             #+#    #+#             */
/*   Updated: 2022/03/04 15:48:51 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/* ************************************************************************** */
/*  This function returns if #arg1 is a number character.                     */
/*  48 means '0' and 57 means '9'.                                            */
/* ************************************************************************** */
int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}
