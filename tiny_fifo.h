


#ifndef  __TINY_FIFO_H
#define __TINY_FIFO_H

typedef  int  FIFO_NODE_TYPE


#define MAX_BIT  7
#define MAX_SIZE (1<<MAX_BIT)

struct ts_fifo {
    pthread_mutex_t fifo_lock ;
    int wr_ptr;
    int rd_ptr;
    int gap;
    FIFO_NODE_TYPE buff[MAX_SIZE]
};

#endif 
