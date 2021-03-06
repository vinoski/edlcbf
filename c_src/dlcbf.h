#ifndef EDLCBF_DLCBF_H
#define EDLCBF_DLCBF_H

/*
** -------------------------------------------------------------------
**
** dlcbf.h: d-left counting bloom filter interface
**
** Copyright (c) 2012 Basho Technologies, Inc. All Rights Reserved.
**
** This file is provided to you under the Apache License,
** Version 2.0 (the "License"); you may not use this file
** except in compliance with the License.  You may obtain
** a copy of the License at
**
**   http:**www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing,
** software distributed under the License is distributed on an
** "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
** KIND, either express or implied.  See the License for the
** specific language governing permissions and limitations
** under the License.
**
** -------------------------------------------------------------------
*/

#include <stdint.h>

#define BUCKET_HEIGHT 8
#define FINGERPRINT_BITS 13

typedef unsigned char Counter;
typedef uint16_t Fingerprint;

#define COUNTER_BITS (sizeof(uint16_t)*8 - FINGERPRINT_BITS)

typedef union {
    uint16_t all;
    struct {
        Counter     count:       COUNTER_BITS;
        Fingerprint fingerprint: FINGERPRINT_BITS;
    } f;
} DlcbfField;

typedef struct {
    uint16_t bucket_i;
    Fingerprint fingerprint;
} DlcbfBucketFingerprint;

typedef struct {
    DlcbfField fields[BUCKET_HEIGHT];
    unsigned char count;
} DlcbfBucket;

typedef struct {
    DlcbfBucket *buckets;
} DlcbfTable;

typedef struct {
    DlcbfTable* tables;
    const unsigned d;
    const unsigned b;
    const unsigned bits;
} Dlcbf;

typedef struct {
    DlcbfField* field;
} DlcbfLoc;

extern Dlcbf* dlcbf_init(unsigned d, unsigned b);
extern void dlcbf_add(const unsigned char* data, unsigned length, Dlcbf* dlcbf);
extern void dlcbf_delete(const unsigned char* data, unsigned length, Dlcbf* dlcbf);
extern int dlcbf_member(const unsigned char* data, unsigned length, Dlcbf* dlcbf);
extern void dlcbf_destroy(Dlcbf* dlcbf);

#endif
