/**
 * @brief Base 64 encoder/decoder library
 * @author Michael Burmeister
 * @date March 13, 2021
 * @version 1.0
 * 
*/

/**
 * @brief Encode data to base 64
 * @param from data buffer
 * @param to base64 data buffer
 * @param len data buffer from length
 * @return to buffer length
 */
int Base64_Encode(unsigned char *from, char *to, int len);

/**
 * @brief Decode base 64 data 
 * @param from base64 data terminated
 * @param to data buffer
 * @return to buffer length
 */
int Base64_Decode(char *from, unsigned char *to);
