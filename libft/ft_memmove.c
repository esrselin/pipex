/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:39:25 by esakgul           #+#    #+#             */
/*   Updated: 2025/06/19 16:11:49 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dstmv;
	const unsigned char	*srcmv;

	if (!dest && !src)
		return (NULL);
	dstmv = (unsigned char *)dest;
	srcmv = (const unsigned char *)src;
	i = 0;
	if (dstmv == srcmv || len == 0)
		return (dest);
	if (dstmv > srcmv && dstmv < srcmv + len)
	{
		while (len--)
			dstmv[len] = srcmv[len];
	}
	else
	{
		while (i < len)
		{
			dstmv[i] = srcmv[i];
			i++;
		}
	}
	return (dest);
}
