CC= gcc
OBJECTS = mqtt-cloud-agent.o get_config.o logger.o mqtt.o json.o
LIBS = -I. -lconfig  -lmosquitto -ljson-c
crabgrass: $(OBJECTS)
	$(CC) -o crabgrass $(OBJECTS) $(LIBS)

mqtt-cloud-agent.o : mqtt-cloud-agent.c
	$(CC) -c -w mqtt-cloud-agent.c $(LIBS)

get_config.o : get_config.c
	$(CC) -c -w get_config.c $(LIBS)

logger.o : logger.c
	$(CC) -c -w logger.c $(LIBS)

mqtt.o : mqtt.c
	$(CC) -c -w mqtt.c $(LIBS)

json.o : json.c
	$(CC) -c -w json.c $(LIBS)

clean :
	rm -rf *.o