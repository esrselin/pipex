/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:22:35 by esakgul           #+#    #+#             */
/*   Updated: 2025/06/19 16:08:07 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1cmp;
	const unsigned char	*s2cmp;

	i = 0;
	s1cmp = (const unsigned char *)s1;
	s2cmp = (const unsigned char *)s2;
	while (i < n)
	{
		if (s1cmp[i] != s2cmp[i])
			return (s1cmp[i] - s2cmp[i]);
		i++;
	}
	return (0);
}
