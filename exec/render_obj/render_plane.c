/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:12:37 by user              #+#    #+#             */
/*   Updated: 2023/05/01 20:22:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static double calc_Rsplane(t_vecinf *eye2scr, t_vecinf *its2lgt, t_plane *plane, double n_l)
{
	t_vecinf	reflect_vec;
	t_vecinf	rev_eye2scr;
	double		v_r;

	v_r = 0.0;
	t_mix_vec_all(&reflect_vec, 2.0 * n_l, &plane->n->u_vec, -1.0, &its2lgt->u_vec);
	set_vec(&rev_eye2scr, -1.0 * eye2scr->vec.x, -1.0 * eye2scr->vec.y, -1.0 * eye2scr->vec.z);
	v_r = dot_vec(&reflect_vec.vec, &rev_eye2scr.u_vec);
	if (v_r >= 0.0)
		return (plane->t_refCoeff.Ii * pow(v_r, plane->t_refCoeff.alpha));
	return (0.0);
}

static  void    render_plane2(t_plane *plane, t_allinfs *infs, t_vecinf *eye2scr, t_vecinf *its_v, t_RGB *R_all)
{
    double      n_l;
    t_vecinf    its2lgt;
    t_vecinf    eye2its;
    t_lgtarr    *lgtarr;

    lgtarr = infs->fix_vecs->lgtarr;
    neg_vec(&eye2its, &its_v->vec, &infs->fix_vecs->eye_v->vec);
    while (lgtarr != NULL)
    {
        neg_vec(&its2lgt, &lgtarr->lgt_v.vec, &its_v->vec);
        n_l = dot_vec(&its2lgt.u_vec, &plane->n->u_vec);
        if (n_l >= 0.0)
        {
            if (plane->has_specmir == false)
            {
                cal_RGB(R_all, &plane->t_refCoeff.kd, plane->t_refCoeff.Ii * n_l);
                cal_RGB(R_all, &plane->t_refCoeff.ks, calc_Rsplane(eye2scr, &its2lgt, plane, n_l));
            }
        }
        lgtarr = lgtarr->next_lgt;
    }
}

void    render_plane(t_vecinf *eye2scr, t_allinfs *infs, t_plane *plane, double t)
{
    t_vecinf    its_v;
    t_RGB       R_all;

    t_mix_vec(&its_v, &infs->fix_vecs->eye_v->vec, t, &eye2scr->vec);
    init_RGB(&R_all);
    cal_RGB(&R_all, &plane->t_refCoeff.ka, plane->t_refCoeff.Ia);
    render_plane2(plane, infs, eye2scr, &its_v, &R_all);
    if (R_all.red > 1.0)
        R_all.red = 1.0;
    if (R_all.green > 1.0)
        R_all.green = 1.0;
    if (R_all.blue > 1.0)
        R_all.blue = 1.0;
    my_mlx_pixel_put(infs->drawinf, infs->drawinf->x, infs->drawinf->y, (int)(255 * R_all.red) << 16 | (int)(255 * R_all.green) << 8 | (int)(255 * R_all.blue));
}