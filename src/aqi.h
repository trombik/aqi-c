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

#if !defined(__AQI_H__)
#define __AQI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* error codes */
#define AQI_OK              (0)
#define AQI_FAIL            (1)
#define AQI_ERR_INVALID_ARG (2)
#define AQI_ERR_BUG         (3) // should not happen

/* type of the pollutant */
typedef enum {
    AQI_TYPE_PM_2_5 = 0,
    AQI_TYPE_PM_10_0,
    AQI_TYPE_MAX,
} aqi_pollutant_type_t;

int aqi_calc(const aqi_pollutant_type_t type, const float c, int *aqi);

#ifdef __cplusplus
}
#endif

#endif // __AQI_H__
