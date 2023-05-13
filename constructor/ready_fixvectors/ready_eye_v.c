/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_eye_v.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 14:57:01 by user              #+#    #+#             */
/*   Updated: 2023/05/04 03:35:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void    ready_eye_v(t_fvec *fvecs)
{
    fvecs->eye_v = malloc(sizeof(t_eyevec_inf) * 1);
    fvecs->eye_v->eye_position = malloc(sizeof(t_vecinf) * 1);
    set_vec(fvecs->eye_v->eye_position, 3.0, 3.0, 3.0);
    fvecs->eye_v->eye_dim_vec = malloc(sizeof(t_vecinf) * 1);
    set_vec(fvecs->eye_v->eye_dim_vec, 0.0, -1.0, 0.0);
    fvecs->eye_v->FOV = 90;
}