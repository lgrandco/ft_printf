/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:57:26 by leo               #+#    #+#             */
/*   Updated: 2023/11/09 09:34:30 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H
# include "libft/libft.h"
# include <stdarg.h>

# define SPECIFIERS "cspdiuxX%%"
# define FLAGS "-0# +"
# define SPECIAL ".*"

typedef struct s_struct
{
	int		dash;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		star;
	size_t	width;
	int		dot;
	int		precision;
	va_list	ap;
	char	*string;
	int		len;
	int		percent;
	char	specifier;
	int		is_nul;
	int		is_pos;
	int		is_neg;
	int		hex_low;
	int		hex_up;
	int		is_str;
}			t_struct;
/* FUNCTIONS */
int			ft_printf(const char *s, ...);
char		*add_preff(const char *preffix, char *s);
void		init(t_struct *vars);
void		setflag(char c, t_struct *vars);

#endif // !FT_H
