// { dg-options "-std=c++0x" }
static_assert(7 / 0, "X"); // { dg-error "non-constant condition" }
// { dg-warning "division by zero" "" { target *-*-* } 2 }
// { dg-error "7 / 0.. is not a constant expression" "" { target *-*-* } 2 }
