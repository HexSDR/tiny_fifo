

#typedef  int  FIFO_NODE_TYPE
#define MAX_BIT  7
#define MAX_SIZE (1<<MAX_BIT)

struct ts_fifo 
{
    pthread_mutex_t fifo_lock ;
    int wr_ptr,
    int rd_ptr,
    int gap,
    FIFO_NODE_TYPE buff[MAX_SIZE]
};


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
    p->buff[wr_ptr++]=d ;
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
//#define is_fifo_full() (gap==MAX_SIZE )
unsigned int is_fifo_full(struct ts_fifo*p)
{
    int r ;
    pthread_mutex_lock(&(p->fifo_lock));
    r=(gap==MAX_SIZE);
    pthread_mutex_unlock(&(p->fifo_lock));
    return r ;
}

FIFO_NODE_TYPE pop(struct ts_fifo*p)
{
    NODE_TYPE r 
    pthread_mutex_lock(&(p->fifo_lock));
    r=buff[rd_ptr++];
    rd_ptr&=(MAX_SIZE-1);
    gap--;
    pthread_mutex_unlock(&(p->fifo_lock));
    
    return r ;
}
