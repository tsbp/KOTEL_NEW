//============================================================================================================================
#include "ets_sys.h"
#include "osapi.h"
#include "c_types.h"
#include "gpio.h"
#include "os_type.h"
#include <mem.h>
#include "user_config.h"
#include "user_interface.h"
//#include <espconn.h>
#include "driver/uart.h"
#include "driver/lcd1100.h"
#include "driver/DS18B20_PR.h"
#include "driver/Configs.h"
#include "driver/UDP_Source.h"
#include "driver/wifi.h"
#include "driver/gpio16.h"
#include "driver/services.h"
//============================================================================================================================
extern s_DATE_TIME date_time;

#define GPIO_LED_PIN 0


#define user_procLcdUpdatePeriod      1000
#define user_procTaskPrio        0
#define user_procTaskQueueLen    1

static char temperature[2][POINTS_CNT][4];

static volatile os_timer_t loop_timer;

void user_init(void);
static void loop(os_event_t *events);


//======================= Main code function ============================================================
static void ICACHE_FLASH_ATTR loop(os_event_t *events)
{

}


/*========================================================================
 * Setup program. When user_init runs the debug printouts will not always
 * show on the serial console. So i run the inits in here, 2 seconds later.
 *============================================================================*/
static void ICACHE_FLASH_ATTR setup(void)
{


	//saveConfigs();

	setup_wifi_ap_mode();

//	if     (configs.hwSettings.wifi.mode == SOFTAP_MODE) 		setup_wifi_ap_mode();
//	else if(configs.hwSettings.wifi.mode == STATION_MODE)		setup_wifi_st_mode();

	ets_uart_printf("configs.nastr.SSID = %s\r\n", configs.hwSettings.wifi.SSID);
	ets_uart_printf("configs.nastr.SSID_PASS = %s\r\n", configs.hwSettings.wifi.SSID_PASS);

	//UDP_Init();
	UDP_Init_client();


	// Start loop timer
	os_timer_disarm(&loop_timer);
	os_timer_setfn(&loop_timer, (os_timer_func_t *) loop, NULL);
	os_timer_arm(&loop_timer, user_procLcdUpdatePeriod, true);

}

void user_rf_pre_init(void)
{
}

//========================== Init function  =============================================================
//
void ICACHE_FLASH_ATTR user_init(void) {

	uart_init(BIT_RATE_115200, BIT_RATE_115200);
	os_delay_us(1000000);
	ets_uart_printf("System init...\r\n");


	//saveConfigs();

	// turn off WiFi for this console only demo
	wifi_station_set_auto_connect(false);
	wifi_station_disconnect();

	readConfigs();




	// Start setup timer
	os_timer_disarm(&loop_timer);
	os_timer_setfn(&loop_timer, (os_timer_func_t *) setup, NULL);
	os_timer_arm(&loop_timer, user_procLcdUpdatePeriod, false);
}
