/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:09:16 by thabeck-          #+#    #+#             */
/*   Updated: 2023/01/06 14:17:33 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit_sign(int ch, int next_ch)
{
	if (ft_isdigit(ch)
		|| (((ch == '-') || (ch == '+'))
			&& ft_isdigit(next_ch)))
		return (1);
	return (0);
}
