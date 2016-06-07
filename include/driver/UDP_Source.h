//======================================================================================

//=========== pack structure ==================================
//
//     +-----------+--------+------+-----+
//     |  byte cnt | command| data | crc |
//     +-----------+--------+------+-----+
//
//=============================================================

//================== Commands ====================================================

#define BROADCASTY_SYSTEM_DATA			(10) // (pusrdata[0] == 'R' && pusrdata[1] == 'T' && pusrdata[2] == 'M'	&& pusrdata[3] == 'P')
#define HARDWARE_CFG					(11) //(pusrdata[0] == 'H' && pusrdata[1] == 'W' && pusrdata[2] == 'C' && pusrdata[3] == 'F' && pusrdata[4] == 'G')

#define PLOT_DATA						(20)

#define READ_DAY_CONFIGS				(30)	//========= read day configs =========================== 		if (pusrdata[0] == 'C' && pusrdata[1] == 'O' && pusrdata[2] == 'N'	&& pusrdata[3] == 'F')
#define SAVE_DAY_CONFIGS				(31)	//========= save day configs =========================== 		if (pusrdata[0] == 'C' && pusrdata[1] == 'S' && pusrdata[2] == 'A'	&& pusrdata[3] == 'V')
#define READ_WEEK_CONFIGS				(32)	//========= read week configs ===========================		if (pusrdata[0] == 'W' && pusrdata[1] == 'E' && pusrdata[2] == 'E' && pusrdata[3] == 'K')
#define SAVE_WEEK_CONFIGS				(33)	//========= save week configs ===========================		if (pusrdata[0] == 'C' && pusrdata[1] == 'S' && pusrdata[2] == 'A' && pusrdata[3] == 'W')
#define READ_USTANOVKI					(34) 	//========= read ustanovki ===========================  		if (pusrdata[0] == 'G' && pusrdata[1] == 'U' && pusrdata[2] == 'S' 	&& pusrdata[3] == 'T')
#define SAVE_USTANOVKI					(35)	//========= save ustanovki ===========================  		if (pusrdata[0] == 'S' && pusrdata[1] == 'U' && pusrdata[2] == 'S' && pusrdata[3] == 'T')

//======================================================================================

void ICACHE_FLASH_ATTR UDP_Init();
void ICACHE_FLASH_ATTR UDP_Init_client();
void UDP_Recieved(void *arg, char *pusrdata, unsigned short length);
void   mergeAnswerWith(char tPtr[2][24][4]);
void ICACHE_FLASH_ATTR sendUDPbroadcast(uint8* abuf, uint16 aLen);


extern uint8 channelFree;

