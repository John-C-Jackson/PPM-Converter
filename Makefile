all: ppm_read_write

ppm_read_write: ppm_read_write.c
	gcc ppm_read_write.c -o ppm_read_write

clean:
	rm -f ppm_read_write
