/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:34:54 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/06/19 11:54:36 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

char	*remove_str_quotes(char *arg)
{
	int		i;
	int		j;
	int		quote;
	char	*result;

	i = 0;
	j = 0;
	quote = 0;
	result = allocate_result(arg);
	if (result == NULL)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] == '\"')
		{
			quote = !quote;
			i++;
			continue ;
		}
		if (arg[i] == '\\' && arg[i + 1] != '\0' && !quote)
			i++;
		result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (result);
}

void	remove_array_quotes(char **array)
{
	int		i;
	char	*new_str;

	i = 0;
	while (array[i] != NULL)
	{
		new_str = remove_str_quotes(array[i]);
		if (new_str != NULL)
		{
			free(array[i]);
			array[i] = new_str;
		}
		else
		{
			free(array[i]);
			array[i] = NULL;
		}
		i++;
	}
}

char	*remove_double_quotes(const char *arg)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == '\"' && arg[i + 1] == '\"')
			i += 2;
		else
			result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (result);
}

char	**clean_arguments(char *arg)
{
	char	*clean;
	char	**args;

	clean = remove_double_quotes(arg);
	if (clean == NULL)
		return (NULL);
	args = parse_cmd_args(clean);
	if (args == NULL)
	{
		free(clean);
		return (NULL);
	}
	remove_array_quotes(args);
	free(clean);
	return (args);
}
