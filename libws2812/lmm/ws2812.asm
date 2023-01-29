 GNU assembler version 2.21 (propeller-elf)
	 using BFD version (propellergcc_v1_0_0_2408) 2.21.
 options passed	: -lmm -ahdlnsg=lmm/ws2812.asm 
 input file    	: C:\Users\mbmis006\AppData\Local\Temp\ccn0eFH1.s
 output file   	: lmm/ws2812.o
 target        	: propeller-parallax-elf
 time stamp    	: 

   1              		.text
   2              	.Ltext0
   3              		.balign	4
   4              		.global	_ws2812_set
   5              	_ws2812_set
   6              	.LFB1
   7              		.file 1 "ws2812.c"
   1:ws2812.c      **** /**
   2:ws2812.c      ****  * @brief Drive Neo Pixel ws2812 leds
   3:ws2812.c      ****  * @author Michael Burmeister
   4:ws2812.c      ****  * @date November 11, 2020
   5:ws2812.c      ****  * @version 1.0
   6:ws2812.c      ****  * 
   7:ws2812.c      **** */
   8:ws2812.c      **** 
   9:ws2812.c      **** #include "ws2812.h"
  10:ws2812.c      **** #include "simpletools.h"
  11:ws2812.c      **** 
  12:ws2812.c      **** void ws2812_set(int pin, unsigned long *leds, int num)
  13:ws2812.c      **** {
   8              		.loc 1 13 0
   9              	.LVL0
  10 0000 5B00FCA0 		mov	__TMP0,#(5<<4)+11
  11 0004 0000FC5C 		call	#__LMM_PUSHM
  12              	.LCFI0
  14:ws2812.c      ****   int txmask = 1 << pin;
  13              		.loc 1 14 0
  14 0008 0100FCA0 		mov	r14, #1
  13:ws2812.c      **** {
  15              		.loc 1 13 0
  16 000c 0000BCA0 		mov	r13, r1
  17 0010 0000BCA0 		mov	r12, r2
  18              		.loc 1 14 0
  19 0014 0000BC2C 		shl	r14, r0
  20              	.LVL1
  15:ws2812.c      ****   unsigned long color;
  16:ws2812.c      ****   unsigned int w;
  17:ws2812.c      ****   int bits;
  18:ws2812.c      ****   unsigned long hi, lo;
  19:ws2812.c      ****   
  20:ws2812.c      ****   hi = 72;
  21:ws2812.c      ****   lo = 28;
  22:ws2812.c      ****   
  23:ws2812.c      ****   low(pin);
  21              		.loc 1 23 0
  22 0018 00007C5C 		lcall	#_low
  22      00000000 
  23              	.LVL2
  24 0020 0000BCA0 		mov	r1, r13
  25              	.LBB2
  24:ws2812.c      ****   
  25:ws2812.c      ****   for (int j=0;j<num;j++)
  26              		.loc 1 25 0
  27 0024 0000FCA0 		mov	r6, #0
  28              	.LBB3
  26:ws2812.c      ****   {
  27:ws2812.c      ****     color = leds[j];
  28:ws2812.c      ****     color = color << 8;
  29:ws2812.c      ****   
  30:ws2812.c      ****     for (int i=0;i<24;i++)
  31:ws2812.c      ****     {
  32:ws2812.c      ****       __asm__ volatile (
  29              		.loc 1 32 0
  30 0028 4800FCA0 		mov	r3, #72
  31 002c 1C00FCA0 		mov	r4, #28
  32 0030 00007C5C 		jmp	#__LMM_FCACHE_LOAD
  33 0034 50000000 		long	.L7-.L6
  34              	.L6
  35 0038 00007C5C 		jmp	#__LMM_FCACHE_START+(.L2-.L6)
  36              	.LVL3
  37              	.L4
  38              	.LBE3
  27:ws2812.c      ****     color = leds[j];
  39              		.loc 1 27 0
  40 003c 0000BC08 		rdlong	r7, r1
  41              	.LVL4
  28:ws2812.c      ****     color = color << 8;
  42              		.loc 1 28 0
  43 0040 0800FC2C 		shl	r7, #8
  44              	.LVL5
  45 0044 1800FCA0 		mov	r5, #24
  46              	.LVL6
  47              	.L3
  48              	.LBB4
  49              		.loc 1 32 0 discriminator 2
  50              	' 32 "ws2812.c" 1
  51 0048 0100FC35 		          rcl     r7, #1 wc  
  52 004c 0000B0A0 		    if_c  mov     r11, r3      
  53 0050 00008CA0 		    if_nc mov     r11, r4      
  54 0054 0000BC68 		          or      outa, r14  
  55 0058 0000BC80 		          add     r11, cnt        
  56 005c 0000B0F8 		    if_c  waitcnt r11, r4      
  57 0060 00008CF8 		    if_nc waitcnt r11, r3      
  58 0064 0000BC64 		          andn    outa, r14  
  59 0068 0000FCF8 		          waitcnt r11, #0         
  60              		
  61              	' 0 "" 2
  30:ws2812.c      ****     for (int i=0;i<24;i++)
  62              		.loc 1 30 0 discriminator 2
  63 006c 0100FC86 		sub	r5, #1 wz
  64 0070 0000545C 		IF_NE	jmp	#__LMM_FCACHE_START+(.L3-.L6)
  65              	.LBE4
  25:ws2812.c      ****   for (int j=0;j<num;j++)
  66              		.loc 1 25 0
  67 0074 0100FC80 		add	r6, #1
  68              	.LVL7
  69 0078 0400FC80 		add	r1, #4
  70              	.LVL8
  71              	.L2
  25:ws2812.c      ****   for (int j=0;j<num;j++)
  72              		.loc 1 25 0 is_stmt 0 discriminator 1
  73 007c 00003CC3 		cmps	r6, r12 wz,wc
  74 0080 0000705C 		IF_B 	jmp	#__LMM_FCACHE_START+(.L4-.L6)
  75 0084 00003C5C 		jmp	__LMM_RET
  76              		.compress default
  77              	.L7
  78              	.LBE2
  33:ws2812.c      ****         "          rcl     %[color], #1 wc  \n\t"
  34:ws2812.c      ****         "    if_c  mov     %[w], %[hi]      \n\t"
  35:ws2812.c      ****         "    if_nc mov     %[w], %[lo]      \n\t"
  36:ws2812.c      ****         "          or      outa, %[txmask]  \n\t"
  37:ws2812.c      ****         "          add     %[w], cnt        \n\t"
  38:ws2812.c      ****         "    if_c  waitcnt %[w], %[lo]      \n\t"
  39:ws2812.c      ****         "    if_nc waitcnt %[w], %[hi]      \n\t"
  40:ws2812.c      ****         "          andn    outa, %[txmask]  \n\t"
  41:ws2812.c      ****         "          waitcnt %[w], #0         \n\t"
  42:ws2812.c      ****                    : [w]      "+r" (w),
  43:ws2812.c      ****                      [color]  "+r" (color)
  44:ws2812.c      ****                    : [txmask] "r"  (txmask),
  45:ws2812.c      ****                      [hi]     "r"  (hi),
  46:ws2812.c      ****                      [lo]     "r"  (lo)
  47:ws2812.c      ****          );
  48:ws2812.c      ****     }
  49:ws2812.c      ****   }
  50:ws2812.c      **** }  ...
  79              		.loc 1 50 0 is_stmt 1
  80 0088 5F00FCA0 		mov	__TMP0,#(5<<4)+15
  81 008c 0000FC5C 		call	#__LMM_POPRET
  82              		'' never returns
  83              	.LFE1
 125              	.Letext0
 126              		.file 2 "D:/Documents/SimpleIDE/Learn/Simple Libraries/TextDevices/libsimpletext/simpletext.h"
DEFINED SYMBOLS
C:\Users\mbmis006\AppData\Local\Temp\ccn0eFH1.s:5      .text:00000000 _ws2812_set
C:\Users\mbmis006\AppData\Local\Temp\ccn0eFH1.s:10     .text:00000000 L0
                     .debug_frame:00000000 .Lframe0
                            .text:00000000 .LFB1
                            .text:00000090 .LFE1
                    .debug_abbrev:00000000 .Ldebug_abbrev0
                            .text:00000000 .Ltext0
                            .text:00000090 .Letext0
                      .debug_line:00000000 .Ldebug_line0
                       .debug_loc:00000000 .LLST0
                       .debug_loc:00000020 .LLST1
                       .debug_loc:00000033 .LLST2
                       .debug_loc:00000051 .LLST3
                       .debug_loc:0000006f .LLST4
                       .debug_loc:0000008e .LLST5
                            .text:00000024 .LBB2
                            .text:00000088 .LBE2
                       .debug_loc:000000ac .LLST6
                    .debug_ranges:00000000 .Ldebug_ranges0
                       .debug_loc:000000cb .LLST7
                      .debug_info:00000000 .Ldebug_info0

UNDEFINED SYMBOLS
__TMP0
__LMM_PUSHM
__LMM_PUSHM_ret
r14
r13
r1
r12
r2
r0
__LMM_CALL
_low
r6
r3
r4
__LMM_FCACHE_LOAD
__LMM_FCACHE_START
r7
r5
r11
outa
cnt
__LMM_RET
__LMM_POPRET
__LMM_POPRET_ret
