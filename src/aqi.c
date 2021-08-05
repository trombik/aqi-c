/*
 * Copyright (c) 2021 Tomoyuki Sakurai <y@trombik.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stddef.h>
#include "aqi.h"

typedef struct {
    int i_hi;
    int i_low;
    float c_hi;
    float c_low;
} aqi_break_point_t;

/* revised breakpoints
 * https://www.epa.gov/sites/default/files/2016-04/documents/2012_aqi_factsheet.pdf (page 4)
 */
static int aqi_break_point_pm_2_5(float c, aqi_break_point_t *b)
{
    int err = AQI_FAIL;

    if (c < 0) {
        err = AQI_ERR_INVALID_ARG;
        goto fail;
    }
    if (c <= 12) {
        b->i_low = 0;
        b->i_hi  = 50;
        b->c_low = 0;
        b->c_hi  = 12;
    } else if (c <= 35.4) {
        b->i_low = 51;
        b->i_hi  = 100;
        b->c_low = 12.1;
        b->c_hi  = 35.4;
    } else if (c <= 55.4) {
        b->i_low = 101;
        b->i_hi  = 150;
        b->c_low = 35.5;
        b->c_hi  = 55.4;
    } else if (c <= 150.4) {
        b->i_low = 151;
        b->i_hi  = 200;
        b->c_low = 55.5;
        b->c_hi  = 150.4;
    } else if (c <= 250.4) {
        b->i_low = 201;
        b->i_hi  = 300;
        b->c_low = 150.5;
        b->c_hi  = 250.4;
    } else if (c <= 350.4) {
        b->i_low = 301;
        b->i_hi  = 400;
        b->c_low = 250.5;
        b->c_hi  = 350.4;

    } else {
        b->i_low = 401;
        b->i_hi  = 500;
        b->c_low = 350.5;
        b->c_hi  = 500.4;
    }
    err = AQI_OK;
fail:
    return err;
}

static int aqi_break_point_pm_10_0(const float c, aqi_break_point_t *b)
{
    int err = AQI_FAIL;

    if (c < 0) {
        err = AQI_ERR_INVALID_ARG;
        goto fail;
    }
    if (c <= 54) {
        b->i_low = 0;
        b->i_hi  = 54;
        b->c_low = 0;
        b->c_hi  = 50;
    } else if (c <= 154) {
        b->i_low = 51;
        b->i_hi  = 100;
        b->c_low = 55;
        b->c_hi  = 154;
    } else if (c <= 254) {
        b->i_low = 101;
        b->i_hi  = 150;
        b->c_low = 155;
        b->c_hi  = 254;
    } else if (c <= 354) {
        b->i_low = 151;
        b->i_hi  = 200;
        b->c_low = 255;
        b->c_hi  = 354;
    } else if (c <= 424) {
        b->i_low = 201;
        b->i_hi  = 300;
        b->c_low = 355;
        b->c_hi  = 424;
    } else if (c <= 504) {
        b->i_low = 301;
        b->i_hi  = 400;
        b->c_low = 425;
        b->c_hi  = 504;
    } else {
        b->i_low = 401;
        b->i_hi  = 500;
        b->c_low = 505;
        b->c_hi  = 604;
    }
    err = AQI_OK;
fail:
    return err;
}

static int aqi_break_point(const aqi_pollutant_type_t type, const float c, aqi_break_point_t *b)
{
    switch(type) {
        case AQI_TYPE_PM_10_0:
            return aqi_break_point_pm_10_0(c, b);
        case AQI_TYPE_PM_2_5:
            return aqi_break_point_pm_2_5(c, b);
        default:
            return AQI_ERR_INVALID_ARG;
    }
}

int aqi_calc(const aqi_pollutant_type_t type, const float c, int *aqi)
{
    int err = AQI_FAIL;
    aqi_break_point_t break_point;

    if (aqi == NULL) {
        err = AQI_ERR_INVALID_ARG;
        goto fail;
    }
    if (type >= AQI_TYPE_MAX) {
        err = AQI_ERR_INVALID_ARG;
        goto fail;
    }
    if (c < 0) {
        err = AQI_ERR_INVALID_ARG;
        goto fail;
    }

    err = aqi_break_point(type, c, &break_point);
    if (err != AQI_OK) {
        goto fail;
    }

    if (break_point.c_hi - break_point.c_low == 0) {
        err = AQI_ERR_BUG;
        goto fail;
    }
    *aqi = ((break_point.i_hi - break_point.i_low) / (break_point.c_hi - break_point.c_low)) * (c - break_point.c_low) + break_point.i_low;

    if (*aqi < 0) {
        err = AQI_ERR_BUG;
        goto fail;
    }
    err = AQI_OK;
fail:
    return err;
}
