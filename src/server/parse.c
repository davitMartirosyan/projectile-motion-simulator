#include "server.h"

headers_t *get_headers(char *r)
{
    if (!r)
        return (NULL);
    headers_t *rq = malloc(sizeof(headers_t));
    if (!rq)
        return (NULL);
    memset(rq, 0, sizeof(headers_t));
    rq->headers = ft_split_sized(r, '\n', &rq->size);
    if (rq->headers)
        rq->reqline = ft_split_sized(rq->headers[0], ' ', &rq->reqline_size);
    else
    {
        free(rq);
        return (NULL);
    }
    return (rq);
}

int parseHTTPRequest(char *req)
{
    return (0);
}