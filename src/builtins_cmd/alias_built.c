#include "shell.h"

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
		ft_putstr(curr->shortcut);
		ft_putendl(curr->cmd);
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
			ft_putendl_fd(curr->cmd, 1);
			ft_strdel(&tmp);
			return ;
		}
		curr = curr->next;
	}
	ft_print_error("not found", "42sh: alias: ", shortcut, 0);
}

int isequalfound(char *arg)
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

/*
** export alias
*/

void            ft_buil_alias(t_tokens *st_tokens)
{
    int i;
    char    *arg;

    i = 1;
    arg = NULL;
    st_tokens = st_tokens->next;
    (!st_tokens) ? printlist() : NULL;
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
				printf("arg = %s \n",arg);
				removealiasbyelemorbyflag(arg, 0);
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