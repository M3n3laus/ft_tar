/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 16:22:08 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/29 16:03:20 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "trashcan.h"

# define BASE_DIGITS "0123456789abcdef"
# define DEFAULT_TRASH_SIZE 100
# define TABLE_LEN 12
# define NUM_H_FLAGS 5
# define NUM_L_FLAGS 3
# define H_FLAGS " #0-+"
# define L_FLAGS "hlL"
# define S { 's', &s }
# define C { 'c', &c }
# define P { 'p', &p }
# define D { 'd', &d }
# define I { 'i', &d }
# define O { 'o', &o }
# define U { 'u', &u }
# define X { 'x', &x }
# define XX { 'X', &xx }
# define F { 'f', &f }
# define PC { '%', &percent }
# define V { 'v', &v } //new addition
# define FUNCS { V, S, C, P, D, I, O, U, X, XX, F, PC}
# define INIT_TABLE(x) t_dispatch_table x = { FUNCS }

typedef struct					s_string
{
	int							len;
	char						*str;
}								t_string;
t_string						*t_string_join(t_string string_one,
		t_string string_two);
void							print_t_string(t_string *result);
typedef struct					s_flags
{
	char						h_flag[NUM_H_FLAGS];
	int							min_width;
	int							precision;
	char						l_flag[3];
	char						arg_type;
}								t_flag;
typedef struct					s_dispatch_funcs
{
	const char					key;
	int							(*func)(t_flag, va_list, t_string**);
}								t_dispatch_funcs;
typedef struct					s_dispatch_table
{
	t_dispatch_funcs			table[TABLE_LEN];
}								t_dispatch_table;
int								ft_printf(const char *format, ...);
typedef struct					s_package
{
	t_flag						flag;
	t_string					*string;
	t_string					*mws;
	t_string					sign;
}								t_package;
const char						*parse_no_key(const char *format,
		t_string **result);
const char						*parse_key(const char *format, t_string
		**result,
		t_dispatch_table dispatch, va_list list);
void							init_t_flag(t_flag *flags);
const char						*set_h_flags(const char *format, t_flag *flags);
const char						*set_min_width(const char *format, t_flag *flags);
const char						*set_precision(const char *format, t_flag *flags);
const char						*set_l_flags(const char *formatt, t_flag *flags);
const char						*set_arg_type(const char *format, t_flag *flags, int *code, t_dispatch_table dispatch);
void							result_watcher(t_string **watch, t_string *result);
int								s(t_flag flags, va_list list, t_string **result);
void							str_precision(t_flag *flags, t_string **string);
void							str_min_width(t_flag *flags, t_string **string);
int								c(t_flag flags, va_list list, t_string **result);
void							c_min_width(t_flag flags, t_string **string);
int								p(t_flag flags, va_list list, t_string **result);
void							p_min_width(t_flag *flags, t_string **string);
void							helper(t_flag *flags, t_string **string, t_string *newstr);
size_t							pointer_length(unsigned long long number);
char							*convert_pointer(unsigned long long pointer);
int								percent(t_flag flags, va_list list, t_string **result);
int								d(t_flag flags, va_list list, t_string **result);
void							d_adjust_precision(t_package *package);
void							d_formatter(t_package *package);
void							d_sign(t_package *package);
void							d_min_width(t_package *package);
void							dhelper(t_package *package);
int								o(t_flag flags, va_list list, t_string **result);
void							o_formatter(t_package *package);
void							o_adjust_precision(t_package *package);
int								u(t_flag flags, va_list list, t_string **result);
int								x(t_flag flags, va_list list, t_string **result);
void							x_formatter(t_package *package);
void							hex_prefix(t_package *package);
int								xx(t_flag flags, va_list list, t_string **result);
void							capital(t_package *package);
int								f(t_flag flags, va_list list, t_string **result);
void							f_formatter(t_package *package);
void							f_limit(t_package *package);
void							print_flags(t_flag *flags);
int								contains(char c, char *str, int len);
int								str_num_len(const char *format);
void                            t_string_mom(t_string *pointer);
int								v(t_flag flags, va_list list, t_string **result);
#endif
