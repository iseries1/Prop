 GNU assembler version 2.21 (propeller-elf)
	 using BFD version (propellergcc_v1_0_0_2408) 2.21.
 options passed	: -lmm -ahdlnsg=lmm/SSD1306.asm 
 input file    	: C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s
 output file   	: lmm/SSD1306.o
 target        	: propeller-parallax-elf
 time stamp    	: 

   1              		.text
   2              	.Ltext0
   3              		.balign	4
   4              		.global	_SSD1306_write
   5              	_SSD1306_write
   6              	.LFB2
   7              		.file 1 "SSD1306.c"
   1:SSD1306.c     **** /*
   2:SSD1306.c     ****  * @brief SSD1306 Display Driver
   3:SSD1306.c     ****  * @author Michael Burmeister
   4:SSD1306.c     ****  * @date March 14, 2018
   5:SSD1306.c     ****  * @version 1.0
   6:SSD1306.c     ****  */
   7:SSD1306.c     **** 
   8:SSD1306.c     **** #include "simpletools.h"
   9:SSD1306.c     **** #include "SSD1306.h"
  10:SSD1306.c     **** 
  11:SSD1306.c     **** void drawLine(short, short, short, short, char);
  12:SSD1306.c     **** 
  13:SSD1306.c     **** 
  14:SSD1306.c     **** int _CS;
  15:SSD1306.c     **** int _DC;
  16:SSD1306.c     **** int _SDA;
  17:SSD1306.c     **** int _SCL;
  18:SSD1306.c     **** int _RST;
  19:SSD1306.c     **** int _Auto;
  20:SSD1306.c     **** int _Width;
  21:SSD1306.c     **** int _Height;
  22:SSD1306.c     **** char _Buffer[LCD_BUFFER_SIZE_BOTH_TYPES];
  23:SSD1306.c     **** 
  24:SSD1306.c     **** // font 5x7 in 8x8 format line by line
  25:SSD1306.c     **** long Font_57[] = {0x1f1f1f1f, 0x1f1f1f1f, //0x0
  26:SSD1306.c     ****                0x07030101, 0x3f1f0f07, //0x1
  27:SSD1306.c     ****                0x151b111f, 0x1f111b15, //0x2
  28:SSD1306.c     ****                0x1c1e1e1f, 0x10101818, //0x3
  29:SSD1306.c     ****                0x18040201, 0x01020418, //0x4
  30:SSD1306.c     ****                0x1f000000, 0x0000001f, //0x5
  31:SSD1306.c     ****                0x04040404, 0x04040404, //0x6
  32:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x7
  33:SSD1306.c     ****                0x150a150a, 0x150a150a, //0x8
  34:SSD1306.c     ****                0x150a150a, 0x150a150a, //0x9
  35:SSD1306.c     ****                0x150a150a, 0x150a150a, //0xa
  36:SSD1306.c     ****                0x150a150a, 0x150a150a, //0xb
  37:SSD1306.c     ****                0x150a150a, 0x150a150a, //0xc
  38:SSD1306.c     ****                0x150a150a, 0x150a150a, //0xd
  39:SSD1306.c     ****                0x150a150a, 0x150a150a, //0xe
  40:SSD1306.c     ****                0x150a150a, 0x150a150a, //0xf
  41:SSD1306.c     ****                0x1f1f1f1f, 0x1f1f1f1f, //0x10
  42:SSD1306.c     ****                0x071b1d1e, 0x1e1d1b07, //0x11
  43:SSD1306.c     ****                0x00001f1f, 0x1f1f0000, //0x12
  44:SSD1306.c     ****                0x11111111, 0x11111111, //0x13
  45:SSD1306.c     ****                0x151b1b1f, 0x1f1b1b15, //0x14
  46:SSD1306.c     ****                0x1313131f, 0x1f131313, //0x15
  47:SSD1306.c     ****                0x1919191f, 0x1f191919, //0x16
  48:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x17
  49:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x18
  50:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x19
  51:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x1a
  52:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x1b
  53:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x1c
  54:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x1d
  55:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x1e
  56:SSD1306.c     ****                0x1111111f, 0x1f111111, //0x1f
  57:SSD1306.c     ****                0x00000000, 0x00000000, //0x20
  58:SSD1306.c     ****                0x01010101, 0x00010001, //0x21
  59:SSD1306.c     ****                0x0012091b, 0x00000000, //0x22
  60:SSD1306.c     ****                0x0a1f0a00, 0x00000a1f, //0x23
  61:SSD1306.c     ****                0x0e051e04, 0x00040f14, //0x24
  62:SSD1306.c     ****                0x04081111, 0x00111102, //0x25
  63:SSD1306.c     ****                0x02050502, 0x00160915, //0x26
  64:SSD1306.c     ****                0x0004080c, 0x00000000, //0x27
  65:SSD1306.c     ****                0x04040810, 0x00100804, //0x28
  66:SSD1306.c     ****                0x04040201, 0x00010204, //0x29
  67:SSD1306.c     ****                0x0e150400, 0x0004150e, //0x2a
  68:SSD1306.c     ****                0x1f040400, 0x00000404, //0x2b
  69:SSD1306.c     ****                0x00000000, 0x01020300, //0x2c
  70:SSD1306.c     ****                0x1f000000, 0x00000000, //0x2d
  71:SSD1306.c     ****                0x00000000, 0x00030300, //0x2e
  72:SSD1306.c     ****                0x04081010, 0x00010102, //0x2f
  73:SSD1306.c     ****                0x1519110e, 0x000e1113, //0x30
  74:SSD1306.c     ****                0x04040604, 0x000e0404, //0x31
  75:SSD1306.c     ****                0x0810110e, 0x001f0106, //0x32
  76:SSD1306.c     ****                0x0e10110e, 0x000e1110, //0x33
  77:SSD1306.c     ****                0x090a0c08, 0x0008081f, //0x34
  78:SSD1306.c     ****                0x100f011f, 0x000e1110, //0x35
  79:SSD1306.c     ****                0x0f01020c, 0x000e1111, //0x36
  80:SSD1306.c     ****                0x0408101f, 0x00020202, //0x37
  81:SSD1306.c     ****                0x0e11110e, 0x000e1111, //0x38
  82:SSD1306.c     ****                0x1e11110e, 0x00060810, //0x39
  83:SSD1306.c     ****                0x00030300, 0x00000303, //0x3a
  84:SSD1306.c     ****                0x00030300, 0x01020303, //0x3b
  85:SSD1306.c     ****                0x02040810, 0x00100804, //0x3c
  86:SSD1306.c     ****                0x001f0000, 0x0000001f, //0x3d
  87:SSD1306.c     ****                0x08040201, 0x00010204, //0x3e
  88:SSD1306.c     ****                0x0810110e, 0x00040004, //0x3f
  89:SSD1306.c     ****                0x1515110e, 0x001e010d, //0x40
  90:SSD1306.c     ****                0x11110a04, 0x0011111f, //0x41
  91:SSD1306.c     ****                0x0f11110f, 0x000f1111, //0x42
  92:SSD1306.c     ****                0x0101120c, 0x000c1201, //0x43
  93:SSD1306.c     ****                0x11110907, 0x00070911, //0x44
  94:SSD1306.c     ****                0x0f01011f, 0x001f0101, //0x45
  95:SSD1306.c     ****                0x0f01011f, 0x00010101, //0x46
  96:SSD1306.c     ****                0x0101110e, 0x000e1119, //0x47
  97:SSD1306.c     ****                0x1f111111, 0x00111111, //0x48
  98:SSD1306.c     ****                0x0404041f, 0x001f0404, //0x49
  99:SSD1306.c     ****                0x10101010, 0x000e1110, //0x4a
 100:SSD1306.c     ****                0x03050911, 0x00110905, //0x4b
 101:SSD1306.c     ****                0x01010101, 0x001f0101, //0x4c
 102:SSD1306.c     ****                0x15151b11, 0x00111111, //0x4d
 103:SSD1306.c     ****                0x15131111, 0x00111119, //0x4e
 104:SSD1306.c     ****                0x1111110e, 0x000e1111, //0x4f
 105:SSD1306.c     ****                0x0f11110f, 0x00010101, //0x50
 106:SSD1306.c     ****                0x1111110e, 0x00160915, //0x51
 107:SSD1306.c     ****                0x0f11110f, 0x00110905, //0x52
 108:SSD1306.c     ****                0x0e01110e, 0x000e1110, //0x53
 109:SSD1306.c     ****                0x0404041f, 0x00040404, //0x54
 110:SSD1306.c     ****                0x11111111, 0x000e1111, //0x55
 111:SSD1306.c     ****                0x0a111111, 0x0004040a, //0x56
 112:SSD1306.c     ****                0x15111111, 0x000a1515, //0x57
 113:SSD1306.c     ****                0x040a1111, 0x0011110a, //0x58
 114:SSD1306.c     ****                0x040a1111, 0x00040404, //0x59
 115:SSD1306.c     ****                0x0408101f, 0x001f0102, //0x5a
 116:SSD1306.c     ****                0x0303031f, 0x001f0303, //0x5b
 117:SSD1306.c     ****                0x04020101, 0x00101008, //0x5c
 118:SSD1306.c     ****                0x1818181f, 0x001f1818, //0x5d
 119:SSD1306.c     ****                0x0a040000, 0x00000011, //0x5e
 120:SSD1306.c     ****                0x00000000, 0x1f000000, //0x5f
 121:SSD1306.c     ****                0x000c0408, 0x00000000, //0x60
 122:SSD1306.c     ****                0x100e0000, 0x001e111e, //0x61
 123:SSD1306.c     ****                0x110f0101, 0x000f1111, //0x62
 124:SSD1306.c     ****                0x011e0000, 0x001e0101, //0x63
 125:SSD1306.c     ****                0x111e1010, 0x001e1111, //0x64
 126:SSD1306.c     ****                0x110e0000, 0x001e011f, //0x65
 127:SSD1306.c     ****                0x0f02120c, 0x00020202, //0x66
 128:SSD1306.c     ****                0x110e0000, 0x0e101e11, //0x67
 129:SSD1306.c     ****                0x110f0101, 0x00111111, //0x68
 130:SSD1306.c     ****                0x04060004, 0x000e0404, //0x69
 131:SSD1306.c     ****                0x080c0008, 0x06090808, //0x6a
 132:SSD1306.c     ****                0x09110101, 0x00110906, //0x6b
 133:SSD1306.c     ****                0x04040406, 0x000e0404, //0x6c
 134:SSD1306.c     ****                0x151b0000, 0x00111515, //0x6d
 135:SSD1306.c     ****                0x110f0000, 0x00111111, //0x6e
 136:SSD1306.c     ****                0x110e0000, 0x000e1111, //0x6f
 137:SSD1306.c     ****                0x110f0000, 0x01010f11, //0x70
 138:SSD1306.c     ****                0x111e0000, 0x10101e11, //0x71
 139:SSD1306.c     ****                0x031d0000, 0x00010101, //0x72
 140:SSD1306.c     ****                0x011e0000, 0x000f100e, //0x73
 141:SSD1306.c     ****                0x020f0202, 0x000c1202, //0x74
 142:SSD1306.c     ****                0x11110000, 0x00161911, //0x75
 143:SSD1306.c     ****                0x11110000, 0x00040a11, //0x76
 144:SSD1306.c     ****                0x11110000, 0x001b1515, //0x77
 145:SSD1306.c     ****                0x0a110000, 0x00110a04, //0x78
 146:SSD1306.c     ****                0x11110000, 0x0e101e11, //0x79
 147:SSD1306.c     ****                0x081f0000, 0x001f0204, //0x7a
 148:SSD1306.c     ****                0x0306061c, 0x001c0606, //0x7b
 149:SSD1306.c     ****                0x04040404, 0x04040404, //0x7c
 150:SSD1306.c     ****                0x180c0c07, 0x00070c0c, //0x7d
 151:SSD1306.c     ****                0x000d1600, 0x00000000, //0x7e
 152:SSD1306.c     ****                0x1f1f1f1f, 0x1f1f1f1f}; //0x7f
 153:SSD1306.c     **** 
 154:SSD1306.c     **** int SSD1306_init(int scl, int sda, int cs, int dc, int rst)
 155:SSD1306.c     **** {
 156:SSD1306.c     ****   _SCL = scl;
 157:SSD1306.c     ****   _SDA = sda;
 158:SSD1306.c     ****   _CS = cs;
 159:SSD1306.c     ****   _DC = dc;
 160:SSD1306.c     ****   _RST = rst;
 161:SSD1306.c     ****   _Auto = 0;
 162:SSD1306.c     ****   
 163:SSD1306.c     ****   if (DSIZE == TYPE_128X32)
 164:SSD1306.c     ****   {
 165:SSD1306.c     ****     _Width = SSD1306_LCDWIDTH;
 166:SSD1306.c     ****     _Height = SSD1306_LCDHEIGHT32;
 167:SSD1306.c     ****   }
 168:SSD1306.c     ****   else
 169:SSD1306.c     ****   {
 170:SSD1306.c     ****     _Width = SSD1306_LCDWIDTH;
 171:SSD1306.c     ****     _Height = SSD1306_LCDHEIGHT64;
 172:SSD1306.c     ****   }
 173:SSD1306.c     ****   
 174:SSD1306.c     ****   //reset display
 175:SSD1306.c     ****   high(_RST);
 176:SSD1306.c     ****   pause(10);
 177:SSD1306.c     ****   low(_RST);
 178:SSD1306.c     ****   pause(10);
 179:SSD1306.c     ****   high(_RST);
 180:SSD1306.c     **** 
 181:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYOFF);
 182:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETDISPLAYCLOCKDIV);
 183:SSD1306.c     ****   SSD1306_cmd(0x80);
 184:SSD1306.c     ****   
 185:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETMULTIPLEX);
 186:SSD1306.c     ****   SSD1306_cmd(_Height - 1);
 187:SSD1306.c     **** 
 188:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETDISPLAYOFFSET);
 189:SSD1306.c     ****   SSD1306_cmd(0x0);
 190:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETSTARTLINE);
 191:SSD1306.c     ****   SSD1306_cmd(SSD1306_CHARGEPUMP);
 192:SSD1306.c     ****   if (CHRGPUMP == SSD1306_EXTERNALVCC)
 193:SSD1306.c     ****     SSD1306_cmd(0x10);  //Charge pump off
 194:SSD1306.c     ****   else
 195:SSD1306.c     ****     SSD1306_cmd(0x14);  //Charge pump on
 196:SSD1306.c     ****   SSD1306_cmd(SSD1306_MEMORYMODE);
 197:SSD1306.c     ****   SSD1306_cmd(0x00);
 198:SSD1306.c     ****   SSD1306_cmd(SSD1306_SEGREMAP | 0x1);
 199:SSD1306.c     ****   SSD1306_cmd(SSD1306_COMSCANDEC);
 200:SSD1306.c     ****   
 201:SSD1306.c     ****   if (DSIZE == TYPE_128X32)
 202:SSD1306.c     ****   {
 203:SSD1306.c     ****     SSD1306_cmd(SSD1306_SETCOMPINS);
 204:SSD1306.c     ****     SSD1306_cmd(0x02);
 205:SSD1306.c     ****     SSD1306_cmd(SSD1306_SETCONTRAST);
 206:SSD1306.c     ****     SSD1306_cmd(0x8F);
 207:SSD1306.c     ****   }    
 208:SSD1306.c     ****   
 209:SSD1306.c     ****   if (DSIZE == TYPE_128X64)
 210:SSD1306.c     ****   {
 211:SSD1306.c     ****     SSD1306_cmd(SSD1306_SETCOMPINS);
 212:SSD1306.c     ****     SSD1306_cmd(0x12);
 213:SSD1306.c     ****     SSD1306_cmd(SSD1306_SETCONTRAST);
 214:SSD1306.c     ****     if (CHRGPUMP == SSD1306_EXTERNALVCC)
 215:SSD1306.c     ****       SSD1306_cmd(0x9F);
 216:SSD1306.c     ****     else
 217:SSD1306.c     ****       SSD1306_cmd(0xCF);
 218:SSD1306.c     ****   }
 219:SSD1306.c     ****   
 220:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETPRECHARGE);
 221:SSD1306.c     ****   if (CHRGPUMP == SSD1306_EXTERNALVCC)
 222:SSD1306.c     ****     SSD1306_cmd(0x22);
 223:SSD1306.c     ****   else
 224:SSD1306.c     ****     SSD1306_cmd(0xF1);
 225:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETVCOMDETECT);
 226:SSD1306.c     ****   SSD1306_cmd(0x40);
 227:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYALLON_RESUME);
 228:SSD1306.c     ****   SSD1306_cmd(SSD1306_NORMALDISPLAY);
 229:SSD1306.c     ****   SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
 230:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYON);
 231:SSD1306.c     ****   SSD1306_invert(0);
 232:SSD1306.c     ****   SSD1306_cls();
 233:SSD1306.c     **** }
 234:SSD1306.c     **** 
 235:SSD1306.c     **** void SSD1306_write(char b)
 236:SSD1306.c     **** {
   8              		.loc 1 236 0
   9              	.LVL0
  10 0000 3D00FCA0 		mov	__TMP0,#(3<<4)+13
  11 0004 0000FC5C 		call	#__LMM_PUSHM
  12              	.LCFI0
 237:SSD1306.c     ****   low(_CS);
  13              		.loc 1 237 0
  14 0008 00007C5C 		mvi	r14,#__CS
  14      00000000 
 236:SSD1306.c     **** {
  15              		.loc 1 236 0
  16 0010 0000BCA0 		mov	r13, r0
  17              		.loc 1 237 0
  18 0014 0000BC08 		rdlong	r0, r14
  19              	.LVL1
  20 0018 00007C5C 		lcall	#_low
  20      00000000 
 238:SSD1306.c     ****   shift_out(_SDA, _SCL, MSBFIRST, 8, b);
  21              		.loc 1 238 0
  22 0020 00007C5C 		mvi	r7,#__SDA
  22      00000000 
  23 0028 00007C5C 		mvi	r6,#__SCL
  23      00000000 
  24 0030 0100FCA0 		mov	r2, #1
  25 0034 0800FCA0 		mov	r3, #8
  26 0038 0000BCA0 		mov	r4, r13
  27 003c 0000BC08 		rdlong	r7, r7
  28 0040 0000BCA0 		mov	r0, r7
  29 0044 0000BC08 		rdlong	r1, r6
  30 0048 00007C5C 		lcall	#_shift_out
  30      00000000 
 239:SSD1306.c     ****   high(_CS);
  31              		.loc 1 239 0
  32 0050 0000BC08 		rdlong	r0, r14
  33 0054 00007C5C 		lcall	#_high
  33      00000000 
 240:SSD1306.c     **** }
  34              		.loc 1 240 0
  35 005c 3F00FCA0 		mov	__TMP0,#(3<<4)+15
  36 0060 0000FC5C 		call	#__LMM_POPRET
  37              		'' never returns
  38              	.LFE2
  39              		.balign	4
  40              		.global	_SSD1306_cmd
  41              	_SSD1306_cmd
  42              	.LFB3
 241:SSD1306.c     **** 
 242:SSD1306.c     **** void SSD1306_cmd(char c)
 243:SSD1306.c     **** {
  43              		.loc 1 243 0
  44              	.LVL2
  45 0064 3D00FCA0 		mov	__TMP0,#(3<<4)+13
  46 0068 0000FC5C 		call	#__LMM_PUSHM
  47              	.LCFI1
 244:SSD1306.c     ****   low(_DC);
  48              		.loc 1 244 0
  49 006c 00007C5C 		mvi	r14,#__DC
  49      00000000 
 243:SSD1306.c     **** {
  50              		.loc 1 243 0
  51 0074 0000BCA0 		mov	r13, r0
  52              		.loc 1 244 0
  53 0078 0000BC08 		rdlong	r0, r14
  54              	.LVL3
  55 007c 00007C5C 		lcall	#_low
  55      00000000 
 245:SSD1306.c     ****   SSD1306_write(c);
  56              		.loc 1 245 0
  57 0084 0000BCA0 		mov	r0, r13
  58 0088 00007C5C 		lcall	#_SSD1306_write
  58      00000000 
 246:SSD1306.c     ****   high(_DC);
  59              		.loc 1 246 0
  60 0090 0000BC08 		rdlong	r0, r14
  61 0094 00007C5C 		lcall	#_high
  61      00000000 
 247:SSD1306.c     **** }
  62              		.loc 1 247 0
  63 009c 3F00FCA0 		mov	__TMP0,#(3<<4)+15
  64 00a0 0000FC5C 		call	#__LMM_POPRET
  65              		'' never returns
  66              	.LFE3
  67              		.balign	4
  68              		.global	_SSD1306_invert
  69              	_SSD1306_invert
  70              	.LFB4
 248:SSD1306.c     **** 
 249:SSD1306.c     **** void SSD1306_invert(int i)
 250:SSD1306.c     **** {
  71              		.loc 1 250 0
  72              	.LVL4
  73 00a4 0400FC84 		sub	sp, #4
  74              	.LCFI2
  75 00a8 00003C08 		wrlong	lr, sp
  76              	.LCFI3
 251:SSD1306.c     ****   if (i)
  77              		.loc 1 251 0
  78 00ac 00007CC3 		cmps	r0, #0 wz,wc
 252:SSD1306.c     ****     SSD1306_cmd(SSD1306_INVERTDISPLAY);
  79              		.loc 1 252 0
  80 00b0 A700D4A0 		IF_NE mov	r0, #167
  81              	.LVL5
 253:SSD1306.c     ****   else
 254:SSD1306.c     ****     SSD1306_cmd(SSD1306_NORMALDISPLAY);
  82              		.loc 1 254 0
  83 00b4 A600E8A0 		IF_E  mov	r0, #166
  84 00b8 00007C5C 		lcall	#_SSD1306_cmd
  84      00000000 
 255:SSD1306.c     **** }
  85              		.loc 1 255 0
  86 00c0 0000BC08 		rdlong	lr, sp
  87 00c4 0400FC80 		add	sp, #4
  88 00c8 0000BCA0 		mov	pc,lr
  89              	.LFE4
  90              		.balign	4
  91              		.global	_SSD1306_auto
  92              	_SSD1306_auto
  93              	.LFB5
 256:SSD1306.c     **** 
 257:SSD1306.c     **** void SSD1306_auto(int a)
 258:SSD1306.c     **** {
  94              		.loc 1 258 0
  95              	.LVL6
 259:SSD1306.c     ****   _Auto = a;
  96              		.loc 1 259 0
  97 00cc 00007C5C 		mvi	r7,#__Auto
  97      00000000 
  98 00d4 00003C08 		wrlong	r0, r7
 260:SSD1306.c     **** }
  99              		.loc 1 260 0
 100 00d8 0000BCA0 		mov	pc,lr
 101              	.LFE5
 102              		.balign	4
 103              		.global	_SSD1306_update
 104              	_SSD1306_update
 105              	.LFB6
 261:SSD1306.c     **** 
 262:SSD1306.c     **** void SSD1306_update()
 263:SSD1306.c     **** {
 106              		.loc 1 263 0
 107 00dc 4C00FCA0 		mov	__TMP0,#(4<<4)+12
 108 00e0 0000FC5C 		call	#__LMM_PUSHM
 109              	.LCFI4
 264:SSD1306.c     ****   int k;
 265:SSD1306.c     ****   
 266:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETLOWCOLUMN);
 110              		.loc 1 266 0
 111 00e4 0000FCA0 		mov	r0, #0
 267:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETHIGHCOLUMN);
 268:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETSTARTLINE);
 269:SSD1306.c     ****   
 270:SSD1306.c     ****   k = 0;
 112              		.loc 1 270 0
 113 00e8 0000FCA0 		mov	r14, #0
 262:SSD1306.c     **** void SSD1306_update()
 114              		.loc 1 262 0
 115 00ec 00007C5C 		mvi	r12,#__Buffer
 115      00000000 
 271:SSD1306.c     ****   low(_CS);
 272:SSD1306.c     ****   while (k < 1024)
 273:SSD1306.c     ****   {
 274:SSD1306.c     ****     shift_out(_SDA, _SCL, MSBFIRST, 8, _Buffer[k++]);
 116              		.loc 1 274 0
 117 00f4 00007C5C 		mvi	r13,#__SDA
 117      00000000 
 266:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETLOWCOLUMN);
 118              		.loc 1 266 0
 119 00fc 00007C5C 		lcall	#_SSD1306_cmd
 119      00000000 
 267:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETHIGHCOLUMN);
 120              		.loc 1 267 0
 121 0104 1000FCA0 		mov	r0, #16
 122 0108 00007C5C 		lcall	#_SSD1306_cmd
 122      00000000 
 268:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETSTARTLINE);
 123              		.loc 1 268 0
 124 0110 4000FCA0 		mov	r0, #64
 125 0114 00007C5C 		lcall	#_SSD1306_cmd
 125      00000000 
 126              	.LVL7
 271:SSD1306.c     ****   low(_CS);
 127              		.loc 1 271 0
 128 011c 00007C5C 		mvi	r7,#__CS
 128      00000000 
 129 0124 0000BC08 		rdlong	r0, r7
 130 0128 00007C5C 		lcall	#_low
 130      00000000 
 131              	.LVL8
 132              	.L9
 262:SSD1306.c     **** void SSD1306_update()
 133              		.loc 1 262 0
 134 0130 0000BCA0 		mov	r7, r14
 135 0134 0000BC80 		add	r7, r12
 136              		.loc 1 274 0
 137 0138 00007C5C 		mvi	r6,#__SCL
 137      00000000 
 138 0140 0100FCA0 		mov	r2, #1
 139 0144 0800FCA0 		mov	r3, #8
 140 0148 0100FC80 		add	r14, #1
 141              	.LVL9
 142 014c 0000BC00 		rdbyte	r4, r7
 143 0150 0000BC08 		rdlong	r0, r13
 144 0154 0000BC08 		rdlong	r1, r6
 145 0158 00007C5C 		lcall	#_shift_out
 145      00000000 
 272:SSD1306.c     ****   while (k < 1024)
 146              		.loc 1 272 0
 147 0160 00007C5C 		mvi	r7,#1024
 147      00040000 
 148 0168 00003CC3 		cmps	r14, r7 wz,wc
 149 016c 4000D484 		IF_NE	brs	#.L9
 275:SSD1306.c     ****   }
 276:SSD1306.c     ****   high(_CS);  
 150              		.loc 1 276 0
 151 0170 00007C5C 		mvi	r7,#__CS
 151      00000000 
 152 0178 0000BC08 		rdlong	r0, r7
 153 017c 00007C5C 		lcall	#_high
 153      00000000 
 277:SSD1306.c     **** }
 154              		.loc 1 277 0
 155 0184 4F00FCA0 		mov	__TMP0,#(4<<4)+15
 156 0188 0000FC5C 		call	#__LMM_POPRET
 157              		'' never returns
 158              	.LFE6
 159              		.balign	4
 160              		.global	_SSD1306_cls
 161              	_SSD1306_cls
 162              	.LFB7
 278:SSD1306.c     ****   
 279:SSD1306.c     **** void SSD1306_cls()
 280:SSD1306.c     **** {
 163              		.loc 1 280 0
 164 018c 0400FC84 		sub	sp, #4
 165              	.LCFI5
 166 0190 00003C08 		wrlong	lr, sp
 167              	.LCFI6
 281:SSD1306.c     ****   memset(&_Buffer, 0, sizeof(_Buffer));
 168              		.loc 1 281 0
 169 0194 0000FCA0 		mov	r1, #0
 170 0198 00007C5C 		mvi	r2,#1024
 170      00040000 
 171 01a0 00007C5C 		mvi	r0,#__Buffer
 171      00000000 
 172 01a8 00007C5C 		lcall	#_memset
 172      00000000 
 282:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYOFF);
 173              		.loc 1 282 0
 174 01b0 AE00FCA0 		mov	r0, #174
 175 01b4 00007C5C 		lcall	#_SSD1306_cmd
 175      00000000 
 283:SSD1306.c     ****   SSD1306_update();
 176              		.loc 1 283 0
 177 01bc 00007C5C 		lcall	#_SSD1306_update
 177      00000000 
 284:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYON);
 178              		.loc 1 284 0
 179 01c4 AF00FCA0 		mov	r0, #175
 180 01c8 00007C5C 		lcall	#_SSD1306_cmd
 180      00000000 
 285:SSD1306.c     **** }
 181              		.loc 1 285 0
 182 01d0 0000BC08 		rdlong	lr, sp
 183 01d4 0400FC80 		add	sp, #4
 184 01d8 0000BCA0 		mov	pc,lr
 185              	.LFE7
 186              		.balign	4
 187              		.global	_SSD1306_init
 188              	_SSD1306_init
 189              	.LFB1
 155:SSD1306.c     **** {
 190              		.loc 1 155 0
 191              	.LVL10
 192 01dc 3D00FCA0 		mov	__TMP0,#(3<<4)+13
 193 01e0 0000FC5C 		call	#__LMM_PUSHM
 194              	.LCFI7
 156:SSD1306.c     ****   _SCL = scl;
 195              		.loc 1 156 0
 196 01e4 00007C5C 		mvi	r7,#__SCL
 196      00000000 
 161:SSD1306.c     ****   _Auto = 0;
 197              		.loc 1 161 0
 198 01ec 0000FCA0 		mov	r6, #0
 160:SSD1306.c     ****   _RST = rst;
 199              		.loc 1 160 0
 200 01f0 00007C5C 		mvi	r14,#__RST
 200      00000000 
 171:SSD1306.c     ****     _Height = SSD1306_LCDHEIGHT64;
 201              		.loc 1 171 0
 202 01f8 00007C5C 		mvi	r13,#__Height
 202      00000000 
 156:SSD1306.c     ****   _SCL = scl;
 203              		.loc 1 156 0
 204 0200 00003C08 		wrlong	r0, r7
 157:SSD1306.c     ****   _SDA = sda;
 205              		.loc 1 157 0
 206 0204 00007C5C 		mvi	r7,#__SDA
 206      00000000 
 175:SSD1306.c     ****   high(_RST);
 207              		.loc 1 175 0
 208 020c 0000BCA0 		mov	r0, r4
 209              	.LVL11
 157:SSD1306.c     ****   _SDA = sda;
 210              		.loc 1 157 0
 211 0210 00003C08 		wrlong	r1, r7
 158:SSD1306.c     ****   _CS = cs;
 212              		.loc 1 158 0
 213 0214 00007C5C 		mvi	r7,#__CS
 213      00000000 
 214 021c 00003C08 		wrlong	r2, r7
 159:SSD1306.c     ****   _DC = dc;
 215              		.loc 1 159 0
 216 0220 00007C5C 		mvi	r7,#__DC
 216      00000000 
 217 0228 00003C08 		wrlong	r3, r7
 161:SSD1306.c     ****   _Auto = 0;
 218              		.loc 1 161 0
 219 022c 00007C5C 		mvi	r7,#__Auto
 219      00000000 
 220 0234 00003C08 		wrlong	r6, r7
 170:SSD1306.c     ****     _Width = SSD1306_LCDWIDTH;
 221              		.loc 1 170 0
 222 0238 8000FCA0 		mov	r6, #128
 223 023c 00007C5C 		mvi	r7,#__Width
 223      00000000 
 224 0244 00003C08 		wrlong	r6, r7
 171:SSD1306.c     ****     _Height = SSD1306_LCDHEIGHT64;
 225              		.loc 1 171 0
 226 0248 4000FCA0 		mov	r7, #64
 160:SSD1306.c     ****   _RST = rst;
 227              		.loc 1 160 0
 228 024c 00003C08 		wrlong	r4, r14
 171:SSD1306.c     ****     _Height = SSD1306_LCDHEIGHT64;
 229              		.loc 1 171 0
 230 0250 00003C08 		wrlong	r7, r13
 175:SSD1306.c     ****   high(_RST);
 231              		.loc 1 175 0
 232 0254 00007C5C 		lcall	#_high
 232      00000000 
 233              	.LVL12
 176:SSD1306.c     ****   pause(10);
 234              		.loc 1 176 0
 235 025c 0A00FCA0 		mov	r0, #10
 236 0260 00007C5C 		lcall	#_pause
 236      00000000 
 177:SSD1306.c     ****   low(_RST);
 237              		.loc 1 177 0
 238 0268 0000BC08 		rdlong	r0, r14
 239 026c 00007C5C 		lcall	#_low
 239      00000000 
 178:SSD1306.c     ****   pause(10);
 240              		.loc 1 178 0
 241 0274 0A00FCA0 		mov	r0, #10
 242 0278 00007C5C 		lcall	#_pause
 242      00000000 
 179:SSD1306.c     ****   high(_RST);
 243              		.loc 1 179 0
 244 0280 0000BC08 		rdlong	r0, r14
 245 0284 00007C5C 		lcall	#_high
 245      00000000 
 181:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYOFF);
 246              		.loc 1 181 0
 247 028c AE00FCA0 		mov	r0, #174
 248 0290 00007C5C 		lcall	#_SSD1306_cmd
 248      00000000 
 182:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETDISPLAYCLOCKDIV);
 249              		.loc 1 182 0
 250 0298 D500FCA0 		mov	r0, #213
 251 029c 00007C5C 		lcall	#_SSD1306_cmd
 251      00000000 
 183:SSD1306.c     ****   SSD1306_cmd(0x80);
 252              		.loc 1 183 0
 253 02a4 8000FCA0 		mov	r0, #128
 254 02a8 00007C5C 		lcall	#_SSD1306_cmd
 254      00000000 
 185:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETMULTIPLEX);
 255              		.loc 1 185 0
 256 02b0 A800FCA0 		mov	r0, #168
 257 02b4 00007C5C 		lcall	#_SSD1306_cmd
 257      00000000 
 186:SSD1306.c     ****   SSD1306_cmd(_Height - 1);
 258              		.loc 1 186 0
 259 02bc 0000BC08 		rdlong	r0, r13
 260 02c0 0100FC84 		sub	r0, #1
 261 02c4 FF00FC60 		and	r0,#255
 262 02c8 00007C5C 		lcall	#_SSD1306_cmd
 262      00000000 
 188:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETDISPLAYOFFSET);
 263              		.loc 1 188 0
 264 02d0 D300FCA0 		mov	r0, #211
 265 02d4 00007C5C 		lcall	#_SSD1306_cmd
 265      00000000 
 189:SSD1306.c     ****   SSD1306_cmd(0x0);
 266              		.loc 1 189 0
 267 02dc 0000FCA0 		mov	r0, #0
 268 02e0 00007C5C 		lcall	#_SSD1306_cmd
 268      00000000 
 190:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETSTARTLINE);
 269              		.loc 1 190 0
 270 02e8 4000FCA0 		mov	r0, #64
 271 02ec 00007C5C 		lcall	#_SSD1306_cmd
 271      00000000 
 191:SSD1306.c     ****   SSD1306_cmd(SSD1306_CHARGEPUMP);
 272              		.loc 1 191 0
 273 02f4 8D00FCA0 		mov	r0, #141
 274 02f8 00007C5C 		lcall	#_SSD1306_cmd
 274      00000000 
 195:SSD1306.c     ****     SSD1306_cmd(0x14);  //Charge pump on
 275              		.loc 1 195 0
 276 0300 1400FCA0 		mov	r0, #20
 277 0304 00007C5C 		lcall	#_SSD1306_cmd
 277      00000000 
 196:SSD1306.c     ****   SSD1306_cmd(SSD1306_MEMORYMODE);
 278              		.loc 1 196 0
 279 030c 2000FCA0 		mov	r0, #32
 280 0310 00007C5C 		lcall	#_SSD1306_cmd
 280      00000000 
 197:SSD1306.c     ****   SSD1306_cmd(0x00);
 281              		.loc 1 197 0
 282 0318 0000FCA0 		mov	r0, #0
 283 031c 00007C5C 		lcall	#_SSD1306_cmd
 283      00000000 
 198:SSD1306.c     ****   SSD1306_cmd(SSD1306_SEGREMAP | 0x1);
 284              		.loc 1 198 0
 285 0324 A100FCA0 		mov	r0, #161
 286 0328 00007C5C 		lcall	#_SSD1306_cmd
 286      00000000 
 199:SSD1306.c     ****   SSD1306_cmd(SSD1306_COMSCANDEC);
 287              		.loc 1 199 0
 288 0330 C800FCA0 		mov	r0, #200
 289 0334 00007C5C 		lcall	#_SSD1306_cmd
 289      00000000 
 211:SSD1306.c     ****     SSD1306_cmd(SSD1306_SETCOMPINS);
 290              		.loc 1 211 0
 291 033c DA00FCA0 		mov	r0, #218
 292 0340 00007C5C 		lcall	#_SSD1306_cmd
 292      00000000 
 212:SSD1306.c     ****     SSD1306_cmd(0x12);
 293              		.loc 1 212 0
 294 0348 1200FCA0 		mov	r0, #18
 295 034c 00007C5C 		lcall	#_SSD1306_cmd
 295      00000000 
 213:SSD1306.c     ****     SSD1306_cmd(SSD1306_SETCONTRAST);
 296              		.loc 1 213 0
 297 0354 8100FCA0 		mov	r0, #129
 298 0358 00007C5C 		lcall	#_SSD1306_cmd
 298      00000000 
 217:SSD1306.c     ****       SSD1306_cmd(0xCF);
 299              		.loc 1 217 0
 300 0360 CF00FCA0 		mov	r0, #207
 301 0364 00007C5C 		lcall	#_SSD1306_cmd
 301      00000000 
 220:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETPRECHARGE);
 302              		.loc 1 220 0
 303 036c D900FCA0 		mov	r0, #217
 304 0370 00007C5C 		lcall	#_SSD1306_cmd
 304      00000000 
 224:SSD1306.c     ****     SSD1306_cmd(0xF1);
 305              		.loc 1 224 0
 306 0378 F100FCA0 		mov	r0, #241
 307 037c 00007C5C 		lcall	#_SSD1306_cmd
 307      00000000 
 225:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETVCOMDETECT);
 308              		.loc 1 225 0
 309 0384 DB00FCA0 		mov	r0, #219
 310 0388 00007C5C 		lcall	#_SSD1306_cmd
 310      00000000 
 226:SSD1306.c     ****   SSD1306_cmd(0x40);
 311              		.loc 1 226 0
 312 0390 4000FCA0 		mov	r0, #64
 313 0394 00007C5C 		lcall	#_SSD1306_cmd
 313      00000000 
 227:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYALLON_RESUME);
 314              		.loc 1 227 0
 315 039c A400FCA0 		mov	r0, #164
 316 03a0 00007C5C 		lcall	#_SSD1306_cmd
 316      00000000 
 228:SSD1306.c     ****   SSD1306_cmd(SSD1306_NORMALDISPLAY);
 317              		.loc 1 228 0
 318 03a8 A600FCA0 		mov	r0, #166
 319 03ac 00007C5C 		lcall	#_SSD1306_cmd
 319      00000000 
 229:SSD1306.c     ****   SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
 320              		.loc 1 229 0
 321 03b4 2E00FCA0 		mov	r0, #46
 322 03b8 00007C5C 		lcall	#_SSD1306_cmd
 322      00000000 
 230:SSD1306.c     ****   SSD1306_cmd(SSD1306_DISPLAYON);
 323              		.loc 1 230 0
 324 03c0 AF00FCA0 		mov	r0, #175
 325 03c4 00007C5C 		lcall	#_SSD1306_cmd
 325      00000000 
 231:SSD1306.c     ****   SSD1306_invert(0);
 326              		.loc 1 231 0
 327 03cc 0000FCA0 		mov	r0, #0
 328 03d0 00007C5C 		lcall	#_SSD1306_invert
 328      00000000 
 232:SSD1306.c     ****   SSD1306_cls();
 329              		.loc 1 232 0
 330 03d8 00007C5C 		lcall	#_SSD1306_cls
 330      00000000 
 233:SSD1306.c     **** }
 331              		.loc 1 233 0
 332 03e0 3F00FCA0 		mov	__TMP0,#(3<<4)+15
 333 03e4 0000FC5C 		call	#__LMM_POPRET
 334              		'' never returns
 335              	.LFE1
 336              		.balign	4
 337              		.global	_SSD1306_getBuffer
 338              	_SSD1306_getBuffer
 339              	.LFB8
 286:SSD1306.c     **** 
 287:SSD1306.c     **** char* SSD1306_getBuffer()
 288:SSD1306.c     **** {
 340              		.loc 1 288 0
 289:SSD1306.c     ****   return _Buffer;
 290:SSD1306.c     **** }
 341              		.loc 1 290 0
 342 03e8 00007C5C 		mvi	r0,#__Buffer
 342      00000000 
 343 03f0 0000BCA0 		mov	pc,lr
 344              	.LFE8
 345              		.balign	4
 346              		.global	_SSD1306_scrollRight
 347              	_SSD1306_scrollRight
 348              	.LFB9
 291:SSD1306.c     **** 
 292:SSD1306.c     **** void SSD1306_scrollRight(char sp, char ep, char f)
 293:SSD1306.c     **** {
 349              		.loc 1 293 0
 350              	.LVL13
 351 03f4 4C00FCA0 		mov	__TMP0,#(4<<4)+12
 352 03f8 0000FC5C 		call	#__LMM_PUSHM
 353              	.LCFI8
 354              		.loc 1 293 0
 355 03fc 0000BCA0 		mov	r12, r0
 294:SSD1306.c     ****   SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
 356              		.loc 1 294 0
 357 0400 2E00FCA0 		mov	r0, #46
 358              	.LVL14
 293:SSD1306.c     **** {
 359              		.loc 1 293 0
 360 0404 0000BCA0 		mov	r14, r1
 361 0408 0000BCA0 		mov	r13, r2
 362              		.loc 1 294 0
 363 040c 00007C5C 		lcall	#_SSD1306_cmd
 363      00000000 
 364              	.LVL15
 295:SSD1306.c     ****   SSD1306_cmd(SSD1306_RIGHT_HORIZ_SCROLL);
 365              		.loc 1 295 0
 366 0414 2600FCA0 		mov	r0, #38
 367 0418 00007C5C 		lcall	#_SSD1306_cmd
 367      00000000 
 296:SSD1306.c     ****   SSD1306_cmd(0x00); // Dummy
 368              		.loc 1 296 0
 369 0420 0000FCA0 		mov	r0, #0
 370 0424 00007C5C 		lcall	#_SSD1306_cmd
 370      00000000 
 297:SSD1306.c     ****   SSD1306_cmd(sp & 0x07);
 371              		.loc 1 297 0
 372 042c 0000BCA0 		mov	r0, r12
 373 0430 0700FC60 		and	r0, #7
 374 0434 00007C5C 		lcall	#_SSD1306_cmd
 374      00000000 
 298:SSD1306.c     ****   SSD1306_cmd(f & 0x07);
 375              		.loc 1 298 0
 376 043c 0000BCA0 		mov	r0, r13
 377 0440 0700FC60 		and	r0, #7
 378 0444 00007C5C 		lcall	#_SSD1306_cmd
 378      00000000 
 299:SSD1306.c     ****   SSD1306_cmd(ep & 0x07);
 379              		.loc 1 299 0
 380 044c 0000BCA0 		mov	r0, r14
 381 0450 0700FC60 		and	r0, #7
 382 0454 00007C5C 		lcall	#_SSD1306_cmd
 382      00000000 
 300:SSD1306.c     ****   SSD1306_cmd(0x00);
 383              		.loc 1 300 0
 384 045c 0000FCA0 		mov	r0, #0
 385 0460 00007C5C 		lcall	#_SSD1306_cmd
 385      00000000 
 301:SSD1306.c     ****   SSD1306_cmd(0xFF);
 386              		.loc 1 301 0
 387 0468 FF00FCA0 		mov	r0, #255
 388 046c 00007C5C 		lcall	#_SSD1306_cmd
 388      00000000 
 302:SSD1306.c     ****   SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
 389              		.loc 1 302 0
 390 0474 2F00FCA0 		mov	r0, #47
 391 0478 00007C5C 		lcall	#_SSD1306_cmd
 391      00000000 
 303:SSD1306.c     **** }
 392              		.loc 1 303 0
 393 0480 4F00FCA0 		mov	__TMP0,#(4<<4)+15
 394 0484 0000FC5C 		call	#__LMM_POPRET
 395              		'' never returns
 396              	.LFE9
 397              		.balign	4
 398              		.global	_SSD1306_scrollLeft
 399              	_SSD1306_scrollLeft
 400              	.LFB10
 304:SSD1306.c     **** 
 305:SSD1306.c     **** void SSD1306_scrollLeft(char sp, char ep, char f)
 306:SSD1306.c     **** {
 401              		.loc 1 306 0
 402              	.LVL16
 403 0488 4C00FCA0 		mov	__TMP0,#(4<<4)+12
 404 048c 0000FC5C 		call	#__LMM_PUSHM
 405              	.LCFI9
 406              		.loc 1 306 0
 407 0490 0000BCA0 		mov	r12, r0
 307:SSD1306.c     ****   SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
 408              		.loc 1 307 0
 409 0494 2E00FCA0 		mov	r0, #46
 410              	.LVL17
 306:SSD1306.c     **** {
 411              		.loc 1 306 0
 412 0498 0000BCA0 		mov	r14, r1
 413 049c 0000BCA0 		mov	r13, r2
 414              		.loc 1 307 0
 415 04a0 00007C5C 		lcall	#_SSD1306_cmd
 415      00000000 
 416              	.LVL18
 308:SSD1306.c     ****   SSD1306_cmd(SSD1306_LEFT_HORIZ_SCROLL);
 417              		.loc 1 308 0
 418 04a8 2700FCA0 		mov	r0, #39
 419 04ac 00007C5C 		lcall	#_SSD1306_cmd
 419      00000000 
 309:SSD1306.c     ****   SSD1306_cmd(0x00); // Dummy
 420              		.loc 1 309 0
 421 04b4 0000FCA0 		mov	r0, #0
 422 04b8 00007C5C 		lcall	#_SSD1306_cmd
 422      00000000 
 310:SSD1306.c     ****   SSD1306_cmd(sp & 0x07);
 423              		.loc 1 310 0
 424 04c0 0000BCA0 		mov	r0, r12
 425 04c4 0700FC60 		and	r0, #7
 426 04c8 00007C5C 		lcall	#_SSD1306_cmd
 426      00000000 
 311:SSD1306.c     ****   SSD1306_cmd(f & 0x07);
 427              		.loc 1 311 0
 428 04d0 0000BCA0 		mov	r0, r13
 429 04d4 0700FC60 		and	r0, #7
 430 04d8 00007C5C 		lcall	#_SSD1306_cmd
 430      00000000 
 312:SSD1306.c     ****   SSD1306_cmd(ep & 0x07);
 431              		.loc 1 312 0
 432 04e0 0000BCA0 		mov	r0, r14
 433 04e4 0700FC60 		and	r0, #7
 434 04e8 00007C5C 		lcall	#_SSD1306_cmd
 434      00000000 
 313:SSD1306.c     ****   SSD1306_cmd(0x00);
 435              		.loc 1 313 0
 436 04f0 0000FCA0 		mov	r0, #0
 437 04f4 00007C5C 		lcall	#_SSD1306_cmd
 437      00000000 
 314:SSD1306.c     ****   SSD1306_cmd(0xFF);
 438              		.loc 1 314 0
 439 04fc FF00FCA0 		mov	r0, #255
 440 0500 00007C5C 		lcall	#_SSD1306_cmd
 440      00000000 
 315:SSD1306.c     ****   SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
 441              		.loc 1 315 0
 442 0508 2F00FCA0 		mov	r0, #47
 443 050c 00007C5C 		lcall	#_SSD1306_cmd
 443      00000000 
 316:SSD1306.c     **** }
 444              		.loc 1 316 0
 445 0514 4F00FCA0 		mov	__TMP0,#(4<<4)+15
 446 0518 0000FC5C 		call	#__LMM_POPRET
 447              		'' never returns
 448              	.LFE10
 449              		.balign	4
 450              		.global	_SSD1306_scrollDiagRight
 451              	_SSD1306_scrollDiagRight
 452              	.LFB11
 317:SSD1306.c     **** 
 318:SSD1306.c     **** void SSD1306_scrollDiagRight(char sp, char ep, char f)
 319:SSD1306.c     **** {
 453              		.loc 1 319 0
 454              	.LVL19
 455 051c 4C00FCA0 		mov	__TMP0,#(4<<4)+12
 456 0520 0000FC5C 		call	#__LMM_PUSHM
 457              	.LCFI10
 458              		.loc 1 319 0
 459 0524 0000BCA0 		mov	r12, r0
 320:SSD1306.c     ****   SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
 460              		.loc 1 320 0
 461 0528 2E00FCA0 		mov	r0, #46
 462              	.LVL20
 319:SSD1306.c     **** {
 463              		.loc 1 319 0
 464 052c 0000BCA0 		mov	r14, r1
 465 0530 0000BCA0 		mov	r13, r2
 466              		.loc 1 320 0
 467 0534 00007C5C 		lcall	#_SSD1306_cmd
 467      00000000 
 468              	.LVL21
 321:SSD1306.c     ****   SSD1306_cmd(SSD1306_VERTRIGHTHORIZSCROLL);
 469              		.loc 1 321 0
 470 053c 2900FCA0 		mov	r0, #41
 471 0540 00007C5C 		lcall	#_SSD1306_cmd
 471      00000000 
 322:SSD1306.c     ****   SSD1306_cmd(0x00); // Dummy
 472              		.loc 1 322 0
 473 0548 0000FCA0 		mov	r0, #0
 474 054c 00007C5C 		lcall	#_SSD1306_cmd
 474      00000000 
 323:SSD1306.c     ****   SSD1306_cmd(sp & 0x07);
 475              		.loc 1 323 0
 476 0554 0000BCA0 		mov	r7, r12
 477 0558 0700FC60 		and	r7, #7
 478 055c 0000BCA0 		mov	r0, r7
 479 0560 00007C5C 		lcall	#_SSD1306_cmd
 479      00000000 
 324:SSD1306.c     ****   SSD1306_cmd(f & 0x07);
 480              		.loc 1 324 0
 481 0568 0000BCA0 		mov	r2, r13
 482 056c 0700FC60 		and	r2, #7
 483 0570 0000BCA0 		mov	r0, r2
 484 0574 00007C5C 		lcall	#_SSD1306_cmd
 484      00000000 
 325:SSD1306.c     ****   SSD1306_cmd(ep);
 485              		.loc 1 325 0
 486 057c 0000BCA0 		mov	r0, r14
 487 0580 00007C5C 		lcall	#_SSD1306_cmd
 487      00000000 
 326:SSD1306.c     ****   SSD1306_cmd(0x01);
 488              		.loc 1 326 0
 489 0588 0100FCA0 		mov	r0, #1
 490 058c 00007C5C 		lcall	#_SSD1306_cmd
 490      00000000 
 327:SSD1306.c     ****   SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
 491              		.loc 1 327 0
 492 0594 2F00FCA0 		mov	r0, #47
 493 0598 00007C5C 		lcall	#_SSD1306_cmd
 493      00000000 
 328:SSD1306.c     **** }
 494              		.loc 1 328 0
 495 05a0 4F00FCA0 		mov	__TMP0,#(4<<4)+15
 496 05a4 0000FC5C 		call	#__LMM_POPRET
 497              		'' never returns
 498              	.LFE11
 499              		.balign	4
 500              		.global	_SSD1306_scrollDiagLeft
 501              	_SSD1306_scrollDiagLeft
 502              	.LFB12
 329:SSD1306.c     **** 
 330:SSD1306.c     **** void SSD1306_scrollDiagLeft(char sp, char ep, char f)
 331:SSD1306.c     **** {
 503              		.loc 1 331 0
 504              	.LVL22
 505 05a8 4C00FCA0 		mov	__TMP0,#(4<<4)+12
 506 05ac 0000FC5C 		call	#__LMM_PUSHM
 507              	.LCFI11
 508              		.loc 1 331 0
 509 05b0 0000BCA0 		mov	r12, r0
 332:SSD1306.c     ****   SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
 510              		.loc 1 332 0
 511 05b4 2E00FCA0 		mov	r0, #46
 512              	.LVL23
 331:SSD1306.c     **** {
 513              		.loc 1 331 0
 514 05b8 0000BCA0 		mov	r14, r1
 515 05bc 0000BCA0 		mov	r13, r2
 516              		.loc 1 332 0
 517 05c0 00007C5C 		lcall	#_SSD1306_cmd
 517      00000000 
 518              	.LVL24
 333:SSD1306.c     ****   SSD1306_cmd(SSD1306_VERTLEFTHORIZSCROLL);
 519              		.loc 1 333 0
 520 05c8 2A00FCA0 		mov	r0, #42
 521 05cc 00007C5C 		lcall	#_SSD1306_cmd
 521      00000000 
 334:SSD1306.c     ****   SSD1306_cmd(0x00); // Dummy
 522              		.loc 1 334 0
 523 05d4 0000FCA0 		mov	r0, #0
 524 05d8 00007C5C 		lcall	#_SSD1306_cmd
 524      00000000 
 335:SSD1306.c     ****   SSD1306_cmd(sp & 0x07);
 525              		.loc 1 335 0
 526 05e0 0000BCA0 		mov	r0, r12
 527 05e4 0700FC60 		and	r0, #7
 528 05e8 00007C5C 		lcall	#_SSD1306_cmd
 528      00000000 
 336:SSD1306.c     ****   SSD1306_cmd(f & 0x07);
 529              		.loc 1 336 0
 530 05f0 0000BCA0 		mov	r0, r13
 531 05f4 0700FC60 		and	r0, #7
 532 05f8 00007C5C 		lcall	#_SSD1306_cmd
 532      00000000 
 337:SSD1306.c     ****   SSD1306_cmd(ep & 0x07);
 533              		.loc 1 337 0
 534 0600 0000BCA0 		mov	r0, r14
 535 0604 0700FC60 		and	r0, #7
 536 0608 00007C5C 		lcall	#_SSD1306_cmd
 536      00000000 
 338:SSD1306.c     ****   SSD1306_cmd(0x01);
 537              		.loc 1 338 0
 538 0610 0100FCA0 		mov	r0, #1
 539 0614 00007C5C 		lcall	#_SSD1306_cmd
 539      00000000 
 339:SSD1306.c     ****   SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
 540              		.loc 1 339 0
 541 061c 2F00FCA0 		mov	r0, #47
 542 0620 00007C5C 		lcall	#_SSD1306_cmd
 542      00000000 
 340:SSD1306.c     **** }
 543              		.loc 1 340 0
 544 0628 4F00FCA0 		mov	__TMP0,#(4<<4)+15
 545 062c 0000FC5C 		call	#__LMM_POPRET
 546              		'' never returns
 547              	.LFE12
 548              		.balign	4
 549              		.global	_SSD1306_scrollStop
 550              	_SSD1306_scrollStop
 551              	.LFB13
 341:SSD1306.c     **** 
 342:SSD1306.c     **** void SSD1306_scrollStop()
 343:SSD1306.c     **** {
 552              		.loc 1 343 0
 553 0630 0400FC84 		sub	sp, #4
 554              	.LCFI12
 555 0634 00003C08 		wrlong	lr, sp
 556              	.LCFI13
 344:SSD1306.c     ****   SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
 557              		.loc 1 344 0
 558 0638 2E00FCA0 		mov	r0, #46
 559 063c 00007C5C 		lcall	#_SSD1306_cmd
 559      00000000 
 345:SSD1306.c     **** }
 560              		.loc 1 345 0
 561 0644 0000BC08 		rdlong	lr, sp
 562 0648 0400FC80 		add	sp, #4
 563 064c 0000BCA0 		mov	pc,lr
 564              	.LFE13
 565              		.balign	4
 566              		.global	_SSD1306_plot
 567              	_SSD1306_plot
 568              	.LFB14
 346:SSD1306.c     **** 
 347:SSD1306.c     **** void SSD1306_plot(short x, short y, char z)
 348:SSD1306.c     **** {
 569              		.loc 1 348 0
 570              	.LVL25
 349:SSD1306.c     ****   int i;
 350:SSD1306.c     ****   char r, p;
 351:SSD1306.c     ****   
 352:SSD1306.c     ****   if (x >= _Width)
 571              		.loc 1 352 0
 572 0650 00007C5C 		mvi	r6,#__Width
 572      00000000 
 348:SSD1306.c     **** {
 573              		.loc 1 348 0
 574 0658 0000BCA0 		mov	r5, r0
 575 065c 0000BCA0 		mov	r7, r1
 576              		.loc 1 352 0
 577 0660 0000BC08 		rdlong	r6, r6
 578 0664 00003CC3 		cmps	r0, r6 wz,wc
 579 0668 8000CC80 		IF_AE	brs	#.L19
 353:SSD1306.c     ****     return;
 354:SSD1306.c     ****   if (y >= _Height)
 580              		.loc 1 354 0
 581 066c 00007C5C 		mvi	r6,#__Height
 581      00000000 
 582 0674 0000BC08 		rdlong	r6, r6
 583 0678 00003CC3 		cmps	r1, r6 wz,wc
 584 067c 6C00CC80 		IF_AE	brs	#.L19
 585              	.LVL26
 586              	.LBB4
 587              	.LBB5
 355:SSD1306.c     ****     return;
 356:SSD1306.c     **** 
 357:SSD1306.c     ****   i = y / 8 * 128;
 358:SSD1306.c     ****   r = y % 8;
 588              		.loc 1 358 0
 589 0680 0000BCA0 		mov	r0, r1
 590              	.LVL27
 591 0684 0800FCA0 		mov	r1, #8
 592              	.LVL28
 359:SSD1306.c     ****   r = 1 << r;
 593              		.loc 1 359 0
 594 0688 0100FCA0 		mov	r6, #1
 358:SSD1306.c     ****   r = y % 8;
 595              		.loc 1 358 0
 596 068c 0000FC5C 		call	#__DIVSI
 597              	.LVL29
 598              		.loc 1 359 0
 599 0690 FF00FC60 		and	r1,#255
 600 0694 0000BC2C 		shl	r6, r1
 357:SSD1306.c     ****   i = y / 8 * 128;
 601              		.loc 1 357 0
 602 0698 0000BCA0 		mov	r0, r7
 603 069c 0800FCA0 		mov	r1, #8
 604 06a0 0000FC5C 		call	#__DIVSI
 605 06a4 0000BCA0 		mov	r7, r0
 606              	.LVL30
 607 06a8 1000FC2C 		shl	r7, #16
 608 06ac 1000FC38 		sar	r7, #16
 609 06b0 0700FC2C 		shl	r7, #7
 610              		.loc 1 359 0
 611 06b4 0000BCA0 		mov	r4, r6
 360:SSD1306.c     ****   p = _Buffer[i+x];
 612              		.loc 1 360 0
 613 06b8 0000BC80 		add	r7, r5
 614 06bc 00007C5C 		mvi	r6,#__Buffer
 614      00000000 
 615 06c4 0000BC80 		add	r6, r7
 361:SSD1306.c     ****   if (z)
 616              		.loc 1 361 0
 617 06c8 00007CC3 		cmps	r2, #0 wz,wc
 359:SSD1306.c     ****   r = 1 << r;
 618              		.loc 1 359 0
 619 06cc FF00FC60 		and	r4,#255
 620              	.LVL31
 360:SSD1306.c     ****   p = _Buffer[i+x];
 621              		.loc 1 360 0
 622 06d0 0000BC00 		rdbyte	r7, r6
 623              	.LVL32
 362:SSD1306.c     ****     _Buffer[i+x] = p | r;
 363:SSD1306.c     ****   else
 364:SSD1306.c     ****     _Buffer[i+x] = p & ~r;
 624              		.loc 1 364 0
 625 06d4 0000A864 		IF_E  andn	r7, r4
 626              	.LVL33
 627 06d8 00002800 		IF_E  wrbyte	r7, r6
 361:SSD1306.c     ****   if (z)
 628              		.loc 1 361 0
 629 06dc 0C00E880 		IF_E 	brs	#.L19
 362:SSD1306.c     ****     _Buffer[i+x] = p | r;
 630              		.loc 1 362 0
 631 06e0 0000BC68 		or	r7, r4
 632 06e4 00003C00 		wrbyte	r7, r6
 633 06e8 0000BCA0 		mov	pc,lr
 634              	.LVL34
 635              	.L19
 636 06ec 0000BCA0 		mov	pc,lr
 637              	.LBE5
 638              	.LBE4
 639              	.LFE14
 640              		.balign	4
 641              		.global	_SSD1306_writeChar
 642              	_SSD1306_writeChar
 643              	.LFB15
 365:SSD1306.c     **** }
 366:SSD1306.c     **** 
 367:SSD1306.c     **** void SSD1306_writeChar(char x, char y, char ch)
 368:SSD1306.c     **** {
 644              		.loc 1 368 0
 645              	.LVL35
 646 06f0 8800FCA0 		mov	__TMP0,#(8<<4)+8
 647 06f4 0000FC5C 		call	#__LMM_PUSHM
 648              	.LCFI14
 649 06f8 0400FC84 		sub	sp, #4
 650              	.LCFI15
 651              	.LVL36
 369:SSD1306.c     ****   long *base;
 370:SSD1306.c     ****   int offset;
 371:SSD1306.c     ****   long v;
 372:SSD1306.c     ****   
 373:SSD1306.c     ****   offset = ch & 0xfe; // Two characters per location
 652              		.loc 1 373 0
 653 06fc 0000BCA0 		mov	r14, r2
 654 0700 FE00FC60 		and	r14, #254
 374:SSD1306.c     ****   base = (long*)(0x8000 + (offset << 6)); // jump to character position
 655              		.loc 1 374 0
 656 0704 0600FC2C 		shl	r14, #6
 657 0708 00007C5C 		mvi	r7,#32768
 657      00800000 
 658              	.LBB6
 375:SSD1306.c     **** 
 376:SSD1306.c     ****   offset = 0;
 377:SSD1306.c     ****   for (int i=0;i<32;i++)
 378:SSD1306.c     ****   {
 379:SSD1306.c     ****     v = base[offset++];
 380:SSD1306.c     ****     if (ch & 0x01)
 659              		.loc 1 380 0
 660 0710 0000BCA0 		mov	r6, r2
 661              	.LBE6
 368:SSD1306.c     **** {
 662              		.loc 1 368 0
 663 0714 0000BCA0 		mov	r8, r0
 664 0718 0000BCA0 		mov	r9, r1
 374:SSD1306.c     ****   base = (long*)(0x8000 + (offset << 6)); // jump to character position
 665              		.loc 1 374 0
 666 071c 0000BC80 		add	r14, r7
 667 0720 0000FCA0 		mov	r11, #0
 668              	.LBB12
 669              		.loc 1 380 0
 670 0724 0100FC60 		and	r6, #1
 671              	.LVL37
 672              	.L25
 673              	.LBB7
 367:SSD1306.c     **** void SSD1306_writeChar(char x, char y, char ch)
 674              		.loc 1 367 0
 675 0728 0000BCA0 		mov	r13, r11
 676 072c 0000BC80 		add	r13, r9
 677              	.LBE7
 678              		.loc 1 380 0
 679 0730 00007CC3 		cmps	r6, #0 wz,wc
 680              	.LBB8
 381:SSD1306.c     ****       v = v >> 1;
 382:SSD1306.c     ****   
 383:SSD1306.c     ****     for (int j=0;j<16;j++)
 384:SSD1306.c     ****     {
 385:SSD1306.c     ****       SSD1306_plot(x+j, y+i, (v & 0x01));
 681              		.loc 1 385 0
 682 0734 1000FC2C 		shl	r13, #16
 683              	.LBE8
 684              	.LBE12
 374:SSD1306.c     ****   base = (long*)(0x8000 + (offset << 6)); // jump to character position
 685              		.loc 1 374 0
 686 0738 0000FCA0 		mov	r10, #0
 687              	.LBB13
 688              	.LBB9
 689              		.loc 1 385 0
 690 073c 1000FC38 		sar	r13, #16
 691              	.LBE9
 379:SSD1306.c     ****     v = base[offset++];
 692              		.loc 1 379 0
 693 0740 0000BC08 		rdlong	r12, r14
 694              	.LVL38
 381:SSD1306.c     ****       v = v >> 1;
 695              		.loc 1 381 0
 696 0744 0100D438 		IF_NE sar	r12, #1
 697              	.LVL39
 698              	.L24
 699              	.LBB10
 367:SSD1306.c     **** void SSD1306_writeChar(char x, char y, char ch)
 700              		.loc 1 367 0 discriminator 2
 701 0748 0000BCA0 		mov	r7, r10
 702 074c 0000BC80 		add	r7, r8
 703              		.loc 1 385 0 discriminator 2
 704 0750 1000FC2C 		shl	r7, #16
 705 0754 1000FC38 		sar	r7, #16
 706 0758 0000BCA0 		mov	r2, r12
 707 075c 0000BCA0 		mov	r0, r7
 708 0760 0000BCA0 		mov	r1, r13
 709 0764 0100FC60 		and	r2, #1
 386:SSD1306.c     ****       v = v >> 2;
 710              		.loc 1 386 0 discriminator 2
 711 0768 0100FC80 		add	r10, #1
 712 076c 0000BC60 		and	r10,__MASK_0000FFFF
 713 0770 0200FC38 		sar	r12, #2
 714              	.LVL40
 385:SSD1306.c     ****       SSD1306_plot(x+j, y+i, (v & 0x01));
 715              		.loc 1 385 0 discriminator 2
 716 0774 00003C08 		wrlong	r6, sp
 717 0778 00007C5C 		lcall	#_SSD1306_plot
 717      00000000 
 718              	.LVL41
 383:SSD1306.c     ****     for (int j=0;j<16;j++)
 719              		.loc 1 383 0 discriminator 2
 720 0780 10007CC3 		cmps	r10, #16 wz,wc
 721 0784 0000BC08 		rdlong	r6, sp
 722 0788 4400D484 		IF_NE	brs	#.L24
 383:SSD1306.c     ****     for (int j=0;j<16;j++)
 723              		.loc 1 383 0 is_stmt 0
 724 078c 0100FC80 		add	r11, #1
 725 0790 0000BC60 		and	r11,__MASK_0000FFFF
 726              	.LBE10
 377:SSD1306.c     ****   for (int i=0;i<32;i++)
 727              		.loc 1 377 0 is_stmt 1
 728 0794 20007CC3 		cmps	r11, #32 wz,wc
 729              	.LBB11
 383:SSD1306.c     ****     for (int j=0;j<16;j++)
 730              		.loc 1 383 0
 731 0798 0400FC80 		add	r14, #4
 732              	.LBE11
 377:SSD1306.c     ****   for (int i=0;i<32;i++)
 733              		.loc 1 377 0
 734 079c 7800D484 		IF_NE	brs	#.L25
 735              	.LBE13
 387:SSD1306.c     ****     }
 388:SSD1306.c     ****   }    
 389:SSD1306.c     **** }
 736              		.loc 1 389 0
 737 07a0 0400FC80 		add	sp, #4
 738 07a4 8F00FCA0 		mov	__TMP0,#(8<<4)+15
 739 07a8 0000FC5C 		call	#__LMM_POPRET
 740              		'' never returns
 741              	.LFE15
 742              		.balign	4
 743              		.global	_SSD1306_writeStr
 744              	_SSD1306_writeStr
 745              	.LFB16
 390:SSD1306.c     **** 
 391:SSD1306.c     **** void SSD1306_writeStr(char x, char y, char *c)
 392:SSD1306.c     **** {
 746              		.loc 1 392 0
 747              	.LVL42
 748 07ac 6A00FCA0 		mov	__TMP0,#(6<<4)+10
 749 07b0 0000FC5C 		call	#__LMM_PUSHM
 750              	.LCFI16
 751              	.LVL43
 393:SSD1306.c     ****   int i, v;
 394:SSD1306.c     ****   char x1;
 395:SSD1306.c     ****   
 396:SSD1306.c     ****   x1 = x;
 397:SSD1306.c     ****   i = 0;
 752              		.loc 1 397 0
 753 07b4 0000FCA0 		mov	r14, #0
 392:SSD1306.c     **** {
 754              		.loc 1 392 0
 755 07b8 0000BCA0 		mov	r11, r0
 756 07bc 0000BCA0 		mov	r12, r1
 757 07c0 0000BCA0 		mov	r10, r2
 398:SSD1306.c     ****   while ((i < 16) && (c[i] > 0))
 399:SSD1306.c     ****   {
 400:SSD1306.c     ****     v = c[i++];
 401:SSD1306.c     ****     SSD1306_writeChar(x, y, v);
 402:SSD1306.c     ****     if (i == 8)
 403:SSD1306.c     ****     {
 404:SSD1306.c     ****       y = y + 32;
 405:SSD1306.c     ****       x = x1;
 758              		.loc 1 405 0
 759 07c4 0000BCA0 		mov	r13, r0
 760 07c8 4000FC80 		brs	#.L35
 761              	.LVL44
 762              	.L33
 401:SSD1306.c     ****     SSD1306_writeChar(x, y, v);
 763              		.loc 1 401 0
 764 07cc 0000BCA0 		mov	r0, r13
 765 07d0 0000BCA0 		mov	r1, r12
 766 07d4 0000BCA0 		mov	r2, r7
 400:SSD1306.c     ****     v = c[i++];
 767              		.loc 1 400 0
 768 07d8 0100FC80 		add	r14, #1
 769              	.LVL45
 401:SSD1306.c     ****     SSD1306_writeChar(x, y, v);
 770              		.loc 1 401 0
 771 07dc 00007C5C 		lcall	#_SSD1306_writeChar
 771      00000000 
 772              	.LVL46
 402:SSD1306.c     ****     if (i == 8)
 773              		.loc 1 402 0
 774 07e4 08007CC3 		cmps	r14, #8 wz,wc
 775 07e8 1000D480 		IF_NE	brs	#.L30
 404:SSD1306.c     ****       y = y + 32;
 776              		.loc 1 404 0
 777 07ec 2000FC80 		add	r12, #32
 778 07f0 FF00FC60 		and	r12,#255
 779              	.LVL47
 780              		.loc 1 405 0
 781 07f4 0000BCA0 		mov	r13, r11
 782 07f8 1000FC80 		brs	#.L35
 783              	.LVL48
 784              	.L30
 398:SSD1306.c     ****   while ((i < 16) && (c[i] > 0))
 785              		.loc 1 398 0
 786 07fc 10007CC3 		cmps	r14, #16 wz,wc
 787 0800 1800E880 		IF_E 	brs	#.L32
 406:SSD1306.c     ****     }
 407:SSD1306.c     ****     else
 408:SSD1306.c     ****       x = x + 16;
 788              		.loc 1 408 0
 789 0804 1000FC80 		add	r13, #16
 790              	.LVL49
 791 0808 FF00FC60 		and	r13,#255
 792              	.LVL50
 793              	.L35
 398:SSD1306.c     ****   while ((i < 16) && (c[i] > 0))
 794              		.loc 1 398 0 discriminator 2
 795 080c 0000BCA0 		mov	r7, r10
 796 0810 0000BC80 		add	r7, r14
 797 0814 0000BC02 		rdbyte	r7, r7 wz
 798 0818 5000D484 		IF_NE	brs	#.L33
 799              	.L32
 409:SSD1306.c     ****   }
 410:SSD1306.c     ****   if (_Auto)
 800              		.loc 1 410 0
 801 081c 00007C5C 		mvi	r7,#__Auto
 801      00000000 
 802 0824 0000BC08 		rdlong	r7, r7
 803 0828 00007CC3 		cmps	r7, #0 wz,wc
 804 082c 0800E880 		IF_E 	brs	#.L28
 411:SSD1306.c     ****     SSD1306_update();
 805              		.loc 1 411 0
 806 0830 00007C5C 		lcall	#_SSD1306_update
 806      00000000 
 807              	.L28
 412:SSD1306.c     **** }
 808              		.loc 1 412 0
 809 0838 6F00FCA0 		mov	__TMP0,#(6<<4)+15
 810 083c 0000FC5C 		call	#__LMM_POPRET
 811              		'' never returns
 812              	.LFE16
 813              		.balign	4
 814              		.global	_SSD1306_writeSChar
 815              	_SSD1306_writeSChar
 816              	.LFB17
 413:SSD1306.c     **** 
 414:SSD1306.c     **** void SSD1306_writeSChar(char x, char y, char c)
 415:SSD1306.c     **** {
 817              		.loc 1 415 0
 818              	.LVL51
 819 0840 8800FCA0 		mov	__TMP0,#(8<<4)+8
 820 0844 0000FC5C 		call	#__LMM_PUSHM
 821              	.LCFI17
 822 0848 0800FC84 		sub	sp, #8
 823              	.LCFI18
 416:SSD1306.c     ****   char t;
 417:SSD1306.c     ****   long v;
 418:SSD1306.c     ****   
 419:SSD1306.c     ****   t = c * 2;
 824              		.loc 1 419 0
 825 084c 0100FC2C 		shl	r2, #1
 826              	.LVL52
 414:SSD1306.c     **** void SSD1306_writeSChar(char x, char y, char c)
 827              		.loc 1 414 0
 828 0850 0000BCA0 		mov	r6, r1
 829              		.loc 1 419 0
 830 0854 0000BCA0 		mov	r11, r2
 414:SSD1306.c     **** void SSD1306_writeSChar(char x, char y, char c)
 831              		.loc 1 414 0
 832 0858 0800FC80 		add	r6, #8
 415:SSD1306.c     **** {
 833              		.loc 1 415 0
 834 085c 0000BCA0 		mov	r9, r0
 835 0860 0000BCA0 		mov	r14, r1
 836              		.loc 1 419 0
 837 0864 FF00FC60 		and	r11,#255
 838              	.LVL53
 414:SSD1306.c     **** void SSD1306_writeSChar(char x, char y, char c)
 839              		.loc 1 414 0
 840 0868 FF00FC60 		and	r6,#255
 841              	.LBB14
 420:SSD1306.c     ****   for (int l=0;l<2;l++)
 421:SSD1306.c     ****   {
 422:SSD1306.c     ****     v = Font_57[t++];
 842              		.loc 1 422 0
 843 086c 00007C5C 		mvi	r8,#_Font_57
 843      00000000 
 844              	.LVL54
 845              	.L40
 846 0874 0000BCA0 		mov	r7, r11
 847 0878 0200FC2C 		shl	r7, #2
 848 087c 0000BC80 		add	r7, r8
 849 0880 0100FC80 		add	r11, #1
 850 0884 FF00FC60 		and	r11,#255
 423:SSD1306.c     ****     for (int i=0;i<4;i++)
 851              		.loc 1 423 0
 852 0888 0000FCA0 		mov	r13, #0
 422:SSD1306.c     ****     v = Font_57[t++];
 853              		.loc 1 422 0
 854 088c 0000BC08 		rdlong	r10, r7
 855              	.LVL55
 856 0890 6800FC80 		brs	#.L37
 857              	.LVL56
 858              	.L38
 859              	.LBB15
 860              	.LBB16
 414:SSD1306.c     **** void SSD1306_writeSChar(char x, char y, char c)
 861              		.loc 1 414 0 discriminator 2
 862 0894 0000BCA0 		mov	r7, r12
 863 0898 0000BC80 		add	r7, r9
 424:SSD1306.c     ****     {
 425:SSD1306.c     ****       for (int j=0;j<8;j++)
 426:SSD1306.c     ****       {
 427:SSD1306.c     ****         SSD1306_plot(x+j, y, (v & 0x01));
 864              		.loc 1 427 0 discriminator 2
 865 089c 1000FC2C 		shl	r7, #16
 866 08a0 1000FC38 		sar	r7, #16
 867 08a4 0000BCA0 		mov	r0, r7
 868 08a8 0400FCA0 		mov	r7, #4
 869 08ac 0000BC80 		add	r7, sp
 870 08b0 0000BCA0 		mov	r2, r10
 871 08b4 0000BCA0 		mov	r1, r5
 872 08b8 0100FC60 		and	r2, #1
 428:SSD1306.c     ****         v = v >> 1;
 873              		.loc 1 428 0 discriminator 2
 874 08bc 0100FC80 		add	r12, #1
 875 08c0 0000BC60 		and	r12,__MASK_0000FFFF
 876 08c4 0100FC38 		sar	r10, #1
 877              	.LVL57
 427:SSD1306.c     ****         SSD1306_plot(x+j, y, (v & 0x01));
 878              		.loc 1 427 0 discriminator 2
 879 08c8 00003C08 		wrlong	r5, r7
 880 08cc 00003C08 		wrlong	r6, sp
 881 08d0 00007C5C 		lcall	#_SSD1306_plot
 881      00000000 
 882              	.LVL58
 425:SSD1306.c     ****       for (int j=0;j<8;j++)
 883              		.loc 1 425 0 discriminator 2
 884 08d8 0400FCA0 		mov	r7, #4
 885 08dc 0000BC80 		add	r7, sp
 886 08e0 08007CC3 		cmps	r12, #8 wz,wc
 887 08e4 0000BC08 		rdlong	r5, r7
 888 08e8 0000BC08 		rdlong	r6, sp
 889 08ec 5C00D484 		IF_NE	brs	#.L38
 890              	.LBE16
 423:SSD1306.c     ****     for (int i=0;i<4;i++)
 891              		.loc 1 423 0
 892 08f0 0100FC80 		add	r13, #1
 893              	.LVL59
 894 08f4 04007CC3 		cmps	r13, #4 wz,wc
 895 08f8 1400E880 		IF_E 	brs	#.L39
 896              	.LVL60
 897              	.L37
 414:SSD1306.c     **** void SSD1306_writeSChar(char x, char y, char c)
 898              		.loc 1 414 0 discriminator 1
 899 08fc 0000BCA0 		mov	r5, r14
 900 0900 0000BC80 		add	r5, r13
 901              	.LBE15
 902              	.LBE14
 903 0904 0000FCA0 		mov	r12, #0
 904              	.LBB19
 905              	.LBB18
 906              	.LBB17
 427:SSD1306.c     ****         SSD1306_plot(x+j, y, (v & 0x01));
 907              		.loc 1 427 0 discriminator 1
 908 0908 FF00FC60 		and	r5,#255
 909 090c 7C00FC84 		brs	#.L38
 910              	.LVL61
 911              	.L39
 912              	.LBE17
 414:SSD1306.c     **** void SSD1306_writeSChar(char x, char y, char c)
 913              		.loc 1 414 0
 914 0910 0400FC80 		add	r14, #4
 915 0914 FF00FC60 		and	r14,#255
 916              	.LVL62
 917              	.LBE18
 420:SSD1306.c     ****   for (int l=0;l<2;l++)
 918              		.loc 1 420 0
 919 0918 00003CC3 		cmps	r14, r6 wz,wc
 920 091c AC00D484 		IF_NE	brs	#.L40
 921              	.LBE19
 429:SSD1306.c     ****       }
 430:SSD1306.c     ****       y++;
 431:SSD1306.c     ****     }
 432:SSD1306.c     ****   }
 433:SSD1306.c     **** }
 922              		.loc 1 433 0
 923 0920 0800FC80 		add	sp, #8
 924 0924 8F00FCA0 		mov	__TMP0,#(8<<4)+15
 925 0928 0000FC5C 		call	#__LMM_POPRET
 926              		'' never returns
 927              	.LFE17
 928              		.balign	4
 929              		.global	_SSD1306_writeSStr
 930              	_SSD1306_writeSStr
 931              	.LFB18
 434:SSD1306.c     **** 
 435:SSD1306.c     **** void SSD1306_writeSStr(char x, char y, char *c)
 436:SSD1306.c     **** {
 932              		.loc 1 436 0
 933              	.LVL63
 934 092c 6A00FCA0 		mov	__TMP0,#(6<<4)+10
 935 0930 0000FC5C 		call	#__LMM_PUSHM
 936              	.LCFI19
 937              	.LVL64
 437:SSD1306.c     ****   int i, v;
 438:SSD1306.c     ****   char x1;
 439:SSD1306.c     ****   
 440:SSD1306.c     ****   x1 = x;
 441:SSD1306.c     ****   i = 0;
 938              		.loc 1 441 0
 939 0934 0000FCA0 		mov	r14, #0
 436:SSD1306.c     **** {
 940              		.loc 1 436 0
 941 0938 0000BCA0 		mov	r11, r0
 942 093c 0000BCA0 		mov	r12, r1
 943 0940 0000BCA0 		mov	r10, r2
 442:SSD1306.c     ****   while ((i < 32) && (c[i] > 0))
 443:SSD1306.c     ****   {
 444:SSD1306.c     ****     v = c[i++];
 445:SSD1306.c     ****     SSD1306_writeSChar(x, y, v);
 446:SSD1306.c     ****     if (i == 16)
 447:SSD1306.c     ****     {
 448:SSD1306.c     ****       y = y + 8;
 449:SSD1306.c     ****       x = x1;
 944              		.loc 1 449 0
 945 0944 0000BCA0 		mov	r13, r0
 946 0948 4000FC80 		brs	#.L50
 947              	.LVL65
 948              	.L48
 445:SSD1306.c     ****     SSD1306_writeSChar(x, y, v);
 949              		.loc 1 445 0
 950 094c 0000BCA0 		mov	r0, r13
 951 0950 0000BCA0 		mov	r1, r12
 952 0954 0000BCA0 		mov	r2, r7
 444:SSD1306.c     ****     v = c[i++];
 953              		.loc 1 444 0
 954 0958 0100FC80 		add	r14, #1
 955              	.LVL66
 445:SSD1306.c     ****     SSD1306_writeSChar(x, y, v);
 956              		.loc 1 445 0
 957 095c 00007C5C 		lcall	#_SSD1306_writeSChar
 957      00000000 
 958              	.LVL67
 446:SSD1306.c     ****     if (i == 16)
 959              		.loc 1 446 0
 960 0964 10007CC3 		cmps	r14, #16 wz,wc
 961 0968 1000D480 		IF_NE	brs	#.L45
 448:SSD1306.c     ****       y = y + 8;
 962              		.loc 1 448 0
 963 096c 0800FC80 		add	r12, #8
 964 0970 FF00FC60 		and	r12,#255
 965              	.LVL68
 966              		.loc 1 449 0
 967 0974 0000BCA0 		mov	r13, r11
 968 0978 1000FC80 		brs	#.L50
 969              	.LVL69
 970              	.L45
 442:SSD1306.c     ****   while ((i < 32) && (c[i] > 0))
 971              		.loc 1 442 0
 972 097c 20007CC3 		cmps	r14, #32 wz,wc
 973 0980 1800E880 		IF_E 	brs	#.L47
 450:SSD1306.c     ****     }
 451:SSD1306.c     ****     else
 452:SSD1306.c     ****       x = x + 8;
 974              		.loc 1 452 0
 975 0984 0800FC80 		add	r13, #8
 976              	.LVL70
 977 0988 FF00FC60 		and	r13,#255
 978              	.LVL71
 979              	.L50
 442:SSD1306.c     ****   while ((i < 32) && (c[i] > 0))
 980              		.loc 1 442 0 discriminator 2
 981 098c 0000BCA0 		mov	r7, r10
 982 0990 0000BC80 		add	r7, r14
 983 0994 0000BC02 		rdbyte	r7, r7 wz
 984 0998 5000D484 		IF_NE	brs	#.L48
 985              	.L47
 453:SSD1306.c     ****   }
 454:SSD1306.c     ****   if (_Auto)
 986              		.loc 1 454 0
 987 099c 00007C5C 		mvi	r7,#__Auto
 987      00000000 
 988 09a4 0000BC08 		rdlong	r7, r7
 989 09a8 00007CC3 		cmps	r7, #0 wz,wc
 990 09ac 0800E880 		IF_E 	brs	#.L43
 455:SSD1306.c     ****     SSD1306_update();
 991              		.loc 1 455 0
 992 09b0 00007C5C 		lcall	#_SSD1306_update
 992      00000000 
 993              	.L43
 456:SSD1306.c     **** }
 994              		.loc 1 456 0
 995 09b8 6F00FCA0 		mov	__TMP0,#(6<<4)+15
 996 09bc 0000FC5C 		call	#__LMM_POPRET
 997              		'' never returns
 998              	.LFE18
 999              		.balign	4
 1000              		.global	_drawLine
 1001              	_drawLine
 1002              	.LFB20
 457:SSD1306.c     **** 
 458:SSD1306.c     **** void SSD1306_drawLine(short x0, short y0, short x1, short y1, char c)
 459:SSD1306.c     **** {
 460:SSD1306.c     ****   short dx, dy, D, x, y, z;
 461:SSD1306.c     ****   
 462:SSD1306.c     ****   dx = x1 - x0;
 463:SSD1306.c     ****   if (dx < 0)
 464:SSD1306.c     ****   {
 465:SSD1306.c     ****     x = x0;x0 = x1;x1 = x;
 466:SSD1306.c     ****     y = y0;y0 = y1;y1 = y;
 467:SSD1306.c     ****   }
 468:SSD1306.c     ****   dx = abs(dx);
 469:SSD1306.c     ****   dy = y1 - y0;
 470:SSD1306.c     ****   if (dy < 0)
 471:SSD1306.c     ****     z = -1;
 472:SSD1306.c     ****   else
 473:SSD1306.c     ****     z = 1;
 474:SSD1306.c     ****   dy = abs(dy);
 475:SSD1306.c     ****   if (dx < dy)
 476:SSD1306.c     ****   {
 477:SSD1306.c     ****     drawLine(x0, y0, x1, y1, 1);
 478:SSD1306.c     ****     return;
 479:SSD1306.c     ****   }
 480:SSD1306.c     ****   D = 2 * dy - dx;
 481:SSD1306.c     ****   y = y0;
 482:SSD1306.c     ****   
 483:SSD1306.c     ****   for (x = x0;x <= x1;x++)
 484:SSD1306.c     ****   {
 485:SSD1306.c     ****     SSD1306_plot(x, y, c);
 486:SSD1306.c     ****     if (D > 0)
 487:SSD1306.c     ****     {
 488:SSD1306.c     ****       y = y + z;
 489:SSD1306.c     ****       D = D - 2 * dx;
 490:SSD1306.c     ****     }
 491:SSD1306.c     ****     D = D + 2 * dy;
 492:SSD1306.c     ****   }          
 493:SSD1306.c     ****   if (_Auto)
 494:SSD1306.c     ****     SSD1306_update();
 495:SSD1306.c     **** }
 496:SSD1306.c     **** 
 497:SSD1306.c     **** void drawLine(short x0, short y0, short x1, short y1, char c)
 498:SSD1306.c     **** {
 1003              		.loc 1 498 0
 1004              	.LVL72
 1005 09c0 8800FCA0 		mov	__TMP0,#(8<<4)+8
 1006 09c4 0000FC5C 		call	#__LMM_PUSHM
 1007              	.LCFI20
 1008 09c8 0400FC84 		sub	sp, #4
 1009              	.LCFI21
 499:SSD1306.c     ****   short dx, dy, D, x, y, z;
 500:SSD1306.c     ****   
 501:SSD1306.c     ****   dy = y1 - y0;
 1010              		.loc 1 501 0
 1011 09cc 0000BCA0 		mov	r7, r3
 1012 09d0 0000BC84 		sub	r7, r1
 1013 09d4 1000FC2C 		shl	r7, #16
 1014 09d8 1000FC38 		sar	r7, #16
 1015              	.LVL73
 502:SSD1306.c     ****   if (dy < 0)
 1016              		.loc 1 502 0
 1017 09dc 00007CC3 		cmps	r7, #0 wz,wc
 498:SSD1306.c     **** {
 1018              		.loc 1 498 0
 1019 09e0 0000BCA0 		mov	r12, r0
 1020 09e4 0000BCA0 		mov	r13, r1
 1021 09e8 0000BCA0 		mov	r6, r2
 1022 09ec 0000BCA0 		mov	r11, r3
 1023              		.loc 1 502 0
 1024 09f0 1000CC80 		IF_AE	brs	#.L52
 503:SSD1306.c     ****   {
 504:SSD1306.c     ****     y = y0;y0 = y1;y1 = y;
 1025              		.loc 1 504 0
 1026 09f4 0000BCA0 		mov	r13, r3
 1027 09f8 0000BCA0 		mov	r11, r1
 505:SSD1306.c     ****     x = x0;x0 = x1;x1 = x;
 1028              		.loc 1 505 0
 1029 09fc 0000BCA0 		mov	r12, r2
 1030 0a00 0000BCA0 		mov	r6, r0
 1031              	.L52
 1032              	.LVL74
 506:SSD1306.c     ****   }
 507:SSD1306.c     ****   dy = abs(dy);
 508:SSD1306.c     ****   dx = x1 - x0;
 1033              		.loc 1 508 0
 1034 0a04 0000BC84 		sub	r6, r12
 1035              	.LVL75
 1036 0a08 1000FC2C 		shl	r6, #16
 1037 0a0c 1000FC38 		sar	r6, #16
 509:SSD1306.c     ****   if (dx < 0)
 510:SSD1306.c     ****     z = -1;
 1038              		.loc 1 510 0
 1039 0a10 00007CC3 		cmps	r6, #0 wz,wc
 511:SSD1306.c     ****   else
 512:SSD1306.c     ****     z = 1;
 513:SSD1306.c     ****   dx = abs(dx);
 1040              		.loc 1 513 0
 1041 0a14 0000BCA8 		abs	r6, r6
 507:SSD1306.c     ****   dy = abs(dy);
 1042              		.loc 1 507 0
 1043 0a18 0000BCA8 		abs	r7, r7
 1044              	.LVL76
 514:SSD1306.c     ****   D = 2 * dx - dy;
 1045              		.loc 1 514 0
 1046 0a1c 0100FC2C 		shl	r6, #1
 507:SSD1306.c     ****   dy = abs(dy);
 1047              		.loc 1 507 0
 1048 0a20 1000FC2C 		shl	r7, #16
 1049              	.LVL77
 1050              		.loc 1 514 0
 1051 0a24 0000BCA0 		mov	r10, r6
 1052 0a28 1000FC28 		shr	r7, #16
 1053              	.LVL78
 1054 0a2c 0000BC60 		and	r10,__MASK_0000FFFF
 1055 0a30 0000BCA0 		mov	r14, r10
 515:SSD1306.c     ****   x = x0;
 516:SSD1306.c     ****   
 517:SSD1306.c     ****   for (y = y0;y <= y1;y++)
 518:SSD1306.c     ****   {
 519:SSD1306.c     ****     SSD1306_plot(x, y, c);
 520:SSD1306.c     ****     if (D > 0)
 521:SSD1306.c     ****     {
 522:SSD1306.c     ****       x = x + z;
 523:SSD1306.c     ****       D = D - 2 * dy;
 1056              		.loc 1 523 0
 1057 0a34 0000BCA0 		mov	r0, r7
 1058 0a38 0200FCA4 		neg	r1, #2
 514:SSD1306.c     ****   D = 2 * dx - dy;
 1059              		.loc 1 514 0
 1060 0a3c 0000BC84 		sub	r14, r7
 1061 0a40 1000FC2C 		shl	r14, #16
 510:SSD1306.c     ****     z = -1;
 1062              		.loc 1 510 0
 1063 0a44 0100CCA0 		IF_AE mov	r8,#1
 1064 0a48 0100F0A4 		IF_B  neg	r8,#1
 1065              	.LVL79
 1066              		.loc 1 523 0
 1067 0a4c 0000FC5C 		call	#__MULSI
 1068 0a50 0000BCA0 		mov	r9, r0
 514:SSD1306.c     ****   D = 2 * dx - dy;
 1069              		.loc 1 514 0
 1070 0a54 1000FC38 		sar	r14, #16
 1071              	.LVL80
 1072              		.loc 1 523 0
 1073 0a58 0000BC60 		and	r9,__MASK_0000FFFF
 517:SSD1306.c     ****   for (y = y0;y <= y1;y++)
 1074              		.loc 1 517 0
 1075 0a5c 5400FC80 		brs	#.L54
 1076              	.LVL81
 1077              	.L56
 519:SSD1306.c     ****     SSD1306_plot(x, y, c);
 1078              		.loc 1 519 0
 1079 0a60 0000BCA0 		mov	r2, r4
 1080 0a64 0000BCA0 		mov	r0, r12
 1081 0a68 0000BCA0 		mov	r1, r13
 1082 0a6c 00003C08 		wrlong	r4, sp
 1083 0a70 00007C5C 		lcall	#_SSD1306_plot
 1083      00000000 
 520:SSD1306.c     ****     if (D > 0)
 1084              		.loc 1 520 0
 1085 0a78 00007CC3 		cmps	r14, #0 wz,wc
 1086 0a7c 0000BC08 		rdlong	r4, sp
 1087 0a80 1800F880 		IF_BE	brs	#.L55
 522:SSD1306.c     ****       x = x + z;
 1088              		.loc 1 522 0
 1089 0a84 0000BC80 		add	r12, r8
 1090              	.LVL82
 1091              		.loc 1 523 0
 1092 0a88 0000BC80 		add	r14, r9
 1093              	.LVL83
 522:SSD1306.c     ****       x = x + z;
 1094              		.loc 1 522 0
 1095 0a8c 1000FC2C 		shl	r12, #16
 1096              		.loc 1 523 0
 1097 0a90 1000FC2C 		shl	r14, #16
 522:SSD1306.c     ****       x = x + z;
 1098              		.loc 1 522 0
 1099 0a94 1000FC38 		sar	r12, #16
 1100              	.LVL84
 1101              		.loc 1 523 0
 1102 0a98 1000FC38 		sar	r14, #16
 1103              	.LVL85
 1104              	.L55
 524:SSD1306.c     ****     }
 525:SSD1306.c     ****     D = D + 2 * dx;
 1105              		.loc 1 525 0
 1106 0a9c 0000BC80 		add	r14, r10
 1107              	.LVL86
 517:SSD1306.c     ****   for (y = y0;y <= y1;y++)
 1108              		.loc 1 517 0
 1109 0aa0 0100FC80 		add	r13, #1
 1110              	.LVL87
 1111              		.loc 1 525 0
 1112 0aa4 1000FC2C 		shl	r14, #16
 517:SSD1306.c     ****   for (y = y0;y <= y1;y++)
 1113              		.loc 1 517 0
 1114 0aa8 1000FC2C 		shl	r13, #16
 1115              	.LVL88
 1116              		.loc 1 525 0
 1117 0aac 1000FC38 		sar	r14, #16
 1118              	.LVL89
 517:SSD1306.c     ****   for (y = y0;y <= y1;y++)
 1119              		.loc 1 517 0
 1120 0ab0 1000FC38 		sar	r13, #16
 1121              	.LVL90
 1122              	.L54
 517:SSD1306.c     ****   for (y = y0;y <= y1;y++)
 1123              		.loc 1 517 0 is_stmt 0 discriminator 1
 1124 0ab4 00003CC3 		cmps	r13, r11 wz,wc
 1125 0ab8 5C00F884 		IF_BE	brs	#.L56
 526:SSD1306.c     ****   }
 527:SSD1306.c     ****   if (_Auto)
 1126              		.loc 1 527 0 is_stmt 1
 1127 0abc 00007C5C 		mvi	r7,#__Auto
 1127      00000000 
 1128 0ac4 0000BC08 		rdlong	r7, r7
 1129 0ac8 00007CC3 		cmps	r7, #0 wz,wc
 1130 0acc 0800E880 		IF_E 	brs	#.L51
 528:SSD1306.c     ****     SSD1306_update();
 1131              		.loc 1 528 0
 1132 0ad0 00007C5C 		lcall	#_SSD1306_update
 1132      00000000 
 1133              	.L51
 529:SSD1306.c     **** }
 1134              		.loc 1 529 0
 1135 0ad8 0400FC80 		add	sp, #4
 1136 0adc 8F00FCA0 		mov	__TMP0,#(8<<4)+15
 1137 0ae0 0000FC5C 		call	#__LMM_POPRET
 1138              		'' never returns
 1139              	.LFE20
 1140              		.balign	4
 1141              		.global	_SSD1306_drawLine
 1142              	_SSD1306_drawLine
 1143              	.LFB19
 459:SSD1306.c     **** {
 1144              		.loc 1 459 0
 1145              	.LVL91
 1146 0ae4 8800FCA0 		mov	__TMP0,#(8<<4)+8
 1147 0ae8 0000FC5C 		call	#__LMM_PUSHM
 1148              	.LCFI22
 1149 0aec 0400FC84 		sub	sp, #4
 1150              	.LCFI23
 459:SSD1306.c     **** {
 1151              		.loc 1 459 0
 1152 0af0 0000BCA0 		mov	r13, r0
 462:SSD1306.c     ****   dx = x1 - x0;
 1153              		.loc 1 462 0
 1154 0af4 0000BCA0 		mov	r0, r2
 1155              	.LVL92
 1156 0af8 0000BC84 		sub	r0, r13
 1157 0afc 1000FC2C 		shl	r0, #16
 1158 0b00 1000FC38 		sar	r0, #16
 1159              	.LVL93
 463:SSD1306.c     ****   if (dx < 0)
 1160              		.loc 1 463 0
 1161 0b04 00007CC3 		cmps	r0, #0 wz,wc
 459:SSD1306.c     **** {
 1162              		.loc 1 459 0
 1163 0b08 0000BCA0 		mov	r12, r1
 1164 0b0c 0000BCA0 		mov	r11, r2
 463:SSD1306.c     ****   if (dx < 0)
 1165              		.loc 1 463 0
 1166 0b10 1400CC80 		IF_AE	brs	#.L61
 1167 0b14 0000BCA0 		mov	r7, r13
 466:SSD1306.c     ****     y = y0;y0 = y1;y1 = y;
 1168              		.loc 1 466 0
 1169 0b18 0000BCA0 		mov	r12, r3
 465:SSD1306.c     ****     x = x0;x0 = x1;x1 = x;
 1170              		.loc 1 465 0
 1171 0b1c 0000BCA0 		mov	r13, r2
 466:SSD1306.c     ****     y = y0;y0 = y1;y1 = y;
 1172              		.loc 1 466 0
 1173 0b20 0000BCA0 		mov	r3, r1
 1174              	.LVL94
 465:SSD1306.c     ****     x = x0;x0 = x1;x1 = x;
 1175              		.loc 1 465 0
 1176 0b24 0000BCA0 		mov	r11, r7
 1177              	.L61
 1178              	.LVL95
 469:SSD1306.c     ****   dy = y1 - y0;
 1179              		.loc 1 469 0
 1180 0b28 0000BCA0 		mov	r7, r3
 1181 0b2c 0000BC84 		sub	r7, r12
 1182 0b30 1000FC2C 		shl	r7, #16
 1183 0b34 1000FC38 		sar	r7, #16
 471:SSD1306.c     ****     z = -1;
 1184              		.loc 1 471 0
 1185 0b38 00007CC3 		cmps	r7, #0 wz,wc
 468:SSD1306.c     ****   dx = abs(dx);
 1186              		.loc 1 468 0
 1187 0b3c 0000BCA8 		abs	r0, r0
 1188              	.LVL96
 474:SSD1306.c     ****   dy = abs(dy);
 1189              		.loc 1 474 0
 1190 0b40 0000BCA8 		abs	r7, r7
 468:SSD1306.c     ****   dx = abs(dx);
 1191              		.loc 1 468 0
 1192 0b44 1000FC2C 		shl	r0, #16
 474:SSD1306.c     ****   dy = abs(dy);
 1193              		.loc 1 474 0
 1194 0b48 1000FC2C 		shl	r7, #16
 468:SSD1306.c     ****   dx = abs(dx);
 1195              		.loc 1 468 0
 1196 0b4c 1000FC38 		sar	r0, #16
 1197              	.LVL97
 474:SSD1306.c     ****   dy = abs(dy);
 1198              		.loc 1 474 0
 1199 0b50 1000FC38 		sar	r7, #16
 471:SSD1306.c     ****     z = -1;
 1200              		.loc 1 471 0
 1201 0b54 0100CCA0 		IF_AE mov	r8,#1
 1202 0b58 0100F0A4 		IF_B  neg	r8,#1
 1203              	.LVL98
 475:SSD1306.c     ****   if (dx < dy)
 1204              		.loc 1 475 0
 1205 0b5c 00003CC3 		cmps	r0, r7 wz,wc
 1206 0b60 1C00CC80 		IF_AE	brs	#.L63
 477:SSD1306.c     ****     drawLine(x0, y0, x1, y1, 1);
 1207              		.loc 1 477 0
 1208 0b64 0000BCA0 		mov	r0, r13
 1209              	.LVL99
 1210 0b68 0000BCA0 		mov	r1, r12
 1211 0b6c 0000BCA0 		mov	r2, r11
 1212 0b70 0100FCA0 		mov	r4, #1
 1213              	.LVL100
 1214 0b74 00007C5C 		lcall	#_drawLine
 1214      00000000 
 1215              	.LVL101
 478:SSD1306.c     ****     return;
 1216              		.loc 1 478 0
 1217 0b7c AC00FC80 		brs	#.L60
 1218              	.LVL102
 1219              	.L63
 480:SSD1306.c     ****   D = 2 * dy - dx;
 1220              		.loc 1 480 0
 1221 0b80 0100FC2C 		shl	r7, #1
 1222              	.LVL103
 1223 0b84 0000BCA0 		mov	r10, r7
 1224 0b88 0000BC60 		and	r10,__MASK_0000FFFF
 1225 0b8c 0000BC60 		and	r0,__MASK_0000FFFF
 1226              	.LVL104
 1227 0b90 0000BCA0 		mov	r14, r10
 489:SSD1306.c     ****       D = D - 2 * dx;
 1228              		.loc 1 489 0
 1229 0b94 0200FCA4 		neg	r1, #2
 480:SSD1306.c     ****   D = 2 * dy - dx;
 1230              		.loc 1 480 0
 1231 0b98 0000BC84 		sub	r14, r0
 1232 0b9c 1000FC2C 		shl	r14, #16
 489:SSD1306.c     ****       D = D - 2 * dx;
 1233              		.loc 1 489 0
 1234 0ba0 0000FC5C 		call	#__MULSI
 1235 0ba4 0000BCA0 		mov	r9, r0
 480:SSD1306.c     ****   D = 2 * dy - dx;
 1236              		.loc 1 480 0
 1237 0ba8 1000FC38 		sar	r14, #16
 1238              	.LVL105
 489:SSD1306.c     ****       D = D - 2 * dx;
 1239              		.loc 1 489 0
 1240 0bac 0000BC60 		and	r9,__MASK_0000FFFF
 483:SSD1306.c     ****   for (x = x0;x <= x1;x++)
 1241              		.loc 1 483 0
 1242 0bb0 5400FC80 		brs	#.L65
 1243              	.LVL106
 1244              	.L67
 485:SSD1306.c     ****     SSD1306_plot(x, y, c);
 1245              		.loc 1 485 0
 1246 0bb4 0000BCA0 		mov	r2, r4
 1247 0bb8 0000BCA0 		mov	r0, r13
 1248 0bbc 0000BCA0 		mov	r1, r12
 1249 0bc0 00003C08 		wrlong	r4, sp
 1250 0bc4 00007C5C 		lcall	#_SSD1306_plot
 1250      00000000 
 486:SSD1306.c     ****     if (D > 0)
 1251              		.loc 1 486 0
 1252 0bcc 00007CC3 		cmps	r14, #0 wz,wc
 1253 0bd0 0000BC08 		rdlong	r4, sp
 1254 0bd4 1800F880 		IF_BE	brs	#.L66
 488:SSD1306.c     ****       y = y + z;
 1255              		.loc 1 488 0
 1256 0bd8 0000BC80 		add	r12, r8
 1257              	.LVL107
 489:SSD1306.c     ****       D = D - 2 * dx;
 1258              		.loc 1 489 0
 1259 0bdc 0000BC80 		add	r14, r9
 1260              	.LVL108
 488:SSD1306.c     ****       y = y + z;
 1261              		.loc 1 488 0
 1262 0be0 1000FC2C 		shl	r12, #16
 489:SSD1306.c     ****       D = D - 2 * dx;
 1263              		.loc 1 489 0
 1264 0be4 1000FC2C 		shl	r14, #16
 488:SSD1306.c     ****       y = y + z;
 1265              		.loc 1 488 0
 1266 0be8 1000FC38 		sar	r12, #16
 1267              	.LVL109
 489:SSD1306.c     ****       D = D - 2 * dx;
 1268              		.loc 1 489 0
 1269 0bec 1000FC38 		sar	r14, #16
 1270              	.LVL110
 1271              	.L66
 491:SSD1306.c     ****     D = D + 2 * dy;
 1272              		.loc 1 491 0
 1273 0bf0 0000BC80 		add	r14, r10
 1274              	.LVL111
 483:SSD1306.c     ****   for (x = x0;x <= x1;x++)
 1275              		.loc 1 483 0
 1276 0bf4 0100FC80 		add	r13, #1
 1277              	.LVL112
 491:SSD1306.c     ****     D = D + 2 * dy;
 1278              		.loc 1 491 0
 1279 0bf8 1000FC2C 		shl	r14, #16
 483:SSD1306.c     ****   for (x = x0;x <= x1;x++)
 1280              		.loc 1 483 0
 1281 0bfc 1000FC2C 		shl	r13, #16
 1282              	.LVL113
 491:SSD1306.c     ****     D = D + 2 * dy;
 1283              		.loc 1 491 0
 1284 0c00 1000FC38 		sar	r14, #16
 1285              	.LVL114
 483:SSD1306.c     ****   for (x = x0;x <= x1;x++)
 1286              		.loc 1 483 0
 1287 0c04 1000FC38 		sar	r13, #16
 1288              	.LVL115
 1289              	.L65
 483:SSD1306.c     ****   for (x = x0;x <= x1;x++)
 1290              		.loc 1 483 0 is_stmt 0 discriminator 1
 1291 0c08 00003CC3 		cmps	r13, r11 wz,wc
 1292 0c0c 5C00F884 		IF_BE	brs	#.L67
 493:SSD1306.c     ****   if (_Auto)
 1293              		.loc 1 493 0 is_stmt 1
 1294 0c10 00007C5C 		mvi	r7,#__Auto
 1294      00000000 
 1295 0c18 0000BC08 		rdlong	r7, r7
 1296 0c1c 00007CC3 		cmps	r7, #0 wz,wc
 1297 0c20 0800E880 		IF_E 	brs	#.L60
 494:SSD1306.c     ****     SSD1306_update();
 1298              		.loc 1 494 0
 1299 0c24 00007C5C 		lcall	#_SSD1306_update
 1299      00000000 
 1300              	.LVL116
 1301              	.L60
 495:SSD1306.c     **** }
 1302              		.loc 1 495 0
 1303 0c2c 0400FC80 		add	sp, #4
 1304 0c30 8F00FCA0 		mov	__TMP0,#(8<<4)+15
 1305 0c34 0000FC5C 		call	#__LMM_POPRET
 1306              		'' never returns
 1307              	.LFE19
 1308              		.balign	4
 1309              		.global	_SSD1306_drawBox
 1310              	_SSD1306_drawBox
 1311              	.LFB21
 530:SSD1306.c     **** 
 531:SSD1306.c     **** void SSD1306_drawBox(short x0, short y0, short x1, short y1, char c)
 532:SSD1306.c     **** {
 1312              		.loc 1 532 0
 1313              	.LVL117
 1314 0c38 6A00FCA0 		mov	__TMP0,#(6<<4)+10
 1315 0c3c 0000FC5C 		call	#__LMM_PUSHM
 1316              	.LCFI24
 1317              		.loc 1 532 0
 1318 0c40 0000BCA0 		mov	r13, r1
 1319 0c44 0000BCA0 		mov	r10, r3
 533:SSD1306.c     ****   SSD1306_drawLine(x0, y0, x1, y0, c);
 1320              		.loc 1 533 0
 1321 0c48 0000BCA0 		mov	r3, r13
 1322              	.LVL118
 532:SSD1306.c     **** {
 1323              		.loc 1 532 0
 1324 0c4c 0000BCA0 		mov	r11, r2
 1325 0c50 0000BCA0 		mov	r14, r0
 1326 0c54 0000BCA0 		mov	r12, r4
 1327              		.loc 1 533 0
 1328 0c58 00007C5C 		lcall	#_SSD1306_drawLine
 1328      00000000 
 1329              	.LVL119
 534:SSD1306.c     ****   SSD1306_drawLine(x0, y0, x0, y1, c);
 1330              		.loc 1 534 0
 1331 0c60 0000BCA0 		mov	r0, r14
 1332 0c64 0000BCA0 		mov	r1, r13
 1333 0c68 0000BCA0 		mov	r2, r14
 1334 0c6c 0000BCA0 		mov	r3, r10
 1335 0c70 0000BCA0 		mov	r4, r12
 1336 0c74 00007C5C 		lcall	#_SSD1306_drawLine
 1336      00000000 
 535:SSD1306.c     ****   SSD1306_drawLine(x1, y0, x1, y1, c);
 1337              		.loc 1 535 0
 1338 0c7c 0000BCA0 		mov	r0, r11
 1339 0c80 0000BCA0 		mov	r1, r13
 1340 0c84 0000BCA0 		mov	r2, r11
 1341 0c88 0000BCA0 		mov	r3, r10
 1342 0c8c 0000BCA0 		mov	r4, r12
 1343 0c90 00007C5C 		lcall	#_SSD1306_drawLine
 1343      00000000 
 536:SSD1306.c     ****   SSD1306_drawLine(x0, y1, x1, y1, c);
 1344              		.loc 1 536 0
 1345 0c98 0000BCA0 		mov	r0, r14
 1346 0c9c 0000BCA0 		mov	r1, r10
 1347 0ca0 0000BCA0 		mov	r2, r11
 1348 0ca4 0000BCA0 		mov	r3, r10
 1349 0ca8 0000BCA0 		mov	r4, r12
 1350 0cac 00007C5C 		lcall	#_SSD1306_drawLine
 1350      00000000 
 537:SSD1306.c     **** }
 1351              		.loc 1 537 0
 1352 0cb4 6F00FCA0 		mov	__TMP0,#(6<<4)+15
 1353 0cb8 0000FC5C 		call	#__LMM_POPRET
 1354              		'' never returns
 1355              	.LFE21
 1356              		.balign	4
 1357              		.global	_SSD1306_setContrast
 1358              	_SSD1306_setContrast
 1359              	.LFB22
 538:SSD1306.c     ****   
 539:SSD1306.c     **** void SSD1306_setContrast(short c)
 540:SSD1306.c     **** {
 1360              		.loc 1 540 0
 1361              	.LVL120
 1362 0cbc 2E00FCA0 		mov	__TMP0,#(2<<4)+14
 1363 0cc0 0000FC5C 		call	#__LMM_PUSHM
 1364              	.LCFI25
 1365              		.loc 1 540 0
 1366 0cc4 0000BCA0 		mov	r14, r0
 541:SSD1306.c     ****   SSD1306_cmd(SSD1306_SETCONTRAST);
 1367              		.loc 1 541 0
 1368 0cc8 8100FCA0 		mov	r0, #129
 1369              	.LVL121
 1370 0ccc 00007C5C 		lcall	#_SSD1306_cmd
 1370      00000000 
 542:SSD1306.c     ****   SSD1306_cmd(c);
 1371              		.loc 1 542 0
 1372 0cd4 0000BCA0 		mov	r0, r14
 1373 0cd8 FF00FC60 		and	r0,#255
 1374 0cdc 00007C5C 		lcall	#_SSD1306_cmd
 1374      00000000 
 543:SSD1306.c     **** }
 1375              		.loc 1 543 0
 1376 0ce4 2F00FCA0 		mov	__TMP0,#(2<<4)+15
 1377 0ce8 0000FC5C 		call	#__LMM_POPRET
 1378              		'' never returns
 1379              	.LFE22
 1380              		.global	_Font_57
 1381              		.data
 1382              		.balign	4
 1383              	_Font_57
 1384 0000 1F1F1F1F 		long	522133279
 1385 0004 1F1F1F1F 		long	522133279
 1386 0008 01010307 		long	117637377
 1387 000c 070F1F3F 		long	1059000071
 1388 0010 1F111B15 		long	354095391
 1389 0014 151B111F 		long	521214741
 1390 0018 1F1E1E1C 		long	471735839
 1391 001c 18181010 		long	269490200
 1392 0020 01020418 		long	402915841
 1393 0024 18040201 		long	16909336
 1394 0028 0000001F 		long	520093696
 1395 002c 1F000000 		long	31
 1396 0030 04040404 		long	67372036
 1397 0034 04040404 		long	67372036
 1398 0038 1F111111 		long	286331167
 1399 003c 1111111F 		long	521212177
 1400 0040 0A150A15 		long	352982282
 1401 0044 0A150A15 		long	352982282
 1402 0048 0A150A15 		long	352982282
 1403 004c 0A150A15 		long	352982282
 1404 0050 0A150A15 		long	352982282
 1405 0054 0A150A15 		long	352982282
 1406 0058 0A150A15 		long	352982282
 1407 005c 0A150A15 		long	352982282
 1408 0060 0A150A15 		long	352982282
 1409 0064 0A150A15 		long	352982282
 1410 0068 0A150A15 		long	352982282
 1411 006c 0A150A15 		long	352982282
 1412 0070 0A150A15 		long	352982282
 1413 0074 0A150A15 		long	352982282
 1414 0078 0A150A15 		long	352982282
 1415 007c 0A150A15 		long	352982282
 1416 0080 1F1F1F1F 		long	522133279
 1417 0084 1F1F1F1F 		long	522133279
 1418 0088 1E1D1B07 		long	119217438
 1419 008c 071B1D1E 		long	505223943
 1420 0090 1F1F0000 		long	7967
 1421 0094 00001F1F 		long	522125312
 1422 0098 11111111 		long	286331153
 1423 009c 11111111 		long	286331153
 1424 00a0 1F1B1B15 		long	354097951
 1425 00a4 151B1B1F 		long	521870101
 1426 00a8 1F131313 		long	320017183
 1427 00ac 1313131F 		long	521343763
 1428 00b0 1F191919 		long	421075231
 1429 00b4 1919191F 		long	521738521
 1430 00b8 1F111111 		long	286331167
 1431 00bc 1111111F 		long	521212177
 1432 00c0 1F111111 		long	286331167
 1433 00c4 1111111F 		long	521212177
 1434 00c8 1F111111 		long	286331167
 1435 00cc 1111111F 		long	521212177
 1436 00d0 1F111111 		long	286331167
 1437 00d4 1111111F 		long	521212177
 1438 00d8 1F111111 		long	286331167
 1439 00dc 1111111F 		long	521212177
 1440 00e0 1F111111 		long	286331167
 1441 00e4 1111111F 		long	521212177
 1442 00e8 1F111111 		long	286331167
 1443 00ec 1111111F 		long	521212177
 1444 00f0 1F111111 		long	286331167
 1445 00f4 1111111F 		long	521212177
 1446 00f8 1F111111 		long	286331167
 1447 00fc 1111111F 		long	521212177
 1448 0100 00000000 		long	0
 1449 0104 00000000 		long	0
 1450 0108 01010101 		long	16843009
 1451 010c 01000100 		long	65537
 1452 0110 1B091200 		long	1181979
 1453 0114 00000000 		long	0
 1454 0118 000A1F0A 		long	169806336
 1455 011c 1F0A0000 		long	2591
 1456 0120 041E050E 		long	235216388
 1457 0124 140F0400 		long	266004
 1458 0128 11110804 		long	67637521
 1459 012c 02111100 		long	1118466
 1460 0130 02050502 		long	33883394
 1461 0134 15091600 		long	1444117
 1462 0138 0C080400 		long	264204
 1463 013c 00000000 		long	0
 1464 0140 10080404 		long	67373072
 1465 0144 04081000 		long	1050628
 1466 0148 01020404 		long	67371521
 1467 014c 04020100 		long	66052
 1468 0150 0004150E 		long	236258304
 1469 0154 0E150400 		long	267534
 1470 0158 0004041F 		long	520356864
 1471 015c 04040000 		long	1028
 1472 0160 00000000 		long	0
 1473 0164 00030201 		long	16909056
 1474 0168 0000001F 		long	520093696
 1475 016c 00000000 		long	0
 1476 0170 00000000 		long	0
 1477 0174 00030300 		long	197376
 1478 0178 10100804 		long	67637264
 1479 017c 02010100 		long	65794
 1480 0180 0E111915 		long	353964302
 1481 0184 13110E00 		long	921875
 1482 0188 04060404 		long	67372548
 1483 018c 04040E00 		long	918532
 1484 0190 0E111008 		long	135270670
 1485 0194 06011F00 		long	2031878
 1486 0198 0E11100E 		long	235933966
 1487 019c 10110E00 		long	921872
 1488 01a0 080C0A09 		long	151653384
 1489 01a4 1F080800 		long	526367
 1490 01a8 1F010F10 		long	269418783
 1491 01ac 10110E00 		long	921872
 1492 01b0 0C02010F 		long	251724300
 1493 01b4 11110E00 		long	921873
 1494 01b8 1F100804 		long	67637279
 1495 01bc 02020200 		long	131586
 1496 01c0 0E11110E 		long	235999502
 1497 01c4 11110E00 		long	921873
 1498 01c8 0E11111E 		long	504434958
 1499 01cc 10080600 		long	395280
 1500 01d0 00030300 		long	197376
 1501 01d4 03030000 		long	771
 1502 01d8 00030300 		long	197376
 1503 01dc 03030201 		long	16909059
 1504 01e0 10080402 		long	33818640
 1505 01e4 04081000 		long	1050628
 1506 01e8 00001F00 		long	2031616
 1507 01ec 1F000000 		long	31
 1508 01f0 01020408 		long	134480385
 1509 01f4 04020100 		long	66052
 1510 01f8 0E111008 		long	135270670
 1511 01fc 04000400 		long	262148
 1512 0200 0E111515 		long	353702158
 1513 0204 0D011E00 		long	1966349
 1514 0208 040A1111 		long	286329348
 1515 020c 1F111100 		long	1118495
 1516 0210 0F11110F 		long	252776719
 1517 0214 11110F00 		long	987409
 1518 0218 0C120101 		long	16847372
 1519 021c 01120C00 		long	791041
 1520 0220 07091111 		long	286329095
 1521 0224 11090700 		long	461073
 1522 0228 1F01010F 		long	251724063
 1523 022c 01011F00 		long	2031873
 1524 0230 1F01010F 		long	251724063
 1525 0234 01010100 		long	65793
 1526 0238 0E110101 		long	16847118
 1527 023c 19110E00 		long	921881
 1528 0240 1111111F 		long	521212177
 1529 0244 11111100 		long	1118481
 1530 0248 1F040404 		long	67372063
 1531 024c 04041F00 		long	2032644
 1532 0250 10101010 		long	269488144
 1533 0254 10110E00 		long	921872
 1534 0258 11090503 		long	50661649
 1535 025c 05091100 		long	1116421
 1536 0260 01010101 		long	16843009
 1537 0264 01011F00 		long	2031873
 1538 0268 111B1515 		long	353704721
 1539 026c 11111100 		long	1118481
 1540 0270 11111315 		long	353571089
 1541 0274 19111100 		long	1118489
 1542 0278 0E111111 		long	286331150
 1543 027c 11110E00 		long	921873
 1544 0280 0F11110F 		long	252776719
 1545 0284 01010100 		long	65793
 1546 0288 0E111111 		long	286331150
 1547 028c 15091600 		long	1444117
 1548 0290 0F11110F 		long	252776719
 1549 0294 05091100 		long	1116421
 1550 0298 0E11010E 		long	234950926
 1551 029c 10110E00 		long	921872
 1552 02a0 1F040404 		long	67372063
 1553 02a4 04040400 		long	263172
 1554 02a8 11111111 		long	286331153
 1555 02ac 11110E00 		long	921873
 1556 02b0 1111110A 		long	168890641
 1557 02b4 0A040400 		long	263178
 1558 02b8 11111115 		long	353440017
 1559 02bc 15150A00 		long	660757
 1560 02c0 11110A04 		long	67768593
 1561 02c4 0A111100 		long	1118474
 1562 02c8 11110A04 		long	67768593
 1563 02cc 04040400 		long	263172
 1564 02d0 1F100804 		long	67637279
 1565 02d4 02011F00 		long	2031874
 1566 02d8 1F030303 		long	50529055
 1567 02dc 03031F00 		long	2032387
 1568 02e0 01010204 		long	67240193
 1569 02e4 08101000 		long	1052680
 1570 02e8 1F181818 		long	404232223
 1571 02ec 18181F00 		long	2037784
 1572 02f0 0000040A 		long	168034304
 1573 02f4 11000000 		long	17
 1574 02f8 00000000 		long	0
 1575 02fc 0000001F 		long	520093696
 1576 0300 08040C00 		long	787464
 1577 0304 00000000 		long	0
 1578 0308 00000E10 		long	269352960
 1579 030c 1E111E00 		long	1970462
 1580 0310 01010F11 		long	286195969
 1581 0314 11110F00 		long	987409
 1582 0318 00001E01 		long	18743296
 1583 031c 01011E00 		long	1966337
 1584 0320 10101E11 		long	287182864
 1585 0324 11111E00 		long	1970449
 1586 0328 00000E11 		long	286130176
 1587 032c 1F011E00 		long	1966367
 1588 0330 0C12020F 		long	251793932
 1589 0334 02020200 		long	131586
 1590 0338 00000E11 		long	286130176
 1591 033c 111E100E 		long	235937297
 1592 0340 01010F11 		long	286195969
 1593 0344 11111100 		long	1118481
 1594 0348 04000604 		long	67502084
 1595 034c 04040E00 		long	918532
 1596 0350 08000C08 		long	135004168
 1597 0354 08080906 		long	101255176
 1598 0358 01011109 		long	152109313
 1599 035c 06091100 		long	1116422
 1600 0360 06040404 		long	67372038
 1601 0364 04040E00 		long	918532
 1602 0368 00001B15 		long	354091008
 1603 036c 15151100 		long	1119509
 1604 0370 00000F11 		long	286195712
 1605 0374 11111100 		long	1118481
 1606 0378 00000E11 		long	286130176
 1607 037c 11110E00 		long	921873
 1608 0380 00000F11 		long	286195712
 1609 0384 110F0101 		long	16846609
 1610 0388 00001E11 		long	287178752
 1611 038c 111E1010 		long	269491729
 1612 0390 00001D03 		long	52232192
 1613 0394 01010100 		long	65793
 1614 0398 00001E01 		long	18743296
 1615 039c 0E100F00 		long	987150
 1616 03a0 02020F02 		long	34537986
 1617 03a4 02120C00 		long	791042
 1618 03a8 00001111 		long	286326784
 1619 03ac 11191600 		long	1448209
 1620 03b0 00001111 		long	286326784
 1621 03b4 110A0400 		long	264721
 1622 03b8 00001111 		long	286326784
 1623 03bc 15151B00 		long	1774869
 1624 03c0 0000110A 		long	168886272
 1625 03c4 040A1100 		long	1116676
 1626 03c8 00001111 		long	286326784
 1627 03cc 111E100E 		long	235937297
 1628 03d0 00001F08 		long	136249344
 1629 03d4 04021F00 		long	2032132
 1630 03d8 1C060603 		long	50726428
 1631 03dc 06061C00 		long	1836550
 1632 03e0 04040404 		long	67372036
 1633 03e4 04040404 		long	67372036
 1634 03e8 070C0C18 		long	403442695
 1635 03ec 0C0C0700 		long	461836
 1636 03f0 00160D00 		long	857600
 1637 03f4 00000000 		long	0
 1638 03f8 1F1F1F1F 		long	522133279
 1639 03fc 1F1F1F1F 		long	522133279
 1640              		.comm	__Buffer,1024,4
 1641              		.comm	__Height,4,4
 1642              		.comm	__Width,4,4
 1643              		.comm	__Auto,4,4
 1644              		.comm	__RST,4,4
 1645              		.comm	__SCL,4,4
 1646              		.comm	__SDA,4,4
 1647              		.comm	__DC,4,4
 1648              		.comm	__CS,4,4
 2110              	.Letext0
 2111              		.file 2 "D:/Documents/SimpleIDE/Learn/Simple Libraries/TextDevices/libsimpletext/simpletext.h"
DEFINED SYMBOLS
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:5      .text:00000000 _SSD1306_write
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:10     .text:00000000 L0
                            *COM*:00000004 __CS
                            *COM*:00000004 __SDA
                            *COM*:00000004 __SCL
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:41     .text:00000064 _SSD1306_cmd
                            *COM*:00000004 __DC
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:69     .text:000000a4 _SSD1306_invert
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:92     .text:000000cc _SSD1306_auto
                            *COM*:00000004 __Auto
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:104    .text:000000dc _SSD1306_update
                            *COM*:00000400 __Buffer
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:161    .text:0000018c _SSD1306_cls
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:188    .text:000001dc _SSD1306_init
                            *COM*:00000004 __RST
                            *COM*:00000004 __Height
                            *COM*:00000004 __Width
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:338    .text:000003e8 _SSD1306_getBuffer
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:347    .text:000003f4 _SSD1306_scrollRight
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:399    .text:00000488 _SSD1306_scrollLeft
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:451    .text:0000051c _SSD1306_scrollDiagRight
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:501    .text:000005a8 _SSD1306_scrollDiagLeft
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:550    .text:00000630 _SSD1306_scrollStop
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:567    .text:00000650 _SSD1306_plot
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:642    .text:000006f0 _SSD1306_writeChar
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:744    .text:000007ac _SSD1306_writeStr
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:815    .text:00000840 _SSD1306_writeSChar
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:1383   .data:00000000 _Font_57
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:930    .text:0000092c _SSD1306_writeSStr
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:1001   .text:000009c0 _drawLine
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:1142   .text:00000ae4 _SSD1306_drawLine
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:1310   .text:00000c38 _SSD1306_drawBox
C:\Users\mbmis006\AppData\Local\Temp\ccVBpKax.s:1358   .text:00000cbc _SSD1306_setContrast
                     .debug_frame:00000000 .Lframe0
                            .text:00000000 .LFB2
                            .text:00000064 .LFB3
                            .text:000000a4 .LFB4
                            .text:000000cc .LFB5
                            .text:000000dc .LFB6
                            .text:0000018c .LFB7
                            .text:000001dc .LFB1
                            .text:000003e8 .LFB8
                            .text:000003f4 .LFB9
                            .text:00000488 .LFB10
                            .text:0000051c .LFB11
                            .text:000005a8 .LFB12
                            .text:00000630 .LFB13
                            .text:00000650 .LFB14
                            .text:000006f0 .LFB15
                            .text:000007ac .LFB16
                            .text:00000840 .LFB17
                            .text:0000092c .LFB18
                            .text:000009c0 .LFB20
                            .text:00000ae4 .LFB19
                            .text:00000c38 .LFB21
                            .text:00000cbc .LFB22
                    .debug_abbrev:00000000 .Ldebug_abbrev0
                            .text:00000000 .Ltext0
                            .text:00000cec .Letext0
                      .debug_line:00000000 .Ldebug_line0
                            .text:00000064 .LFE2
                       .debug_loc:00000000 .LLST0
                       .debug_loc:00000020 .LLST1
                            .text:000000a4 .LFE3
                       .debug_loc:00000033 .LLST2
                       .debug_loc:00000053 .LLST3
                            .text:000000cc .LFE4
                       .debug_loc:00000066 .LLST4
                       .debug_loc:00000086 .LLST5
                            .text:000000dc .LFE5
                            .text:0000018c .LFE6
                       .debug_loc:00000099 .LLST6
                       .debug_loc:000000b9 .LLST7
                            .text:000001dc .LFE7
                       .debug_loc:000000d8 .LLST8
                            .text:000003e8 .LFE1
                       .debug_loc:000000f8 .LLST9
                       .debug_loc:00000118 .LLST10
                       .debug_loc:0000013a .LLST11
                       .debug_loc:0000014d .LLST12
                       .debug_loc:00000160 .LLST13
                       .debug_loc:00000173 .LLST14
                            .text:000003f4 .LFE8
                            .text:00000488 .LFE9
                       .debug_loc:00000186 .LLST15
                       .debug_loc:000001a6 .LLST16
                       .debug_loc:000001b9 .LLST17
                       .debug_loc:000001cc .LLST18
                            .text:0000051c .LFE10
                       .debug_loc:000001df .LLST19
                       .debug_loc:000001ff .LLST20
                       .debug_loc:00000212 .LLST21
                       .debug_loc:00000225 .LLST22
                            .text:000005a8 .LFE11
                       .debug_loc:00000238 .LLST23
                       .debug_loc:00000258 .LLST24
                       .debug_loc:0000026b .LLST25
                       .debug_loc:0000027e .LLST26
                            .text:00000630 .LFE12
                       .debug_loc:00000291 .LLST27
                       .debug_loc:000002b1 .LLST28
                       .debug_loc:000002c4 .LLST29
                       .debug_loc:000002d7 .LLST30
                            .text:00000650 .LFE13
                       .debug_loc:000002ea .LLST31
                            .text:000006f0 .LFE14
                       .debug_loc:0000030a .LLST32
                       .debug_loc:0000031d .LLST33
                            .text:00000680 .LBB4
                            .text:000006f0 .LBE4
                       .debug_loc:00000330 .LLST34
                       .debug_loc:00000343 .LLST35
                       .debug_loc:0000036c .LLST36
                            .text:00000680 .LBB5
                            .text:000006f0 .LBE5
                       .debug_loc:0000038a .LLST37
                       .debug_loc:000003d1 .LLST38
                       .debug_loc:000003e4 .LLST39
                            .text:000007ac .LFE15
                       .debug_loc:000003f7 .LLST40
                       .debug_loc:00000423 .LLST41
                       .debug_loc:00000436 .LLST42
                       .debug_loc:00000449 .LLST43
                       .debug_loc:0000045c .LLST44
                       .debug_loc:0000047a .LLST45
                       .debug_loc:0000048e .LLST46
                    .debug_ranges:00000000 .Ldebug_ranges0
                            .text:00000840 .LFE16
                       .debug_loc:000004b8 .LLST48
                       .debug_loc:000004d8 .LLST49
                       .debug_loc:00000510 .LLST50
                       .debug_loc:0000052e .LLST51
                       .debug_loc:0000054c .LLST52
                       .debug_loc:00000582 .LLST53
                       .debug_loc:0000059b .LLST54
                            .text:0000092c .LFE17
                       .debug_loc:000005b9 .LLST55
                       .debug_loc:000005e5 .LLST56
                       .debug_loc:000005f8 .LLST57
                       .debug_loc:00000621 .LLST58
                       .debug_loc:00000634 .LLST59
                       .debug_loc:00000652 .LLST60
                       .debug_loc:0000067c .LLST61
                       .debug_loc:00000690 .LLST62
                       .debug_loc:000006ba .LLST63
                            .text:000009c0 .LFE18
                       .debug_loc:000006ce .LLST64
                       .debug_loc:000006ee .LLST65
                       .debug_loc:00000726 .LLST66
                       .debug_loc:00000744 .LLST67
                       .debug_loc:00000762 .LLST68
                       .debug_loc:00000798 .LLST69
                       .debug_loc:000007b1 .LLST70
                            .text:00000ae4 .LFE20
                       .debug_loc:000007cf .LLST71
                       .debug_loc:000007fb .LLST72
                       .debug_loc:00000819 .LLST73
                       .debug_loc:00000837 .LLST74
                       .debug_loc:00000855 .LLST75
                       .debug_loc:00000873 .LLST76
                       .debug_loc:00000886 .LLST77
                       .debug_loc:00000899 .LLST78
                       .debug_loc:000008c2 .LLST79
                       .debug_loc:000008e0 .LLST80
                            .text:00000c38 .LFE19
                       .debug_loc:000008fe .LLST81
                       .debug_loc:0000092a .LLST82
                       .debug_loc:00000948 .LLST83
                       .debug_loc:00000966 .LLST84
                       .debug_loc:00000984 .LLST85
                       .debug_loc:000009ad .LLST86
                       .debug_loc:000009cb .LLST87
                       .debug_loc:000009f4 .LLST88
                       .debug_loc:00000a12 .LLST89
                       .debug_loc:00000a3b .LLST90
                       .debug_loc:00000a59 .LLST91
                            .text:00000cbc .LFE21
                       .debug_loc:00000a77 .LLST92
                       .debug_loc:00000a97 .LLST93
                       .debug_loc:00000aaa .LLST94
                       .debug_loc:00000abd .LLST95
                       .debug_loc:00000ad0 .LLST96
                       .debug_loc:00000ae3 .LLST97
                            .text:00000cec .LFE22
                       .debug_loc:00000af6 .LLST98
                       .debug_loc:00000b16 .LLST99
                      .debug_info:00000000 .Ldebug_info0

UNDEFINED SYMBOLS
__TMP0
__LMM_PUSHM
__LMM_PUSHM_ret
__LMM_MVI_r14
r13
r0
r14
__LMM_CALL
_low
__LMM_MVI_r7
__LMM_MVI_r6
r2
r3
r4
r7
r1
r6
_shift_out
_high
__LMM_POPRET
__LMM_POPRET_ret
sp
lr
pc
__LMM_MVI_r12
__LMM_MVI_r13
r12
__LMM_MVI_r2
__LMM_MVI_r0
_memset
_pause
r5
__DIVSI
__DIVSI_ret
r8
r9
r11
r10
__MASK_0000FFFF
__LMM_MVI_r8
__MULSI
__MULSI_ret
