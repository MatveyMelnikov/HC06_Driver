#ifndef HC06_DRIVER_H
#define HC06_DRIVER_H

#include <stdint.h>
#include "hc06_defs.h"

void hc06_create(void);
void hc06_destroy(void);
hc06_status hc06_check_link(void);
hc06_status hc06_set_baudrate(hc06_baudrate baudrate);
hc06_baudrate hc_06_determine_baudrate(void);

#endif