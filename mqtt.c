#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "logger.h"
#include "get_config.h"
#include "json.h"

//char *sub_topic;

struct prog_config this_config;

void mqtt_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
	if(strcmp(message->topic, this_config.event_sub_topic) != 0){
		log_error("received message out of topic range");
	}else{
		// copy in the buffer
		char *buffer = message->payload;
		if(parse_mqtt(mosq, buffer)) {
			log_error("failed to parse message");
		}
	}		
}
