/* --> clang minimal.c -framework Cocoa -o minimal.app */
#include <objc/message.h>
#include <objc/runtime.h>
# include <Carbon/Carbon.h>

/* ... */
static id (&msg)         (id, SEL)                  = (id (&)(id, SEL))                  ::objc_msgSend;
static id (&msg_class)   (Class, SEL)               = (id (&)(Class, SEL))               ::objc_msgSend;
static id (&msg_classChr)(Class, SEL, char const[]) = (id (&)(Class, SEL, char const[])) ::objc_msgSend;
static id (&msg_id)      (id, SEL, id)              = (id (&)(id, SEL, id))              ::objc_msgSend;
static id (&msg_int)     (id, SEL, int)             = (id (&)(id, SEL, int))             ::objc_msgSend;
static id (&msg_ptr)     (id, SEL, void*)           = (id (&)(id, SEL, void*))           ::objc_msgSend;

// poor man's bindings!
enum NSApplicationActivationPolicy {
  NSApplicationActivationPolicyRegular   = 0x00,
  NSApplicationActivationPolicyAccessory = 0x01,
  NSApplicationActivationPolicyERROR     = 0x02
};

enum NSBackingStoreType {
  NSBackingStoreBuffered = 0x02
};

enum NSWindowStyleMask {
  NSWindowStyleMaskBorderless     = 0x00,
  NSWindowStyleMaskTitled         = 0x01,
  NSWindowStyleMaskClosable       = 0x02,
  NSWindowStyleMaskMiniaturizable = 0x04,
  NSWindowStyleMaskResizable      = 0x08
};

/* Main ->> Minimal Pure C code to create a window in Cocoa (Adapted to work on ARM64) --- CITE (Lapys) -> https://stackoverflow.com/a/59596600/834108 */
int main(int count, char* arguments[]) /* noexcept */ {
  // id application = [NSApplication sharedApplication];
  id     const application = ::msg_class(::objc_getClass("NSApplication"), ::sel_getUid("sharedApplication"));
  CGRect const bounds      = {{0, 0}, {600, 500}};

  // [application setActivationPolicy:NSApplicationActivationPolicyRegular];
  ::msg_int(application, ::sel_getUid("setActivationPolicy:"), ::NSApplicationActivationPolicyRegular);

  // id window = [[NSWindow alloc] initWithContentRect:bounds styleMask:NSWindowStyleMaskClosable|NSWindowStyleMaskResizable|NSWindowStyleMaskTitled backing:NSBackingStoreBuffered defer:NO];
  id const window = ((id (&)(id, SEL, CGRect, int, int, int)) ::objc_msgSend)(::msg_class(::objc_getClass("NSWindow"), ::sel_getUid("alloc")), ::sel_getUid("initWithContentRect:styleMask:backing:defer:"), bounds, ::NSWindowStyleMaskClosable | ::NSWindowStyleMaskResizable | ::NSWindowStyleMaskTitled, ::NSBackingStoreBuffered, false);
  ::msg_id(window, ::sel_getUid("setTitle:"), ::msg_classChr(::objc_getClass("NSString"), ::sel_getUid("stringWithUTF8String:"), "Hello, World!"));

  // [window makeKeyAndOrderFront:nil];
  ::msg_ptr(window, ::sel_getUid("makeKeyAndOrderFront:"), nil);

  // [application activateIgnoringOtherApps:YES];
  ::msg_int(application, ::sel_getUid("activateIgnoringOtherApps:"), true);
  ::msg    (application, ::sel_getUid("run"));
}
