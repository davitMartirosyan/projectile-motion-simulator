#include "server.h"

headers_t *get_headers(char *r)
{
    if (!r)
        return (NULL);
    headers_t *rq = malloc(sizeof(rq));
    if (!rq)
        return (NULL);
    memset(rq, 0, sizeof(headers_t));
    rq->headers = ft_split_sized(r, '\n', &rq->size);
    if (rq->headers)
        rq->reqline = ft_split_sized(rq->headers[0], ' ', &rq->reqline_size);
    return (rq);
}

int parseHTTPRequest(char *req)
{
    return (0);
}