#define MAX_BIT  7
#define MAX_SIZE (1<<MAX_BIT) 
typedef int NODE_TYPE 
static NODE_TYPE buff[MAX_SIZE];
static unsigned int  wr_ptr=0,rd_ptr=0,gap=0 ;

void init_fifo(){
wr_ptr = rd_ptr = gap = 0;
}

void  push(NODE_TYPE d){
buff[wr_ptr++] = d;
wr_ptr &= ( MAX_SIZE - 1);
gap++;
}

//#define is_fifo_empty()  (gap==0) 
unsigned int  is_fifo_empty(){
return  ( gap==0 );
}
//#define is_fifo_full() (gap==MAX_SIZE )
unsigned int  is_fifo_full(){
return  ( gap==MAX_SIZE );
}

NODE_TYPE pop(void){
NODE_TYPE r = buff[rd_ptr++];
rd_ptr &= ( MAX_SIZE - 1);
gap--;
return r;
}
