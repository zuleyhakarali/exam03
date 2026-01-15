#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;

    while ((c = fgetc(f)) != EOF)
    {
        if (!isspace(c))
            return (ungetc(c, f), 1);
    }
    return -1;
}

int match_char(FILE *f, char c)
{
    int r =  fgetc(f);
    if (r == c)
        return 1;
    if (r != EOF)
        ungetc(r, f);
    return -1;
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
    if (c == EOF)
        return -1;
    *va_arg(ap, char *) = (char)c;
    return 1;
}

int scan_int(FILE *f, va_list ap)
{
    int sign = 1, val = 0, c;
    int *out = va_arg(ap, int *);

    c =fgetc(f);
    if (c == '-' || c == '+')
        sign = (c == '-') ? -1 : 1;
    else if (isdigit(c))
        val = c - '0';
    else
        return (c != EOF ? ungetc(c, f) : 0, -1);
    while ((c = fgetc(f)) != EOF && isdigit(c))
        val = val * 10 + (c - '0');
    if (c != EOF)
        ungetc(c, f);
    *out = val * sign;
    return 1;
}

int scan_string(FILE *f, va_list ap)
{
    char *s = va_arg(ap, char *);
    int c, i = 0;

    while ((c = fgetc(f)) != EOF && !isspace(c))
        s[i++] = c;
    if (c != EOF)
        ungetc(c, f);
    if (i == 0)
        return -1;
    s[i] = '\0';
    return 1;
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}

int main(void)
{
	int		n;
	char	s[100];
	char	c;
	int		ret;

	printf("Input bekleniyor:\n");

	ret = ft_scanf("%d %s %c", &n, s, &c);

	printf("ft_scanf return = %d\n", ret);
	printf("n = %d\n", n);
	printf("s = %s\n", s);
	printf("c = %c\n", c);

	return 0;
}