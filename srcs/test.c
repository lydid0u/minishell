#include "minishell.h"

// //copy une str jusqua un caratere donne ou la fin dans un malloc et le renvoi
// char	*copystr_v2(const char *original)
// {
// 	char	*copy;
// 	int		i;
//     char    quote;

// 	i = 0;
// 	while (original[i] != '\0' && original[i] != ' ' && original[i] != '\t')
//     {
//         if (original[i] == '"' || original[i] == '\'')
//         {
//             quote = original[i];
//             while (original[i] != quote)
//                 i++;
//         }
//         if (original[i] != '\0' && original[i] != ' ' && original[i] != '\t')
// 		    i++;
//     }
// 	copy = malloc(sizeof(char) * (i + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (original[i] &&  original[i] != ' ' && original[i] != '\t')
// 	{
//         if (original[i] == '"' || original[i] == '\'')
//         {
//             quote = original[i];
//             while (original[i] != quote)
//             {
//                 copy[i] = original[i];
//                 i++;
//             }
//         }
//         if (original[i] != '\0' && original[i] != ' ' && original[i] != '\t')
//         {
//     		copy[i] = original[i];
// 	    	i++;
//         }
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }
