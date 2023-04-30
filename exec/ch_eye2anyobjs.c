/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_eye2anyobjs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:55:24 by user              #+#    #+#             */
/*   Updated: 2023/05/01 01:05:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

bool ch_eye2anyobjs(t_allinfs *infs, t_objarr *objarr, t_vecinf *eye2scr)
{
    while (objarr != NULL)
    {
        if (obtain_shapetype(objarr) == BALL)
        {
			if (ch_eye2ball_its(eye2scr, infs, objarr->ball) == true)
                return (true);
        }
        objarr = objarr->next_obj;
    }
    return (false);
}