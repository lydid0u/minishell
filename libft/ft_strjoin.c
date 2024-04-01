/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lboudjel <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/03 18:55:39 by lboudjel		  #+#	#+#			 */
/*   Updated: 2023/05/03 18:55:39 by lboudjel		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

/*
 - concatene s1 et s2 avec un malloc
*/

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{	
	char	*str;
	int		len;

	len = ft_len(s1) + ft_len(s2) + 1;
	str = malloc(len);
	if (s1 == NULL || s2 == NULL || str == NULL)
		return (NULL);
	str[0] = '\0';
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	return (str);
}

char	*ft_strjoin_slash(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '/';
	i++;
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

//int main()
//{
//	char a[] = "1113";
//	char b[] = "saluhbgvd";
//
//	printf("%s\n", ft_strjoin(a, b));
//
//}