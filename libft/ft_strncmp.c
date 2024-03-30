/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strncmp.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lboudjel <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/03 18:59:09 by lboudjel		  #+#	#+#			 */
/*   Updated: 2023/05/03 18:59:09 by lboudjel		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */
/*
- compare s1 et s2 sur n caractere de s1 et s2
- renvoie un entier de la diff entre les 2 str
*/
#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] == s2[j] && s1[i])
	{
		i++;
		j++;
	}
	if (i == n || (s1[i] == '\0' && s2[j] == '\0'))
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
//int main()
//{
//	char a[] = "test\200";
//	char b[] = "test\0";
//	int n = 6;
//
//	printf("%d\n", ft_strncmp(a, b, n));
//printf("%d\n", strncmp(a, b, n));
//}