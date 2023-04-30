/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grasp_objtype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:19:47 by user              #+#    #+#             */
/*   Updated: 2023/04/30 17:22:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int obtain_shapetype(t_objarr *sub)
{
    if (sub->ball != NULL)
        return (BALL);
    else if (sub->plane != NULL)
        return (PLANE);
    else if (sub->cylinder != NULL)
        return (CYLINDER);
    else
        return (-1);
}