/**
 * @brief BOSCH BNO055 driver library
 * @author Michael Burmeister
 * @date March 14, 2020
 * @version 1.0
 * 
*/

#define BNO055ADDR 0x28
#define BNO055CHIPID 0x00
#define BNO055ACCID 0x01
#define BNO055MAGID 0x02
#define BNO055GYROID 0x03
#define BNO055SWREVIDL 0x04
#define BNO055SWREVIDH 0x05
#define BNO055BLREVID 0x06
#define BNO055PAGEID 0x07
#define BNO055ACCDATAXL 0x08
#define BNO055ACCDATAXH 0x09
#define BNO055ACCDATAYL 0x0A
#define BNO055ACCDATAYH 0x0B
#define BNO055ACCDATAZL 0x0C
#define BNO055ACCDATAZH 0x0D
#define BNO055MAGDATAXL 0x0E
#define BNO055MAGDATAXH 0x0F
#define BNO055MAGDATAYL 0x10
#define BNO055MAGDATAYH 0x11
#define BNO055MAGDATAZL 0x12
#define BNO055MAGDATAZH 0x13
#define BNO055GYRODATAXL 0x14
#define BNO055GYRODATAXH 0x15
#define BNO055GYRODATAYL 0x16
#define BNO055GYRODATAYH 0x17
#define BNO055GYRODATAZL 0x18
#define BNO055GYRODATAZH 0x19
#define BNO055EULDATAXL 0x1A
#define BNO055EULDATAXH 0x1B
#define BNO055EULDATAYL 0x1C
#define BNO055EULDATAYH 0x1D
#define BNO055EULDATAZL 0x1E
#define BNO055EULDATAZH 0x1F
#define BNO055QUADATAWL 0x20
#define BNO055QUADATAWH 0x21
#define BNO055QUADATAXL 0x22
#define BNO055QUADATAXH 0x23
#define BNO055QUADATAYL 0x24
#define BNO055QUADATAYH 0x25
#define BNO055QUADATAZL 0x26
#define BNO055QUADATAZH 0x27
#define BNO055LIADATAXL 0x28
#define BNO055LIADATAXH 0x29
#define BNO055LIADATAYL 0x2A
#define BNO055LIADATAYH 0x2B
#define BNO055LIADATAZL 0x2C
#define BNO055LIADATAZH 0x2D
#define BNO055GRVDATAXL 0x2E
#define BNO055GRVDATAXH 0x2F
#define BNO055GRVDATAYL 0x30
#define BNO055GRVDATAYH 0x31
#define BNO055GRVDATAZL 0x32
#define BNO055GRVDATAZH 0x33
#define BNO055TEMP      0x34
#define BNO055CALBSTATS 0x35
#define BNO055STATSRLTS 0x36
#define BNO055INTRSTATS 0x37
#define BNO055CLKSTATS  0x38
#define BNO055SYSSTATS  0x39
#define BNO055SYSERROR  0x3A
#define BNO055UNITSELT  0x3B
#define BNO055OPRMODE   0x3D
#define BNO055PWRMODE   0x3E
#define BNO055SYSTRGR   0x3F
#define BNO055TEMPSRC   0x40
#define BNO055AXISMAP   0x41
#define BNO055AXISMAPS  0x42
#define BNO055ACCOFSETXL 0x55
#define BNO055ACCOFSETXH 0x56
#define BNO055ACCOFSETYL 0x57
#define BNO055ACCOFSETYH 0x58
#define BNO055ACCOFSETZL 0x59
#define BNO055ACCOFSETZH 0x5A
#define BNO055MAGOFSETXL 0x5B
#define BNO055MAGOFSETXH 0x5C
#define BNO055MAGOFSETYL 0x5D
#define BNO055MAGOFSETYH 0x5E
#define BNO055MAGOFSETZL 0x5F
#define BNO055MAGOFSETZH 0x60
#define BNO055GYROFSETXL 0x61
#define BNO055GYROFSETXH 0x62
#define BNO055GYROFSETYL 0x63
#define BNO055GYROFSETYH 0x64
#define BNO055GYROFSETZL 0x65
#define BNO055GYROFSETZH 0x66
#define BNO055ACCRDOFSTL 0x67
#define BNO055ACCRDOFSTH 0x68
#define BNO055MAGRDOFSTL 0x69
#define BNO055MAGRDOFSTH 0x6A
// Page 1
#define BNO055ACCCONFIG 0x08
#define BNO055MAGCONFIG 0x09
#define BNO055GYRCONFIG0 0x0A
#define BNO055GYRCONFIG1 0x0B
#define BNO055ACCSLPCFG 0x0C
#define BNO055GYRSLPCFG 0x0D
#define BNO055INTMASK   0x0F
#define BNO055INTENABLE 0x10
#define BNO055ACCTHRES  0x11
#define BNO055ACCTINTST 0x12

  