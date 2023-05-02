/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_objarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:02:13 by user              #+#    #+#             */
/*   Updated: 2023/05/03 01:12:06 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

// static  void    refCoeff(t_refCoeff *refcoeff)
// {
//     refcoeff->ka.red = 0.01;
//     refcoeff->ka.green = 0.01;
//     refcoeff->ka.blue = 0.01;
// 	refcoeff->kd = 0.69;
// 	refcoeff->ks = 0.3;
// 	refcoeff->alpha = 8.0;
// 	refcoeff->Ia = 0.1;
// 	refcoeff->Ii = 1.0;
// }

// static  void    refCoeff2(t_refCoeff *refcoeff)
// {
//     refcoeff->ka = 0;
// 	refcoeff->kd = 0;
// 	refcoeff->ks = 0;
// 	refcoeff->alpha = 0;
// 	refcoeff->Ia = 0;
// 	refcoeff->Ii = 0;
// }

// static  void    ready_plane(t_plane *plane)
// {
//     plane->n = malloc(sizeof(t_vecinf) * 1);
//     set_vec(plane->n, 0.0, 1.0, 0.0);
//     plane->point = malloc(sizeof(t_vecinf) * 1);
//     set_vec(plane->point, 0.0, -1.0, 0.0);
//     refCoeff(&plane->t_refCoeff);
//     plane->has_specmir = false;
//     plane->spec_mir = 0.0;
// }

// static  void    ready_ball(t_ball *ball)
// {
//     ball->center_v = malloc(sizeof(t_vecinf) * 1);
//     set_vec(ball->center_v, 0, 0, 5);
//         // set_vec(ball->center_v, -2, 0, 10);
//         // ball->rad = 1;
//         // refCoeff2(&ball->t_refCoeff);
//         // ball->has_specmir = true;
//         // ball->spec_mir = 1;
//         // return ;
//     ball->rad = 2.0;
//     refCoeff(&ball->t_refCoeff);
//     ball->has_specmir = false;
//     ball->spec_mir = 0;
// }

// static void    ready_cylinder(t_cylinder	*cylinder)
// {
//     cylinder->center_v = malloc(sizeof(t_vecinf) * 1);
//     set_vec(cylinder->center_v, 0.0, 0.0, 0.0);
//     cylinder->center_n_v = malloc(sizeof(t_vecinf) * 1);
//     set_vec(cylinder->center_n_v, 0.0, 1.0, 0.0);
//     refCoeff(&cylinder->t_refCoeff);
//     cylinder->rad = 0.5;
//     cylinder->height = 0.5;
//     cylinder->has_specmir = false;
//     cylinder->spec_mir = 0;
// }

static  void    refCoeff_ka(t_refCoeff *refcoeff, double R, double G, double B)
{
    refcoeff->ka.red = R;
    refcoeff->ka.green = G;
    refcoeff->ka.blue = B;
}

static  void    refCoeff_kd(t_refCoeff *refcoeff, double R, double G, double B)
{
    refcoeff->kd.red = R;
    refcoeff->kd.green = G;
    refcoeff->kd.blue = B;
}

static  void    refCoeff_ks(t_refCoeff *refcoeff, double R, double G, double B)
{
    refcoeff->ks.red = R;
    refcoeff->ks.green = G;
    refcoeff->ks.blue = B;
}

static void    ready_object(t_objarr *objarr, double type)
{
    if (type == BALL)
    {
        objarr->ball = malloc(sizeof(t_ball) * 1);
        objarr->plane = NULL;
        objarr->cylinder = NULL;
    }
    else if (type == PLANE)
    {
        objarr->plane = malloc(sizeof(t_plane) * 1);
        objarr->ball = NULL;
        objarr->cylinder = NULL;
    }
    else if (type == CYLINDER)
    {
        objarr->cylinder = malloc(sizeof(t_cylinder) * 1);
        objarr->ball = NULL;
        objarr->plane = NULL;
    }
}

void    ready_objarr(t_fvec *fvecs)
{
	t_objarr	*tmp_obj;

	fvecs->objarr = malloc(sizeof(t_objarr) * 1);
	tmp_obj = fvecs->objarr;
	ready_object(tmp_obj, BALL);
    //set ball//
    t_ball  *ball;

    ball = tmp_obj->ball;
    ball->center_v = malloc(sizeof(t_vecinf) * 1);
    set_vec(ball->center_v, 0.0, 0.0, 5.0);
    ball->rad = 0.5;
    refCoeff_ka(&ball->t_refCoeff, 0.01, 0.01, 0.01);
    refCoeff_kd(&ball->t_refCoeff, 0.69, 0.0, 0.0);
    refCoeff_ks(&ball->t_refCoeff, 0.30, 0.30, 0.30);
    ball->t_refCoeff.Ia = 0.1;
    ball->t_refCoeff.Ii = 1.0;
    ball->t_refCoeff.alpha = 8.0;
    ball->has_specmir = false;
    ball->spec_mir = 0;
    //END of setting ballinfo//

    tmp_obj->next_obj = malloc(sizeof(t_objarr) * 1);
    tmp_obj = tmp_obj->next_obj;
    ready_object(tmp_obj, BALL);
    ball = tmp_obj->ball;
    ball->center_v = malloc(sizeof(t_vecinf) * 1);
    set_vec(ball->center_v, -1.0, 0.0, 5.0);
    ball->rad = 1.0;
    refCoeff_ka(&ball->t_refCoeff, 0.01, 0.01, 0.01);
    refCoeff_kd(&ball->t_refCoeff, 0.69, 0.69, 0.69);
    refCoeff_ks(&ball->t_refCoeff, 0.30, 0.30, 0.30);
    ball->t_refCoeff.Ia = 0.1;
    ball->t_refCoeff.Ii = 1.0;
    ball->t_refCoeff.alpha = 8.0;
    ball->has_specmir = false;
    ball->spec_mir = 0;

    t_plane *plane;
    // tmp_obj->next_obj = malloc(sizeof(t_objarr) * 1);
    // tmp_obj = tmp_obj->next_obj;
    // ready_object(tmp_obj, PLANE);
    // plane = tmp_obj->plane;
    // plane->n = malloc(sizeof(t_vecinf) * 1);
    // set_vec(plane->n, -1.0, 0.0, 0.0);
    // plane->point = malloc(sizeof(t_vecinf) * 1);
    // set_vec(plane->point, 3.0, 0.0, 0.0);
    // refCoeff_ka(&plane->t_refCoeff, 0.01, 0.01, 0.01);
    // refCoeff_kd(&plane->t_refCoeff, 0.25, 0.06, 0.51);
    // refCoeff_ks(&plane->t_refCoeff, 0.30, 0.30, 0.30);
    // plane->t_refCoeff.Ia = 0.1;
    // plane->t_refCoeff.Ii = 1.0;
    // plane->t_refCoeff.alpha = 8.0;
    // plane->has_specmir = false;
    // plane->spec_mir = 0.0;

    tmp_obj->next_obj = malloc(sizeof(t_objarr) * 1);
    tmp_obj = tmp_obj->next_obj;
    ready_object(tmp_obj, PLANE);
    plane = tmp_obj->plane;
    plane->n = malloc(sizeof(t_vecinf) * 1);
    set_vec(plane->n, 0.0, 1.0, 0.0);
    plane->point = malloc(sizeof(t_vecinf) * 1);
    set_vec(plane->point, 0.0, -1.0, 0.0);
    refCoeff_ka(&plane->t_refCoeff, 0.01, 0.01, 0.01);
    refCoeff_kd(&plane->t_refCoeff, 0.00, 0.60, 0.60);
    refCoeff_ks(&plane->t_refCoeff, 0.00, 0.60, 0.00);
    plane->t_refCoeff.Ia = 0.1;
    plane->t_refCoeff.Ii = 1.0;
    plane->t_refCoeff.alpha = 8.0;
    plane->has_specmir = false;
    plane->spec_mir = 0.0;

    t_cylinder *cylinder;
    tmp_obj->next_obj = malloc(sizeof(t_objarr) * 1);
    tmp_obj = tmp_obj->next_obj;
    ready_object(tmp_obj, CYLINDER);
    cylinder = tmp_obj->cylinder;
    cylinder->center_v = malloc(sizeof(t_vecinf) * 1);
    set_vec(cylinder->center_v, 0.0, 0.0, 6.0);
    cylinder->center_n_v = malloc(sizeof(t_vecinf) * 1);
    set_vec(cylinder->center_n_v, 1.0, 1.0, 0.0);
    refCoeff_ka(&cylinder->t_refCoeff, 0.01, 0.01, 0.01);
    refCoeff_kd(&cylinder->t_refCoeff, 0.00, 0.60, 0.60);
    refCoeff_ks(&cylinder->t_refCoeff, 0.00, 0.60, 0.00);
    cylinder->t_refCoeff.Ia = 0.1;
    cylinder->t_refCoeff.Ii = 1.0;
    cylinder->t_refCoeff.alpha = 8.0;
    cylinder->rad = 0.5;
    cylinder->height = 0.3;
    cylinder->has_specmir = false;
    cylinder->spec_mir = 0.0;

    tmp_obj->next_obj = NULL;
}