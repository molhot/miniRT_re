/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:59:08 by user              #+#    #+#             */
/*   Updated: 2023/05/09 21:59:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

// static  void	dim2tdim(t_vecinf *dim_vec, double x, double y, double width, double height)
// {
// 	double	tdim_x;
// 	double	tdim_y;
// 	double	tdim_z;

// 	tdim_x = (2 * x / (width - 1)) - 1;
// 	tdim_y = (-2 * y / (height - 1)) + 1;
// 	tdim_z = 0;
// 	set_vec(dim_vec, tdim_x, tdim_y, tdim_z);
// }

static  size_t grasp_objpos(t_objarr *objarr, t_vecinf *eye2scr, t_allinfs *infs, double t, size_t position)
{
    double  tmp_t;
    size_t  r_pos;

    r_pos = 0;
    while (objarr != NULL)
    {
        tmp_t = -1.0;
        if (obtain_shapetype(objarr) == BALL)
			tmp_t = calc_ratio_ball(eye2scr, infs, objarr->ball);
        if (obtain_shapetype(objarr) == PLANE)
			tmp_t = calc_ratio_plane(eye2scr, infs, objarr->plane);
        if (obtain_shapetype(objarr) == CYLINDER)
			tmp_t = calc_ratio_cylinder(eye2scr, infs, objarr->cylinder);
        if ((t == 0.0 && tmp_t >= 0) || (tmp_t >= 0.0 && t > tmp_t))
        {
            t = tmp_t;
            r_pos = position;
        }
        objarr = objarr->next_obj;
        position++;
    }
    return (r_pos);
}

static  void    render_obj(t_allinfs *infs, t_vecinf *eye2scr, size_t obj_pos, t_objarr *objarr)
{
    while (obj_pos != 0)
    {
        objarr = objarr->next_obj;
        obj_pos--;
    }
    if (obtain_shapetype(objarr) == BALL)
        render_ball(eye2scr, infs, objarr->ball, infs->fix_vecs->lgtarr, calc_ratio_ball(eye2scr, infs, objarr->ball));
    if (obtain_shapetype(objarr) == PLANE)
        render_plane(eye2scr, infs, objarr->plane, calc_ratio_plane(eye2scr, infs, objarr->plane));
    if (obtain_shapetype(objarr) == CYLINDER)
        render_cylinder(eye2scr, infs, objarr->cylinder);
}

void    render(t_allinfs *infs, t_vecinf *eye2scr)
{
    if (ch_eye2anyobjs(infs, infs->fix_vecs->objarr, eye2scr) == false)
        my_mlx_pixel_put(infs->drawinf, infs->drawinf->x, infs->drawinf->y, BACKCOLOR);
    else
        render_obj(infs, eye2scr, grasp_objpos(infs->fix_vecs->objarr, eye2scr, infs, 0.0, 0), infs->fix_vecs->objarr);
}

void    exec(t_allinfs *infs)
{
    int         x;
    int         y;
    t_vecinf	eye2scr;

    x = 0;
    y = 0;
    while (y != infs->drawinf->height)
    {
        while (x != infs->drawinf->width)
        {
            // if ((x > 350 && y > 80) && (x < 450 && y < 150))
            // {
                infs->drawinf->x = x;
                infs->drawinf->y = y;
                ray_trans(&eye2scr, infs->fix_vecs->eye_v->FOV, infs->fix_vecs->eye_v->eye_dim_vec, infs, infs->drawinf->width, infs->drawinf->height);
                add_vec(infs->fix_vecs->scr_v, &eye2scr.vec, &infs->fix_vecs->eye_v->eye_position->vec);
                // dim2tdim(infs->fix_vecs->eye_v, x, y, infs->drawinf->width, infs->drawinf->height);
                // neg_vec(&eye2scr, &infs->fix_vecs->scr_v->vec, &infs->fix_vecs->eye_v->vec);
                render(infs, &eye2scr);
            // }
            //printf("%f %f %f\n", eye2scr.vec.x, eye2scr.vec.y, eye2scr.vec.z);
            x++;
        }
        x = 0;
        y++;
    }
    mlx_put_image_to_window(infs->drawinf->mlx, infs->drawinf->mlx_win, infs->drawinf->img, 0, 0);
	mlx_loop(infs->drawinf->mlx);
}