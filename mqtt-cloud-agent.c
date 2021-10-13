//--------------------------------------------------------------------------
//	This program is free software : you can redistribute it and / or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//--------------------------------------------------------------------------
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//  GNU General Public License for more details.
//--------------------------------------------------------------------------
//  You should have received a copy of the GNU General Public License
//  along with this program.If not, see < https : //www.gnu.org/licenses/>.
//--------------------------------------------------------------------------
///	\file		mqtt-cloud-agent
///
///
///	\version	0.0.0 (alpha)
///
///
///	\brief		simple cloud agent using an mqtt api
///
///
///	\author		Kurt Braun kurt.braun@gmail.com
///
//--------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>
#include "get_config.h"
#include "mqtt.h"
#include "logger.h"

// main mosquitto object
struct mosquitto *mosq; // = NULL;
//struct prog_config this_config;
int switch_state = 0;
int mqtt_state = 0;
int led_state = 0;
int i = 0;

int main(int argc, char *argv[])
{

	log_set_quiet(false);
	log_set_level(1);

	// get the config
	this_config = get_program_config();
	usleep(1000);

	mosquitto_lib_init();
	printf("\nCrabgrass Started.\n");
	mosq = mosquitto_new(NULL, true, NULL);
	if (!mosq)
	{
		log_error("Can't initialize Mosquitto library\n");
		exit(-1);
	}

	if (this_config.support_tls)
	{
		mosquitto_tls_set(mosq, this_config.rootca_path, NULL, this_config.cert_path, this_config.key_path, NULL);
	}

	int Connected = 0;
	// Establish a connection to the MQTT server. Do not use a keep-alive ping
	printf("Connecting...\n");
	int mosqConnectResp = mosquitto_connect(mosq, this_config.mqtt_endpoint, this_config.mqtt_port, 0);
	if (mosqConnectResp)
	{
		log_error("Failed to connect to %s at port %d", this_config.mqtt_endpoint, this_config.mqtt_port);
		return -1;
	}
	else
	{
		if (!Connected)
		{
			printf("Connected to %s at port %d\n", this_config.mqtt_endpoint, this_config.mqtt_port);
			Connected = 1;
		}
		int mosqSubResp = mosquitto_subscribe(mosq, NULL, this_config.event_sub_topic, 0);
		//int mosqSubResp = mosquitto_subscribe(mosq, NULL, "#", 0);
		if (mosqSubResp)
		{
			log_error("Problem subscribing to %s", this_config.event_sub_topic);
		}
		else
		{
			printf("Subscribed to %s\n", this_config.event_sub_topic);
			// Specify the function to call when a new message is received
			mosquitto_message_callback_set(mosq, mqtt_callback);
			mqtt_state = 1;
		}
	}
	int initCycles = 0;
	sleep(2);
while (1)
{
	mosquitto_loop(mosq, -1, 1);
}
}