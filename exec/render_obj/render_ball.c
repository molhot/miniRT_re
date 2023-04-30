/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ball.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:46:27 by user              #+#    #+#             */
/*   Updated: 2023/04/30 23:15:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static  void    init_RGB(t_RGB *RGB)
{
    RGB->red = 0.0;
    RGB->green = 0.0;
    RGB->blue = 0.0;
}

static void   cal_RGB(t_RGB *origin_RGB, t_RGB *add_RGB, double k)
{
    origin_RGB->red = origin_RGB->red + add_RGB->red * k;
    origin_RGB->green = origin_RGB->green + add_RGB->green * k;
    origin_RGB->blue = origin_RGB->blue + add_RGB->blue * k;
}

static double calc_Rsball(t_vecinf *eye2scr, t_vecinf	*ballmid2lgt, t_vecinf *ballmid2ballits, t_refCoeff *refcoeff_inf, double n_l)
{
	t_vecinf	reflect_vec;
	t_vecinf	rev_eye2scr;
	double		v_r;

	v_r = 0.0;
	t_mix_vec_all(&reflect_vec, 2 * n_l, &ballmid2ballits->u_vec, -1, &ballmid2lgt->u_vec);
	set_vec(&rev_eye2scr, -1 * eye2scr->vec.x, -1 * eye2scr->vec.y, -1 * eye2scr->vec.z);
	v_r = map(dot_vec(&reflect_vec.vec, &rev_eye2scr.u_vec), -1.0, 1.0, 0.0, 1.0);
	if (v_r != 0.0)
		return (refcoeff_inf->Ii * pow(v_r, refcoeff_inf->alpha));
	return (0.0);
}

void    render_ball(t_vecinf *eye2scr, t_allinfs *infs, t_ball *ball, t_lgtarr *lgtarr, double t)
{
    t_vecinf    its_v;
    t_vecinf    center2its;
    t_RGB       *R_all;
    t_vecinf	ballmid2lgt;
    t_vecinf	ballmid2ballits;
    double      n_l;

    t_mix_vec(&its_v, &infs->fix_vecs->eye_v->vec, t, &eye2scr->vec);
    neg_vec(&center2its, &its_v.vec, &ball->center_v->vec);
    neg_vec(&ballmid2ballits, &its_v.vec, &ball->center_v->vec);
    R_all = malloc(sizeof(t_RGB) * 1);
    init_RGB(R_all);
    cal_RGB(R_all, &ball->t_refCoeff.ka, ball->t_refCoeff.Ia);
    while (lgtarr != NULL)
    {
        neg_vec(&ballmid2lgt, &lgtarr->lgt_v.vec, &ball->center_v->vec);
        n_l = map(dot_vec(&ballmid2ballits.u_vec, &ballmid2lgt.u_vec), -1.0, 1.0, 0.0, 1.0);
        if (n_l != 0.0)
        {
            if (ball->has_specmir == false)
            {
                cal_RGB(R_all, &ball->t_refCoeff.kd, ball->t_refCoeff.Ii * n_l);
                printf("%f\n", n_l);
                cal_RGB(R_all, &ball->t_refCoeff.ks, calc_Rsball(eye2scr, &ballmid2lgt, &ballmid2ballits, &ball->t_refCoeff, n_l));
            }
            // else if (ball->has_specmir == true)
            // {
            //     // recursive = recursive_ray(&ballits_v, infs, &ballmid2ballits);
            //     // set_vec(infs->fix_vecs->eye_v, 0, 0, -5);
            //     // if (recursive >= 0)
            //     //     return (recursive);
            //     // else
            //     //     return (-1);
            // }
        }
        lgtarr = lgtarr->next_lgt;
    }
    my_mlx_pixel_put(infs->drawinf, infs->drawinf->x, infs->drawinf->y, (int)(255 * R_all->red) << 16 | (int)(255 * R_all->green) << 8 | (int)(255 * R_all->blue));
    free(R_all);
}