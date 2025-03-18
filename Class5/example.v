module example(input clk, input rst, output reg [3:0] counter);
  always @(posedge clk or posedge rst) begin
    if (rst)
      counter <= 0;
    else
      counter <= counter + 1;
  end
endmodule
