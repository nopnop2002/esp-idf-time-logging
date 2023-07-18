#include <string.h>
#include <assert.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_sntp.h"

#include "time_logging.h"

#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0))
#define sntp_setoperatingmode esp_sntp_setoperatingmode
#define sntp_setservername esp_sntp_setservername
#define sntp_init esp_sntp_init
#endif

int __format = FORMAT_DEFAULT;
char __time_format[256];
bool __init_sntp = false;

int logging_vprintf( const char *fmt, va_list l ) {
	if (__format == FORMAT_DEFAULT) {
		return vprintf( fmt, l );
	}

	// Get current date & time
	time_t now;
	struct tm timeinfo;
	time(&now);
	now = now + (CONFIG_LOCAL_TIMEZONE*60*60);
	localtime_r(&now, &timeinfo);

	// Convert from tm to string using format
	char time_str[256];
	memset(time_str, 0, sizeof(time_str));
	size_t time_str_len;
	if (__format == FORMAT_NULL) {
		time_str_len = 0;
	} else {
		strcpy(time_str, "(");
		time_str_len = strftime(&time_str[1], 256, __time_format, &timeinfo);
		strcat(time_str, ")");
		time_str_len = time_str_len + 2;
		//printf("time_str_len=%zd %s\n", time_str_len, time_str);
		//printf("[%s]\n", fmt);
	}

	// Get formatted string length
	va_list _l;
	int len;
	va_copy(_l, l);
	len = vsnprintf(NULL, 0, fmt, _l);
	va_end(_l);
	//printf("len=%d\n", len);

	// Allocate memory
	char *src;
	char *dst;
	src = malloc(len + 1);
	dst = malloc(len + time_str_len + 1);
	memset(dst, 0, len + time_str_len + 1);
	vsnprintf(src, len + 1, fmt, _l);
	//int ret = vprintf( fmt, l );

	int dpos = 0;
	int pass = 0;
	// Replace tick to date & time
	for (int spos=0;spos<len;spos++) {
		if (src[spos] == '(') {
			strcat(dst, time_str);
			pass = 1;
		
		} else if (src[spos] == ')') {
			strcat(dst, &src[spos+1]);
			break;

		} else {
			if (pass == 0) dst[dpos] = src[spos];
			dpos++;
		}
	}
			
	// Show logging
	int ret = printf( "%s", dst );
	//printf("ret=%d\n", ret);

	// Free memory
	free(src);
	free(dst);
	return ret;
}


void time_sync_notification_cb(struct timeval *tv)
{
	printf("Notification of a time synchronization event\n");
}

static void initialize_sntp(void)
{
	printf("Initializing SNTP\n");
	sntp_setoperatingmode(SNTP_OPMODE_POLL);
	//sntp_setservername(0, "pool.ntp.org");
	printf("Your NTP Server is %s\n", CONFIG_NTP_SERVER);
	sntp_setservername(0, CONFIG_NTP_SERVER);
	sntp_set_time_sync_notification_cb(time_sync_notification_cb);
	sntp_init();
}

static esp_err_t obtain_time(void)
{
	initialize_sntp();
	// wait for time to be set
	int retry = 0;
	const int retry_count = 10;
	while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
		printf("Waiting for system time to be set... (%d/%d)\n", retry, retry_count);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}

	if (retry == retry_count) return ESP_FAIL;
	return ESP_OK;
}

void time_logging_init(char * time_format) {
	// obtain time over NTP
	if (__init_sntp == false) {
		esp_err_t ret = obtain_time();
		if(ret != ESP_OK) {
			printf("Fail to getting time over NTP\n");
			while(1) {
				vTaskDelay(1);
			}
		}
		__init_sntp = true;
	}
	

	if (time_format == NULL) {
		__format = FORMAT_NULL;
	} else if (strlen(time_format)) {
		strcpy(__time_format, time_format);
		__format = FORMAT_TIME;
	} else {
		__format = FORMAT_DEFAULT;
	}
	esp_log_set_vprintf(logging_vprintf);
}

