#include "minishell.h"

typedef struct {
    char *cmd;
    char *args[100];
    int arg_count;
    int redir[100]; // 1 pour '>', 2 pour '>>', 3 pour '<', 4 pour '<<'
    char *files[10];
    int file_count;
} Command;

int	countword_v2(const char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] != '\0')
			len++;
		while (s[i] != '\0' && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	return (len);
}

//copy une str jusqua un caratere donne ou la fin dans un malloc et le renvoi
char	*copystr_v2(const char *original)
{
	char	*copy;
	int		i;

	i = 0;
	while (original[i] != '\0' && original[i] != ' ' && original[i] != '\t')
		i++;
	copy = malloc(sizeof(char) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (original[i] &&  original[i] != ' ' && original[i] != '\t')
	{
		copy[i] = original[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**ft_fill_tab_v2(char const *s, char **tab, int len_tab)
{
	int	i;

	i = 0;
	while (i != len_tab)
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			s++;
		tab[i] = copystr_v2(&s[i]);
		if (!tab[i])
		{
			i--;
			while (i >= 0)
				free(tab[i--]);
			return (NULL);
		}
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			s++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split_v2(char *s)
{
	int		len_tab = 0;
	char	**tab;

	len_tab = countword_v2(s);
	if (!s)
		return (NULL);
	tab = malloc (sizeof(char *) * (len_tab + 1));
	if (!tab)
		return (NULL);
	return (ft_fill_tab_v2(s, tab, len_tab));
}

int is_a_redirection(char *str) 
{
    if (strcmp(str, ">") == 0)
        return (1);
    else if (strcmp(str, ">>") == 0)
        return (2);
    else if (strcmp(str, "<") == 0)
        return (3);
    else if (strcmp(str, "<<") == 0)
        return (4);
    else
        return (0);
}

void parse(char *input, Command *cmd) 
{
    char **token;
    char *input2 = add_spaces(input);
    printf("%s\n", input2);
    token = ft_split_v2(input2);
    if (!token)
        return ;
    int flag = 0;
    cmd->arg_count = 0;
    cmd->file_count = 0;
    int i = 0;
    int redir = 0;
    // int j = 0;

    while (token[i]) 
    {
        redir = is_a_redirection(token[i]);
        if (redir != 0) 
        {
            cmd->redir[cmd->file_count] = redir;
            cmd->files[cmd->file_count++] = token[i + 1];
            i+=2;
            continue;
        } 
        else 
        {
            if (flag == 0)
            {
                cmd->cmd = token[i];
                flag = 1;
            }
            else
                cmd->args[cmd->arg_count++] = token[i];
        }
        i++;
    }
}

int main() 
{
    char *input = malloc(100000);
    printf("INPUT : ");
    input = " <out			ls -l	    -a ";
    Command cmd;
    parse(input, &cmd);
    printf("\nCommand: %s\n", cmd.cmd);
    for (int i = 0; i < cmd.arg_count; i++) 
    {
        printf( "argument : %s\n", cmd.args[i]);
    }
    printf("\n");
    for (int i = 0; i < cmd.file_count; i++) 
    {
        printf("Redirection: %d\n", cmd.redir[i]);
        printf("File: %s\n", cmd.files[i]);
    }
    return 0;
}