/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:52:58 by chaekim           #+#    #+#             */
/*   Updated: 2022/06/10 16:42:59 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export(char **command, int *status, int i, t_info *info)
{
	char	**envp_item;
	int		flag;

	flag = 0;
	envp_item = parsing_equal(command[i], &flag);
	if (envp_item && !is_key_valid(envp_item[0]))
	{
		if (have_equal(command[i]))
			list_insert(&(info->env_list), \
			new_item(ft_strdup(envp_item[0]), ft_strdup(envp_item[1]), 1));
		else
			list_insert(&(info->env_list), \
			new_item(ft_strdup(envp_item[0]), 0, 0));
	}
	else
	{
		*status = 1;
		if (flag == 1)
			return (0);
		ft_print_error(command[0], command[i], "not a valid identifier");
	}
	free_str(envp_item);
	return (1);
}

int	ft_export(char **command, t_info *info)
{
	int	i;
	int	status;

	if (command[1] && command[1][0] == '-')
	{
		command[1][2] = 0;
		ft_print_error(command[0], command[1], "invalid option");
		return (1);
	}
	i = 0;
	status = 0;
	while (command[++i])
	{
		if (!export(command, &status, i, info))
		{
			status = -1000;
			break ;
		}
	}
	if (status != -1000)
		export_print(i, info);
	return (status);
}
