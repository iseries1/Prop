/**
 * @file Bluesio.h
 * @brief Blues IO Notecard driver
 * @date March 15, 2024
 * @version 1.0
 * 
*/

/**
 * @brief Initialize Blues IO
 * @param rx receive pin
 * @param tx transmitt pin
 * @param status 0=ok, -1=no found
 */
int Bluesio_Init(int rx, int tx);

/**
 * @brief Send Request
 * @param request to send
 */
void Bluesio_Request(char *request);

/**
 * @brief Receive Data
 * @param buffer to hold data
 * @return number of bytes returned
 */
int Bluesio_Receive(char *buffer);

/**
 * @brief Sync notecard with cloud
 */
void Bluesio_Sync(void);

/**
 * @brief Status of Notecard sync
 * @return status 0=ready, 1=syncing
 */
int Bluesio_Status(void);

/**
 * @brief Notecard Version
 * @return version number
 */
int Bluesio_Version(void);

/**
 * @brief Add a Note
 * @param note json data
 * @param file name or NULL
 * @return total
 */
int Bluesio_Add(char *note, char *file);

/**
 * @brief Add Note Payload
 * @param payload to add base64
 * @return total
 */
int Bluesio_AddPayload(char *payload);

/**
 * @brief Check for note file
 * @return total number of files
 */
int Bluesio_Check(void);

/**
 * @brief Get notecard data
 * @param data buffer to hold json data
 * @param remove data 0=keep, 1=remove
 * @return number of bytes return
 */
int Bluesio_GetData(char *data, int remove);

/**
 * @brief Set attn pin
 * @param mode 1=arm, 2=sleep, 3=disarm
 * @param time to sleep
 */
void Bluesio_SetAttn(int mode, int time);

/**
 * @brief Get Notecard Voltage
 * @return voltage
 */
float Bluesio_GetVoltage(void);

/**
 * @brief Get Notecard Temperature
 * @return temp value in celsius
 */
float Bluesio_GetTemperature(void);

/**
 * @brief Get Current Unix Time
 * @return unix time
 */
int Bluesio_GetTime(void);
