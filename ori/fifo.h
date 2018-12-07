/*****************************************************************************************

                              a simple fifo implementation.

*****************************************************************************************/

#ifndef _FIFO555_H_
#define _FIFO555_H_

#define ARR_CNT(x)		(sizeof(x) / sizeof(x[0]))  /* array count */
#define F_TRUE    		(1)
#define F_FALSE			(!F_TRUE)

typedef enum {
	F_OK = 0,
	F_ERR_PA,		// parameter error
	F_ERR_NM,		// no memory
	F_ERR_BS,		// busy
} fres_t;			// fifo result

struct NODE {
	void *fifo;
	unsigned int head;
	unsigned int end;
	unsigned int usz;			// unit size(in byte)
	unsigned int fifo_deep;		// this is fifo units total, not fifo size!
	unsigned int lock_flag;
};

fres_t fifo_in(struct NODE *node, void *unit);
fres_t fifo_inl(struct NODE *node, void *unit);
fres_t fifo_out(struct NODE *node, void *unit);
fres_t fifo_read(struct NODE *node, void *units, unsigned int cnt, unsigned int *rc);
fres_t fifo_peep(struct NODE *node, void *units, unsigned int cnt, unsigned int *rc);
fres_t fifo_od(struct NODE *node, void *unit);
fres_t fifo_nd(struct NODE *node, void *unit);
fres_t fifo_write(struct NODE *node, void *units, unsigned int cnt, unsigned int *wc);
fres_t fifo_writel(struct NODE *node, void *units, unsigned int cnt, unsigned int *wc);
fres_t fifo_init(struct NODE *node, void *fifo, unsigned int usz, unsigned int uto);
fres_t fifo_deep(struct NODE *node, unsigned int *deep);
fres_t fifo_deeptotal(struct NODE *node, unsigned int *deeptotal);

#endif
