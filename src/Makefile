include $(ROOT)/config.$(OSTYPE).mk

OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
SERVER_OBJS = tcp_server.o
CLIENT_OBJS = tcp_client.o
all:$(BINARYDIR)/server $(SERVER_OBJS) $(BINARYDIR)/client $(CLIENT_OBJS)
$(BINARYDIR)/server:$(SERVER_OBJS)
	$(LD) -o $@ $(SERVER_OBJS) $(LDFLAGS)
$(BINARYDIR)/client:$(CLIENT_OBJS)
	$(LD) -o $@ $(CLIENT_OBJS) $(LDFLAGS)

#main.o:main.c
#	$(CROSS_COMPILER)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
.PHONY:clean
