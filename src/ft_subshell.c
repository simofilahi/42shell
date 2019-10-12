/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 23:42:21 by onouaman          #+#    #+#             */
/*   Updated: 2019/10/02 23:42:22 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

char		*exec_subsh(char *cmd)
{
	int		fds[2];
	char	buff[10];
	char	*result;


	fds[0] = 0;
	fds[1] = 0;
	if (pipe(fds) == -1)
		ft_putendl_fd("Error Create Pipe", 2);
	if (fork() == 0)
	{
		close(fds[0]);
		if (dup2(fds[1] , 1) == -1)
			ft_putendl_fd("Error in dub STD_OUT in SUB_SHELL", 2);
		cmd[ft_strlen(cmd) - 1] = 0;
		ft_strcpy(cmd, &cmd[2]);
		ft_multi_cmd(cmd, 1);
		close(fds[1]);
		exit(EXIT_SUCCESS);
	}
	close(fds[1]);
	result = ft_strnew(0);
	wait(NULL);
	while (read(fds[0] , &buff, 10) > 0)
	{
		result = ft_strjoir(result, buff, 1);
		ft_bzero(buff, 10);
	}
	close(fds[0]);
	if (result && result[ft_strlen(result) - 1] == '\n')
		result[ft_strlen(result) - 1] = '\0';
	return (result);
}

char		*change_subsh_quot(char *arg)
{
	char	*result;
	char	*cmd;
	char	*value;
	int		i;
	int		len;

	if (!arg)
		return (NULL);
	result = NULL;
	cmd = NULL;
	i = 0;
	len = 0;
	while (arg[i])
	{
		if (arg[i] == '(' && i && M_SUBSH(arg[i - 1]))
		{
			if ((len = find_subsh(&arg[i])) != -1)
				cmd = ft_strsub(arg, i - 1, len + 2);
			value = exec_subsh(cmd);
			arg = ft_str_remp(arg, value, i - 1, ft_strlen(cmd));
		}
		i++;
	}
	return (result);
}

void		apply_subsh(t_tokens *st_tokens)
{
	char	*value;
	int		i;

	i = 0;
	if (!st_tokens)
		return ;
	while (st_tokens)
	{
		value = NULL;
		if (st_tokens->token == T_SUBSHL)
		{
			value = exec_subsh(st_tokens->value);
		}
		else if (st_tokens->token == T_DQUO && st_tokens->value)
		{
			if ((i = ft_find_char(st_tokens->value, '(')) != -1 && i && M_SUBSH(st_tokens->value[i - 1]))
				value = change_subsh_quot(st_tokens->value);
		}
		if (value)
		{
			//ft_strdel(&st_tokens->value);
			st_tokens->value = value;
		}
		st_tokens = st_tokens->next;
	}
}