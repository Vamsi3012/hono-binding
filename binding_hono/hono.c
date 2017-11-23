#define AFB_BINDING_VERSION 2
#define _GNU_SOURCE
#define MAXCPUS 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <json-c/json.h>

#include <afb/afb-binding.h>


char buffer[25600];
char num_buffer[33];
int status_code;

void list(struct afb_req req);

int handleCode(int code)
{
        int status = 0;
        switch (code)
        {
                case 200: //Accepted
                        printf("200 Accepted\n");
                        printf("Registration of device to Hono instance accepted.\n");
                        status = 1;
                        break;
                case 201: //Created
                        printf("201 Created\n");
                        printf("Registration of device to Hono instance is done.\n");
                        status = 1;
                        break;
                case 202:
                        status = 1; //Telemetry data accepted
                        break;
                case 203:
                case 204:
                case 205:
                case 206:
                case 207:
                case 208:
                case 209:
                        status = 1;
                        break;
                case 400:
                        fprintf(stderr, ("400 Bad Request\n"));
			puts("400 Bad Request\n");
                        status = 0;
                        break;
                case 403:
                        fprintf(stderr, ("403 Forbidden\n"));
			puts("403 Forbidden\n");
			status_code = 403;
                        status = 0;
                        break;
                case 409:
                        fprintf(stderr, ("409 Conflict. A device with this ID is registered already. \n"));
			puts("409 Conflict. A device with this ID is registered already. \n");
                        status = 0;
			status_code = 409;
                        break;
                case 503:
                        fprintf(stderr, ("503 Service Unavailable. You may need to create a consumer."));
			puts("503 Service Unavailable. You may need to create a consumer.\n");
			status_code = 503;
                        status = 0;
                        break;
                case 401:
                case 402:
                case 404:
                case 405:
                case 406:
                case 407:
                case 408:
                        fprintf(stderr, ("Error\n"));
			puts("Error: 408\n");
			status_code = 408;
                        status = 0;
                        break;
                default:
                        status = 0;
			status_code = code;
			puts("Error: default\n");
                        break;
        }
        return status;
} 

int registerDeviceToHonoInstance (char * host_name, int port, char * tenant_name, char * device_id)
{
	FILE *fp;
	int code;
	int status;

	//Prepare command as string
	//Example: "curl -X POST -i -H 'Content-Type: ' 'device_id=AStringID' http://localhost:28080/registration/DEFAULT_TENANT"
	//sprintf(buffer, "curl -X POST -i -d 'device_id=");
	sprintf(buffer, "curl -X POST -i -H 'Content-Type: application/json' -d '{\"device-id\": \"");
	strcat(buffer, device_id);
	strcat(buffer, "\"}' http://");
	strcat(buffer, host_name);
	strcat(buffer, ":");
	snprintf(num_buffer, sizeof(num_buffer), "%d", port);
	strcat(buffer, num_buffer);
	num_buffer[0] = 0; //Clear array
	strcat(buffer, "/registration/");
	strcat(buffer, tenant_name);

	//To redirect pipe to prevent stdout showing all outputs generated by curl
	strcat(buffer, " 2>/dev/null"); //2>&1 would redirect to stderr, we choose to be able to parse returned code

	puts(buffer);
	//Execute the command
	fp = popen(buffer,"r");

	//Get and Parse the output
	fgets(buffer, 13, fp); //Get the string HTTP/1.1 XXX

	puts(buffer);

	//Prepare the response code
	sscanf(buffer, "HTTP/1.1 %d", &code);

	//Handle the code and return status: 1-succeeded 0-failed
	status = handleCode(code);

	//Close the file
	fclose(fp);

	//Return status
	return status;
}

int sendTelemetryDataToHonoInstance (char * sensor_id, char * host_name, int port, char * tenant_name, char * field, double value)
{
	FILE *fp;
	int code;
	int status;

	buffer[0] = NULL; 
	// curl -X POST -i -u sensor1@DEFAULT_TENANT:hono-secret -H 'Content-Type: application/json' --data-binary '{"temp": 5}' http://localhost:8080/telemetry
	strcat(buffer, "curl -X POST -i -u ");
	strcat(buffer, sensor_id);
	strcat(buffer, "@");
	strcat(buffer, tenant_name);
	strcat(buffer, ":hono-secret -H 'Content-Type: application/json' --data-binary '{\"");
	strcat(buffer, field);
	strcat(buffer, "\": ");
	snprintf(num_buffer, sizeof(num_buffer), "%f", value);
	strcat(buffer, num_buffer);
	num_buffer[0] = 0; //Clear array
	strcat(buffer, "}' http://");
	strcat(buffer, host_name);
	strcat(buffer, ":");
	snprintf(num_buffer, sizeof(num_buffer), "%d", port);
	strcat(buffer, num_buffer);
	num_buffer[0] = 0; //Clear array
	strcat(buffer, "/telemetry/");	

	//To redirect pipe to prevent stdout showing all outputs generated by curl
	strcat(buffer, " 2>/dev/null"); //2>&1 would redirect to stderr, we choose to be able to parse returned code

	puts(buffer);
	//Execute the command
	fp = popen(buffer,"r");

	//Get and Parse the output
	fgets(buffer, 13, fp); //Get the string HTTP/1.1 XXX

	//Prepare the response code
	sscanf(buffer, "HTTP/1.1 %d", &code);

	//Handle the code and return status: 1-succeeded 0-failed
	status = handleCode(code);

	//Close the file
	fclose(fp);

	//Return status
	return status;
}


