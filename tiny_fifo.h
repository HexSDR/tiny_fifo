


#ifndef  __TINY_FIFO_H
#define __TINY_FIFO_H

typedef  int  FIFO_NODE_TYPE   ;


#define MAX_BIT  7
#define MAX_SIZE (1<<MAX_BIT)

struct ts_fifo {
    pthread_mutex_t fifo_lock ;
    int wr_ptr;
    int rd_ptr;
    int gap;
    FIFO_NODE_TYPE buff[MAX_SIZE]
};



void init_ts_fifo(struct ts_fifo*p) ; 
void push(struct ts_fifo*p,FIFO_NODE_TYPE d) ; 
int is_fifo_empty(struct ts_fifo*p) ; 
unsigned int is_fifo_full(struct ts_fifo*p) ;
FIFO_NODE_TYPE pop(struct ts_fifo*p)  ;

#endif 
