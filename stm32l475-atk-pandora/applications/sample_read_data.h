
#ifndef __READ_DATA_H__
#define __READ_DATA_H__


#include <sensor.h>

#define INFORM_EVENT_NAME    "inform"
#define INFORM_FLAG_STORE    (1 << 0)
#define INFORM_FLAG_UPLORD   (1 << 1)

int temp_get_data(struct rt_sensor_data *data);
int humi_get_data(struct rt_sensor_data *data);
int collection_init(void);

#endif
