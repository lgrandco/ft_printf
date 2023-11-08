/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:29:00 by leo               #+#    #+#             */
/*   Updated: 2023/11/08 02:45:29 by leo              ###   ########.fr       */
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
	if (!s)
		vars->string = ft_strdup("(null)");
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
		vars->string = ft_itoa(va_arg(vars->ap, int));
	else if (vars->specifier == 'u')
		vars->string = ft_itoa_base(va_arg(vars->ap, unsigned int), DEC);
	else if (vars->specifier == 'x')
		vars->string = ft_itoa_base(va_arg(vars->ap, unsigned int), HEX_LOW);
	else if (vars->specifier == 'X')
		vars->string = ft_itoa_base(va_arg(vars->ap, unsigned int), HEX_UP);
	else if (vars->specifier == '%' && ++vars->percent)
		vars->string = ft_strdup("%");
	if (!vars->string)
		return (-1);
	return (ft_strlen(vars->string));
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
			ret += write(1, vars.string, vars.len);
			free(vars.string);
		}
		else
			ret += write(1, s, 1);
		s++;
	}
	va_end(vars.ap);
	return (ret);
}
