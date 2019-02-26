#include <limits.h>
#include <errno.h>
#include "libft.h"

long				ft_strtol(const char *str, char **endptr, int base)
{
	int				flag_neg;
	int				c;
	int				any;
	int				cutlim;
	unsigned long	cutoff;
	long			acc;
	char			*nptr;

	nptr = str;
	flag_neg = 0;
	c = *str;
	while (ft_isspace(c))
		c = *str++;
	if (c == '-' || c == '+')
	{
		if (c == '-')
			flag_neg = 1;
		c = *str++;
	}
	if ((base == 0 || base == 16) && c == '0' && (*str == 'x' || *str == 'X'))
	{
		c = str[1];
		str += 2;
		base = 16;
	}
	if (base == 0)
		base = c == '0' ? 8 : 10;
	cutoff = flag_neg ? -(unsigned long)LONG_MIN : LONG_MAX;
	cutlim = cutoff % (unsigned long)base;
	cutoff /= (unsigned long)base;
	acc = 0;
	any = 0;
	while (1)
	{
		if (ft_isdigit(c))
			c -= '0';
		else if (ft_isalpha(c))
			c -= ft_isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break ;
		if (c >= base)
			break ;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else
		{
			any = 1;
			acc *= base;
			acc += c;
		}
		c = *str++;
	}
	if (any < 0) {
		acc = flag_neg ? LONG_MIN : LONG_MAX;
		errno = ERANGE;
	} else if (flag_neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (char *) (any ? str - 1 : nptr);
	return (acc);
}
