/*****************************************************************************************

                              a simple fifo implementation.

*****************************************************************************************/

#include "fifo.h"
#include <string.h>
#include <stdio.h>

#define FIFO_LOCK(node)                       do { (node)->lock_flag = F_TRUE;  } while(0)
#define FIFO_UNLOCK(node)                     do { (node)->lock_flag = F_FALSE; } while(0)
#define FIFO_ISLOCK(node)                     ((node)->lock_flag)
#define HEADNODE_MOVE2NEXT(node)              do { if(++(node)->head >= ((node)->fifo_deep + 1)){(node)->head = 0;} } while(0)
#define ENDNODE_MOVE2NEXT(node)               do { if(++(node)->end >= ((node)->fifo_deep + 1)){(node)->end = 0;} } while(0)
// write one unit to fifo
#define WRITEONEUNIT_INTOFIFO(node, unit)     do { memcpy(((unsigned char *)((node)->fifo) + ((node)->head) * ((node)->usz)), (unit), (node)->usz); } while(0)
#define READONEUNIT_FROMFIFO(node, unit)      do { memcpy((unit), ((unsigned char *)((node)->fifo) + ((node)->end) * ((node)->usz)), (node)->usz); } while(0)
#define READANYUNIT_FROMFIFO(node, unit, seq) do { memcpy((unit), ((unsigned char *)((node)->fifo) + (seq) * ((node)->usz)), (node)->usz); } while(0)
#define UNIT_MOVE2NEXT(node, unit)            do { (unit) = (unsigned char *)(unit) + (node)->usz; } while(0)

/**
 * if the end node is behind the head node, the fifo is considerd to be
 * full. this is not equal to the case that head == end. the former is
 * for write, the latter is for read.
 * @param node: the node to be operated.
 * @return: F_TRUE --- full.
 *          F_FALSE --- not full.
 */
static int is_fifofull(struct NODE *node)
{
	unsigned int _head = node->head;

	if(++_head >= (node->fifo_deep + 1))
	{
		_head = 0;
	}
	if(_head == node->end)
	{
		return F_TRUE;
	}
	return F_FALSE;
}

/**
 * write one unit into fifo. ignoring the fifo is full or not.
 * @param node: the node to be operated.
 * @param unit: the unit to be written into the fifo.
 * @return: the result of this function.
 */
