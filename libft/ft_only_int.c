#include "libft.h"

int ft_only_int(char *s)
{
    for(int i = 0; i < (int)ft_strlen(s); i++)
        if (!ft_isdigit((unsigned char)s[i]))
            return (0);
    return (1);
}