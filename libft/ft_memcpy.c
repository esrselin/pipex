/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:07:29 by esakgul           #+#    #+#             */
/*   Updated: 2025/06/19 16:55:00 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dstcpy;
	const unsigned char	*srcpy;

	if (!dest && !src)
		return (NULL);
	dstcpy = (unsigned char *)dest;
	srcpy = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dstcpy[i] = srcpy[i];
		i++;
	}
	return (dest);
}
