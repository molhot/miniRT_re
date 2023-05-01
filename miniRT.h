/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 23:39:45 by user              #+#    #+#             */
/*   Updated: 2023/05/02 01:24:49 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

//include
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "minilibx-linux/mlx.h"

//judge shape by magic number
# define BALL 1
# define PLANE 2
# define CYLINDER 3

//background define
# define BACKCOLOR (int)(129 << 16) | (int)(198 << 8) | (int)(39)

// simple vector
typedef	struct s_vec
{
	double	x;
	double	y;
	double	z;
} t_vec;

// contain vec variable info
typedef struct	s_vecinf
{
	t_vec		vec;
	t_vec		u_vec;
	double		size;
} t_vecinf;

// fixpoint vector
// from here, all vectors name is [_v]
//if name not contain [2], it means that vector is from (0,0,0) to the only point

//lightsource is only or not ,so i have the lightinfo as list
typedef	struct	s_lgtarr t_lgtarr;

struct	s_lgtarr
{
	t_vecinf	lgt_v;
	t_lgtarr	*next_lgt;
};

//there are lot of objs, under infs are objs infs
//obj's type is [ball, plane, corn](i will add any other shape)
//depend on obj's type, obj's lgt reflect coefficient are different
//so objct has those infos

//display color depend on item
//same coefficient related to color
//compose of three color RGB
//so same info calculated by RGB ratio

typedef struct s_RGB
{
    double  red;
    double  green;
    double  blue;
} t_RGB;

//refrect coefficient info
typedef struct s_refCoeff {
	t_RGB	ka;
	t_RGB	kd;
	t_RGB	ks;
	double	alpha;
	double	Ia;
	double	Ii;
    double  shinness;
}t_refCoeff;

typedef	struct s_cylinder{
	t_vecinf	*center_v;
	t_vecinf	*center_n_v;
	t_refCoeff	t_refCoeff;
	double		rad;
	double		height;
	bool		has_specmir;
	double		spec_mir;
}t_cylinder;

typedef	struct s_plane{
	t_vecinf	*n;
	t_vecinf	*point;
	t_refCoeff	t_refCoeff;
	bool		has_specmir;
	double		spec_mir;
}t_plane;

typedef	struct s_ball{
	t_vecinf	*center_v;
	double		rad;
	t_refCoeff	t_refCoeff;
	bool		has_specmir;
	double		spec_mir;
} t_ball;

//item amount is one or more, so have the inf of objs as list
typedef	struct	s_objarr t_objarr;

struct s_objarr
{
	t_plane		*plane;
	t_ball		*ball;
	t_cylinder	*cylinder;
	t_objarr	*next_obj;
};

//above, shape infos

//any fixed vec(ex: item inf, eye point...) contains t_fvec(=fixedpointvec)
//* scrnvectr is prepared when x and y point is recognized
typedef	struct	s_fvec
{
	t_vecinf	*eye_v;
	t_vecinf	*scr_v;
	t_lgtarr	*lgtarr;
	t_objarr	*objarr;
} t_fvec;

//minilibx needs any drawinfo, above is all needs infos
typedef struct s_drawinf
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	int			x;
	int			y;
}t_drawinf;

//allinfo put togather to above struct
typedef struct s_allinfs
{
	t_drawinf	*drawinf;
	t_fvec		*fix_vecs;
}t_allinfs;

//explain functions flaw

//temporaryfunction
void    set_vec(t_vecinf *vec, double x, double y, double z);

//under sapce is function space
void    constructor(t_allinfs *allinf);
void    ready_eye_v(t_fvec *fvecs);
void    ready_lgtarr(t_fvec *fvecs);
void    ready_objarr(t_fvec *fvecs);

//exec
void    exec(t_allinfs *infs);
void	my_mlx_pixel_put(t_drawinf *data, int x, int y, int color);
int		obtain_shapetype(t_objarr *sub);
// check its exist or not
void    render(t_allinfs *infs, t_vecinf *eye2scr);
bool	ch_eye2anyobjs(t_allinfs *infs, t_objarr *objarr, t_vecinf *eye2scr);
bool    ch_eye2ball_its(t_vecinf *eye2scr, t_allinfs *infs, t_ball *ball);
bool    ch_eye2plane_its(t_vecinf *eye2scr, t_allinfs *infs, t_plane *plane);
bool    ch_eye2cylinder_its(t_vecinf *eye2scr, t_allinfs *infs, t_cylinder *cylinder);

//calc retio
double  calc_ratio_ball(t_vecinf *eye2scr, t_allinfs *infs, t_ball *ball);
double  calc_ratio_plane(t_vecinf *eye2scr, t_allinfs *infs, t_plane *plane);
double  calc_ratio_cylinder(t_vecinf *eye2scr, t_allinfs *infs, t_cylinder *cylinder);

// render any objects
void    render_ball(t_vecinf *eye2scr, t_allinfs *infs, t_ball *ball, t_lgtarr *lgtarr, double t);
void    render_plane(t_vecinf *eye2scr, t_allinfs *infs, t_plane *plane, double t);
void	render_cylinder(t_vecinf *eye2scr, t_allinfs *infs, t_cylinder *cylinder);

//exec utils
double	map(double num, double min, double max, double t_min, double t_max);
void    init_RGB(t_RGB *RGB);
void	cal_RGB(t_RGB *origin_RGB, t_RGB *add_RGB, double k);

//calculate vector
void    add_vec(t_vecinf *sub, t_vec *v1, t_vec *v2);//v1 + v2
void	neg_vec(t_vecinf *sub, t_vec *v1, t_vec *v2);//v1 - v2
double	dot_vec(t_vec *v1, t_vec *v2);//v1 * v2
void	calc_outerproduct(t_vecinf *sub, t_vec *v1, t_vec *v2);//v1 × v2
void    t_mix_vec(t_vecinf *sub, t_vec *v1, double t, t_vec *v2);//v1 + t * v2
void    t_neg_vec(t_vecinf *sub, t_vec *v1, double t, t_vec *v2);//v1 - t * v2
void    t_mix_vec_all(t_vecinf *sub, double t1, t_vec *v1, double t2, t_vec *v2);// t1 * v1 + t2 * v2

# endif