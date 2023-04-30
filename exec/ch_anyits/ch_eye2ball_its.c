/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_eye2ball_its.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:05:04 by user              #+#    #+#             */
/*   Updated: 2023/04/30 17:58:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

bool    ch_eye2ball_its(t_vecinf *eye2scr, t_allinfs *infs, t_ball *ball)
{
    t_vecinf    ballcenter2eye;
    double      coefficient_A;
	double      coefficient_B;
	double      coefficient_C;
    
    neg_vec(&ballcenter2eye, &infs->fix_vecs->eye_v->vec, &ball->center_v->vec);
    coefficient_A = pow(eye2scr->size, 2);
	coefficient_B = 2 * (dot_vec(&ballcenter2eye.vec, &eye2scr->vec));
	coefficient_C = pow(ballcenter2eye.size, 2) - pow(ball->rad, 2);
    if ((pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C) >= 0)
        return (true);
    return (false);
}