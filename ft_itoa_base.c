/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:24:17 by leo               #+#    #+#             */
/*   Updated: 2023/11/07 23:43:08 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(unsigned long n, char *base)
{
	unsigned long	nb;
	size_t			len;
	int				base_len;
	char			*ret;

	nb = n;
	len = n == 0;
	base_len = ft_strlen(base);
	while (n && ++len)
		n /= ft_strlen(base);
	ret = ft_calloc(len + 1, 1);
	if (!ret)
		return (NULL);
	*ret = *base;
	while (nb)
	{
		ret[--len] = base[nb % base_len];
		nb /= base_len;
	}
	return (ret);
}
