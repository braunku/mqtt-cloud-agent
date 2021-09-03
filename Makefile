CFLAGS = -I../usr/include
LDFLAGS = -L../../lib
LIBS = -llibconfig -lmosquitto
CC= gcc
mqtt-cloud-agent: mqtt-cloud-agent.o get_config.o logger.o mqtt.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) mqtt-cloud-agent.o get_config.o logger.o mqtt.o -o mqtt-cloud-agent $(LIBS)

mqtt-cloud-agent.o : mqtt-cloud-agent.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) mqtt-cloud-agent.c -o mqtt-cloud-agent.o $(LIBS)

get_config.o : get_config.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) get_config.c -o get_config.o $(LIBS)

logger.o : logger.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) logger.c -o logger.o $(LIBS)

mqtt.o : mqtt.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) mqtt.c -o mmqtt.o $(LIBS)

clean :
	rm -rf *.o 