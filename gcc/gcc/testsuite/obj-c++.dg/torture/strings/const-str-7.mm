/* Test to make sure that the const objc strings are the same across
   scopes.  */
/* Developed by Andrew Pinski <pinskia@physics.uc.edu> */

/* { dg-do run } */
/* { dg-options "-fconstant-string-class=Foo" } */
/* { dg-options "-mno-constant-cfstrings -fconstant-string-class=Foo" { target *-*-darwin* } } */
/* { dg-additional-sources "../../../objc-obj-c++-shared/Object1.mm" } */

#include "../../../objc-obj-c++-shared/Object1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <objc/objc.h>

@interface Foo: Object {
  char *cString;
  unsigned int len;
}
- (char *)customString;
@end

#ifdef NEXT_OBJC_USE_NEW_INTERFACE
Class  _FooClassReference;
#else
struct objc_class _FooClassReference;
#endif

@implementation Foo : Object
- (char *)customString {
  return cString;
}
@end


int main () {
  Foo *string = @"bla";
  {
    Foo *string2 = @"bla";

    if(string != string2)
      abort();
    printf("Strings are being uniqued properly\n");
   }
  return 0;
}
