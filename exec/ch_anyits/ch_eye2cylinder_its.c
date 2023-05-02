/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_eye2cylinder_its.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:19:42 by user              #+#    #+#             */
/*   Updated: 2023/05/03 01:54:44 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static double  calc_ratio_2(double A, double B, double D)
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

static  bool    ch_its_overcylinder(t_vecinf *eye2scr, double t, t_cylinder *cylinder, t_allinfs *infs)
{
    t_vecinf    its_v;
    t_vecinf    center2its;
    double      n_center2its_dot;

    t_mix_vec(&its_v, &infs->fix_vecs->eye_v->vec, t, &eye2scr->vec);
    neg_vec(&center2its, &its_v.vec, &cylinder->center_v->vec);
    n_center2its_dot = dot_vec(&center2its.vec, &cylinder->center_n_v->u_vec);
    if (n_center2its_dot < 0)
        return (false);
    if (n_center2its_dot > cylinder->height)
        return (false);
    return (true);
}

static  bool    ch_cylinder_its_helper(t_vecinf *dn_oupro, t_vecinf *pn_oupro, t_cylinder *cylinder, t_vecinf *eye2scr, t_allinfs *infs)
{
    double  A;
    double  B;
    double  C;
    double  D;

    A = pow(dn_oupro->size, 2);
    B = 2 * dot_vec(&dn_oupro->vec, &pn_oupro->vec);
    C = pow(pn_oupro->size, 2) - pow(cylinder->rad, 2);
    D = pow(B, 2) - 4 * A * C;
    if (dn_oupro->size == 0 || D < 0)
        return (false);
    return (ch_its_overcylinder(eye2scr, calc_ratio_2(A, B, D), cylinder, infs));
}

bool    ch_eye2cylinder_its(t_vecinf *eye2scr, t_allinfs *infs, t_cylinder *cylinder)
{
    t_vecinf    center2eye;
    t_vecinf    dn_oupro;
    t_vecinf    pn_oupro;

    neg_vec(&center2eye, &infs->fix_vecs->eye_v->vec, &cylinder->center_v->vec);
    calc_outerproduct(&dn_oupro, &eye2scr->vec, &cylinder->center_n_v->u_vec);
    calc_outerproduct(&pn_oupro, &center2eye.vec, &cylinder->center_n_v->u_vec);
    return (ch_cylinder_its_helper(&dn_oupro, &pn_oupro, cylinder, eye2scr, infs));
}