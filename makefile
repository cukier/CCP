CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT

all: ccp ccp2 ccp3


ccp: ccp.c
	$(CC) $(CFLAGS) ccp.c
ccp2: ccp2.c
	$(CC) $(CFLAGS) ccp2.c
ccp3: ccp3.c
	$(CC) $(CFLAGS) ccp3.c

clean:
	rm *.cof *.err *.esym *.hex *.lst *.PWI *.bak *.STA *.sym *.tre *.DBK