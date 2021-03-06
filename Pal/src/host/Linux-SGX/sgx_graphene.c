/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* Copyright (C) 2014 Stony Brook University */

#include <pal.h>
#include <pal_error.h>
#include <atomic.h>

#include <linux/futex.h>
#include <errno.h>

#include "sgx_internal.h"

#define PRINTBUF_SIZE        256

struct printbuf {
    int idx;    // current buffer index
    int cnt;    // total bytes printed so far
    char buf[PRINTBUF_SIZE];
};

static int
fputch(void * f, int ch, struct printbuf * b)
{
    __UNUSED(f);

    b->buf[b->idx++] = ch;
    if (b->idx == PRINTBUF_SIZE - 1) {
        INLINE_SYSCALL(write, 3, 2, b->buf, b->idx);
        b->idx = 0;
    }
    b->cnt++;
    return 0;
}

static int
vprintf(const char * fmt, va_list ap)
{
    struct printbuf b;

    b.idx = 0;
    b.cnt = 0;
    vfprintfmt((void *) &fputch, NULL, &b, fmt, ap);
    INLINE_SYSCALL(write, 3, 2, b.buf, b.idx);

    return b.cnt;
}

int
pal_printf(const char * fmt, ...)
{
    va_list ap;
    int cnt;

    va_start(ap, fmt);
    cnt = vprintf(fmt, ap);
    va_end(ap);

    return cnt;
}
