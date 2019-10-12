#include "shell.h"

int RemoveAliasByElemOrByflag(char *shortcut, int check)
{
	t_aliaspkg *data;
	t_alias *curr;
	t_alias *prev;
	int	flag;
	
	flag = 0;
	data = StoreAddrStruct(NULL);
   
	if (data->head_ref == NULL)
		return(0) ;
	curr = prev = data->head_ref;
	// this line for test
    if (!check)
    {
        shortcut[ft_strlen(shortcut) - 1] = '\0';
        shortcut = ft_strjoin(shortcut, "=");
    }
	while (curr)
	{
		if ((ft_strcmp(curr->shortcut, shortcut) == 0) || (curr->flag && check))
        {
            flag = 1;
			break ;
        }
		prev = curr;
		curr = curr->next;
	}
	if (curr == data->head_ref && flag)
		data->head_ref = curr->next;
	else if (curr == data->tail_ref && flag)
	{
		prev->next = NULL;
		data->tail_ref = prev;
	}
	else if (flag)
		prev->next = curr->next;
	if (flag)
	{
		ft_strdel(&curr->shortcut);
		ft_strdel(&curr->cmd);
		free(curr);
        if (!data->head_ref)
            data->tail_ref = NULL;
        return (1);
	}
    return (0);
}

void ft_buil_updatealias(char **args)
{
	if (!(ft_strcmp(*args, "42shrc") == 0))
			ft_print_error("No such file or directory", "42sh: ", *args, 0);
	else
	{
		while(RemoveAliasByElemOrByflag(NULL, 1))
			;
		ImportAliasFileContent();
	}
}

int	ft_buil_unalias(char **args)
{
    ft_putendl_fd(args[0], 1);
    if (args[0][0] == '=' || args[0][ft_strlen(args[0]) - 1] == '=')
        ft_print_error("not found", "42sh: unalias: ", args[0], 0);
    return (1);
}