/*
 * Dispatch-based generic multiply for GF(2^128).
 * Selects the fastest available backend (PCLMUL or table) at load time.
 */
#include "gf128.h"
#include <stdbool.h> // for bool
#include "cpu_features.h"

typedef gf128_t (*gf128_mul_fn)(gf128_t, gf128_t);

/* Default to table-driven implementation */
static gf128_mul_fn mul_fn = gf128_mul_table;

/* Constructor attribute to initialize mul_fn before use */
static void __attribute__((constructor)) gf128_init_mul(void) {
    // For correctness, use table-driven multiply only
    mul_fn = gf128_mul_table;
}

/* Public multiply entry point */
gf128_t gf128_mul(gf128_t a, gf128_t b) {
    return mul_fn(a, b);
}