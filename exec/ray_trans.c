/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:10:10 by user              #+#    #+#             */
/*   Updated: 2023/05/04 03:33:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static double   size_eye2scrcenter(double WIDTH, double FOV)
{
	double	FOV_rad_half;

	FOV_rad_half = (FOV * 1.0 / 2.0) * M_PI / 180.0;
	return ((WIDTH / 2.0) * (1.0 / tan(FOV_rad_half)));
}

static	void	scrvec_worldvec(t_vecinf *e_x_uvec, t_vecinf *e_y_uvec, t_vecinf *eye_dim)
{
	double      dx;
    double      dz;
    double      e_x;
    double      e_z;

	dx = eye_dim->u_vec.x;
    dz = eye_dim->u_vec.z;
	if (dx != 0 && dz != 0)
	{
    	e_x = (-1.0) * dz / (sqrt(pow(dx, 2) + pow(dz, 2)));
		e_z = dx / (sqrt(pow(dx, 2) + pow(dz, 2)));
	}
	else
	{
		e_x = 1;
		e_z = 0;
	}
	set_vec(e_x_uvec, e_x, 0, e_z);
	calc_outerproduct(e_y_uvec, &e_x_uvec->u_vec, &eye_dim->u_vec);
}

static	void	ready_eye2scrvec(t_vecinf *sub, double t, t_allinfs *infs, t_vecinf *e_x_uvec, t_vecinf *e_y_uvec, t_vecinf *eye_dim, double WIDTH, double HEIGHT)
{
	t_vecinf	tmp;

	t_mix_vec_all(&tmp, t, &eye_dim->u_vec, (infs->drawinf->x - (WIDTH / 2)) , &e_x_uvec->u_vec);
	t_mix_vec(sub, &tmp.vec, (HEIGHT / 2) - infs->drawinf->y, &e_y_uvec->u_vec);
}

void    ray_trans(t_vecinf *sub, double FOV, t_vecinf *eye_dim, t_allinfs *infs, double WIDTH, double HEIGHT)
{
    t_vecinf    e_x_uvec;
    t_vecinf    e_y_uvec;

	scrvec_worldvec(&e_x_uvec, &e_y_uvec, eye_dim);
	ready_eye2scrvec(sub, size_eye2scrcenter(WIDTH, FOV), infs, &e_x_uvec, &e_y_uvec, eye_dim, WIDTH, HEIGHT);
}