#include <osapi.h>
#include <user_interface.h>

/* secrets.h is not included in the repo. YUou must provide it in the 
search path and it must define
#define SSID "MySSID"
#define PASSWORD "MyPassword"
*/
#include "secrets.h"

static os_timer_t p_on_timer;
static os_timer_t p_off_timer;

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABBBCDDD
 *                A : rf cal
 *                B : at parameters
 *                C : rf init data
 *                D : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
*******************************************************************************/
uint32 ICACHE_FLASH_ATTR
user_rf_cal_sector_set(void)
{
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;
        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;
        default:
            rf_cal_sec = 0;
            break;
    }
    return rf_cal_sec;
}

void blinky(void *arg)
{
	static uint8_t state = 0;

	if (state) {
		GPIO_OUTPUT_SET(2, 1);
	} else {
		GPIO_OUTPUT_SET(2, 0);
	}
	state ^= 1;
}

void ICACHE_FLASH_ATTR user_init(void)
{
    gpio_init();

    uart_init(115200, 115200);
    os_printf("SDK version:%s\n", system_get_sdk_version());

    // Disable WiFi
    //wifi_set_opmode(NULL_MODE);
    wifi_set_opmode(STATION_MODE);
    wifi_station_set_hostname("esp8266.1");
    static char ssid[32] = SSID;
    static char password[64] = PASSWORD;
    static struct station_config stationConf;

    stationConf.bssid_set = 0;
    os_memcpy(&stationConf.ssid, ssid, 32);
    os_memcpy(&stationConf.password, password, 64);

    wifi_station_set_config(&stationConf);

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

    os_timer_disarm(&p_on_timer);
    os_timer_setfn(&p_on_timer, (os_timer_func_t *)blinky, NULL);
    os_timer_arm(&p_on_timer, 500, 1);

    os_delay_us(500);

    os_timer_disarm(&p_off_timer);
    os_timer_setfn(&p_off_timer, (os_timer_func_t *)blinky, NULL);
    os_timer_arm(&p_off_timer, 500, 1);
}
