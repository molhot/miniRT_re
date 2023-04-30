/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGB_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 00:02:49 by user              #+#    #+#             */
/*   Updated: 2023/05/01 00:03:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void    init_RGB(t_RGB *RGB)
{
    RGB->red = 0.0;
    RGB->green = 0.0;
    RGB->blue = 0.0;
}

void   cal_RGB(t_RGB *origin_RGB, t_RGB *add_RGB, double k)
{
    origin_RGB->red = origin_RGB->red + add_RGB->red * k;
    origin_RGB->green = origin_RGB->green + add_RGB->green * k;
    origin_RGB->blue = origin_RGB->blue + add_RGB->blue * k;
}