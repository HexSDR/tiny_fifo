
/*

module sc_fifo#(
.AW(4),
.DW(32)
)(

.clk(),
.rst(),

.din(),
.wr(),
.full(),

.dout(),
.rd(),
.empty(),


.fwft_dout(),
.fifo_cntr() 

);
*/

module sc_fifo#(
        parameter AW = 5 ,
        parameter DW = 64,
        parameter ALMOST_FULL = 10 ,
        parameter ALMOST_EMPTY = 12
    )(
        input clk,rst,
        input [ DW-1:0] din,
        input wr,rd,
        output full,empty,
        output reg  almost_full,
        output reg almost_empty,
        output  reg  [ DW-1:0] dout,
        output   [ DW-1:0] fwft_dout,
        output reg [ AW:0] fifo_cntr
    );
    
    /*
        ILA4FIFO ILA4FIFO_i (
        .clk_0(clk),
        .probe0_0(wr),
        .probe1_0(rd),
        .probe2_0(full),
        .probe3_0(empty),
        .probe4_0(fifo_cntr),
        .probe5_0(din),
        .probe6_0(fwft_dout)
        );
        */
        
    localparam MAX_FIFO_LEN = (1<<AW ) ;
    localparam ALMOST_FULL_LEN  = MAX_FIFO_LEN - 10  ;
    localparam ALMOST_EMPTY_LEN = 5  ;
    reg [ DW-1:0] buff[0:  MAX_FIFO_LEN -1] ;
    reg [ AW-1:0] wr_ptr, rd_ptr ;
    assign full  = fifo_cntr >= (  MAX_FIFO_LEN   - 2 ) ;
   /// assign real_full  = fifo_cntr >= (  MAX_FIFO_LEN   - 2 ) ;
    assign empty = fifo_cntr == 0 ;
    always @* almost_full <= fifo_cntr > ALMOST_FULL_LEN ;
    always @* almost_empty <= fifo_cntr < ALMOST_EMPTY_LEN ;
    wire valid_rd =  rd ;
    wire valid_wr =    wr ;
    always@(posedge clk) if (rst) wr_ptr <= 0;else if(valid_wr)wr_ptr<=wr_ptr+1;
    always@(posedge clk) if (rst)rd_ptr <= 0 ;else if (valid_rd)rd_ptr <= rd_ptr+1;
    
    always@(posedge clk)
    casex ({rst,valid_wr,valid_rd})
        3'b1xx : fifo_cntr<=0;
        3'b010 : fifo_cntr<=fifo_cntr+1;
        3'b001 : fifo_cntr<=fifo_cntr-1;
        3'b011 ,3'b000 :fifo_cntr<=fifo_cntr ;
    endcase
    
    always@(posedge clk) if (valid_wr) buff[wr_ptr] <=din ;
    always@(posedge clk) if (valid_rd) dout <= buff[rd_ptr] ;
    assign  fwft_dout = buff[rd_ptr] ;
endmodule


