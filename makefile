CC=ccsc
CFLAGS=+FH +LN -T -A -M -Z +DF +Y=9 +STDOUT

all: ccp

ccp: ccp.c
	$(CC) $(CFLAGS) ccp.c

clean:
	rm *.cof *.err *.esym *.hex *.lst *.PWI *.bak *.STA *.sym *.tre *.DBK