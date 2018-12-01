# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\rens_\Documents\platooning\PSoC\Platooning\AngleMeasurement.cydsn\AngleMeasurement.cyprj
# Date: Sat, 01 Dec 2018 13:56:03 GMT
#set_units -time ns
create_clock -name {Clock_In(routed)} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {Clock_In_1(routed)} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {Clock_In} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_clock -name {Clock_In_1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {ADC_SAR_B_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_generated_clock -name {ADC_SAR_A_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/aclk_glb_1}]]
create_generated_clock -name {SPI_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 13 25} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {UART_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Servo_Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 480001 960001} [list [get_pins {ClockBlock/dclk_glb_5}]]
create_generated_clock -name {Hbridge_Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2993 6001} [list [get_pins {ClockBlock/dclk_glb_4}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\rens_\Documents\platooning\PSoC\Platooning\AngleMeasurement.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\rens_\Documents\platooning\PSoC\Platooning\AngleMeasurement.cydsn\AngleMeasurement.cyprj
# Date: Sat, 01 Dec 2018 13:55:47 GMT
