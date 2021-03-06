//=============================================================================
#include <ets_sys.h>
#include "osapi.h"
#include "c_types.h"
#include "gpio.h"
#include "os_type.h"
#include <mem.h>
#include "user_config.h"
#include "user_interface.h"
#include "driver/lcd1100.h"
#include "driver/Configs.h"
#include "driver/services.h"
//==============================================================================
s_DATE_TIME date_time = {.DATE.day   = 25,
                         .DATE.month = 1,
                         .DATE.year  = 2016,
                         .TIME.hour = 16,
                         .TIME.min = 24};
unsigned char daysInMonth[]  = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char   Months[12][3] = {{"���"},{"���"},{"���"},{"���"},{"���"},{"���"},
                              {"���"},{"���"},{"���"},{"���"},{"���"},{"���"}};
const char   Days[7][3]    = {{"���"},{"���"},{"���"},{"���"},{"���"},{"���"},{"���"}};
int  dayOfWeek;
//==============================================================================
void ICACHE_FLASH_ATTR printTime(void)
{
  char_10x16(8 , 0 , date_time.TIME.hour/10);
  char_10x16(18, 0 , date_time.TIME.hour%10);
  char_10x16(28, 0 , 10);
  char_10x16(34, 0 , date_time.TIME.min/10);
  char_10x16(44, 0 , date_time.TIME.min%10);

  int i;
    Gotoxy(60,0);
    print_char(date_time.DATE.day/10 + 0x30);
    print_char(date_time.DATE.day%10 + 0x30);
    print_char('.');
    print_char((date_time.DATE.month+1)/10 + 0x30);
    print_char((date_time.DATE.month+1)%10 + 0x30);

    int m, Y = date_time.DATE.year;
    if (date_time.DATE.month < 2) { Y = Y - 1; m = date_time.DATE.month + 13;}
    else                          {            m = date_time.DATE.month + 1;}
    dayOfWeek = getDayOfWeek();

    Gotoxy(60, 1);
    print_char('-');
    for (i = 0; i < 3; i++) print_char(Days[dayOfWeek][i]);
    print_char('-');

}
//==============================================================================
int getDayOfWeek(void)
{
  int m, Y = date_time.DATE.year;
  if (date_time.DATE.month < 2) { Y = Y - 1; m = date_time.DATE.month + 13;}
  else                          {            m = date_time.DATE.month + 1;}

  int a = (date_time.DATE.day + (26*(m+1)/10) + Y + Y/4 + 6*Y/100 + Y/400) % 7;
  //ets_uart_printf("Day number is %d\r\n", a);

  return a;
}
//==============================================================================
void ICACHE_FLASH_ATTR timeIncrement(void)
{
  date_time.TIME.sec++;
  if(date_time.TIME.sec >= 60)
  {
    date_time.TIME.sec = 0;
    date_time.TIME.min++;
    if(date_time.TIME.min >= 60)
    {
      date_time.TIME.min = 0;
      date_time.TIME.hour++;
      if(date_time.TIME.hour >= 24)
      {
        date_time.TIME.hour = 0;
        date_time.DATE.day++;
        if (date_time.DATE.day > daysInMonth[date_time.DATE.month])
        {
          date_time.DATE.day = 1;
          date_time.DATE.month ++;
          if(date_time.DATE.month >= 12)
          {
            date_time.DATE.month = 0;
            date_time.DATE.year++;
          }
        }
      }
    }
  }
        remoteTemp.timeData[0] = (uint8) date_time.TIME.sec;
  		remoteTemp.timeData[1] = (uint8) date_time.TIME.min;
  		remoteTemp.timeData[2] = (uint8) date_time.TIME.hour;
  		remoteTemp.timeData[3] = (uint8) date_time.DATE.day;
  		remoteTemp.timeData[4] = (uint8) date_time.DATE.month;
  		remoteTemp.timeData[5] = (uint8) (date_time.DATE.year - 2000);
//  		int i;
//  		for (i = 0; i < 6; i++) ets_uart_printf("%d ",  remoteTemp.timeData[i]);
//  					ets_uart_printf("\r\n");
}
//==============================================================================
void ICACHE_FLASH_ATTR timeUpdate(char *aPtr)
{
	ets_uart_printf("Time update: %s\r\n", aPtr);
					  date_time.DATE.year  = aPtr[2] + 2000;
	                  date_time.DATE.month = aPtr[3];
	                  date_time.DATE.day   = aPtr[4];

	                  date_time.TIME.hour =  aPtr[5];
	                  date_time.TIME.min   = aPtr[6];
	                  date_time.TIME.sec   = aPtr[7];
}
//=============================================================================
u_CONFIG configs /*= {
		.cfg[0].periodsCnt = 0x30303036,
		.cfg[0].pConfig[0].hmStart = 0x30303030, .cfg[0].pConfig[0].temperature = 0x30313930,
		.cfg[0].pConfig[1].hmStart = 0x30363030, .cfg[0].pConfig[1].temperature = 0x30323232,
		.cfg[0].pConfig[2].hmStart = 0x30373330, .cfg[0].pConfig[2].temperature = 0x30313930,
		.cfg[0].pConfig[3].hmStart = 0x31323135, .cfg[0].pConfig[3].temperature = 0x30323035,
		.cfg[0].pConfig[4].hmStart = 0x31333030, .cfg[0].pConfig[4].temperature = 0x30313930,
		.cfg[0].pConfig[5].hmStart = 0x31373330, .cfg[0].pConfig[5].temperature = 0x30323135,
		.cfg[1].periodsCnt = 0x30303036,
		.cfg[1].pConfig[0].hmStart = 0x30303030, .cfg[1].pConfig[0].temperature = 0x30313930,
		.cfg[1].pConfig[1].hmStart = 0x30383030, .cfg[1].pConfig[1].temperature = 0x30323232,
		.cfg[1].pConfig[2].hmStart = 0x30393030, .cfg[1].pConfig[2].temperature = 0x30313930,
		.cfg[1].pConfig[3].hmStart = 0x31323030, .cfg[1].pConfig[3].temperature = 0x30323035,
		.cfg[1].pConfig[4].hmStart = 0x31353030, .cfg[1].pConfig[4].temperature = 0x30313930,
		.cfg[1].pConfig[5].hmStart = 0x31383030, .cfg[1].pConfig[5].temperature = 0x30323135,
        .nastr.interval = 600,
		.nastr.delta = 5,
		.nastr.day[0] = 'W',
		.nastr.day[1] = 'H',
		.nastr.day[2] = 'W',
		.nastr.day[3] = 'H',
		.nastr.day[4] = 'W',
		.nastr.day[5] = 'H',
		.nastr.day[6] = 'H',
		.hwSettings.wifi.mode = SOFTAP_MODE,
		.hwSettings.wifi.auth = AUTH_OPEN,
		.hwSettings.wifi.SSID = "voodoo",
        .hwSettings.wifi.SSID_PASS = "eminem82"}*/;
