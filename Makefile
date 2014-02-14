LDFLAGS += -lm -s
CFLAGS += -Os

fft2txt: fft2txt.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
fft2json: fft2json.o
	$(CC) -o $@ $^ $(CFLAGS)
