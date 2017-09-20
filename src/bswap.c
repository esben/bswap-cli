/*
 * Simple wrapper to bswap(3) C functions
 *
 * Copyright 2017 Esben Haabendal <esben@haabendal.dk>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <endian.h>
#include <byteswap.h>

static void usage(const char *progname)
{
	printf("usage: %s [-h] [INPUT] [OUTPUT]\n", progname);
}

static void read_bswap_write_16(FILE *in, FILE *out)
{
	uint16_t buf;
	size_t read;

	read = fread(&buf, 1, sizeof(buf), in);
	if (read == 0)
		return;
	if (read < sizeof(buf))
		memset(((void *)&buf) + read, 0, sizeof(buf) - read);
	buf = bswap_16(buf);
	fwrite(&buf, 1, sizeof(buf), out);
}

static void read_bswap_write_32(FILE *in, FILE *out)
{
	uint32_t buf;
	size_t read;

	read = fread(&buf, 1, sizeof(buf), in);
	if (read == 0)
		return;
	if (read < sizeof(buf))
		memset(((void *)&buf) + read, 0, sizeof(buf) - read);
	buf = bswap_32(buf);
	fwrite(&buf, 1, sizeof(buf), out);
}

static void read_bswap_write_64(FILE *in, FILE *out)
{
	uint64_t buf;
	size_t read;

	read = fread(&buf, 1, sizeof(buf), in);
	if (read == 0)
		return;
	if (read < sizeof(buf))
		memset(((void *)&buf) + read, 0, sizeof(buf) - read);
	buf = bswap_64(buf);
	fwrite(&buf, 1, sizeof(buf), out);
}

int main(int argc, char **argv)
{
	char *progname;
	void (*read_bswap_write)(FILE *in, FILE *out);
	int opt;
	FILE *in = stdin, *out = stdout;

	progname = basename(argv[0]);
	if (strcmp(progname, "bswap-16") == 0) {
		read_bswap_write = read_bswap_write_16;
	} else if (strcmp(progname, "bswap-32") == 0) {
		read_bswap_write = read_bswap_write_32;
	} else if (strcmp(progname, "bswap-64") == 0) {
		read_bswap_write = read_bswap_write_64;
	} else {
		fprintf(stderr, "Error: invalid program name: %s\n", progname);
		printf("Please install as one of: "
		       "bswap-16, bswap-32 or bswap-64\n");
		return EXIT_FAILURE;
	}

	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
		case 'h':
			usage(progname);
			return EXIT_SUCCESS;
		default:
			usage(progname);
			exit(EXIT_FAILURE);
		}
	}

	if (argc >= 2) {
		in = fopen(argv[1], "rb");
		if (in == NULL) {
			perror("fopen");
			return EXIT_FAILURE;
		}
	}

	if (argc >= 3) {
		out = fopen(argv[2], "wb");
		if (out == NULL) {
			perror("fopen");
			return EXIT_FAILURE;
		}
	}
 
	while (1) {
		if (ferror(in) || ferror(out))
			return EXIT_FAILURE;
		if (feof(in))
			break;
		read_bswap_write(in, out);
	}

	if (fclose(in))
		return EXIT_FAILURE;
	if (fclose(out))
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
