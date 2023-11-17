#pragma once

#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "driver/spi_slave.h"
#include "driver/spi_common.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "driver/pulse_cnt.h"

#include "soc/i2c_reg.h"
#include "soc/i2c_struct.h"

#include "esp_err.h"
#include "esp_task_wdt.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
