

#ifdef __cplusplus
 extern "C" {
 #endif



#include <pthread.h>
#include <semaphore.h>

#include "tiny_fifo.h"
void init_ts_fifo(struct ts_fifo*p)
{
    
    pthread_mutex_init(&(p->fifo_lock),NULL);
    //init mutex
    p->wr_ptr=p->rd_ptr=p->gap=0 ;
    pthread_mutex_unlock(&(p->fifo_lock));
    
}

void push(struct ts_fifo*p,FIFO_NODE_TYPE d)
{
    pthread_mutex_lock(&(p->fifo_lock));
    p->buff[p->wr_ptr++]=d ;
    p->wr_ptr&=(MAX_SIZE-1);
    p->gap++;
    pthread_mutex_unlock(&(p->fifo_lock));
}



int is_fifo_empty(struct ts_fifo*p)
{
    int r ;
    pthread_mutex_lock(&(p->fifo_lock));
    r=(p->gap==0);
    pthread_mutex_unlock(&(p->fifo_lock));
    return r ;
} 
unsigned int is_fifo_full(struct ts_fifo*p)
{
    int r ;
    pthread_mutex_lock(&(p->fifo_lock));
    r=(p->gap==MAX_SIZE);
    pthread_mutex_unlock(&(p->fifo_lock));
    return r ;
}

FIFO_NODE_TYPE pop(struct ts_fifo*p)
{
    FIFO_NODE_TYPE r ;
    pthread_mutex_lock(&(p->fifo_lock));
    r=p->buff[p->rd_ptr++];
    p->rd_ptr&=(MAX_SIZE-1);
    p->gap--;
    pthread_mutex_unlock(&(p->fifo_lock));
    
    return r ;
}

 
 
#ifdef __cplusplus
}
#endif

