#include "shell.h"

char *handleqoutes(char *str)
{
	char *tmp;
	int		i;
	int		j;
	int		a;

	if (str[0] != '\'' && str[0] != '"')
		return (str);
	else 
	{
		j = 0;
		while (str[j] && (str[j] == '\'' || str[j] == '"'))
			j++;
		a = str[j - 1];
		i = j - 1;
		while (str[++i] && str[i] != a)
			;
	}
	tmp =  str;
	str = ft_strsub(str, j, i - j);
	ft_strdel(&tmp);
	return (str);
}

void aliasmatched(char **args)
{
	t_aliaspkg *data;
	t_alias *curr;
	char *tmp;

	data = storeaddrstruct(NULL);
	tmp = ft_strjoin(args[0], "=");
	curr = data->head_ref;
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, tmp) == 0)
		{
			ft_strdel(&args[0]);
//			args[0] = handleqoutes(ft_strdup(curr->cmd));
			 args[0] = ft_strdup(curr->cmd);
			break ;
		}
		curr = curr->next;
	}
}

void printlist()
{
	t_aliaspkg *data;
	t_alias *curr;

	data = storeaddrstruct(NULL);
	curr = data->head_ref;
	while (curr)
	{
		ft_putstr_fd(curr->shortcut, 1);
		(curr->cmd[0] != '\'') ? ft_putchar_fd('\'', 1) : 0;
		ft_putstr_fd(curr->cmd, 1);
		(curr->cmd[ft_strlen(curr->cmd) - 1] != '\'') ? ft_putendl_fd("\'", 1) : ft_putchar_fd('\n', 1);
		curr = curr->next;
	}
}

void printelement(char *shortcut)
{
	t_aliaspkg  *data;
	t_alias		*curr;
	char		*tmp;

	data = storeaddrstruct(NULL);
	curr = data->head_ref;
	tmp = ft_strjoin(shortcut, "=");
	while (curr)
	{
		if (ft_strcmp(curr->shortcut, tmp) == 0)
		{
			ft_putstr_fd("alias ", 1);
			ft_putstr_fd(curr->shortcut, 1);
			(curr->cmd[0] != '\'') ? ft_putchar_fd('\'', 1) : 0;
			ft_putstr_fd(curr->cmd, 1);
			(curr->cmd[ft_strlen(curr->cmd) - 1] != '\'') ? ft_putendl_fd("\'", 1) : ft_putchar_fd('\n', 1);
			ft_strdel(&tmp);
			return ;
		}
		curr = curr->next;
	}
	ft_print_error("not found", "42sh: alias: ", shortcut, 0);
}

/*
** export alias
*/

void 			ft_buil_alias_2(t_tokens *st_tokens, char *arg, char *tmp, int i)
{
	int j;

	i = 1;
	 while (st_tokens)
    {
        if (st_tokens->indx == i)
        {
            if (NEXT && NEXT->token == T_EQUAL && NEXT->indx == st_tokens->indx)
            {
                arg = ft_strjoir("", st_tokens->value, 0);
                arg = ft_strjoir(arg, NEXT->value, 1);
                if (NEXT && NEXT->next && NEXT->next->indx == st_tokens->indx)
                    arg = ft_strjoir(arg, NEXT->next->value, 1);
				j = 0;
				while (arg[j] && arg[j] != '=')
					j++;
				tmp = ft_strsub(arg, 0, j);
				removealiasbyelemorbyflag(tmp, 0);
                pushtolist(arg, 0);
                ft_strdel(&arg);
            }
            else
                printelement(st_tokens->value);
			i++;
		}
        st_tokens = st_tokens->next;
    }
}

void            ft_buil_alias(t_tokens *st_tokens)
{
    st_tokens = st_tokens->next;
    if (!st_tokens)
	{
		printlist();
		return ;
	}
	if (st_tokens->value[0] == '-')
	{
		ft_print_error(" invalid option", "42sh: alias: ", st_tokens->value, 0);
		ft_print_error("alias [name[=value] ... ]", NULL, "alias: usage: ",0);
		return ;
	}
	ft_buil_alias_2(st_tokens, NULL, NULL, 0);
}
