#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <json-c/json.h>
#include "json.h"
#include "get_config.h"
#include <time.h>

#define MAX_IMG_LENGTH 2048

int *parse_mqtt(struct mosquitto *mosq, char *message) {
    struct json_object *jobj;

    char val = "";
	jobj = json_tokener_parse(message);
	//printf("Command Sent:\n%s\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
 
    json_object *root_obj = json_tokener_parse(message);
    json_object *tmp;
    if (json_object_object_get_ex(root_obj, "command", &tmp)){
        printf("command: %s\n", json_object_get_string(tmp));
    }

	// -------============--------
	// CLI Command
	FILE *pf;
	char command[100];
	char data[512];
	// Execute a process listing
	//sprintf(command, "ps aux wwwf"); 
    sprintf(command, json_object_get_string(tmp));
	// Setup our pipe for reading and execute our command.
	pf = popen(command,"r"); 
	// Error handling
	// Get the data from the process execution
	fgets(data, 512 , pf);
    printf("data: %s", data);
	// the data is now in 'data'
	if(pclose(pf) != 0){
		fprintf(stderr," Error: Failed to close command stream \n");
	}
    // -------============--------
    // {response : "response object"}
    struct json_object	*jsonMain = json_object_new_object();
    json_object_object_add(jsonMain, "payload", json_object_new_string(data));
    char *response_string = json_object_to_json_string(jsonMain);
	//int pub_resp = mosquitto_publish(mosq, NULL, this_config.status_pub_topic, strlen(response_string), response_string, 0, 0);
	int pub_resp = mosquitto_publish(mosq, NULL, "cli_response", strlen(response_string), response_string, 0, 0);
    printf("Command Sent:\n%s\n", json_object_to_json_string_ext(jsonMain, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    // -------============--------

	return 0;
};
