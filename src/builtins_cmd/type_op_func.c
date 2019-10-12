#include "shell.h"

char    *aliaslist_typecmd(char *shortcut)
{
    t_aliaspkg *data;
    t_alias *curr;
    char    *tmp;

    data = storeaddrstruct(NULL);
    curr = data->head_ref;
    tmp = shortcut;
    shortcut = ft_strjoin(shortcut, "=");
    ft_strdel(&tmp);
    while (curr)
    {
        if (ft_strcmp(curr->shortcut, shortcut) == 0)
        {
            ft_strdel(&shortcut);
            return (ft_strdup(curr->cmd));
        }
        curr = curr->next;
    }
    ft_strdel(&shortcut);
    return (NULL);
}

void    no_options(char *arg, int *flag)
{
    char *path;

    path = NULL;
    if ((path = aliaslist_typecmd(ft_strdup(arg))))
        buil_putstr(arg, " is aliased to ", path, 1);
    else if (is_builtin(arg))
        buil_putstr(arg, " is a shell builtin", NULL, 1);
    else if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr(arg, " is ", path, 1);
    else if ((*flag = 1))
        buil_putstr("42sh: type ", arg, ": not found", 2);
    ft_strdel(&path);
}

void    a_option(char *arg)
{
    char *path;

    path = NULL;
    if ((path = aliaslist_typecmd(ft_strdup(arg))))
        buil_putstr(arg, " is aliased to ", path, 1);
    if (is_builtin(arg))
        buil_putstr(arg, " is a shell builtin", NULL, 1);
    if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr(arg, " is ", path, 1);
}

void   p_option(char *arg, int maj_p)
{
    char *path;

    path = NULL;
    if ((path = ft_find_path(arg,  g_environ)) &&\
         !is_builtin(arg) &&\
         !aliaslist_typecmd(ft_strdup(arg)))
        buil_putstr(path, NULL, NULL, 1);
    else if ((path = ft_find_path(arg,  g_environ)) &&\
         (is_builtin(arg) || aliaslist_typecmd(ft_strdup(arg))) &&\
          maj_p)
        buil_putstr(path, NULL, NULL, 1);
    ft_strdel(&path);
}


void    t_option(char *arg, int flag)
{
    char *path;

    path = NULL;
    if ((path = aliaslist_typecmd(ft_strdup(arg))) && flag)
        buil_putstr("alias", NULL, NULL, 1);
    else if (is_builtin(arg) && flag)
        buil_putstr("builtin", NULL, NULL, 1);
    else if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr("file", NULL, NULL, 1);
    ft_strdel(&path);
}


void    at_option(char *arg)
{
    char *path;

    path = NULL;
    if ((path = aliaslist_typecmd(ft_strdup(arg))))
        buil_putstr("alias", NULL, NULL, 1);
    if (is_builtin(arg))
        buil_putstr("builtin", NULL, NULL, 1);
    if ((path = ft_find_path(arg,  g_environ)))
        buil_putstr("file", NULL, NULL, 1);
    ft_strdel(&path);
}