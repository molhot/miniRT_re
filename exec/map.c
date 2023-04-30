/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 22:59:00 by user              #+#    #+#             */
/*   Updated: 2023/04/30 23:59:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static double	constrain(double num, double min, double max)
{
	if (min > num)
		return (min);
	else if (min <= num && num <= max)
		return (num);
	else
		return (max);
}

double map(double num, double min, double max, double t_min, double t_max)
{
	double	constrain_num;
	double	tmp;

	constrain_num = constrain(num, min, max);
	tmp = t_min + (t_max - t_min) * constrain_num / (max - min);
	if (tmp < t_min)
		return (t_min);
	else
		return (tmp);
}