fres_t fifo_in(struct NODE *node, void *unit)
{
	if(!node || !unit)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
        WRITEONEUNIT_INTOFIFO(node, unit);

		HEADNODE_MOVE2NEXT(node);
		if(node->head == node->end)
		{
			ENDNODE_MOVE2NEXT(node);
		}
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * write one unit into fifo with a limitation: failed if fifo is full.
 * @param node: the node to be operated.
 * @param unit: the unit to be written into the fifo.
 * @return: the result of this function.
 */
fres_t fifo_inl(struct NODE *node, void *unit)
{
	if(!node || !unit)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		if(is_fifofull(node) == F_TRUE)
		{
			FIFO_UNLOCK(node);
			return F_ERR_NM;
		}

        WRITEONEUNIT_INTOFIFO(node, unit);
		HEADNODE_MOVE2NEXT(node);
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * read out one data from fifo.
 * @param node: the node to be operated.
 * @param unit: the memory store the read out data.
 * @return: the result of this function.
 */
fres_t fifo_out(struct NODE *node, void *unit)
{
	if(!node || !unit)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		if(node->head == node->end)
		{
			FIFO_UNLOCK(node);
			return F_ERR_NM;
		}
        READONEUNIT_FROMFIFO(node, unit);
		ENDNODE_MOVE2NEXT(node);
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * read numbers of units from fifo.
 * @param node: the node to be operated.
 * @param units: the memory store the read out data.
 * @param cnt: how many units to read.
 * @param rc: it is "read count", means the real number of read out units.
 * @return: the result of this function.
 */
fres_t fifo_read(struct NODE *node, void *units, unsigned int cnt, unsigned int *rc)
{
    unsigned int i = 0;

	if(!node || !units || !cnt || !rc)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		while(node->end != node->head)
		{
            READONEUNIT_FROMFIFO(node, units);
            UNIT_MOVE2NEXT(node, units);
			ENDNODE_MOVE2NEXT(node);
			if(++i >= cnt)
			{
				break;
			}
		}
		*rc = i;
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * peep numbers of units from fifo, and the fifo won't outflow.
 * @param node: the node to be operated.
 * @param units: the memory store the read out data.
 * @param cnt: how many units to read.
 * @param rc: it is "read count", means the real number of read out units.
 * @return: the result of this function.
 */
fres_t fifo_peep(struct NODE *node, void *units, unsigned int cnt, unsigned int *rc)
{
	unsigned int _end, i = 0;

	if(!node || !units || !cnt || !rc)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
	    _end = node->end;
		while(_end != node->head)
		{
            READANYUNIT_FROMFIFO(node, units, _end);
            UNIT_MOVE2NEXT(node, units);

			if(++_end >= (node->fifo_deep + 1))
            {
                _end = 0;
            }
			if(++i >= cnt)
			{
				break;
			}
		}
		*rc = i;
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * get the odest data from the fifo, and the fifo won't outflow.
 * @param node: the node to be operated.
 * @param unit: the memory store the read out data.
 * @return: the result of this function.
 */
fres_t fifo_od(struct NODE *node, void *unit)
{
	if(!node || !unit)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		if(node->head == node->end)
		{
			FIFO_UNLOCK(node);
			return F_ERR_NM;
		}
        READONEUNIT_FROMFIFO(node, unit);
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * get the newest data from the fifo, and the fifo won't outflow.
 * @param node: the node to be operated.
 * @param unit: the memory store the read out data.
 * @return: the result of this function.
 */
fres_t fifo_nd(struct NODE *node, void *unit)
{
	unsigned int _head;

	if(!node || !unit)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		if(node->head == node->end)
		{
			FIFO_UNLOCK(node);
			return F_ERR_NM;
		}

		// get the position of the newest data
		if(node->head == 0)
		{
			_head = node->fifo_deep;
		}
		else
		{
			_head = node->head - 1;
		}
        READANYUNIT_FROMFIFO(node, unit, _head);
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * write numbers of units into fifo, ignoring the fifo is full or not.
 * @param node: the node to be operated.
 * @param units: the memory store the write data.
 * @param cnt: how many units to write.
 * @param wc: it is "write count", means the real number of write units.
 *			  it always equals to cnt.
 * @return: the result of this function.
 */
fres_t fifo_write(struct NODE *node, void *units, unsigned int cnt, unsigned int *wc)
{
    unsigned int i;

	if(!node || !units || !cnt || !wc)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		for(i = 0; i < cnt; i++)
		{
            WRITEONEUNIT_INTOFIFO(node, units);
            UNIT_MOVE2NEXT(node, units);

			HEADNODE_MOVE2NEXT(node);
			if(node->head == node->end)
			{
				ENDNODE_MOVE2NEXT(node);
			}
		}
		*wc = cnt;
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * write many units into fifo with a limitation: failed if fifo full.
 * @param node: the node to be operated.
 * @param units: the memory store the write data.
 * @param cnt: how many units to write.
 * @param wc: it is "write count", means the real number of write units.
 * @return: the result of this function.
 */
fres_t fifo_writel(struct NODE *node, void *units, unsigned int cnt, unsigned int *wc)
{
	unsigned int i;

	if(!node || !units || !cnt || !wc)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		for(i = 0; i < cnt; i++)
		{
			if(is_fifofull(node) == F_TRUE)
			{
				goto out;
			}

            WRITEONEUNIT_INTOFIFO(node, units);
            UNIT_MOVE2NEXT(node, units);
			HEADNODE_MOVE2NEXT(node);
		}
	}

out:
	*wc = i;
	FIFO_UNLOCK(node);
	return F_OK;
}

/**
 * initialize a fifo.
 * @param node: the node to be operated. you must make sure the @node
 *              had been clear to zero before executing this function.
 * @param fifo: the user data to be bonded to the node. in general,
 *              it is an array.
 * @param usz: unit size(in byte). one element size of @fifo.
 * @param uto: units total. the total elements of @fifo.
 * @return: the result of this function.
 * @note: the fifo deep total would be @uto - 1!
 */
fres_t fifo_init(struct NODE *node, void *fifo, unsigned int usz,
					unsigned int uto)
{
	if(!node || !fifo || !usz || !uto)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		memset(node, 0, sizeof(*node));
		memset(fifo, 0, uto * usz);
		node->fifo = fifo;
		node->usz = usz;
		node->fifo_deep = uto - 1;
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * get fifo deep, means how many units had been written into this fifo.
 * @param node: the node to be operated.
 * @param deep: the variable to store the fifo deep.
 * @return: the result of this function.
 */
fres_t fifo_deep(struct NODE *node, unsigned int *deep)
{
	unsigned int _deep = 0;
	unsigned int _end;

	if(!node || !deep)
	{
		return F_ERR_PA;
	}
	if(FIFO_ISLOCK(node) == F_TRUE)
	{
		return F_ERR_BS;
	}

	FIFO_LOCK(node);
	{
		_end = node->end;
		while(_end != node->head)
		{
			_deep++;
			if(++_end >= (node->fifo_deep + 1))
			{
				_end = 0;
			}
		}
		*deep = _deep;
	}
	FIFO_UNLOCK(node);

	return F_OK;
}

/**
 * get the max units of this fifo.
 * @param node: the node to be operated.
 * @param deeptotal: the variable to store the total deep of this fifo.
 * @return: the result of this function.
 */
fres_t fifo_deeptotal(struct NODE *node, unsigned int *deeptotal)
{
	if(!node || !deeptotal)
	{
		return F_ERR_PA;
	}

	*deeptotal = node->fifo_deep;
	return F_OK;
}

#if 0
int main(void)
{
#define ERR_HANDLE(x) \
	if(x != F_OK) {printf("[ERROR]:@%s@%d,res=%d\n", __FUNCTION__, __LINE__, x); return -1;}

#define MY_FIFOCNT	10    /* 9 deep in fact */
typedef int USER_DATATYPE;

	USER_DATATYPE data[MY_FIFOCNT];
	struct NODE node;
	fres_t res;
	unsigned int deeptotal, deep;

	memset(&node, 0, sizeof(node));
	res = fifo_init(&node, data, sizeof(data[0]), ARR_CNT(data));
	ERR_HANDLE(res);

	res = fifo_deeptotal(&node, &deeptotal);
	ERR_HANDLE(res);
	printf("fifo_deeptotal=%d\n", deeptotal);

	res = fifo_deep(&node, &deep);
	ERR_HANDLE(res);
	printf("fifo_deep=%d\n", deep);

	// write fifo with data one by one
	{
		USER_DATATYPE testdata[MY_FIFOCNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		unsigned int i;

		printf("fifo in  ...\n");
		printf("write=");
		for(i = 0; i < deeptotal; i++)
		{
			res = fifo_in(&node, &testdata[i]);
			ERR_HANDLE(res);
			printf("%d ", testdata[i]);
		}
		printf("\n");
	}

	// read fifo with one by one
	{
		USER_DATATYPE read;
		unsigned int i;

		printf("fifo out ...\n");
		res = fifo_deep(&node, &deep);
		ERR_HANDLE(res);
		printf("fifo_deep=%d\n", deep);
		printf("read=");
		for(i = 0; i < deep; i++)
		{
			res = fifo_out(&node, &read);
			ERR_HANDLE(res);
			printf("%d ", read);
		}
		printf("\n");
	}

	// write fifo with many units
	{
		USER_DATATYPE testdata[] = {11, 22, 33, 44, 55, 66, 77, 88, 99, 111, 222, 333, 444, 555};
		unsigned int wc, i;

		printf("write fifo ...\n");
		res = fifo_deep(&node, &deep);
		ERR_HANDLE(res);
		printf("fifo_deep=%d\n", deep);
		printf("write=");
		for(i = 0; i < ARR_CNT(testdata); i++)
		{
			printf("%d ", testdata[i]);
		}
		printf("\n");
		res = fifo_write(&node, testdata, ARR_CNT(testdata), &wc);
		ERR_HANDLE(res);
		printf("wc=%d\n", wc);
	}

	// read fifo with many units
	{
		USER_DATATYPE buf[20] = {0};
		unsigned int rc, i;

		printf("read fifo ...\n");
		res = fifo_deep(&node, &deep);
		ERR_HANDLE(res);
		printf("fifo_deep=%d\n", deep);
		res = fifo_read(&node, buf, deep, &rc);
		ERR_HANDLE(res);
		printf("read=");
		for(i = 0; i < rc; i++)
		{
			printf("%d ", buf[i]);
		}
		printf("\n");
		printf("rc=%d\n", rc);
	}

	// writel fifo with many units
	{
		USER_DATATYPE testdata[] = {99, 88, 77, 66, 55, 44, 33, 22, 11, 111, 222, 333, 444, 555};
		unsigned int wc, i;

		printf("writel fifo ...\n");
		res = fifo_deep(&node, &deep);
		ERR_HANDLE(res);
		printf("fifo_deep=%d\n", deep);
		printf("writel=");
		for(i = 0; i < ARR_CNT(testdata); i++)
		{
			printf("%d ", testdata[i]);
		}
		printf("\n");
		res = fifo_writel(&node, testdata, ARR_CNT(testdata), &wc);
		ERR_HANDLE(res);
		printf("wc=%d\n", wc);
	}

	// read fifo with many units
	{
		USER_DATATYPE buf[20] = {0};
		unsigned int rc, i;

		printf("read fifo ...\n");
		res = fifo_deep(&node, &deep);
		ERR_HANDLE(res);
		printf("fifo_deep=%d\n", deep);
		res = fifo_read(&node, buf, deep, &rc);
		ERR_HANDLE(res);
		printf("read=");
		for(i = 0; i < rc; i++)
		{
			printf("%d ", buf[i]);
		}
		printf("\n");
		printf("rc=%d\n", rc);
	}

	return 0;
}
#endif
