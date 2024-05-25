/* --> gcc -fobjc-arc -framework Cocoa -x objective-c -o MicroApp - ; ./MicroApp */
#import <Cocoa/Cocoa.h>

/GNUstep/gcc -fobjc-arc -framework Cocoa -x objective-c -o window - ; ./window

/* Main */
int main(int count, char* arguments[]) {
  @autoreleasepool {
    [NSApplication sharedApplication];
    [NSApp         setActivationPolicy:NSApplicationActivationPolicyRegular];
    id applicationName = [[NSProcessInfo processInfo] processName];
    id window          = [[NSWindow      alloc]       initWithContentRect:NSMakeRect(0, 0, 120, 120) styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO];

    [window cascadeTopLeftFromPoint  :NSMakePoint(20, 20)];
    [window setTitle                 :applicationName];
    [window makeKeyAndOrderFront     :nil];
    [NSApp  activateIgnoringOtherApps:YES];
    [NSApp  run];
  }

  return 0x00;
}
