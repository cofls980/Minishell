/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaekim <chaekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:53:04 by chaekim           #+#    #+#             */
/*   Updated: 2022/06/13 14:08:04 by chaekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pwd_valid(char **cmd)
{
	int	i;

	if (cmd[1])
	{
		i = 0;
		if (cmd[1][i] == '-')
		{
			cmd[1][i + 2] = 0;
			ft_print_error(cmd[0], cmd[1], "invalid option");
			return (1);
		}
	}
	return (0);
}

int	ft_pwd(char **cmd, t_info *info)
{
	char	*path;

	if (check_pwd_valid(cmd) == 1)
	{
		return (1);
	}
	path = getcwd(0, 0);
	if (!path)
	{
		ft_print_error(cmd[0], cmd[1], strerror(errno));
		if (info->have_pipe == 0 && info->r_in_fd != -1)
			close_fd(info->r_in_fd, info);
		close_fd(info->output_fd, info);
		free_exit(info);
	}
	ft_print(info, path);
	ft_print(info, "\n");
	free(path);
	return (0);
}
