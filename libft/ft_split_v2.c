/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lboudjel <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/03 17:44:47 by lboudjel		  #+#	#+#			 */
/*   Updated: 2023/05/03 17:49:10 by lboudjel		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

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
	while (original[i] && original[i] != ' ' && original[i] != '\t')
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
	int		len_tab;
	char	**tab;

	len_tab = 0;
	len_tab = countword_v2(s);
	if (!s)
		return (NULL);
	tab = malloc (sizeof(char *) * (len_tab + 1));
	if (!tab)
		return (NULL);
	return (ft_fill_tab_v2(s, tab, len_tab));
}
