#include <endian.h>
#ifndef htobe16
# define htobe16(x) htons(x)
#endif
#ifndef htobe32
# define htobe32(x) htonl(x)
#endif
#ifndef be16toh
# define be16toh(x) ntohs(x)
#endif
#ifndef be32toh
# define be32toh(x) ntohl(x)
#endif
#ifndef htobe64
# define htobe64(x)      (x)
#endif
#ifndef be64toh
# define be64toh(x)      (x)
#endif
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

typedef int8_t s8;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint64_t u64;

/* taken from ath9k.h */
#define SPECTRAL_HT20_NUM_BINS          56

enum ath_fft_sample_type {
	ATH_FFT_SAMPLE_HT20 = 1
};

struct fft_sample_tlv {
	u8 type; /* see ath_fft_sample */
	u16 length;
	/* type dependent data follows */
} __attribute__((packed));

struct fft_sample_ht20 {
	u8 max_exp;

	u16 freq;
	s8 rssi;
	s8 noise;

	u16 max_magnitude;
	u8 max_index;
	u8 bitmap_weight;

	u64 tsf;

	u8 data[SPECTRAL_HT20_NUM_BINS];
} __attribute__((packed));

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


static void parse_ht20(void) {
	struct fft_sample_ht20 sample;
	int i;
	
	memset(&sample, 0, sizeof(sample));
	if (fread(&sample, sizeof(sample), 1, stdin) != 1) {
		fprintf(stderr, "error: incomplete read in %s\n", __func__);
		return;
	}

	sample.freq = be16toh(sample.freq);
	sample.max_magnitude = be16toh(sample.max_magnitude);
	sample.tsf = be64toh(sample.tsf);
	
	printf("{");
	printf("\"max_exp\": %u,", sample.max_exp);
	printf("\"freq\":%u,", sample.freq);
	printf("\"rssi\": %i,", sample.rssi);
	printf("\"noise\": %i,", sample.noise);
	printf("\"max_magnitude\": %u,", sample.max_magnitude);
	printf("\"max_index\": %u,", sample.max_index);
	printf("\"bitmap_weight\": %u,", sample.bitmap_weight);
	printf("\"tsf\": %llu,", sample.tsf);
	
	printf("\"data\": [");
	for (i=0; i<ARRAY_SIZE(sample.data); i++) {
		if (i != 0)
			printf(",");
		printf("%u", sample.data[i]);
	}
	printf("]");
	printf("}");
}

int main() {
	struct fft_sample_tlv tlv;
	u8 discard;
	u8 first = 1;
	
	printf("HTTP/1.1 200 OK\r\n");
	printf("Access-Control-Allow-Origin: *\r\n");
	printf("Content-Type: text/plain\r\n\r\n");
	
	printf("{");
	
	printf("\"spectral_scan\": [");
	while (!feof(stdin)) {
		if (fread(&tlv.type, 1, 1, stdin) != 1)
			break;
		if (fread(&tlv.length, 2, 1, stdin) != 1)
			break;

		switch (tlv.type) {
		case ATH_FFT_SAMPLE_HT20:
			if (!first)
				printf(","); 
			first = 0;
			parse_ht20();
			break;
		default:
			printf("\"error\": \"unsupported TLV type = %hhu\"", tlv.type);
			for (; tlv.length > 0; tlv.length--)
				fread(&discard, 1, 1, stdin);
			break;
		}
	}
	printf("]");
	printf("}\r\n\r\n");
	fflush(stdout);
	return 0;
}
