#include "shell.h"

void AliasMatched(char **args)
{
	t_aliaspkg *data;
	t_alias *curr;
	char *tmp;

	data = StoreAddrStruct(NULL);
	tmp = ft_strjoin(args[0], "=");
	curr = data->head_ref;
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, tmp) == 0)
		{
			ft_strdel(&args[0]);
			args[0] = ft_strdup(curr->cmd);
			break ;
		}
		curr = curr->next;
	}
}

void PrintList()
{
	t_aliaspkg *data;
	t_alias *curr;

	data = StoreAddrStruct(NULL);
	curr = data->head_ref;
	while (curr)
	{
		ft_putstr(curr->shortcut);
		ft_putendl(curr->cmd);
		curr = curr->next;
	}
}

void PrintElement(char *shortcut)
{
	t_aliaspkg  *data;
	t_alias		*curr;
	char		*tmp;

	data = StoreAddrStruct(NULL);
	curr = data->head_ref;
	tmp = ft_strjoin(shortcut, "=");
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, tmp) == 0)
		{
			ft_putstr_fd("alias ", 1);
			ft_putstr_fd(curr->shortcut, 1);
			ft_putendl_fd(curr->cmd, 1);
			ft_strdel(&tmp);
			return ;
		}
		curr = curr->next;
	}
	ft_print_error("not found", "42sh: alias: ", shortcut, 0);
}

int isEqualFound(char *arg)
{
	if (arg[0] == '=')
		return (0);
	while (*arg)
	{
		if (*arg == '=')
			return (1);
		arg++;
	}
	return (0);
}

int  ft_buil_alias(char **args)
{
	t_aliaspkg *data;
	int			i;

	data = StoreAddrStruct(NULL);
	if (!args[0])
		PrintList();
	else 
	{
		// for test;
		//args = ft_strsplit("m=m", ' ');
		// args[0] = ft_strdup("zzz=");
		i = 0;
		while (args[i])
		{
			// ft_putendl_fd(args[i], 2);
			if (isEqualFound(args[i]))
				PushToList(args[i], data, 0);
			else
				PrintElement(args[i]);
			i++;
		}
	}
	return (1);
}