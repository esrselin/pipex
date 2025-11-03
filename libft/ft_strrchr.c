/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:50:31 by esakgul           #+#    #+#             */
/*   Updated: 2025/06/23 19:40:50 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	last;

	last = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(s + last));
	while (last > 0)
	{
		if (s[last - 1] == (char)c)
			return ((char *)(s + last - 1));
		last--;
	}
	return (NULL);
}
