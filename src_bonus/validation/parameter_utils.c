/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:07:09 by thabeck-          #+#    #+#             */
/*   Updated: 2023/11/11 01:01:57 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	init_params(t_params *params)
{
	params->ceil_color = -1;
	params->floor_color = -1;
	params->east = NULL;
	params->north = NULL;
	params->south = NULL;
	params->west = NULL;
}

void	free_params_validation(t_params *params)
{
	free_map(params->map);
	free_map(params->dev_map);
	free(params->north);
	free(params->south);
	free(params->west);
	free(params->east);
}

short int	map_validation_failed(t_params *params)
{
	free_map(params->map);
	free_map(params->dev_map);
	free(params->north);
	free(params->south);
	free(params->west);
	free(params->east);
	return (FALSE);
}
