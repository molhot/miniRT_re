/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_anyvector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:59:29 by user              #+#    #+#             */
/*   Updated: 2023/05/03 00:01:14 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	free_one_vecs(t_vecinf *a)
{
	free(a);
}

void	free_two_vecs(t_vecinf *a, t_vecinf *b)
{
	free(a);
	free(b);
}

void	free_three_vecs(t_vecinf *a, t_vecinf *b, t_vecinf *c)
{
	free(a);
	free(b);
	free(c);
}