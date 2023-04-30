/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:31:52 by user              #+#    #+#             */
/*   Updated: 2023/04/30 16:31:28 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void    add_vec(t_vecinf *sub, t_vec *v1, t_vec *v2)
{
	set_vec(sub, v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}

void	neg_vec(t_vecinf *sub, t_vec *v1, t_vec *v2)
{
	set_vec(sub, v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}

double	dot_vec(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

void	calc_outerproduct(t_vecinf *sub, t_vec *v1, t_vec *v2)
{
	set_vec(sub,
		v1->y * v2->z - v1->z * v2->y,
		v1->z * v2->x - v1->x * v2->z,
		v1->x * v2->y - v1->y * v2->x
	);
}

void    t_mix_vec(t_vecinf *sub, t_vec *v1, double t, t_vec *v2)
{
    set_vec(
        sub, \
        v1->x + t * v2->x, \
        v1->y + t * v2->y, \
        v1->z + t * v2->z
    );
}

void    t_neg_vec(t_vecinf *sub, t_vec *v1, double t, t_vec *v2)
{
    set_vec(
        sub, \
        v1->x - t * v2->x, \
        v1->y - t * v2->y, \
        v1->z - t * v2->z
    );
}

void    t_mix_vec_all(t_vecinf *sub, double t1, t_vec *v1, double t2, t_vec *v2)
{
    set_vec(
        sub, \
        t1 * v1->x + t2 * v2->x, \
        t1 * v1->y + t2 * v2->y, \
        t1 * v1->z + t2 * v2->z
    );
}