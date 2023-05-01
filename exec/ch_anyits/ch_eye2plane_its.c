/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_eye2plane_its.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 10:17:14 by user              #+#    #+#             */
/*   Updated: 2023/05/01 11:08:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

bool    ch_eye2plane_its(t_vecinf *eye2scr, t_allinfs *infs, t_plane *plane)
{
    double  onepoint_n;
    double  eye_n;
    double  eye2scr_n;

    onepoint_n = dot_vec(&plane->point->vec, &plane->n->vec);
    eye_n = dot_vec(&infs->fix_vecs->eye_v->vec, &plane->n->vec);
    eye2scr_n = dot_vec(&eye2scr->vec , &plane->n->vec);
    if (eye2scr_n == 0.0)
        return (false);
    if ((onepoint_n - eye_n) / eye2scr_n <= 0)
        return (false);
    return (true);
}