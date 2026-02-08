### **Project Created**: Fall 2025 

### **Class**: Computer Organization and Design

##	Problem Description

The objective of this experiment was to design, simulate, and implement a digital 
stopwatch on the Diligent NEXYS4 FPGA board using Verilog. The stopwatch was required to 
measure elapsed time up to 10 minutes and display it on four multiplexed 7-segment displays 
representing minutes, tens of seconds, seconds, and tenths of seconds. To achieve this, the 100 
MHz on-board oscillator was divided down to 5 MHz using a clock management IP core. From 
this 5 MHz clock, additional derived clocks were generated to increment digit counters at 0.1-
second, 1-second, 10-second, and 1-minute intervals. The design also incorporated asynchronous 
reset functionality, start/stop control, and support for a blinking mode when paused. Verification 
was performed through functional simulation, timing analysis, and hardware implementation on 
the FPGA.
