/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_ratio_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:19:39 by user              #+#    #+#             */
/*   Updated: 2023/05/02 00:00:58 by user             ###   ########.fr       */
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

double  calc_ratio_cylinder(t_vecinf *eye2scr, t_allinfs *infs, t_cylinder *cylinder)
{
    t_vecinf    center2eye;
    t_vecinf    dn_oupro;
    t_vecinf    pn_oupro;
    double      discriminant;

    neg_vec(&center2eye, &infs->fix_vecs->eye_v->vec, &cylinder->center_v->vec);
    calc_outerproduct(&dn_oupro, &eye2scr->vec, &cylinder->center_n_v->u_vec);
    calc_outerproduct(&pn_oupro, &center2eye.vec, &cylinder->center_n_v->u_vec);
	if (ch_eye2cylinder_its(eye2scr, infs, cylinder) == true)
    {
        discriminant = pow(2 * dot_vec(&dn_oupro.vec, &pn_oupro.vec), 2) - 4 * pow(dn_oupro.size, 2) * (pow(pn_oupro.size, 2) - pow(cylinder->rad, 2));
		return (calc_ratio(pow(dn_oupro.size, 2), 2 * dot_vec(&dn_oupro.vec, &pn_oupro.vec), discriminant));
    }
	return (-1.0);
}