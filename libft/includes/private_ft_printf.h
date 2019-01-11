/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_ft_printf.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:10:13 by pcarles           #+#    #+#             */
/*   Updated: 2018/11/26 13:10:15 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_FT_PRINTF_H
# define PRIVATE_FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>

typedef struct		s_arg
{
	int				len;
	int				hashtag;
	int				force_hashtag;
	int				zero;
	int				minus;
	int				plus;
	int				space;
	int				width;
	int				got_precision;
	int				precision;
	int				hh;
	int				h;
	int				ll;
	int				l;
	int				j;
	int				z;
}					t_arg;

int					ft_printf(char const *format, ...);
void				ft_printf_init_handlers(int (*converter[256])\
					(va_list ap, t_arg *arg));
int					ft_printf_x(va_list ap, t_arg *arg);
int					ft_printf_lx(va_list ap, t_arg *arg);
int					ft_printf_p(va_list ap, t_arg *arg);
int					ft_printf_o(va_list ap, t_arg *arg);
int					ft_printf_lo(va_list ap, t_arg *arg);
int					ft_printf_u(va_list ap, t_arg *arg);
int					ft_printf_lu(va_list ap, t_arg *arg);
int					ft_printf_ld(va_list ap, t_arg *arg);
int					ft_printf_d(va_list ap, t_arg *arg);
int					ft_printf_c(va_list ap, t_arg *arg);
int					ft_printf_s(va_list ap, t_arg *arg);
int					ft_printf_lc(va_list ap, t_arg *arg);
int					ft_printf_ls(va_list ap, t_arg *arg);
int					ft_printf_pourcent(va_list ap, t_arg *arg);
char				*ft_printf_parse_arg(char *argc, t_arg *arg);
char				*ft_printf_itoa_base(uintmax_t nb, int base, char c);
int					ft_printf_check_precision(int nblen, t_arg *arg);
int					ft_printf_put_width(int	nblen, t_arg *arg, int check);
void				ft_printf_reset_arg(t_arg *arg);
intmax_t			ft_printf_signed_conv(va_list ap, t_arg *arg);
uintmax_t			ft_printf_unsigned_conv(va_list ap, t_arg *arg);
int					ft_printf_check_conv(char c);
void				ft_printf_plusspace(t_arg *arg);
int					ft_printf_widthneg(t_arg *arg, int res, \
					int n, int length);

#endif
