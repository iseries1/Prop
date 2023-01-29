 GNU assembler version 2.21 (propeller-elf)
	 using BFD version (propellergcc_v1_0_0_2408) 2.21.
 options passed	: -lmm -cmm -ahdlnsg=cmm/libSSD1331.asm 
 input file    	: C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s
 output file   	: cmm/libSSD1331.o
 target        	: propeller-parallax-elf
 time stamp    	: 

   1              		.text
   2              	.Ltext0
   3              		.data
   4              		.balign	4
   5              	.LC0
   6 0000 48656C6C 		.ascii "Hello\0"
   6      6F00
   7 0006 0000     		.text
   8              		.global	_main
   9              	_main
  10              	.LFB1
  11              		.file 1 "libSSD1331.c"
   1:libSSD1331.c  **** /**
   2:libSSD1331.c  ****  * @brief Colored SSD1331 Display Driver
   3:libSSD1331.c  ****  * @author Michael Burmeister
   4:libSSD1331.c  ****  * @date December 11, 2018
   5:libSSD1331.c  ****  * @version 1.0
   6:libSSD1331.c  ****  * 
   7:libSSD1331.c  **** */
   8:libSSD1331.c  **** #include "SSD1331.h"
   9:libSSD1331.c  **** #include "simpletools.h"
  10:libSSD1331.c  **** 
  11:libSSD1331.c  **** #define OLEDDIN 6
  12:libSSD1331.c  **** #define OLEDCLK 5
  13:libSSD1331.c  **** #define OLEDCS  4
  14:libSSD1331.c  **** #define OLEDDC  3
  15:libSSD1331.c  **** #define OLEDRST 2
  16:libSSD1331.c  **** 
  17:libSSD1331.c  **** 
  18:libSSD1331.c  **** int main()
  19:libSSD1331.c  **** {
  12              		.loc 1 19 0
  13 0000 031F     		lpushm	#16+15
  14              	.LCFI0
  20:libSSD1331.c  ****   SSD1331_init(OLEDDIN, OLEDCLK, OLEDCS, OLEDDC, OLEDRST);
  15              		.loc 1 20 0
  16 0002 A303     		mov	r3, #3
  17 0004 A402     		mov	r4, #2
  18 0006 A006     		mov	r0, #6
  19 0008 A105     		mov	r1, #5
  20 000a A204     		mov	r2, #4
  21 000c 060000   		lcall	#_SSD1331_init
  21:libSSD1331.c  **** 
  22:libSSD1331.c  ****   SSD1331_textColor(SSD1331_color(255, 255, 255), 0);
  22              		.loc 1 22 0
  23 000f A2FF     		mov	r2, #255
  24 0011 A1FF     		mov	r1, #255
  25 0013 A0FF     		mov	r0, #255
  26 0015 060000   		lcall	#_SSD1331_color
  27 0018 B1       		mov	r1, #0
  28 0019 060000   		lcall	#_SSD1331_textColor
  23:libSSD1331.c  ****   
  24:libSSD1331.c  ****   SSD1331_writeSStr(15, 20, "Hello");
  29              		.loc 1 24 0
  30 001c A00F     		mov	r0, #15
  31 001e A114     		mov	r1, #20
  32 0020 620000   		mviw	r2,#.LC0
  33 0023 060000   		lcall	#_SSD1331_writeSStr
  25:libSSD1331.c  ****   
  26:libSSD1331.c  ****   SSD1331_drawLine(15, 50, 90, 50, SSD1331_color(255, 0, 0));
  34              		.loc 1 26 0
  35 0026 B1       		mov	r1, #0
  36 0027 B2       		mov	r2, #0
  37 0028 A0FF     		mov	r0, #255
  38 002a 060000   		lcall	#_SSD1331_color
  39 002d 0A40     		mov	r4, r0
  40 002f A332     		mov	r3, #50
  41 0031 A00F     		mov	r0, #15
  42 0033 A132     		mov	r1, #50
  43 0035 A25A     		mov	r2, #90
  44 0037 060000   		lcall	#_SSD1331_drawLine
  27:libSSD1331.c  ****   
  28:libSSD1331.c  ****   SSD1331_drawBox(10, 15, 95, 55, SSD1331_color(0, 255, 0));
  45              		.loc 1 28 0
  46 003a A1FF     		mov	r1, #255
  47 003c B2       		mov	r2, #0
  48 003d B0       		mov	r0, #0
  49 003e 060000   		lcall	#_SSD1331_color
  50 0041 0A40     		mov	r4, r0
  51 0043 A10F     		mov	r1, #15
  52 0045 A25F     		mov	r2, #95
  53 0047 A337     		mov	r3, #55
  54 0049 A00A     		mov	r0, #10
  55 004b 060000   		lcall	#_SSD1331_drawBox
  29:libSSD1331.c  ****   
  30:libSSD1331.c  ****   pause(5000);
  56              		.loc 1 30 0
  57 004e 608813   		mviw	r0,#5000
  58 0051 060000   		lcall	#_pause
  31:libSSD1331.c  ****   
  32:libSSD1331.c  ****   SSD1331_scrollRight(1, 0, 63, 1);
  59              		.loc 1 32 0
  60 0054 A001     		mov	r0, #1
  61 0056 B1       		mov	r1, #0
  62 0057 A23F     		mov	r2, #63
  63 0059 A301     		mov	r3, #1
  64 005b 060000   		lcall	#_SSD1331_scrollRight
  33:libSSD1331.c  ****   
  34:libSSD1331.c  ****   pause(5000);
  65              		.loc 1 34 0
  66 005e 608813   		mviw	r0,#5000
  67 0061 060000   		lcall	#_pause
  35:libSSD1331.c  ****   
  36:libSSD1331.c  ****   SSD1331_scrollStop();
  68              		.loc 1 36 0
  69 0064 060000   		lcall	#_SSD1331_scrollStop
  70              	.L2
  71 0067 7FFE     		brs	#.L2
  72              	.LFE1
 100              	.Letext0
 101              		.file 2 "D:/Documents/SimpleIDE/Learn/Simple Libraries/TextDevices/libsimpletext/simpletext.h"
DEFINED SYMBOLS
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:2      .text:00000000 .Ltext0
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:5      .data:00000000 .LC0
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:9      .text:00000000 _main
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:10     .text:00000000 .LFB1
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:13     .text:00000000 L0
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:72     .text:00000069 .LFE1
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:74     .debug_frame:00000000 .Lframe0
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:100    .text:00000069 .Letext0
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:103    .debug_info:00000000 .Ldebug_info0
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:315    .debug_abbrev:00000000 .Ldebug_abbrev0
C:\Users\mbmis006\AppData\Local\Temp\ccKC1vwv.s:498    .debug_line:00000000 .Ldebug_line0

UNDEFINED SYMBOLS
_SSD1331_init
_SSD1331_color
_SSD1331_textColor
_SSD1331_writeSStr
_SSD1331_drawLine
_SSD1331_drawBox
_pause
_SSD1331_scrollRight
_SSD1331_scrollStop
