// Run-time library interface                                  -*- C++ -*-
//
// This header defines the interface of the run-time library. It is not actually
// used anywhere because the compiler pass inserts calls to the library
// functions at the level of LLVM bitcode, but it serves as documentation of the
// intended interface.

#ifndef RUNTIME_H
#define RUNTIME_H

#include <z3.h>

extern "C" {
/*
 * Initialization
 */
void _sym_initialize(void);

/*
 * Construction of simple values
 */
Z3_ast _sym_build_integer(uint64_t value, uint8_t bits);
Z3_ast _sym_build_float(double value, int is_double);
uint32_t _sym_build_variable(const char *name, uint32_t value, uint8_t bits);
Z3_ast _sym_build_null_pointer();
Z3_ast _sym_build_true();
Z3_ast _sym_build_false();

/*
 * Arithmetic
 */
Z3_ast _sym_build_add(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_mul(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_signed_rem(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_shift_left(Z3_ast a, Z3_ast b);

Z3_ast _sym_build_fp_add(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_fp_sub(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_fp_mul(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_fp_div(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_fp_rem(Z3_ast a, Z3_ast b);

/*
 * Boolean operations
 */
Z3_ast _sym_build_neg(Z3_ast expr);
Z3_ast _sym_build_signed_less_than(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_signed_less_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_signed_greater_than(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_signed_greater_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_unsigned_less_than(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_unsigned_less_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_unsigned_greater_than(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_unsigned_greater_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_not_equal(Z3_ast a, Z3_ast b);

Z3_ast _sym_build_float_ordered_greater_than(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_float_ordered_greater_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_float_ordered_less_than(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_float_ordered_less_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_float_ordered_equal(Z3_ast a, Z3_ast b);
Z3_ast _sym_build_float_ordered_not_equal(Z3_ast a, Z3_ast b);

/*
 * Casts
 */
Z3_ast _sym_build_sext(Z3_ast expr, uint8_t bits);
Z3_ast _sym_build_zext(Z3_ast expr, uint8_t bits);
Z3_ast _sym_build_trunc(Z3_ast expr, uint8_t bits);
Z3_ast _sym_build_int_to_float(Z3_ast value, int is_double);
Z3_ast _sym_build_float_to_float(Z3_ast expr, int to_double);
Z3_ast _sym_build_bits_to_float(Z3_ast expr, int to_double);
Z3_ast _sym_build_float_to_bits(Z3_ast expr);

/*
 * Function-call helpers
 */
void _sym_set_parameter_expression(uint8_t index, Z3_ast expr);
void *_sym_get_parameter_expression(uint8_t index);
void _sym_set_return_expression(Z3_ast expr);
Z3_ast _sym_get_return_expression(void);

/*
 * Constraint handling
 */
Z3_ast _sym_push_path_constraint(Z3_ast constraint, int taken);

/*
 * Memory management
 */
void _sym_register_memory(uint8_t *addr, Z3_ast *shadow, size_t length);
void _sym_initialize_memory(uint8_t *addr, Z3_ast *shadow, size_t length);
Z3_ast _sym_read_memory(uint8_t *addr, size_t length, bool little_endian);
void _sym_write_memory(uint8_t *addr, size_t length, Z3_ast expr,
                       bool little_endian);
void _sym_memcpy(uint8_t *dest, uint8_t *src, size_t length);
}

#endif
