#ifndef _MIDFILT_H_
#define _MIDFILT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "fifo.h"

typedef float data_t;

/// #define BUFFER_SIZE     (127)   /* 必须是奇数 */
#define BUFFER_SIZE     (1999)   /* 必须是奇数 */

char midfilt1(data_t data, data_t *mid);
char midfilt2(data_t data, data_t *mid);
char midfilt3(data_t data, data_t *mid);
char midfilt4(data_t data, data_t *mid);
char midfilt5(data_t data, data_t *mid);
char midfilt6(data_t data, data_t *mid);
char midfilt7(data_t data, data_t *mid);
char midfilt8(data_t data, data_t *mid);
char midfilt9(data_t data, data_t *mid);
char midfilt10(data_t data, data_t *mid);
char midfilt11(data_t data, data_t *mid);
char midfilt12(data_t data, data_t *mid);

#ifdef __cplusplus
}
#endif

#endif
