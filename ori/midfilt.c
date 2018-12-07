#include "midfilt.h"

// 冒泡排序，从小到大
static void bubble_sort(data_t *buf, unsigned int cnt)
{
    unsigned int i, j;
    data_t tmp;

    for(i = 0; i < cnt; i++)
    {
        for(j = 0; j < cnt - i - 1; j++)
        {
            if(buf[j] > buf[j + 1])
            {
                tmp = buf[j];
                buf[j] = buf[j + 1];
                buf[j + 1] = tmp;
            }
        }
    }
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt1(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}


/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt2(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt3(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt4(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt5(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt6(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt7(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt8(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt9(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt10(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt11(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

/*********************************************************************
 * mid value filter
 * @param
 * @param
 * @return
 */
char midfilt12(data_t data, data_t *mid)
{
#define NOTREADY_HANDLE(x)      if((x) != 0){goto notready;}
#define ERR_HANDLE(x)           if((x) != 0){goto err;}

    static char fifo_initflag;
    static struct NODE node;
    static data_t buf[BUFFER_SIZE + 1];
    static data_t rbuf[BUFFER_SIZE];
    fres_t res;
    unsigned int deep, rc;

    ERR_HANDLE(mid == 0);

    if(fifo_initflag == 0)
    {
        fifo_init(&node, buf, sizeof(buf[0]), ARR_CNT(buf));
        fifo_initflag = 1;
    }

    res = fifo_in(&node, &data);
    ERR_HANDLE(res);

    res = fifo_deep(&node, &deep);
    ERR_HANDLE(res);

    NOTREADY_HANDLE(deep != BUFFER_SIZE);

    res = fifo_peep(&node, &rbuf, ARR_CNT(rbuf), &rc);
    ERR_HANDLE(res);
    ERR_HANDLE(rc != ARR_CNT(rbuf));

    bubble_sort(rbuf, ARR_CNT(rbuf));
    *mid = rbuf[ARR_CNT(rbuf) / 2];

    return 0;

notready:
    *mid = 0;
    return -1;
err:
    *mid = 0;
    return -2;
}

