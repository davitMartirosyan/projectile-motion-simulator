#include "server.h"

headers_t *get_headers(char *r)
{
    if (!r)
        return (NULL);
    headers_t *rq = malloc(sizeof(rq));
    if (!rq)
        return (NULL);
    memset(rq, 0, sizeof(headers_t));
    rq->headers = ft_split(r, '\n');
    rq->reqline = ft_split(rq->headers[0], ' ');
    rq->method = rq->reqline[0];
    rq->path = rq->reqline[1];
    return (rq);
}