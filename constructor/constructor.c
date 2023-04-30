/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 23:57:29 by user              #+#    #+#             */
/*   Updated: 2023/04/30 16:42:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static void    ready_drawinf(t_drawinf *drawinf)
{
    drawinf->width = 525;
    drawinf->height = 525;
    drawinf->mlx = mlx_init();
	drawinf->mlx_win = mlx_new_window(
        drawinf->mlx, 
        drawinf->width, 
        drawinf->height, 
        "miniRT!"
    );
	drawinf->img = mlx_new_image(
        drawinf->mlx, 
        drawinf->width, 
        drawinf->height
    );
	drawinf->addr = mlx_get_data_addr(
		drawinf->img, 
        &drawinf->bits_per_pixel, 
        &drawinf->line_length, 
        &drawinf->endian
    );
}

static void ready_fixvectors(t_fvec *fvecs)
{
    ready_eye_v(fvecs);
	ready_lgtarr(fvecs);
	ready_objarr(fvecs);
}

void    constructor(t_allinfs *allinf)
{
    allinf->drawinf = malloc(sizeof(t_drawinf) * 1);
    ready_drawinf(allinf->drawinf);
    allinf->fix_vecs = malloc(sizeof(t_fvec) * 1);
    ready_fixvectors(allinf->fix_vecs);
    allinf->fix_vecs->scr_v = malloc(sizeof(t_vecinf) * 1);
}