/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: legrandc <legrandc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:57:26 by leo               #+#    #+#             */
/*   Updated: 2023/11/09 18:25:15 by legrandc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>

# define SPECIFIERS "cspdiuxX%%"
# define FLAGS "-0# +"
# define SPECIAL ".*"

typedef struct s_struct
{
	int		dash;
	int		zero;
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
	int		hash;
}			t_struct;
/* FUNCTIONS */
int			pad(t_struct *vars);
int			handle_string(char *s, t_struct *vars);
int			handle_ptr(size_t ptr, t_struct *vars);
int			handle_int(int n, t_struct *vars);
int			handle_unsigned(unsigned int n, t_struct *vars, char *base);
int			ft_printf(const char *s, ...);
void		init(t_struct *vars);
void		setflag(char c, t_struct *vars);

#endif // !FT_H
