#include "hc06_driver.h"
#include "hc06_defs.h"
#include "hc06_io.h"
#include "hc06_time.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static char buffer[20];
static char *baudrate_cmd = "AT+UART=%u,0,0\r\n";
static char *hex_symbols = "123456789A";
static const uint32_t baudrate_int[] = {
    1200, 2400, 4800, 9600, 19200, 38400, 
    57600, 115200, 230400, 460800
};
static hc06_baudrate current_baudrate;

// Defines -------------------------------------------------------------------

#define GET_BAUDRATE_INT(baudrate_enum) \
    baudrate_int[(baudrate_enum)]

// Static functions ----------------------------------------------------------

static void set_check_cmd()
{
    strcpy(buffer, "AT\r\n");
}

static void set_baudrate_cmd(hc06_baudrate baudrate)
{
    sprintf(buffer, baudrate_cmd, GET_BAUDRATE_INT(baudrate));
}

static hc06_status send_at_cmd()
{
    hc06_io_write((uint8_t*)buffer, strlen(buffer));
    hc06_io_read((uint8_t*)buffer, 4);

    if (strstr(buffer, "OK") == NULL)
        return HC06_ERROR;

    return HC06_OK;
}

// Implementations -----------------------------------------------------------

void hc06_create()
{
    hc06_io_set_baudrate(GET_BAUDRATE_INT(HC06_9600));
    current_baudrate = HC06_9600;
}

void hc06_destroy()
{
    hc06_io_set_baudrate(GET_BAUDRATE_INT(HC06_9600));
    current_baudrate = HC06_9600;
}

hc06_status hc06_check_link()
{
    set_check_cmd();

    return send_at_cmd();
}

hc06_status hc06_set_baudrate(hc06_baudrate baudrate)
{
    set_baudrate_cmd(baudrate);

    hc06_status status = hc06_io_write((uint8_t*)buffer, strlen(buffer));
    status |= hc06_io_read((uint8_t*)buffer, 4);
    if (strstr(buffer, "OK") == NULL)
        return HC06_ERROR;

    status |= hc06_io_set_baudrate(GET_BAUDRATE_INT(baudrate));
    current_baudrate = baudrate;

    return status;
}

hc06_baudrate hc_06_determine_baudrate(void)
{
    hc06_baudrate baudrate = HC06_1200;
    for (; baudrate <= HC06_UNDEFINED; baudrate++)
    {
        hc06_io_set_baudrate(GET_BAUDRATE_INT(baudrate));
        if (hc06_check_link() == HC06_OK)
            break;
    }

    return baudrate;
}