/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_ratio_ball.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:27:46 by user              #+#    #+#             */
/*   Updated: 2023/05/04 01:00:04 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static double  calc_ratio(double A, double B, double D)
{
    double	one_ans;
	double	sec_ans;

	if (D == 0)
		return ((-1 * B) / (2 * A));
	one_ans = ((-1 * B) + sqrt(D)) / (2 * A);
	sec_ans = ((-1 * B) - sqrt(D)) / (2 * A);
	if (one_ans < 0 && sec_ans < 0)
		return (-1);
	if (one_ans < 0 && sec_ans > 0)
		return (sec_ans);
	else if (one_ans > 0 && sec_ans < 0)
		return (one_ans);
	if (one_ans > sec_ans)
		return (sec_ans);
	return (one_ans);
}

double  calc_ratio_ball(t_vecinf *eye2scr, t_allinfs *infs, t_ball *ball)
{
    t_vecinf	ballmid2eye;
    double      coefficient_A;
	double      coefficient_B;
	double      coefficient_C;
    double      discriminant;

	neg_vec(&ballmid2eye, &infs->fix_vecs->eye_v->eye_position->vec, &ball->center_v->vec);
    coefficient_A = pow(eye2scr->size, 2);
	coefficient_B = 2 * (dot_vec(&ballmid2eye.vec, &eye2scr->vec));
	coefficient_C = pow(ballmid2eye.size, 2) - pow(ball->rad, 2);
    discriminant = pow(coefficient_B, 2) - 4 * coefficient_A * coefficient_C;
	if (discriminant >= 0)
		return (calc_ratio(coefficient_A, coefficient_B, discriminant));
	return (-1.0);
}