#include "bontaco_init.h"

void init_rx220(){
	
	// release register write protection
	// 0xA500 : key code bit to write into PRCR
	// 0x0001 : write permission to registers related to clock
	// 0x0002 : write permission to registers related to MTU
	SYSTEM.PRCR.WORD = 0xA500 | 0x0001 | 0x0002;
	
	// clock initialization
	SYSTEM.SCKCR.BIT.ICK         = 0x0; // clock division by 1
	SYSTEM.SCKCR.BIT.PCKB        = 0x0; // peripheral clock division by 1
	SYSTEM.SCKCR3.BIT.CKSEL      = 0x1; // HOCO selected
	SYSTEM.HOCOCR.BIT.HCSTP      = 0x0; // HOCO on
	SYSTEM.HOCOCR2.BIT.HCFRQ     = 0x0; // HOCO 32MHz
	SYSTEM.HOCOPCR.BIT.HOCOPCNT  = 0x0; // HOCO power on
	
	// MPC multi-function pin controller
	// choose which peripheral to use
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P26PFS.BYTE = 0xa; // TXD1
	MPC.P40PFS.BIT.ASEL = 1; // analog input for wall sensor
	MPC.P41PFS.BIT.ASEL = 1; // analog input for wall sensor
	MPC.P42PFS.BIT.ASEL = 1; // analog input for wall sensor
	MPC.P43PFS.BIT.ASEL = 1; // analog input for wall sensor
	MPC.P44PFS.BIT.ASEL = 1; // analog input for battery watcher
	MPC.PA1PFS.BIT.PSEL = 0x2; // PA1 for Right motor phase counter A
	MPC.PA3PFS.BIT.PSEL = 0x2; // PA3 for Right motor phase counter B
	MPC.PA4PFS.BIT.PSEL = 0x2; // PA4 for Left motor phase counter A
	MPC.PA6PFS.BIT.PSEL = 0x2; // PA6 for Left motor phase counter B
	MPC.PE1PFS.BIT.PSEL = 0x1; // PE1 for motor PWM output (MTIOC4C)
	MPC.PE2PFS.BIT.PSEL = 0x1; // PE2 for motor PWM output (MTIOC4A)
	
	MPC.PWPR.BIT.PFSWE = 0; // write prphibited again

	
	// IO port initialization
	// PMR port mode register 0:IO, 1:peripheral
    PORTE.PMR.BYTE=0x00;
	PORTE.PMR.BIT.B1=1; // use portE1 and E2 for motor PWM output
	PORTE.PMR.BIT.B2=1;
    PORT1.PMR.BYTE=0x00;
    PORT2.PMR.BYTE=0x00;
	PORT2.PMR.BIT.B6=1; // use port 26 for TXD1 of SCI
    PORT3.PMR.BYTE=0x00;
    PORT4.PMR.BYTE=0x00; // use port40-43 for AD input of wall sensor, 44 for battery voltage watch
    PORT5.PMR.BYTE=0x00;
	PORTH.PMR.BYTE=0x00;
//	PORTA.PMR.BYTE=(1<<1) & (1<<3) & (1<<4) & (1<<6); // PortA1,3,4,6 for motor encoder pulse input
	PORTA.PMR.BIT.B1 = 1;
	PORTA.PMR.BIT.B3 = 1;
	PORTA.PMR.BIT.B4 = 1;
	PORTA.PMR.BIT.B6 = 1;
	PORTB.PMR.BIT.B0 = 0; // motor input2 Right
	PORTB.PMR.BIT.B1 = 0; // motor input1 Right
	PORTB.PMR.BIT.B5 = 0; // motor input1 Left
	PORTB.PMR.BIT.B6 = 0; // motor input2 Left
	PORTB.PMR.BIT.B7 = 0; // motor standby
	PORTB.PMR.BIT.B3 = 0; // buzzer
	
	// PDR port direction register 0:read, 1:write
    PORTE.PDR.BYTE=0x38;
    PORT5.PDR.BYTE=0x30;
    PORT1.PDR.BYTE=0xf0;
    PORT2.PDR.BYTE=0x80;
    PORT3.PDR.BYTE=0x06;
    PORT4.PDR.BYTE=0x00; // port40-44 are input
	PORTH.PDR.BYTE=0xff;
	PORTA.PDR.BYTE=0x00; // portA1,3,4,6 for motor encoder pulse input
	PORTB.PDR.BIT.B0 = 1; // portB0 for motor input2 Right
	PORTB.PDR.BIT.B1 = 1; // portB1 for motor input1 Right
	PORTB.PDR.BIT.B5 = 1; // portB5 for motor input1 Left
	PORTB.PDR.BIT.B6 = 1; // portB6 for motor input2 Left
	PORTB.PDR.BIT.B7 = 1; // portB7 for motor standby
	PORTB.PDR.BIT.B3 = 1; // portB3 for buzzer
    
	// PODR port output data register
	PORTE.PODR.BYTE=0x00;
    PORT5.PODR.BYTE=0x00;
    PORT1.PODR.BYTE=0x00;
    PORT2.PODR.BYTE=0x00;
    PORT3.PODR.BYTE=0x00;	
    PORTH.PODR.BYTE=0x00;
    PORTB.PODR.BIT.B0=0;
    PORTB.PODR.BIT.B1=0;
    PORTB.PODR.BIT.B5=0;
    PORTB.PODR.BIT.B6=0;
    PORTB.PODR.BIT.B7=0;
    PORTB.PODR.BIT.B3=0;
	
		
	// start MTU
	MSTP(MTU) = 0;
	
	// setting MTU
	// timer priscaler, clock divided by 16
	MTU3.TCR.BIT.TPSC = 0x2;
	// clock edge, rising edge
	MTU3.TCR.BIT.CKEG = 0x0;
	// clear at compare match with TGRB
	MTU3.TCR.BIT.CCLR = 0x2;
	// timer mode register, normal mode
	MTU3.TMDR.BIT.MD = 0x0;
	// interrupt permission for TGRB, timer is cleared with TGRB match
	MTU3.TIER.BIT.TGIEB = 1;
	// compare match at every 1/8ms(125us) with 32MHz clock devided by 16
	MTU3.TGRB = 250-1; // 32000/16/8-1
	// interrupt permission for TGRA
	MTU3.TIER.BIT.TGIEA = 1;
	// compare match occurs 25us ahead of TGRB compare match
	MTU3.TGRA = 200-1; // 32000/16(125/1000-25/1000)-1
	
	// permit interrupt by TGRB
	IEN(MTU3, TGIB3) = 1;
	IPR(MTU3, TGIB3) = 15;
	// permit interrupt by TGRA
	IEN(MTU3, TGIA3) = 1;
	IPR(MTU3, TGIA3) = 15;
	
	// encoder pulse counter initialization
	// phase count mode 1
	MTU1.TMDR.BIT.MD = 0x4;
	MTU2.TMDR.BIT.MD = 0x4;

	// timer for motor PWM
	// timer priscaler, clock divided by 1
	MTU4.TCR.BIT.TPSC = 0x0;
	// TCNT cleared by compare-match with TGRB
	MTU4.TCR.BIT.CCLR = 0x2;
	// clock edge, rising edge
	MTU4.TCR.BIT.CKEG = 0x0;
	// set timer mode to PWM mode1
	MTU4.TMDR.BIT.MD = 0x2;
	// enable timer output
	MTU.TOER.BIT.OE4A = 1;
	MTU.TOER.BIT.OE4C = 1;
	// behavior of MTIOC4A pin : initial value of LOW and HIGH on compare-match with TGRA
	MTU4.TIORH.BIT.IOA = 0x2;
	// behavior of MTIOC4A pin : LOW on compare-match with TGRB
	MTU4.TIORH.BIT.IOB = 0x1;
	// behavior of MTIOC4C pin : initial value of LOW and HIGH on compare-match with TGRC
	MTU4.TIORL.BIT.IOC = 0x2;
	// behavior of MTIOC4C pin : LOW on compare-match with TGRB
	MTU4.TIORL.BIT.IOD = 0x1;
	// PWM frequency to 100kHz by setting TGRB
	MTU4.TGRB = 320;
	MTU4.TGRD = 320;
	// initial values ofTGRA and TGRC to 160, duty ratio of 10%
	MTU4.TGRA = 320-32;
	MTU4.TGRC = 320-32;
	
	// MTU0 for buzzer
	// timer priscaler, clock divided by 16
	MTU0.TCR.BIT.TPSC = 0x2;
	// clock edge, rising edge
	MTU0.TCR.BIT.CKEG = 0x0;
	// clear at compare match with TGRB
	MTU0.TCR.BIT.CCLR = 0x2;
	// timer mode register, normal mode
	MTU0.TMDR.BIT.MD = 0x0;
	// interrupt permission for TGRB, timer is cleared with TGRB match
	MTU0.TIER.BIT.TGIEB = 1;
	// compare match at 2*2700Hz with 32MHz clock devided by 16
	MTU0.TGRB = 32000/16*10/27/2-1; // 32000/16/8-1

	// permit interrupt by TGRB
	IEN(MTU0, TGIB0) = 1;
	IPR(MTU0, TGIB0) = 15;

	// start timer
	MTU.TSTR.BIT.CST0 = 1;
	MTU.TSTR.BIT.CST1 = 1;
	MTU.TSTR.BIT.CST2 = 1;
	MTU.TSTR.BIT.CST3 = 1;
	MTU.TSTR.BIT.CST4 = 1;


	// SCI
	MSTP(SCI1) = 0;           // release standby
	SCI1.SMR.BYTE = 0x00;    // PCLK/1, stopbit=1, no parity bit
	SCI1.SEMR.BIT.ABCS = 1;  // 1bit = 8clock cycle
	SCI1.BRR = 51;           // baudrate 38462bps
	SCI1.SCR.BYTE = 0x20;    // TE=1
	
	// AD converter
	MSTP(S12AD) = 0; // release standby
	S12AD.ADCSR.BIT.TRGE = 1; // triger disabled(software trigger is still enabled)
	S12AD.ADCSR.BIT.EXTRG = 1; // asynchronous
	S12AD.ADCSR.BIT.ADCS = 0; // single scan mode
	

}