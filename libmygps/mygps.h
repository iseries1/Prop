/*
 * @brief function definitions
 * @author
 * @date April 15, 2018
 * @version 1.0
 */

#ifndef _MYGPS
#define _MYGPS

#include "simpletools.h"                      // Include simple tools
#include "fdserial.h"

/*
 * @brief start the gps reader
 * @return cog started
 */
int start_gps(int, int, int, int);

/*
 * @brief get RMC string
 * @return char pointer
 */
char *getRMC(void);

/*
 * @brief get GGA string
 * @return char pointer
 */
char *getGGA(void);

#endif
