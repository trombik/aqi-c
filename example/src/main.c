#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

#include <aqi.h>

#define VERSION "0.1.0"

int main(int argc, char *argv[])
{
    float c;
    int aqi;
    int err = 1;
    int opt;

    while ((opt = getopt(argc, argv, "v")) != EOF) {
        switch(opt) {
            case 'v':
                printf("version %s\n", VERSION);
                exit(0);
                break;
        }
    }
    errno = 0;
    c = strtof(argv[optind], NULL);
    if (errno) {
        printf("invalid value: %s\n", argv[optind]);
        err = 1;
        goto fail;
    }
    err = aqi_calc(AQI_TYPE_PM_2_5, c, &aqi);
    if (err) {
        printf("aqi_calc(): %d\n", err);
        goto fail;
    }
    printf("AQI (PM 2.5): %d\n", aqi);
    err = 0;
fail:
    exit(err);
}
