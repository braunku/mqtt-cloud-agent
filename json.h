#ifndef __JSON_H__
#define __JSON_H__

#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <mosquitto.h>
#include "get_config.h"
#include "logger.h"

struct channel_command
{
	int module;
	int channel;
	int value;
};


extern int *parse_mqtt(struct mosquitto *mosq, char *message);

#endif /*__JSON_H__*/