int sendEventDataToHonoInstance (char * sensor_id, char * host_name, int port, char * tenant_name, char * field, char * event)
{
	FILE *fp;
	int code;
	int status;

	buffer[0] = NULL; 
	// curl -X POST -i -u sensor1@DEFAULT_TENANT:hono-secret -H 'Content-Type: application/json' --data-binary '{"alarm": "fire"}' http://localhost:8080/event
	strcat(buffer, "curl -X POST -i -u ");
	strcat(buffer, sensor_id);
	strcat(buffer, "@");
	strcat(buffer, tenant_name);
	strcat(buffer, ":hono-secret -H 'Content-Type: application/json' --data-binary '{\"");
	strcat(buffer, field);
	strcat(buffer, "\": ");
	strcat(buffer, event);
	strcat(buffer, "}' http://");
	strcat(buffer, host_name);
	strcat(buffer, ":");
	snprintf(num_buffer, sizeof(num_buffer), "%d", port);
	strcat(buffer, num_buffer);
	num_buffer[0] = 0; //Clear array
	strcat(buffer, "/event/");	

	//To redirect pipe to prevent stdout showing all outputs generated by curl
	strcat(buffer, " 2>/dev/null"); //2>&1 would redirect to stderr, we choose to be able to parse returned code

	puts(buffer);
	//Execute the command
	fp = popen(buffer,"r");

	//Get and Parse the output
	fgets(buffer, 13, fp); //Get the string HTTP/1.1 XXX

	//Prepare the response code
	sscanf(buffer, "HTTP/1.1 %d", &code);


	//Handle the code and return status: 1-succeeded 0-failed
	status = handleCode(code);

	//Close the file
	fclose(fp);

	//Return status
	return status;
}

void registerDeviceToHono(struct afb_req req)
{
	AFB_NOTICE("Register Device");
	int port = 0;
	const char *hostName = afb_req_value (req, "host_name");
	const char *deviceID = afb_req_value (req, "device_id");
	const char *portStr = afb_req_value(req, "port");
	const char *tenantName = afb_req_value(req, "tenant_name");
	port = atoi(portStr);

	int status = registerDeviceToHonoInstance(hostName, port, tenantName, deviceID);
	
	if(status == 1){
		afb_req_success(req, NULL, "Device Registered");
	}
	else{
		//afb_req_fail(req, "error", "Device already registered");
		switch(status_code){
			case 409: 
				afb_req_fail(req, "error", "Device already registered");
				break;
			case 408:
				afb_req_fail(req, "error", "Error");
				break;
			default:
				afb_req_fail(req, "error", "Device not registered");
		}
	}
}

void sendTeleDataToHono(struct afb_req req){

	AFB_NOTICE("Send Telemetry data");
	double value_data;
	int port_data;
	//const char *hostName, *tenantName, *deviceID, *field_data;

	const char *hostName = afb_req_value (req, "host_name");
	const char *deviceID = afb_req_value (req, "device_id");
	const char *portData = afb_req_value(req, "port");
	const char *field_data = afb_req_value(req, "field");
	const char *valueData = afb_req_value(req, "value");
	const char *tenantName = afb_req_value (req, "tenant_name");
	const char *sensor_id = afb_req_value(req, "sensor_id");
	value_data = atof(valueData); 
	port_data = atoi(portData);

	if(hostName== NULL)
		afb_req_fail(req, "Bad data received", "host_name");
	if(portData == NULL)
		afb_req_fail(req, "Bad data received", "port");
	if(field_data == NULL)
		afb_req_fail(req, "Bad data received", "field");
	if(valueData == NULL)
		afb_req_fail(req, "Bad data received", "value");
	if(tenantName == NULL)
		afb_req_fail(req, "Bad data received", "tenant_name");
	if(sensor_id == NULL)
		afb_req_fail(req, "Bad data received", "sensor_id");


	int status = sendTelemetryDataToHonoInstance(sensor_id, hostName, port_data, tenantName, field_data, value_data);

	if(status == 1){
		afb_req_success(req, NULL, "Data sent and accepted");
	}
	else{
		switch(status_code){
			case 408:
				afb_req_fail(req, "error", "Error");
				break;
			case 403:
				afb_req_fail(req, "error", "Forbidden");
				break;
			case 503:
				afb_req_fail(req, "error", "Consumer not available");
				break;
			default:
				afb_req_fail(req, "error", "sending failed - Hono is down");
		}
	}
}

