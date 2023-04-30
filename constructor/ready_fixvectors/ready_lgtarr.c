/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_lgtarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 15:39:57 by user              #+#    #+#             */
/*   Updated: 2023/04/30 15:52:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

void    ready_lgtarr(t_fvec *fvecs)
{
    t_lgtarr    *lgtinf;

    fvecs->lgtarr = malloc(sizeof(t_lgtarr) * 1);
    lgtinf = fvecs->lgtarr;
    set_vec(&lgtinf->lgt_v, -5, 5, -5);
    lgtinf->next_lgt = NULL;
}