/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:34:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/07/08 12:35:51 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_string(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_array(char ***array)
{
	size_t	i;

	if (*array == NULL)
		return ;
	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	close_pipes(data);
	if (data->cmd1[0] == data->executable)
		data->executable = NULL;
	if (data->cmd2[0] == data->executable)
		data->executable = NULL;
	free_array(&data->cmd1);
	free_array(&data->cmd2);
	free_array(&data->paths);
	free_string(&data->executable);
	free_string(&data->shell);
}
