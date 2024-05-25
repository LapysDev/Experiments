/* --> /GNUstep/bin/gcc hello-world.m -I /GNUstep/GNUstep/System/Library/Headers -L /GNUstep/GNUstep/System/Library/Libraries -fconstant-string-class=NSConstantString -lgnustep-base -lobjc -std=c99 */
#include <Foundation/Foundation.h>

/* ... */
void function() {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  NSLog(@"Hello, World!");
  [pool drain];
}

/* Main */
int main(int count, char* arguments[]) {
  function();
  return 0x00;
}
