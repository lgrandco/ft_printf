/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:29:00 by leo               #+#    #+#             */
/*   Updated: 2023/11/09 10:46:19 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_flags(const char **s, t_struct *vars)
{
	init(vars);
	while (ft_strchr(FLAGS, **s))
		setflag(*(*s)++, vars);
	if (**s == '*')
		vars->width = va_arg(vars->ap, int);
	else
		vars->width = ft_atoi(*s);
	while (ft_isdigit(**s))
		(*s)++;
	if (**s == '.')
	{
		vars->dot = 1;
		if (*(++*s) == '*')
			vars->precision = va_arg(vars->ap, int);
		else
			vars->precision = ft_atoi(*s);
		if (vars->precision < 0)
			vars->precision = 1;
		while (ft_isdigit(**s))
			(*s)++;
	}
}

void	handle_string(char *s, t_struct *vars)
{
	vars->is_str = 1;
	if (!s)
	{
		if (vars->dot && vars->precision < (int)ft_strlen("(null)"))
			vars->string = ft_strdup("");
		else
			vars->string = ft_strdup("(null)");
	}
	else
		vars->string = ft_strdup(s);
}

void	handle_ptr(size_t ptr, t_struct *vars)
{
	if (!ptr)
		vars->string = ft_strdup("(nil)");
	else
		vars->string = add_preff("0x", ft_itoa_base(ptr, HEX_LOW));
}

void	handle_int(int n, t_struct *vars)
{
	if (!n)
		vars->is_nul = 1;
	if (n < 0)
		vars->is_neg = 1;
	else if (vars->space || vars->plus)
		vars->is_pos = 1;
	vars->string = ft_itoa_base(ft_abs(n), DEC);
	if (!vars->dot)
		vars->precision = 1;
}

void	handle_unsigned(unsigned int n, t_struct *vars, char *base)
{
	if (!n)
		vars->is_nul = 1;
	if (!vars->dot)
		vars->precision = 1;
	vars->string = ft_itoa_base(n, base);
}

int	format(t_struct *vars)
{
	if (vars->specifier == 'c')
	{
		vars->string = ft_strdup((char[]){va_arg(vars->ap, int), 0});
		return (1);
	}
	else if (vars->specifier == 's')
		handle_string(va_arg(vars->ap, char *), vars);
	else if (vars->specifier == 'p')
		handle_ptr(va_arg(vars->ap, size_t), vars);
	else if (vars->specifier == 'd' || vars->specifier == 'i')
		handle_int(va_arg(vars->ap, int), vars);
	else if (vars->specifier == 'u')
		handle_unsigned(va_arg(vars->ap, unsigned int), vars, DEC);
	else if (vars->specifier == 'x' && ++vars->hex_low)
		handle_unsigned(va_arg(vars->ap, unsigned int), vars, HEX_LOW);
	else if (vars->specifier == 'X' && ++vars->hex_up)
		handle_unsigned(va_arg(vars->ap, unsigned int), vars, HEX_UP);
	else if (vars->specifier == '%' && ++vars->percent)
		vars->string = ft_strdup("%");
	if (!vars->string)
		return (-1);
	return (ft_strlen(vars->string));
}

int	pad(t_struct *vars)
{
	int	ret;
	int	prec_to_add;
	int	width_to_add;

	ret = 0;
	if (vars->precision == 0 && vars->is_nul == 1)
		vars->len = 0;
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

int	ft_printf(const char *s, ...)
{
	t_struct	vars;
	int			ret;

	va_start(vars.ap, s);
	ret = 0;
	while (*s)
	{
		if (*s == '%' && ++s)
		{
			parse_flags(&s, &vars);
			vars.specifier = *s;
			vars.len = format(&vars);
			if (vars.len == -1)
				return (-1);
			ret += pad(&vars);
			free(vars.string);
		}
		else
			ret += write(1, s, 1);
		s++;
	}
	va_end(vars.ap);
	return (ret);
}
