/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:38:33 by leo               #+#    #+#             */
/*   Updated: 2023/11/09 09:38:53 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_preff(const char *preffix, char *s)
{
	char	*ret;

	ret = ft_strjoin(preffix, s);
	free(s);
	return (ret);
}

void	init(t_struct *vars)
{
	vars->dash = 0;
	vars->zero = 0;
	vars->hash = 0;
	vars->space = 0;
	vars->plus = 0;
	vars->star = 0;
	vars->dot = 0;
	vars->precision = 0;
	vars->percent = 0;
	vars->is_pos = 0;
	vars->is_nul = 0;
	vars->is_neg = 0;
	vars->width = 0;
	vars->hex_low = 0;
	vars->hex_up = 0;
	vars->is_str = 0;
}

void	setflag(char c, t_struct *vars)
{
	if (c == '-')
		vars->dash = 1;
	if (c == '0')
		vars->zero = 1;
	if (c == '#')
		vars->hash = 1;
	if (c == ' ')
		vars->space = 1;
	if (c == '+')
		vars->plus = 1;
	if (c == '.')
		vars->dot = 1;
}
