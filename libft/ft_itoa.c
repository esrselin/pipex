/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 02:49:10 by esakgul           #+#    #+#             */
/*   Updated: 2025/06/19 15:59:21 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_count(int n)
{
	unsigned int	num;
	int				count;

	count = 0;
	if (n <= 0)
		count = 1;
	if (n < 0)
		num = -n;
	else
		num = n;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static void	fill_number(char *str, int n, int digits, int neg)
{
	unsigned int	num;
	int				i;

	i = digits + neg - 1;
	if (n < 0)
		num = -n;
	else
		num = n;
	str[digits + neg] = '\0';
	while (digits > 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
		digits--;
	}
	if (neg)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*str;
	int				neg;
	int				digits;

	neg = 0;
	if (n < 0)
		neg = 1;
	digits = digit_count(n);
	str = malloc(digits + 1);
	if (!str)
		return (NULL);
	fill_number(str, n, digits - neg, neg);
	return (str);
}