////==============================================================================
//u_NASTROYKI nastroyki = {.interval = 600, .delta = 5,
//                             .day[0] = 'W',
//                             .day[1] = 'H',
//                             .day[2] = 'W',
//                             .day[3] = 'H',
//                             .day[4] = 'W',
//                             .day[5] = 'H',
//                             .day[6] = 'H'};
//u_NASTROYKI *nastroyki = (u_NASTROYKI*) 0x1900;
//u_CONFIG *cPtrH, *cPtrW;
//=============================================================================
void ICACHE_FLASH_ATTR saveConfigs(void) {
	int result = -1;
	ets_uart_printf("sizeof(u_CONFIG) = %d\r\n", sizeof(u_CONFIG));
	//uart0_tx_buffer(configs, 50);

	int a = 10000;

	ets_uart_printf("delay %d msec\r\n", a);
	os_delay_us(a);
	ets_uart_printf("Erase sector %d\r\n", a);
	result = spi_flash_erase_sector(PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE);
	ets_uart_printf("Erase sector result = %d\r\n", result);

	result = -1;
	os_delay_us(a);
	ets_uart_printf("Write sector %d \r\n", a);
	result = spi_flash_write(
			(PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE,
			(uint32 *) &configs, sizeof(u_CONFIG));

	ets_uart_printf("Write W = %d", result);



}

//=============================================================================
void ICACHE_FLASH_ATTR readConfigs(void) {
	int result = -1;
	result = spi_flash_read(
			(PRIV_PARAM_START_SEC + PRIV_PARAM_SAVE) * SPI_FLASH_SEC_SIZE,
			(uint32 *) &configs, sizeof(u_CONFIG));

//	ets_uart_printf("read result W = %d\r\n", result);
//
//	//uart0_tx_buffer(configs, 5);
//	int i, k, u;
//	char t[4], tt[4];
//	for(u = 0; u < 2; u++)
//	for(i = 0; i < 6; i++)
//	{
//		for(k = 0; k < 4; k++) t[3-k]  = (char)((configs.cfg[u].pConfig[i].hmStart     >> (k*8)) & 0x000000ff);
//		for(k = 0; k < 4; k++) tt[3-k] = (char)((configs.cfg[u].pConfig[i].temperature >> (k*8)) & 0x000000ff);
//
//			ets_uart_printf("config[%d] %d - time: %s  temp: %s\r\n", u, i, t, tt);
//	}
//
//	for(i = 0; i < 7; i++) ets_uart_printf("day[%d] - %c\r\n", i, (char)(configs.nastr.day[i]));

}
//==============================================================================
uint32 ICACHE_FLASH_ATTR getSetTemperature()  
{
	
  unsigned int aTime = date_time.TIME.hour * 60 + date_time.TIME.min;

  int aDayNumber = getDayOfWeek();
  //ets_uart_printf("aDayNumber = %d\r\n", aDayNumber);

  unsigned char aDay;
  u_CONFIG *aPtr;
  unsigned long col;
  
  if      (aDayNumber == 0)  aDay = configs.nastr.day[5];
  else if (aDayNumber == 1)  aDay = configs.nastr.day[6];
  else                       aDay = configs.nastr.day[aDayNumber - 2];  
  
  u_CONFIG_u cPtr = (aDay == 'H') ? configs.cfg[1] : configs.cfg[0];


      
  uint32 curPeriod = 0;  

  for(curPeriod = 0; curPeriod < (cPtr.periodsCnt  - '0' - 1); curPeriod++)
  {
	uint32 a = cPtr.pConfig[curPeriod + 1].hmStart;	
        unsigned int end = (((a>>24) - '0') * 10 +   (((a>>16) & 0x00000ff) - '0')) * 60 +
                       ((((a>>8) & 0x00000ff) - '0') * 10 +   ((a & 0x00000ff) - '0'));    
    if(aTime < end)  break;     
  }

//    Gotoxy(0,2);
//	print_char((char) (aDay));
//	print_char((char) (cPtr.pConfig[curPeriod].temperature >> 16));
//	print_char((char) (cPtr.pConfig[curPeriod].temperature >> 8));
//	print_char((char) (cPtr.pConfig[curPeriod].temperature));
//	print_char((char) (' '));
  return cPtr.pConfig[curPeriod].temperature;
}
//==============================================================================
unsigned char ICACHE_FLASH_ATTR cmpTemperature (unsigned char *aT, signed int arcTemper)
{  
  static unsigned char out = 0;  

  int tmp = (aT[2] - '0') * 100 + (aT[1] - '0') * 10 + (aT[0] - '0');

  Gotoxy(90,7);
  if      (arcTemper > tmp + (configs.nastr.delta))
  {
	  print_char(0xbd);
	  out = 0;
  }
  else if (arcTemper < tmp - (configs.nastr.delta))
  {    
    out = 1;
    print_char(0x1e);
  }
  

 return out; 
}
