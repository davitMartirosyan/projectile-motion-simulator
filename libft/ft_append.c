#include "libft.h"

char *ft_append(char *s1, char *s2)
{
    int s1len = ft_strlen(s1);
    int s2len = ft_strlen(s2);
    char *app = NULL;

    if (!s1 && s2)
        return (ft_strdup(s2));
    if (s1 && !s2)
        return (ft_strdup(s1));
    if(!s1 && !s2)
        return (ft_strdup(""));
    app = malloc(sizeof(char) * (s1len + s2len + 1));
    if (!app)
        return (NULL);
    char *tmp = app;
    while (*s1)
        *tmp++ = *s1++;
    while (*s2)
        *tmp++ = *s2++;
    *tmp = '\0';
    free(s1);
    return (app);
}