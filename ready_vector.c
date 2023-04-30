/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:31:50 by user              #+#    #+#             */
/*   Updated: 2023/04/30 15:01:02 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static  void    vecset(t_vec *vec, double x, double y, double z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static  void    sizeset(double *size, double x, double y, double z)
{
    *size = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

static  void    u_vecset(t_vec *vec, double size, double x, double y, double z)
{
    vecset(vec, x / size, y / size, z / size);
}

void    set_vec(t_vecinf *vec, double x, double y, double z)
{
    vecset(&vec->vec, x, y, z);
    sizeset(&vec->size, x, y, z);
    u_vecset(&vec->u_vec, vec->size, x, y, z);
}