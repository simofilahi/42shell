#include "shell.h"

t_aliaspkg *StoreAddrStruct(t_aliaspkg *addr)
{
	static t_aliaspkg *ret;

	if (addr == NULL)
		return (ret);
	else
		ret = addr;
	return (ret);
}

void PushToList(char *string, t_aliaspkg *data, int flag)
{
	t_alias *node;
	int	i;
	
	if (!(node = (t_alias *)malloc(sizeof(t_alias))))
		return ;
	i = -1;
	while (string[++i] && string[i] != '=')
		;
	node->shortcut = ft_strsub(string, 0, ++i);
	node->cmd = ft_strsub(string, i, ft_strlen(string) - 1);
	node->flag = flag;
	node->next = NULL;
	if (!data->head_ref && !data->tail_ref)
		data->head_ref = data->tail_ref = node;
	else 
	{
		data->tail_ref->next = node;
		data->tail_ref = node;
	}
}

void CreateAliasFile()
{
	if (!(access("42shrc", F_OK) == 0))
		open("42shrc", O_WRONLY | O_CREAT, 0777);
	else
		open("42shrc", O_WRONLY);
}

void ImportAliasFileContent()
{
	t_aliaspkg *data;
	char	*line;
	int	fd;

	line = NULL;
	data = StoreAddrStruct(NULL);
	fd = open("42shrc", O_RDONLY);
	while (get_next_line(fd, &line))
		PushToList(line, data, 1);
}