/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_eye2cylinder_its.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:19:42 by user              #+#    #+#             */
/*   Updated: 2023/05/01 23:32:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

static  bool    ch_cylinder_its_helper(t_vecinf *dn_oupro, t_vecinf *pn_oupro, t_cylinder *cylinder)
{
    double  A;
    double  B;
    double  C;

    A = pow(dn_oupro->size, 2);
    B = 2 * dot_vec(&dn_oupro->vec, &pn_oupro->vec);
    C = pow(pn_oupro->size, 2) - pow(cylinder->rad, 2);
    if (A == 0 || (pow(B, 2) - 4 * A * C) < 0)
        return (false);
    return (true);
}

bool    ch_eye2cylinder_its(t_vecinf *eye2scr, t_allinfs *infs, t_cylinder *cylinder)
{
    t_vecinf    center2eye;
    t_vecinf    dn_oupro;
    t_vecinf    pn_oupro;

    neg_vec(&center2eye, &infs->fix_vecs->eye_v->vec, &cylinder->center_v->vec);
    calc_outerproduct(&dn_oupro, &eye2scr->vec, &cylinder->center_n_v->u_vec);
    calc_outerproduct(&pn_oupro, &center2eye.vec, &cylinder->center_n_v->u_vec);
    return (ch_cylinder_its_helper(&dn_oupro, &pn_oupro, cylinder));
}