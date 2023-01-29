 GNU assembler version 2.21 (propeller-elf)
	 using BFD version (propellergcc_v1_0_0_2408) 2.21.
 options passed	: -lmm -ahdlnsg=lmm/SBus.asm 
 input file    	: C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s
 output file   	: lmm/SBus.o
 target        	: propeller-parallax-elf
 time stamp    	: 

   1              		.text
   2              	.Ltext0
   3              		.balign	4
   4              		.global	_SBus_open
   5              	_SBus_open
   6              	.LFB1
   7              		.file 1 "SBus.c"
   1:SBus.c        **** /**
   2:SBus.c        ****  * @brief SBus receiver decoder
   3:SBus.c        ****  * @author Michael Burmeister
   4:SBus.c        ****  * @date December 13, 2017
   5:SBus.c        ****  * @version 1.0
   6:SBus.c        ****  * 
   7:SBus.c        **** */
   8:SBus.c        **** 
   9:SBus.c        **** #include "simpletools.h"
  10:SBus.c        **** #include "SBus.h"
  11:SBus.c        **** 
  12:SBus.c        **** void doRecSBus(void *);
  13:SBus.c        **** void doChannel(void);
  14:SBus.c        **** 
  15:SBus.c        **** int _Dc[26];
  16:SBus.c        **** int _Cc[17];
  17:SBus.c        **** int _Er;
  18:SBus.c        **** int _SBPin;
  19:SBus.c        **** int _Lock;
  20:SBus.c        **** 
  21:SBus.c        **** int SBus_open(int p)
  22:SBus.c        **** {
   8              		.loc 1 22 0
   9              	.LVL0
  10 0000 0400FC84 		sub	sp, #4
  11              	.LCFI0
  12 0004 00003C08 		wrlong	lr, sp
  13              	.LCFI1
  23:SBus.c        ****   int *cog;
  24:SBus.c        ****   
  25:SBus.c        ****   _SBPin = p;
  14              		.loc 1 25 0
  15 0008 00007C5C 		mvi	r6,#__SBPin
  15      00000000 
  22:SBus.c        **** {
  16              		.loc 1 22 0
  17 0010 0000BCA0 		mov	r7, r0
  26:SBus.c        ****   *cog = 0;
  27:SBus.c        ****   cog = cog_run(&doRecSBus, 50);
  18              		.loc 1 27 0
  19 0014 3200FCA0 		mov	r1, #50
  20 0018 00007C5C 		mvi	r0,#_doRecSBus
  20      00000000 
  21              	.LVL1
  25:SBus.c        ****   _SBPin = p;
  22              		.loc 1 25 0
  23 0020 00003C08 		wrlong	r7, r6
  24              		.loc 1 27 0
  25 0024 00007C5C 		lcall	#_cog_run
  25      00000000 
  26              	.LVL2
  28:SBus.c        ****   _Lock = locknew();
  27              		.loc 1 28 0
  28 002c 0400FC0D 		locknew	r7 wc
  29 0030 0100F0A4 		IF_B  neg	r7,#1
  30 0034 00007C5C 		mvi	r6,#__Lock
  30      00000000 
  29:SBus.c        ****   if (_Lock < 0)
  31              		.loc 1 29 0
  32 003c 00007CC3 		cmps	r7, #0 wz,wc
  30:SBus.c        ****     return -1;
  33              		.loc 1 30 0
  34 0040 0100F0A4 		IF_B  neg	r0, #1
  35              	.LVL3
  28:SBus.c        ****   _Lock = locknew();
  36              		.loc 1 28 0
  37 0044 00003C08 		wrlong	r7, r6
  29:SBus.c        ****   if (_Lock < 0)
  38              		.loc 1 29 0
  39 0048 1000F080 		IF_B 	brs	#.L2
  31:SBus.c        ****   if (*cog == 0)
  40              		.loc 1 31 0
  41 004c 0000BC08 		rdlong	r7, r0
  32:SBus.c        ****     return -1;
  42              		.loc 1 32 0
  43 0050 00007CC3 		cmps	r7, #0 wz,wc
  44 0054 0000D4A0 		IF_NE mov	r0,#0
  45 0058 0100E8A4 		IF_E  neg	r0,#1
  46              	.L2
  33:SBus.c        ****   else
  34:SBus.c        ****     return 0;
  35:SBus.c        **** }
  47              		.loc 1 35 0
  48 005c 0000BC08 		rdlong	lr, sp
  49 0060 0400FC80 		add	sp, #4
  50 0064 0000BCA0 		mov	pc,lr
  51              	.LFE1
  52              		.balign	4
  53              		.global	_doChannel
  54              	_doChannel
  55              	.LFB3
  36:SBus.c        **** 
  37:SBus.c        **** void doRecSBus(void *par)
  38:SBus.c        **** {
  39:SBus.c        ****   int rxmask;
  40:SBus.c        ****   int rxbits;
  41:SBus.c        ****   int rxdata;
  42:SBus.c        ****   int baud;
  43:SBus.c        ****   int wcnt;
  44:SBus.c        ****   int c;
  45:SBus.c        ****   
  46:SBus.c        ****   rxmask = 1 << _SBPin;
  47:SBus.c        ****   baud = 800;
  48:SBus.c        ****   c = 0;
  49:SBus.c        ****   
  50:SBus.c        ****   while (1)
  51:SBus.c        ****   {
  52:SBus.c        ****     waitpne(0, rxmask);       // Wait for Start Bit
  53:SBus.c        ****     rxbits = 10;
  54:SBus.c        ****     rxdata = 0;
  55:SBus.c        ****     wcnt = baud >> 1;
  56:SBus.c        ****     wcnt = wcnt + CNT;
  57:SBus.c        ****     while (rxbits > 0)
  58:SBus.c        ****     {
  59:SBus.c        ****       wcnt += baud;
  60:SBus.c        ****       waitcnt2(wcnt, baud);   // Wait for Center of Next bit
  61:SBus.c        ****       rxdata = rxdata << 1;
  62:SBus.c        ****       if ((rxmask & INA) != rxmask)  // Reverse Bit value
  63:SBus.c        ****         rxdata = rxdata | 1;
  64:SBus.c        **** 
  65:SBus.c        ****       rxbits--;
  66:SBus.c        ****     }
  67:SBus.c        ****     rxdata = rxdata >> 2;    // Dump Parity and Stop
  68:SBus.c        ****     if (rxdata == 0xf0)      // SBus Start Byte Frame value
  69:SBus.c        ****       c = 0;
  70:SBus.c        ****     _Dc[c] = rxdata;
  71:SBus.c        ****     if (c++ > 25)            // Just in case
  72:SBus.c        ****       c = 25;
  73:SBus.c        ****     if (c == 24)
  74:SBus.c        ****       doChannel();
  75:SBus.c        ****   }
  76:SBus.c        **** }
  77:SBus.c        **** 
  78:SBus.c        **** void doChannel()
  79:SBus.c        **** {
  56              		.loc 1 79 0
  57              	.LVL4
  58 0068 2E00FCA0 		mov	__TMP0,#(2<<4)+14
  59 006c 0000FC5C 		call	#__LMM_PUSHM
  60              	.LCFI2
  61 0070 00007C5C 		mvi	r2,#__Lock
  61      00000000 
  62 0078 00007C5C 		jmp	#__LMM_FCACHE_LOAD
  63 007c 18000000 		long	.L20-.L19
  64              	.L19
  65              	.L7
  80:SBus.c        ****   int i;
  81:SBus.c        ****   short c, b, bc;
  82:SBus.c        ****   
  83:SBus.c        ****   c = 0;         // Channel
  84:SBus.c        ****   b = 0x80;      // Bit Position high -> low
  85:SBus.c        ****   bc = 1;        // Bit Channel value
  86:SBus.c        ****   i = 1;         // Should be 1
  87:SBus.c        ****   while (lockset(_Lock));
  66              		.loc 1 87 0 discriminator 1
  67 0080 0000BC08 		rdlong	r6, r2
  68 0084 06007C0D 		lockset	r6 wc
  69 0088 0000BC70 		muxc	r7,__MASK_FFFFFFFF
  70 008c 00007CC3 		cmps	r7, #0 wz,wc
  71 0090 0000545C 		IF_NE	jmp	#__LMM_FCACHE_START+(.L7-.L19)
  72 0094 00003C5C 		jmp	__LMM_RET
  73              		.compress default
  74              	.L20
  88:SBus.c        ****   _Cc[0] = 0;      // Clear Channel value
  75              		.loc 1 88 0
  76 0098 00007C5C 		mvi	r0,#__Cc
  76      00000000 
  77 00a0 0000FCA0 		mov	r4, #0
  85:SBus.c        ****   bc = 1;        // Bit Channel value
  78              		.loc 1 85 0
  79 00a4 0100FCA0 		mov	r6, #1
  84:SBus.c        ****   b = 0x80;      // Bit Position high -> low
  80              		.loc 1 84 0
  81 00a8 8000FCA0 		mov	r7, #128
  83:SBus.c        ****   c = 0;         // Channel
  82              		.loc 1 83 0
  83 00ac 0000FCA0 		mov	r5, #0
  86:SBus.c        ****   i = 1;         // Should be 1
  84              		.loc 1 86 0
  85 00b0 0100FCA0 		mov	r3, #1
  86 00b4 00007C5C 		mvi	r14,#__Dc
  86      00000000 
  89:SBus.c        ****   while (c < 16) // Do 16 Channels
  90:SBus.c        ****   {
  91:SBus.c        ****     if ((_Dc[i] & b) == b)
  92:SBus.c        ****       _Cc[c] |= bc;
  93:SBus.c        ****     b = b >> 1;
  94:SBus.c        ****     if (b == 0)
  95:SBus.c        ****     {
  96:SBus.c        ****       b = 0x80;
  97:SBus.c        ****       i++;
  98:SBus.c        ****     }
  99:SBus.c        ****     bc = bc << 1;
 100:SBus.c        ****     if (bc > 0x400)
  87              		.loc 1 100 0
  88 00bc 00007C5C 		mvi	lr,#1024
  88      00040000 
  88:SBus.c        ****   _Cc[0] = 0;      // Clear Channel value
  89              		.loc 1 88 0
  90 00c4 00003C08 		wrlong	r4, r0
  91 00c8 4800FC80 		brs	#.L12
  92              	.LVL5
  93              	.L9
  99:SBus.c        ****     bc = bc << 1;
  94              		.loc 1 99 0
  95 00cc 1100FC2C 		shl	r6, #17
  94:SBus.c        ****     if (b == 0)
  96              		.loc 1 94 0
  97 00d0 1000FC3A 		sar	r7, #16 wz
  98              	.LVL6
  99:SBus.c        ****     bc = bc << 1;
  99              		.loc 1 99 0
 100 00d4 1000FC38 		sar	r6, #16
  97:SBus.c        ****       i++;
 101              		.loc 1 97 0
 102 00d8 0100E880 		IF_E  add	r3, #1
 103              	.LVL7
  96:SBus.c        ****       b = 0x80;
 104              		.loc 1 96 0
 105 00dc 8000E8A0 		IF_E  mov	r7, #128
 106              	.LVL8
 107              		.loc 1 100 0
 108 00e0 00003CC3 		cmps	r6, lr wz,wc
 109 00e4 2400F880 		IF_BE	brs	#.L11
 110              	.LVL9
 101:SBus.c        ****     {
 102:SBus.c        ****       bc = 1;
 103:SBus.c        ****       c++;
 111              		.loc 1 103 0
 112 00e8 0100FC80 		add	r5, #1
 113 00ec 1000FC2C 		shl	r5, #16
 114 00f0 1000FC38 		sar	r5, #16
 115              	.LVL10
 104:SBus.c        ****       _Cc[c] = 0;
 116              		.loc 1 104 0
 117 00f4 0000BCA0 		mov	r6, r5
 118 00f8 0200FC2C 		shl	r6, #2
 119 00fc 0000BC80 		add	r6, r0
 120 0100 0000FCA0 		mov	r4, #0
 121 0104 00003C08 		wrlong	r4, r6
 102:SBus.c        ****       bc = 1;
 122              		.loc 1 102 0
 123 0108 0100FCA0 		mov	r6, #1
 124              	.LVL11
 125              	.L11
  89:SBus.c        ****   while (c < 16) // Do 16 Channels
 126              		.loc 1 89 0 discriminator 1
 127 010c 0F007CC3 		cmps	r5, #15 wz,wc
 128 0110 4000C480 		IF_A 	brs	#.L17
 129              	.LVL12
 130              	.L12
  91:SBus.c        ****     if ((_Dc[i] & b) == b)
 131              		.loc 1 91 0
 132 0114 0000BCA0 		mov	r4, r3
 133 0118 0200FC2C 		shl	r4, #2
 134 011c 0000BC80 		add	r4, r14
 135 0120 0000BC08 		rdlong	r4, r4
 136 0124 0000BC60 		and	r4, r7
 137 0128 00003CC3 		cmps	r7, r4 wz,wc
  93:SBus.c        ****     b = b >> 1;
 138              		.loc 1 93 0
 139 012c 0100FC38 		sar	r7, #1
 140 0130 1000FC2C 		shl	r7, #16
  91:SBus.c        ****     if ((_Dc[i] & b) == b)
 141              		.loc 1 91 0
 142 0134 6C00D484 		IF_NE	brs	#.L9
  92:SBus.c        ****       _Cc[c] |= bc;
 143              		.loc 1 92 0
 144 0138 0000BCA0 		mov	r4, r5
 145 013c 0200FC2C 		shl	r4, #2
 146 0140 0000BC80 		add	r4, r0
 147 0144 0000BC08 		rdlong	r1, r4
 148 0148 0000BC68 		or	r1, r6
 149 014c 00003C08 		wrlong	r1, r4
 150 0150 8800FC84 		brs	#.L9
 151              	.LVL13
 152              	.L17
 105:SBus.c        ****     }
 106:SBus.c        ****   }
 107:SBus.c        ****   lockclr(_Lock);
 153              		.loc 1 107 0
 154 0154 0000BC08 		rdlong	r7, r2
 155              	.LVL14
 156 0158 07007C0C 		lockclr	r7
 108:SBus.c        ****   _Er = 0;
 109:SBus.c        ****   if (_Dc[23] == 0x20)
 157              		.loc 1 109 0
 158 015c 00007C5C 		mvi	r6,#__Dc+92
 158      00000000 
 159              	.LVL15
 108:SBus.c        ****   _Er = 0;
 160              		.loc 1 108 0
 161 0164 00007C5C 		mvi	r7,#__Er
 161      00000000 
 162              		.loc 1 109 0
 163 016c 0000BC08 		rdlong	r6, r6
 108:SBus.c        ****   _Er = 0;
 164              		.loc 1 108 0
 165 0170 0000FCA0 		mov	r5, #0
 166              	.LVL16
 167              		.loc 1 109 0
 168 0174 20007CC3 		cmps	r6, #32 wz,wc
 108:SBus.c        ****   _Er = 0;
 169              		.loc 1 108 0
 170 0178 00003C08 		wrlong	r5, r7
 171              		.loc 1 109 0
 172 017c 1400E880 		IF_E 	brs	#.L18
 110:SBus.c        ****     _Er = 1;
 111:SBus.c        ****   if (_Dc[23] == 0x30)
 173              		.loc 1 111 0
 174 0180 30007CC3 		cmps	r6, #48 wz,wc
 112:SBus.c        ****     _Er = -1;
 175              		.loc 1 112 0
 176 0184 0100E8A4 		IF_E  neg	r4, #1
 177 0188 00002808 		IF_E  wrlong	r4, r7
 113:SBus.c        **** }
 178              		.loc 1 113 0
 179 018c 2F00FCA0 		mov	__TMP0,#(2<<4)+15
 180 0190 0000FC5C 		call	#__LMM_POPRET
 181              		'' never returns
 182              	.L18
 110:SBus.c        ****     _Er = 1;
 183              		.loc 1 110 0
 184 0194 0100FCA0 		mov	r6, #1
 185 0198 00003C08 		wrlong	r6, r7
 186              		.loc 1 113 0
 187 019c 2F00FCA0 		mov	__TMP0,#(2<<4)+15
 188 01a0 0000FC5C 		call	#__LMM_POPRET
 189              		'' never returns
 190              	.LFE3
 191              		.balign	4
 192              		.global	_doRecSBus
 193              	_doRecSBus
 194              	.LFB2
  38:SBus.c        **** {
 195              		.loc 1 38 0
 196              	.LVL17
 197 01a4 7900FCA0 		mov	__TMP0,#(7<<4)+9
 198 01a8 0000FC5C 		call	#__LMM_PUSHM
 199              	.LCFI3
  46:SBus.c        ****   rxmask = 1 << _SBPin;
 200              		.loc 1 46 0
 201 01ac 00007C5C 		mvi	r7,#__SBPin
 201      00000000 
 202 01b4 0100FCA0 		mov	r14, #1
  48:SBus.c        ****   c = 0;
 203              		.loc 1 48 0
 204 01b8 0000FCA0 		mov	r12, #0
 205 01bc 00007C5C 		mvi	r9,#__Dc
 205      00000000 
  52:SBus.c        ****     waitpne(0, rxmask);       // Wait for Start Bit
 206              		.loc 1 52 0
 207 01c4 0000FCA0 		mov	r10, #0
  37:SBus.c        **** void doRecSBus(void *par)
 208              		.loc 1 37 0
 209 01c8 00007C5C 		mvi	r11,#8400
 209      D0200000 
  59:SBus.c        ****       wcnt += baud;
 210              		.loc 1 59 0
 211 01d0 00007C5C 		mvi	r13,#800
 211      20030000 
  46:SBus.c        ****   rxmask = 1 << _SBPin;
 212              		.loc 1 46 0
 213 01d8 0000BC08 		rdlong	r7, r7
 214 01dc 0000BC2C 		shl	r14, r7
 215              	.LVL18
 216              	.L31
  52:SBus.c        ****     waitpne(0, rxmask);       // Wait for Start Bit
 217              		.loc 1 52 0
 218 01e0 00003CF4 		waitpne	r10,r14
 219              	.LVL19
  56:SBus.c        ****     wcnt = wcnt + CNT;
 220              		.loc 1 56 0
 221 01e4 0000BCA0 		mov	r4, CNT
 222 01e8 0000BCA0 		mov	r7, r4
 223 01ec 9001FC80 		add	r7, #400
 224              	.LVL20
  37:SBus.c        **** void doRecSBus(void *par)
 225              		.loc 1 37 0
 226 01f0 0000BC80 		add	r4, r11
  54:SBus.c        ****     rxdata = 0;
 227              		.loc 1 54 0
 228 01f4 0000FCA0 		mov	r5, #0
 229              	.LVL21
 230 01f8 00007C5C 		jmp	#__LMM_FCACHE_LOAD
 231 01fc 2C000000 		long	.L33-.L32
 232              	.L32
 233              	.L24
  59:SBus.c        ****       wcnt += baud;
 234              		.loc 1 59 0
 235 0200 0000BC80 		add	r7, r13
 236              	.LVL22
  60:SBus.c        ****       waitcnt2(wcnt, baud);   // Wait for Center of Next bit
 237              		.loc 1 60 0
 238 0204 0000BCA0 		mov	r6, r7
 239 0208 0000BCF8 		waitcnt	r6,r13
  62:SBus.c        ****       if ((rxmask & INA) != rxmask)  // Reverse Bit value
 240              		.loc 1 62 0
 241 020c 0000BCA0 		mov	r6, INA
 242 0210 0000BC60 		and	r6, r14
 243 0214 00003CC3 		cmps	r14, r6 wz,wc
  61:SBus.c        ****       rxdata = rxdata << 1;
 244              		.loc 1 61 0
 245 0218 0100FC2C 		shl	r5, #1
 246              	.LVL23
  63:SBus.c        ****         rxdata = rxdata | 1;
 247              		.loc 1 63 0
 248 021c 0100D468 		IF_NE or	r5, #1
 249              	.LVL24
  57:SBus.c        ****     while (rxbits > 0)
 250              		.loc 1 57 0
 251 0220 00003CC3 		cmps	r7, r4 wz,wc
 252 0224 0000545C 		IF_NE	jmp	#__LMM_FCACHE_START+(.L24-.L32)
 253 0228 00003C5C 		jmp	__LMM_RET
 254              		.compress default
 255              	.L33
  67:SBus.c        ****     rxdata = rxdata >> 2;    // Dump Parity and Stop
 256              		.loc 1 67 0
 257 022c 0200FC38 		sar	r5, #2
 258              	.LVL25
  68:SBus.c        ****     if (rxdata == 0xf0)      // SBus Start Byte Frame value
 259              		.loc 1 68 0
 260 0230 F0007CC3 		cmps	r5, #240 wz,wc
 261 0234 3400E880 		IF_E 	brs	#.L25
  70:SBus.c        ****     _Dc[c] = rxdata;
 262              		.loc 1 70 0
 263 0238 0000BCA0 		mov	r7, r12
 264              	.LVL26
 265 023c 0200FC2C 		shl	r7, #2
 266 0240 0000BC80 		add	r7, r9
  71:SBus.c        ****     if (c++ > 25)            // Just in case
 267              		.loc 1 71 0
 268 0244 19007CC3 		cmps	r12, #25 wz,wc
  72:SBus.c        ****       c = 25;
 269              		.loc 1 72 0
 270 0248 1900C4A0 		IF_A  mov	r12, #25
 271              	.LVL27
  70:SBus.c        ****     _Dc[c] = rxdata;
 272              		.loc 1 70 0
 273 024c 00003C08 		wrlong	r5, r7
  71:SBus.c        ****     if (c++ > 25)            // Just in case
 274              		.loc 1 71 0
 275 0250 7400C484 		IF_A 	brs	#.L31
 276 0254 0100FC80 		add	r12, #1
  73:SBus.c        ****     if (c == 24)
 277              		.loc 1 73 0
 278 0258 18007CC3 		cmps	r12, #24 wz,wc
 279 025c 8000D484 		IF_NE	brs	#.L31
  74:SBus.c        ****       doChannel();
 280              		.loc 1 74 0
 281 0260 00007C5C 		lcall	#_doChannel
 281      00000000 
 282              	.LVL28
 283 0268 8C00FC84 		brs	#.L31
 284              	.LVL29
 285              	.L25
  70:SBus.c        ****     _Dc[c] = rxdata;
 286              		.loc 1 70 0
 287 026c F000FCA0 		mov	r7, #240
 288              	.LVL30
  71:SBus.c        ****     if (c++ > 25)            // Just in case
 289              		.loc 1 71 0
 290 0270 0100FCA0 		mov	r12, #1
  70:SBus.c        ****     _Dc[c] = rxdata;
 291              		.loc 1 70 0
 292 0274 00003C08 		wrlong	r7, r9
 293              	.LVL31
 294 0278 9C00FC84 		brs	#.L31
 295              	.LFE2
 296              		.balign	4
 297              		.global	_SBus_getChannel
 298              	_SBus_getChannel
 299              	.LFB4
 114:SBus.c        **** 
 115:SBus.c        **** short SBus_getChannel(int c)
 116:SBus.c        **** {
 300              		.loc 1 116 0
 301              	.LVL32
 117:SBus.c        ****   if (c > 16)
 302              		.loc 1 117 0
 303 027c 10007CC3 		cmps	r0, #16 wz,wc
 304 0280 5800C480 		IF_A 	brs	#.L37
 118:SBus.c        ****     return -1;
 119:SBus.c        ****   if (c < 1)
 305              		.loc 1 119 0
 306 0284 00007CC3 		cmps	r0, #0 wz,wc
 307 0288 5800F880 		IF_BE	brs	#.L38
 308 028c 00007C5C 		mvi	r5,#__Lock
 308      00000000 
 309 0294 00007C5C 		jmp	#__LMM_FCACHE_LOAD
 310 0298 18000000 		long	.L41-.L40
 311              	.L40
 312              	.L36
 120:SBus.c        ****     return -1;
 121:SBus.c        ****   while (lockset(_Lock));
 313              		.loc 1 121 0 discriminator 1
 314 029c 0000BC08 		rdlong	r7, r5
 315 02a0 06007C0D 		lockset	r7 wc
 316 02a4 0000BC70 		muxc	r6,__MASK_FFFFFFFF
 317 02a8 00007CC3 		cmps	r6, #0 wz,wc
 318 02ac 0000545C 		IF_NE	jmp	#__LMM_FCACHE_START+(.L36-.L40)
 319 02b0 00003C5C 		jmp	__LMM_RET
 320              		.compress default
 321              	.L41
 122:SBus.c        ****   c = _Cc[c-1];
 322              		.loc 1 122 0
 323 02b4 0100FC84 		sub	r0, #1
 324              	.LVL33
 325 02b8 0200FC2C 		shl	r0, #2
 326              	.LVL34
 327 02bc 00007C5C 		mvi	r6,#__Cc
 327      00000000 
 328 02c4 0000BC80 		add	r6, r0
 329 02c8 0000BC08 		rdlong	r0, r6
 330              	.LVL35
 123:SBus.c        ****   lockclr(_Lock);
 331              		.loc 1 123 0
 332 02cc 07007C0C 		lockclr	r7
 124:SBus.c        ****   return c;
 333              		.loc 1 124 0
 334 02d0 1000FC2C 		shl	r0, #16
 335 02d4 1000FC38 		sar	r0, #16
 336 02d8 0000BCA0 		mov	pc,lr
 337              	.LVL36
 338              	.L37
 118:SBus.c        ****     return -1;
 339              		.loc 1 118 0
 340 02dc 0100FCA4 		neg	r0, #1
 341              	.LVL37
 342 02e0 0000BCA0 		mov	pc,lr
 343              	.LVL38
 344              	.L38
 120:SBus.c        ****     return -1;
 345              		.loc 1 120 0
 346 02e4 0100FCA4 		neg	r0, #1
 347              	.LVL39
 125:SBus.c        **** }
 348              		.loc 1 125 0
 349 02e8 0000BCA0 		mov	pc,lr
 350              	.LFE4
 351              		.balign	4
 352              		.global	_SBus_getAdjChannel
 353              	_SBus_getAdjChannel
 354              	.LFB5
 126:SBus.c        **** 
 127:SBus.c        **** short SBus_getAdjChannel(int c)
 128:SBus.c        **** {
 355              		.loc 1 128 0
 356              	.LVL40
 129:SBus.c        ****   if (c > 16)
 357              		.loc 1 129 0
 358 02ec 10007CC3 		cmps	r0, #16 wz,wc
 359 02f0 8800C480 		IF_A 	brs	#.L45
 130:SBus.c        ****     return -1;
 131:SBus.c        ****   if (c < 1)
 360              		.loc 1 131 0
 361 02f4 00007CC3 		cmps	r0, #0 wz,wc
 362 02f8 8800F880 		IF_BE	brs	#.L46
 363 02fc 00007C5C 		mvi	r5,#__Lock
 363      00000000 
 364 0304 00007C5C 		jmp	#__LMM_FCACHE_LOAD
 365 0308 18000000 		long	.L49-.L48
 366              	.L48
 367              	.L44
 132:SBus.c        ****     return -1;
 133:SBus.c        ****   while (lockset(_Lock));
 368              		.loc 1 133 0 discriminator 1
 369 030c 0000BC08 		rdlong	r7, r5
 370 0310 06007C0D 		lockset	r7 wc
 371 0314 0000BC70 		muxc	r6,__MASK_FFFFFFFF
 372 0318 00007CC3 		cmps	r6, #0 wz,wc
 373 031c 0000545C 		IF_NE	jmp	#__LMM_FCACHE_START+(.L44-.L48)
 374 0320 00003C5C 		jmp	__LMM_RET
 375              		.compress default
 376              	.L49
 134:SBus.c        ****   c = _Cc[c-1] * 10/16 + 875;
 377              		.loc 1 134 0
 378 0324 0100FC84 		sub	r0, #1
 379              	.LVL41
 380 0328 0200FC2C 		shl	r0, #2
 381              	.LVL42
 382 032c 00007C5C 		mvi	r6,#__Cc
 382      00000000 
 383 0334 0000BC80 		add	r6, r0
 384 0338 0000BC08 		rdlong	r5, r6
 385 033c 0000BCA0 		mov	r6, r5
 386 0340 0100FC2C 		shl	r6, #1
 387 0344 0300FC2C 		shl	r5, #3
 388 0348 0000BC80 		add	r6, r5
 389 034c 0000BCA0 		mov	r0, r6
 390 0350 00007CC3 		cmps	r6, #0 wz,wc
 391 0354 0F00FC80 		add	r0, #15
 392 0358 00008CA0 		IF_AE mov	r0,r6
 393 035c 0400FC38 		sar	r0, #4
 394              	.LVL43
 135:SBus.c        ****   lockclr(_Lock);
 395              		.loc 1 135 0
 396 0360 07007C0C 		lockclr	r7
 134:SBus.c        ****   c = _Cc[c-1] * 10/16 + 875;
 397              		.loc 1 134 0
 398 0364 00007C5C 		mvi	r7,#875
 398      6B030000 
 399 036c 0000BC80 		add	r0, r7
 400              	.LVL44
 136:SBus.c        ****   return c;
 401              		.loc 1 136 0
 402 0370 1000FC2C 		shl	r0, #16
 403 0374 1000FC38 		sar	r0, #16
 404 0378 0000BCA0 		mov	pc,lr
 405              	.LVL45
 406              	.L45
 130:SBus.c        ****     return -1;
 407              		.loc 1 130 0
 408 037c 0100FCA4 		neg	r0, #1
 409              	.LVL46
 410 0380 0000BCA0 		mov	pc,lr
 411              	.LVL47
 412              	.L46
 132:SBus.c        ****     return -1;
 413              		.loc 1 132 0
 414 0384 0100FCA4 		neg	r0, #1
 415              	.LVL48
 137:SBus.c        **** }
 416              		.loc 1 137 0
 417 0388 0000BCA0 		mov	pc,lr
 418              	.LFE5
 419              		.balign	4
 420              		.global	_SBus_getStatus
 421              	_SBus_getStatus
 422              	.LFB6
 138:SBus.c        **** 
 139:SBus.c        **** short SBus_getStatus()
 140:SBus.c        **** {
 423              		.loc 1 140 0
 141:SBus.c        ****   return _Er;
 424              		.loc 1 141 0
 425 038c 00007C5C 		mvi	r7,#__Er
 425      00000000 
 426 0394 0000BC08 		rdlong	r0, r7
 427 0398 1000FC2C 		shl	r0, #16
 428 039c 1000FC38 		sar	r0, #16
 142:SBus.c        **** }
 429              		.loc 1 142 0
 430 03a0 0000BCA0 		mov	pc,lr
 431              	.LFE6
 432              		.comm	__Lock,4,4
 433              		.comm	__SBPin,4,4
 434              		.comm	__Er,4,4
 435              		.comm	__Cc,68,4
 436              		.comm	__Dc,104,4
 538              	.Letext0
 539              		.file 2 "D:/Documents/SimpleIDE/Learn/Simple Libraries/TextDevices/libsimpletext/simpletext.h"
 540              		.file 3 "c:\\program files (x86)\\simpleide\\propeller-gcc\\bin\\../lib/gcc/propeller-elf/4.6.1/..
DEFINED SYMBOLS
C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s:5      .text:00000000 _SBus_open
C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s:10     .text:00000000 L0
                            *COM*:00000004 __SBPin
C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s:193    .text:000001a4 _doRecSBus
                            *COM*:00000004 __Lock
C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s:54     .text:00000068 _doChannel
                            *COM*:00000044 __Cc
                            *COM*:00000068 __Dc
                            *COM*:00000004 __Er
C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s:298    .text:0000027c _SBus_getChannel
C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s:353    .text:000002ec _SBus_getAdjChannel
C:\Users\mbmis006\AppData\Local\Temp\ccc3R0up.s:421    .text:0000038c _SBus_getStatus
                     .debug_frame:00000000 .Lframe0
                            .text:00000000 .LFB1
                            .text:00000068 .LFB3
                            .text:000001a4 .LFE3
                            .text:000001a4 .LFB2
                            .text:0000027c .LFE2
                            .text:0000027c .LFB4
                            .text:000002ec .LFE4
                            .text:000002ec .LFB5
                            .text:0000038c .LFE5
                            .text:0000038c .LFB6
                    .debug_abbrev:00000000 .Ldebug_abbrev0
                            .text:00000000 .Ltext0
                            .text:000003a4 .Letext0
                      .debug_line:00000000 .Ldebug_line0
                            .text:00000068 .LFE1
                       .debug_loc:00000000 .LLST0
                       .debug_loc:00000020 .LLST1
                       .debug_loc:0000003e .LLST2
                       .debug_loc:00000051 .LLST3
                       .debug_loc:00000071 .LLST4
                       .debug_loc:0000009b .LLST5
                       .debug_loc:000000c5 .LLST6
                       .debug_loc:000000fd .LLST7
                       .debug_loc:0000013e .LLST8
                       .debug_loc:0000015e .LLST9
                       .debug_loc:00000171 .LLST10
                       .debug_loc:00000197 .LLST11
                       .debug_loc:000001ab .LLST12
                       .debug_loc:000001d5 .LLST13
                       .debug_loc:00000201 .LLST14
                       .debug_loc:00000238 .LLST15
                       .debug_loc:0000027a .LLST16
                            .text:000003a4 .LFE6
                      .debug_info:00000000 .Ldebug_info0

UNDEFINED SYMBOLS
sp
lr
__LMM_MVI_r6
r7
r0
r1
__LMM_MVI_r0
r6
__LMM_CALL
_cog_run
pc
__TMP0
__LMM_PUSHM
__LMM_PUSHM_ret
__LMM_MVI_r2
__LMM_FCACHE_LOAD
r2
__MASK_FFFFFFFF
__LMM_FCACHE_START
__LMM_RET
r4
r5
r3
__LMM_MVI_r14
__LMM_MVI_lr
r14
__LMM_MVI_r7
__LMM_POPRET
__LMM_POPRET_ret
r12
__LMM_MVI_r9
r10
__LMM_MVI_r11
__LMM_MVI_r13
CNT
r11
r13
INA
r9
__LMM_MVI_r5
