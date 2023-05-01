/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:19:45 by user              #+#    #+#             */
/*   Updated: 2023/05/02 01:28:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static double calc_Rscylinder(t_vecinf *its_v, t_vecinf	*its_n, t_vecinf *its2lgt, double n_l, t_cylinder *cylinder)
{
	t_vecinf	reflect_vec;
	t_vecinf	rev_eye2scr;
	double		v_r;

	v_r = 0.0;
	t_mix_vec_all(&reflect_vec, 2 * n_l, &its_n->u_vec, -1, &its2lgt->u_vec);
	set_vec(&rev_eye2scr, -1 * its_v->vec.x, -1 * its_v->vec.y, -1 * its_v->vec.z);
	v_r = dot_vec(&reflect_vec.u_vec, &rev_eye2scr.u_vec);
	if (v_r >= 0.0)
		return (cylinder->t_refCoeff.Ii * pow(v_r, cylinder->t_refCoeff.alpha));
	return (0.0);
}

static void     calc_its_nvec(t_vecinf *sub, t_vecinf *cylinderits_v, t_cylinder *cylinder)
{
    t_vecinf    middle2its;
    double      ratio;

    neg_vec(&middle2its, &cylinderits_v->vec, &cylinder->center_v->vec);
    ratio = dot_vec(&middle2its.vec, &cylinder->center_n_v->vec);
    t_neg_vec(sub, &middle2its.vec, ratio, &cylinder->center_n_v->vec);
}

static void render_cylinder2(t_allinfs *infs, t_cylinder *cylinder, t_vecinf *its_v, t_vecinf *its_n, t_RGB *R_all)
{
    t_lgtarr    *lgtarr;
    t_vecinf    its2lgt;
    double      n_l;

    lgtarr = infs->fix_vecs->lgtarr;
    while (lgtarr != NULL)
    {
        neg_vec(&its2lgt, &lgtarr->lgt_v.vec, &its_v->vec);
        n_l = dot_vec(&its_n->u_vec, &its2lgt.u_vec);
        if (n_l >= 0.0)
        {
            if (cylinder->has_specmir == false)
            {
                cal_RGB(R_all, &cylinder->t_refCoeff.kd, cylinder->t_refCoeff.Ii * n_l);
                cal_RGB(R_all, &cylinder->t_refCoeff.ks, calc_Rscylinder(its_v, its_n, &its2lgt, n_l, cylinder));
            }
        }
        lgtarr = lgtarr->next_lgt;
    }
}

void  render_cylinder(t_vecinf *eye2scr, t_allinfs *infs, t_cylinder *cylinder)
{
    t_vecinf    its_v;
    t_vecinf    its_n;
    t_RGB       R_all;

    t_mix_vec(&its_v, &infs->fix_vecs->eye_v->vec, calc_ratio_cylinder(eye2scr, infs, cylinder), &eye2scr->vec);
    calc_its_nvec(&its_n, &its_v, cylinder);
    init_RGB(&R_all);
    cal_RGB(&R_all, &cylinder->t_refCoeff.ka, cylinder->t_refCoeff.Ia);
    render_cylinder2(infs, cylinder, &its_v, &its_n, &R_all);
    if (R_all.red > 1.0)
        R_all.red = 1.0;
    if (R_all.green > 1.0)
        R_all.green = 1.0;
    if (R_all.blue > 1.0)
        R_all.blue = 1.0;
    my_mlx_pixel_put(infs->drawinf, infs->drawinf->x, infs->drawinf->y, (int)(255 * R_all.red) << 16 | (int)(255 * R_all.green) << 8 | (int)(255 * R_all.blue));
}