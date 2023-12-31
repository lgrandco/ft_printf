/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:15:17 by legrandc          #+#    #+#             */
/*   Updated: 2023/11/09 19:11:42 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	output_padding(t_struct *vars, int width_to_add, int prec_to_add)
{
	int	ret;

	ret = 0;
	while (!vars->dash && !vars->zero && width_to_add--)
		ret += write(1, " ", 1);
	if (vars->is_pos && vars->plus)
		ret += write(1, "+", 1);
	if (vars->is_neg)
		ret += write(1, "-", 1);
	else if (vars->is_pos && vars->space)
		ret += write(1, " ", 1);
	if (!vars->is_nul && vars->hash && vars->hex_low)
		ret += write(1, "0x", 2);
	else if (!vars->is_nul && vars->hash && vars->hex_up)
		ret += write(1, "0X", 2);
	while (vars->zero && width_to_add--)
		ret += write(1, "0", 1);
	while (prec_to_add--)
		ret += write(1, "0", 1);
	ret += write(1, vars->string, vars->len);
	while (vars->dash && !vars->zero && width_to_add--)
		ret += write(1, " ", 1);
	return (ret);
}

int	pad(t_struct *vars)
{
	int	prec_to_add;
	int	width_to_add;

	if (vars->is_str && vars->dot)
		vars->len = ft_min(vars->precision, vars->len);
	if (vars->dot)
		vars->zero = 0;
	prec_to_add = ft_max(0, vars->precision - vars->len);
	if (vars->is_str)
		prec_to_add = 0;
	width_to_add = vars->width - vars->len - prec_to_add;
	if (vars->is_pos || vars->is_neg)
		width_to_add--;
	if (vars->hash)
		width_to_add -= 2;
	width_to_add = ft_max(0, width_to_add);
	return (output_padding(vars, width_to_add, prec_to_add));
}