void sendEventDataToHono(struct afb_req req){

	AFB_NOTICE("Send event data");
	int port_data;
	//const char *hostName, *tenantName, *deviceID, *field_data;

	const char *hostName = afb_req_value (req, "host_name");
	const char *deviceID = afb_req_value (req, "device_id");
	const char *portData = afb_req_value(req, "port");
	const char *field_data = afb_req_value(req, "field");
	const char *event_data = afb_req_value(req, "event");
	const char *tenantName = afb_req_value (req, "tenant_name");
	const char *sensor_id = afb_req_value(req, "sensor_id");
	port_data = atoi(portData);

	if(hostName== NULL)
		afb_req_fail(req, "Bad data received", "host_name");
	if(portData == NULL)
		afb_req_fail(req, "Bad data received", "port");
	if(field_data == NULL)
		afb_req_fail(req, "Bad data received", "field");
	if(event_data == NULL)
		afb_req_fail(req, "Bad data received", "event");
	if(tenantName == NULL)
		afb_req_fail(req, "Bad data received", "tenant_name");
	if(sensor_id == NULL)
		afb_req_fail(req, "Bad data received", "sensor_id");


	int status = sendEventDataToHonoInstance(sensor_id, hostName, port_data, tenantName, field_data, event_data);

	if(status == 1){
		afb_req_success(req, NULL, "Data sent and accepted");
	}
	else{
		switch(status_code){
			case 408:
				afb_req_fail(req, "error", "Error");
				break;
			case 403:
				afb_req_fail(req, "error", "Forbidden");
				break;
			case 503:
				afb_req_fail(req, "error", "Consumer not available");
				break;
			default:
				afb_req_fail(req, "error", "sending failed - Hono is down");
		}
	}
}



int init()
{
	AFB_NOTICE("Hono init.");
	return 0;
}

int preinit()
{
	AFB_NOTICE("Hono preinint");
	return 0;
}

const afb_verb_v2 verbs[] = {
	{.verb="connect", .callback=registerDeviceToHono, .info = "Connects a device to hono\", \"commnad\" : \"hono connect\", \"Json Arguments\" : {\"host_name\":\"172.18.0.110\", \"port\":\"28080\", \"tenant_name\":\"DEFAULT_TENANT\"}}" },
	{.verb="sendt", .callback=sendTeleDataToHono, .info = "Sends Telemetry data to hono\", \"command\": \"hono sendt\", \"Json Arguments\" : {\"sensor_id\":\"sensor5\",\"host_name\":\"172.18.0.110\", \"port\":\"8080\", \"tenant_name\":\"DEFAULT_TENANT\", \"field\":\"engineSpeed\", \"value\": 45.45}}" },
	{.verb="sende", .callback=sendTeleDataToHono, .info = "Sends event data to hono\", \"command\": \"hono sende\", \"Json Arguments\" : {\"sensor_id\":\"sensor5\",\"host_name\":\"172.18.0.110\", \"port\":\"8080\", \"tenant_name\":\"DEFAULT_TENANT\", \"field\":\"engineSpeed\", \"event\": \"event_name\"}}" },
	{.verb="list", .callback=list, .info = "lists all the verbs and their information.\"}}" }

};

const struct afb_binding_v2 afbBindingV2 = {
	.api = "hono",
	.specification = NULL,
	.verbs = verbs,
	.preinit = preinit,
	.init = init,
	.noconcurrency = 0
};

void list(struct afb_req req)
{	
	char buffer[10000];
	struct json_object * list = json_object_new_array();
	int num_verbs = sizeof(verbs)/sizeof(afb_verb_v2);
	int i = 0;
	buffer[0]=NULL;
	while(i < num_verbs){
		strcat(buffer, "{\"");
		strcat(buffer, verbs[i].verb);
		strcat(buffer, "\":\"");
		strcat(buffer, verbs[i].info);
		AFB_NOTICE(buffer);
		puts("\n");
		json_object_array_add(list, json_tokener_parse(buffer));
		i++;	
		buffer[0]=NULL;
	}
	afb_req_success(req, list, "Verb that lists all available verbs");
}




