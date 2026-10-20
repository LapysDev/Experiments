/* rc /fofireworks-dark.res fireworks-dark.rc && cl /O2 /DUNICODE /D_UNICODE fireworks-dark.cpp fireworks-dark.res /link kernel32.lib user32.lib gdi32.lib magnification.lib dwmapi.lib d3d11.lib dxgi.lib dcomp.lib d3dcompiler.lib windowsapp.lib runtimeobject.lib shell32.lib && del /q fireworks-dark.obj fireworks-dark.res */
// Fireworks (Dark) v2.0.6: C++98, native Windows Graphics Capture + Magnification.
// Compile in a Visual Studio Developer Command Prompt (Windows SDK required).
// Windows 10 1903+ for WGC; no injection, service, or additional runtime files.

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define _WIN32_WINNT 0x0A00
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h> // Shell_NotifyIconW and the notification-area menu
#include <dwmapi.h>
#include <magnification.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_2.h>
#include <dcomp.h>
#include <roapi.h>
#include <winstring.h>
#include <windows.graphics.capture.h>
#include <windows.graphics.capture.interop.h>
#include <windows.graphics.directx.direct3d11.interop.h>
#include <cstdio>
#include <cmath>
#include <cwchar>
#include <cstring>
#include <vector>

namespace capture = ABI::Windows::Graphics::Capture;
namespace directx = ABI::Windows::Graphics::DirectX;

static wchar_t const* const WINDOW_CLASS = L"FireworksDarkOverlayHost";
static wchar_t const* const MAIN_CLASS = L"Fireworks_CS6_MainWindow";
static UINT const WM_RESCAN = WM_APP + 11;
static UINT const WM_GEOMETRY = WM_APP + 12;
static UINT const WM_TRAY_ICON = WM_APP + 13;
static UINT const WM_TRAY_COMMAND = WM_APP + 14;
static UINT const TRAY_ICON_ID = 1;
static UINT const TRAY_REFRESH = 3108;
static UINT const TRAY_BACKEND = 3107;
static UINT const TRAY_DIAGNOSTICS = 3106;
static UINT const TRAY_QUIT = 3110;
static int const HOTKEY_REFRESH = 1008;
static int const HOTKEY_DIAGNOSTICS = 1006;
static int const HOTKEY_BACKEND = 1007;
static int const HOTKEY_EXIT = 1010;

// RAII for native COM and WinRT ABI interfaces; intentionally C++98-only.
template<class Interface> class com_pointer {
  Interface* pointer;
  com_pointer(com_pointer const&);
  com_pointer& operator=(com_pointer const&);
public:
  com_pointer() : pointer(NULL) {}
  ~com_pointer() { reset(); }
  Interface* get() const { return pointer; }
  Interface** address() { reset(); return &pointer; }
  Interface* operator->() const { return pointer; }
  operator bool() const { return pointer != NULL; }
  void reset() { if (pointer != NULL) pointer->Release(); pointer = NULL; }
};

static ::LONG volatile exiting = 0;
static ::HWND coordinator = NULL;
static ::HWINEVENTHOOK windowEventHook = NULL;
static ::UINT taskbarCreatedMessage = 0;
static ::HICON notificationIcon = NULL;
static bool ownsNotificationIcon = false;
static bool notificationIconPresent = false;
static unsigned long globalRefreshes = 0;
static bool preferGpu = true;
static bool magnificationAvailable = false;
static unsigned long globalZCorrections = 0;
static unsigned long globalRegionUpdates = 0;
static unsigned long globalFilterUpdates = 0;
static unsigned long globalPopupEvents = 0;
static unsigned long globalGpuFallbacks = 0;
static unsigned long globalTransitions = 0;
static unsigned long globalMasksReused = 0;
static unsigned long globalCaptureFrames = 0;
static unsigned long globalPickerSkips = 0;
static unsigned long globalPopupCandidates = 0;
static unsigned long globalMagnifierFailures = 0;
static unsigned long globalMagnifierFilterFailures = 0;
static unsigned long globalScanCount = 0;
static unsigned long globalResizeEvents = 0;
static unsigned long globalSizeChanges = 0;
static unsigned long globalPoolRecreations = 0;
static unsigned long globalDroppedResizeFrames = 0;
static ::HRESULT lastGpuError = S_OK;

// The notification icon is owned by our hidden top-level coordinator window,
// not by a magnifier/D3D11 overlay. Resetting renderers never deletes it.
static void notification_add() {
  if (!coordinator) return;
  ::NOTIFYICONDATAW notification = {};
  notification.cbSize = sizeof(notification);
  notification.hWnd = coordinator;
  notification.uID = TRAY_ICON_ID;
  notification.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
  notification.uCallbackMessage = WM_TRAY_ICON;
  notification.hIcon = notificationIcon;
  wchar_t const tooltip[] = L"Fireworks (Dark)";
  ::CopyMemory(notification.szTip, tooltip, sizeof(tooltip));
  if (::Shell_NotifyIconW(notificationIconPresent ? NIM_MODIFY : NIM_ADD, &notification)) {
    notificationIconPresent = true;
    notification.uVersion = NOTIFYICON_VERSION_4;
    ::Shell_NotifyIconW(NIM_SETVERSION, &notification);
  }
}

static void notification_remove() {
  if (!coordinator || !notificationIconPresent) return;
  ::NOTIFYICONDATAW notification = {};
  notification.cbSize = sizeof(notification);
  notification.hWnd = coordinator;
  notification.uID = TRAY_ICON_ID;
  ::Shell_NotifyIconW(NIM_DELETE, &notification);
  notificationIconPresent = false;
}

static void notification_menu() {
  ::HMENU menu = ::CreatePopupMenu();
  if (!menu) return;
  ::AppendMenuW(menu, MF_STRING, TRAY_REFRESH, L"Refresh\tCtrl+Alt+F8");
  ::AppendMenuW(menu, MF_STRING, TRAY_BACKEND, L"Switch Renderer\tCtrl+Alt+F7");
  ::AppendMenuW(menu, MF_STRING, TRAY_DIAGNOSTICS, L"Save Diagnostics\tCtrl+Alt+F6");
  ::AppendMenuW(menu, MF_SEPARATOR, 0, NULL);
  ::AppendMenuW(menu, MF_STRING, TRAY_QUIT, L"Quit\tCtrl+Alt+F10 / Esc");
  ::POINT position = {};
  ::GetCursorPos(&position);
  // The foreground/WM_NULL pairing ensures the shell closes the menu after
  // clicking elsewhere. A menu action is queued, never run in this callback.
  ::SetForegroundWindow(coordinator);
  UINT command = ::TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON | TPM_NONOTIFY,
    position.x, position.y, 0, coordinator, NULL);
  if (command) ::PostMessageW(coordinator, WM_TRAY_COMMAND, command, 0);
  ::PostMessageW(coordinator, WM_NULL, 0, 0);
  ::DestroyMenu(menu);
}

static bool equal_rect(::RECT const& left, ::RECT const& right) {
  return left.left == right.left && left.top == right.top && left.right == right.right && left.bottom == right.bottom;
}
static int width_of(::RECT const& rect) { return rect.right - rect.left; }
static int height_of(::RECT const& rect) { return rect.bottom - rect.top; }
static bool nonempty(::RECT const& rect) { return rect.right > rect.left && rect.bottom > rect.top; }
static bool window_alive(::HWND window) { return window != NULL && ::IsWindow(window) != FALSE; }

// A WGC window capture normally uses the DWM-visible rectangle; Win32's
// GetWindowRect includes invisible resize borders (especially when maximized).
// Select the rectangle whose dimensions best match the actual capture surface.
// Magnification deliberately keeps GetWindowRect: its source is desktop pixels.
static ::RECT gpu_screen_bounds(::HWND window, int captureWidth, int captureHeight) {
  ::RECT windowBounds = {};
  if (!::GetWindowRect(window, &windowBounds)) return windowBounds;
  ::RECT visibleBounds = {};
  if (FAILED(::DwmGetWindowAttribute(window, DWMWA_EXTENDED_FRAME_BOUNDS,
      &visibleBounds, sizeof(visibleBounds))) || !nonempty(visibleBounds)) return windowBounds;
  if (captureWidth <= 0 || captureHeight <= 0) return visibleBounds;
  int windowWidthDifference = width_of(windowBounds) - captureWidth;
  int windowHeightDifference = height_of(windowBounds) - captureHeight;
  int visibleWidthDifference = width_of(visibleBounds) - captureWidth;
  int visibleHeightDifference = height_of(visibleBounds) - captureHeight;
  int windowDifference = (windowWidthDifference < 0 ? -windowWidthDifference : windowWidthDifference) +
                         (windowHeightDifference < 0 ? -windowHeightDifference : windowHeightDifference);
  int visibleDifference = (visibleWidthDifference < 0 ? -visibleWidthDifference : visibleWidthDifference) +
                          (visibleHeightDifference < 0 ? -visibleHeightDifference : visibleHeightDifference);
  return visibleDifference <= windowDifference ? visibleBounds : windowBounds;
}

static ::RECT screen_client(::HWND window) {
  ::RECT client = {};
  ::GetClientRect(window, &client);
  ::MapWindowPoints(window, NULL, reinterpret_cast< ::POINT*>(&client), 2);
  return client;
}

// Compare region contents, not HWNDs or timestamps. Paint/selection events do not
// touch the existing region unless its actual shape changes.
struct exclusion {
  ::RECT screen;
  bool round;
};

static bool same_exclusions(::std::vector<exclusion> const& first, ::std::vector<exclusion> const& second) {
  if (first.size() != second.size()) return false;
  for (::std::size_t index = 0; index < first.size(); ++index)
    if (first[index].round != second[index].round || !equal_rect(first[index].screen, second[index].screen)) return false;
  return true;
}

static void append_exclusion(::std::vector<exclusion>& masks, ::RECT const& rectangle, bool round) {
  if (!nonempty(rectangle)) return;
  exclusion item = { rectangle, round };
  masks.push_back(item);
}

// A fixed five-physical-pixel corner radius: unlike a superellipse scaled to
// the entire control, the straight sides remain straight near their centres.
static ::HRGN mask_region(::RECT const& rectangle, bool round) {
  if (!round) return ::CreateRectRgn(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
  int radius = 5;
  if (width_of(rectangle) / 2 < radius) radius = width_of(rectangle) / 2;
  if (height_of(rectangle) / 2 < radius) radius = height_of(rectangle) / 2;
  return ::CreateRoundRectRgn(rectangle.left, rectangle.top, rectangle.right, rectangle.bottom,
                              radius * 2, radius * 2);
}

// Fireworks' colour-picker is a separately owned dialog, not a simple swatch.
// Distinguish it from generic dialogs using its large Afx colour-grid child.
// Dimensions are compared with the popup itself, never with the display.
struct picker_probe {
  ::RECT popupBounds;
  bool found;
};

static BOOL CALLBACK inspect_picker_child(::HWND child, LPARAM parameter) {
  picker_probe* probe = reinterpret_cast<picker_probe*>(parameter);
  if (probe->found || !::IsWindowVisible(child)) return !probe->found;
  wchar_t className[128] = {};
  ::RECT rectangle = {};
  if (::GetClassNameW(child, className, 128) &&
      ::wcsncmp(className, L"Afx:00400000:b:00000000:", 24) == 0 &&
      ::GetWindowRect(child, &rectangle) && nonempty(rectangle) &&
      width_of(rectangle) * 3 >= width_of(probe->popupBounds) * 2 &&
      height_of(rectangle) * 3 >= height_of(probe->popupBounds)) {
    probe->found = true;
    return FALSE;
  }
  return TRUE;
}

static bool is_color_picker(::HWND window) {
  if (!window_alive(window) || !::IsWindowVisible(window)) return false;
  wchar_t className[128] = {};
  if (!::GetClassNameW(window, className, 128) || ::wcscmp(className, L"#32770") != 0) return false;
  ::HWND owner = ::GetWindow(window, GW_OWNER);
  if (!owner || !::IsWindow(owner)) return false;
  wchar_t ownerClass[128] = {};
  owner = ::GetAncestor(owner, GA_ROOTOWNER);
  if (!::GetClassNameW(owner, ownerClass, 128) ||
      ::wcscmp(ownerClass, MAIN_CLASS) != 0) return false;
  picker_probe probe = {};
  if (!::GetWindowRect(window, &probe.popupBounds) || !nonempty(probe.popupBounds)) return false;
  // Fireworks' floating colour picker is approximately square; a broad Afx
  // child alone must not cause an unrelated Orange Commands dialog to be skipped.
  if (width_of(probe.popupBounds) < 250 || height_of(probe.popupBounds) < 250 ||
      width_of(probe.popupBounds) * 10 < height_of(probe.popupBounds) * 7 ||
      height_of(probe.popupBounds) * 10 < width_of(probe.popupBounds) * 7) return false;
  ::EnumChildWindows(window, inspect_picker_child, reinterpret_cast<LPARAM>(&probe));
  return probe.found;
}

struct picker_mask_search {
  ::HWND editor;
  ::std::vector<exclusion>* masks;
};

static BOOL CALLBACK collect_picker_mask(::HWND popup, LPARAM parameter) {
  picker_mask_search* search = reinterpret_cast<picker_mask_search*>(parameter);
  if (!is_color_picker(popup)) return TRUE;
  ::HWND owner = ::GetWindow(popup, GW_OWNER);
  if (!owner || ::GetAncestor(owner, GA_ROOTOWNER) != search->editor) return TRUE;
  ::RECT rectangle = {};
  if (::GetWindowRect(popup, &rectangle))
    append_exclusion(*search->masks, rectangle, false);
  return TRUE;
}

struct mask_enumeration {
  ::std::vector<exclusion>* exclusions;
};

static BOOL CALLBACK collect_child(::HWND child, LPARAM parameter) {
  mask_enumeration* scan = reinterpret_cast<mask_enumeration*>(parameter);
  if (!::IsWindowVisible(child)) return TRUE;
  int identifier = ::GetDlgCtrlID(child);
  wchar_t className[100] = {};
  ::GetClassNameW(child, className, 100);
  ::RECT bounds = {};
  if (!::GetWindowRect(child, &bounds) || !nonempty(bounds)) return TRUE;

  if (identifier == 59649 && ::wcscmp(className, L"Fireworks_view_class") == 0) {
    // The canvas client excludes native scrollbars, so those remain darkened.
    append_exclusion(*scan->exclusions, screen_client(child), false);
  } else if (identifier >= 40000 && identifier <= 40023 && ::wcscmp(className, L"Button") == 0) {
    // Centre tool icons while making the vertical and horizontal gaps comparable.
    int horizontalInset = width_of(bounds) / 18;
    int verticalInset = height_of(bounds) / 11;
    bounds.left += horizontalInset;
    bounds.right -= horizontalInset;
    bounds.top += verticalInset;
    bounds.bottom -= verticalInset;
    append_exclusion(*scan->exclusions, bounds, true);
  } else if ((identifier >= 6608 && identifier <= 6633) ||
             (::wcsncmp(className, L"Afx:00400000:b", 14) == 0 && width_of(bounds) < 125 && height_of(bounds) < 125)) {
    append_exclusion(*scan->exclusions, bounds, true);
  } else if (identifier == 3983 && ::wcscmp(className, L"ListBox") == 0) {
    // Fireworks exposes owner-drawn rows in logical units even when its ListBox
    // is DPI-virtualised. Calibrate against the list's current physical width.
    ::RECT physicalClient = screen_client(child);
    ::RECT logicalClient = {};
    ::GetClientRect(child, &logicalClient);
    if (!nonempty(physicalClient)) return TRUE;
    ::DWORD_PTR countResult = 0;
    ::DWORD_PTR firstResult = 0;
    if (!::SendMessageTimeoutW(child, LB_GETCOUNT, 0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 40, &countResult)) return TRUE;
    if (!::SendMessageTimeoutW(child, LB_GETTOPINDEX, 0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 40, &firstResult)) return TRUE;
    int count = static_cast<int>(countResult);
    int first = static_cast<int>(firstResult);
    if (count < 0 || count > 200000 || first < 0 || first >= count) return TRUE;
    double scale = 1.0;
    // Typical screenshots: physical width ~747, logical row width ~332 -> 2.25.
    // Do not use desktop coordinates or a fixed user-specific DPI multiplier.
    ::RECT firstRow = {};
    ::DWORD_PTR rowResult = 0;
    if (::SendMessageTimeoutW(child, LB_GETITEMRECT, static_cast<WPARAM>(first),
                              reinterpret_cast<LPARAM>(&firstRow), SMTO_ABORTIFHUNG | SMTO_BLOCK, 40, &rowResult) &&
        static_cast<LRESULT>(rowResult) != LB_ERR && width_of(firstRow) > 0)
      scale = static_cast<double>(width_of(physicalClient)) / width_of(firstRow);
    if (scale < 0.5 || scale > 8.0) scale = 1.0;
    for (int index = first; index < count && index < first + 120; ++index) {
      ::RECT logicalRow = {};
      ::DWORD_PTR result = 0;
      if (!::SendMessageTimeoutW(child, LB_GETITEMRECT, static_cast<WPARAM>(index),
                                  reinterpret_cast<LPARAM>(&logicalRow), SMTO_ABORTIFHUNG | SMTO_BLOCK, 40, &result)) break;
      if (static_cast<LRESULT>(result) == LB_ERR) break;
      ::RECT row = physicalClient;
      row.top = physicalClient.top + static_cast<int>(logicalRow.top * scale + 0.5);
      row.bottom = physicalClient.top + static_cast<int>(logicalRow.bottom * scale + 0.5);
      if (row.top >= physicalClient.bottom) break;
      if (row.bottom > physicalClient.bottom) row.bottom = physicalClient.bottom;
      if (row.top < physicalClient.top) row.top = physicalClient.top;
      append_exclusion(*scan->exclusions, row, true);
    }
  }
  return TRUE;
}

static void read_exclusions(::HWND target, bool mainEditor, ::std::vector<exclusion>& masks) {
  masks.clear();
  if (!mainEditor) return;
  mask_enumeration scan = { &masks };
  ::EnumChildWindows(target, collect_child, reinterpret_cast<LPARAM>(&scan));
  // A picker can be above or within the main window's GPU capture. Never
  // filter its visible pixels, even if the editor overlay overlaps it.
  picker_mask_search search = { target, &masks };
  ::EnumWindows(collect_picker_mask, reinterpret_cast<LPARAM>(&search));
}

struct graphic_device {
  com_pointer<ID3D11Device> device;
  com_pointer<ID3D11DeviceContext> context;
  com_pointer<IDXGIDevice> dxgi;
  com_pointer<IDXGIFactory2> factory;
  com_pointer<IDCompositionDevice> composition;
  com_pointer<ID3D11VertexShader> vertexShader;
  com_pointer<ID3D11PixelShader> pixelShader;
  com_pointer<ID3D11SamplerState> sampler;
  com_pointer<directx::Direct3D11::IDirect3DDevice> captureDevice;
  bool ready;
  graphic_device() : ready(false) {}
};

static graphic_device gpu;

static char const* const VERTEX_SHADER =
  "struct VSOutput { float4 pos : SV_POSITION; float2 uv : TEXCOORD0; };"
  "VSOutput main(uint id : SV_VertexID) {"
  "  VSOutput output;"
  "  output.uv = float2((id << 1) & 2, id & 2);"
  "  output.pos = float4(output.uv.x * 2 - 1, 1 - output.uv.y * 2, 0, 1);"
  "  return output;"
  "}";

static char const* const PIXEL_SHADER =
  "Texture2D inputImage : register(t0);"
  "SamplerState inputSampler : register(s0);"
  "float4 main(float4 pos : SV_POSITION, float2 uv : TEXCOORD0) : SV_TARGET {"
  "  float4 pixel = inputImage.Sample(inputSampler, uv);"
  "  if (pixel.a <= 0.0001) return float4(0,0,0,0);"
  "  float3 original = saturate(pixel.rgb / pixel.a);"
  "  float luminance = dot(original, float3(0.299, 0.587, 0.114));"
  "  float darkness = saturate(0.82 - 0.72 * luminance);"
  "  return float4(float3(darkness, darkness, darkness) * pixel.a, pixel.a);"
  "}";

static HRESULT initialize_gpu() {
  UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
  D3D_FEATURE_LEVEL const levels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
  D3D_FEATURE_LEVEL supported = D3D_FEATURE_LEVEL_11_0;
  HRESULT result = ::D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, levels, 4,
                                        D3D11_SDK_VERSION, gpu.device.address(), &supported, gpu.context.address());
  if (result == E_INVALIDARG) result = ::D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags,
    levels + 1, 3, D3D11_SDK_VERSION, gpu.device.address(), &supported, gpu.context.address());
  if (FAILED(result)) return result;
  result = gpu.device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(gpu.dxgi.address()));
  if (FAILED(result)) return result;
  com_pointer<IDXGIAdapter> adapter;
  result = gpu.dxgi->GetAdapter(adapter.address());
  if (FAILED(result)) return result;
  result = adapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(gpu.factory.address()));
  if (FAILED(result)) return result;
  result = ::DCompositionCreateDevice(gpu.dxgi.get(), __uuidof(IDCompositionDevice),
                                       reinterpret_cast<void**>(gpu.composition.address()));
  if (FAILED(result)) return result;
  result = ::CreateDirect3D11DeviceFromDXGIDevice(gpu.dxgi.get(),
    reinterpret_cast<IInspectable**>(gpu.captureDevice.address()));
  if (FAILED(result)) return result;
  com_pointer<ID3DBlob> compiled;
  com_pointer<ID3DBlob> errors;
  result = ::D3DCompile(VERTEX_SHADER, ::std::strlen(VERTEX_SHADER), "vertex", NULL, NULL, "main", "vs_4_0", 0, 0,
                        compiled.address(), errors.address());
  if (FAILED(result)) return result;
  result = gpu.device->CreateVertexShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, gpu.vertexShader.address());
  if (FAILED(result)) return result;
  compiled.reset();
  errors.reset();
  result = ::D3DCompile(PIXEL_SHADER, ::std::strlen(PIXEL_SHADER), "pixel", NULL, NULL, "main", "ps_4_0", 0, 0,
                        compiled.address(), errors.address());
  if (FAILED(result)) return result;
  result = gpu.device->CreatePixelShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, gpu.pixelShader.address());
  if (FAILED(result)) return result;
  D3D11_SAMPLER_DESC samplerDescription = {};
  samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
  samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
  samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
  samplerDescription.MaxLOD = D3D11_FLOAT32_MAX;
  result = gpu.device->CreateSamplerState(&samplerDescription, gpu.sampler.address());
  if (SUCCEEDED(result)) gpu.ready = true;
  return result;
}

static HRESULT activation_factory(wchar_t const* className, ::IID const& identifier, void** object) {
  *object = NULL;
  ::HSTRING string = NULL;
  HRESULT result = ::WindowsCreateString(className, static_cast<UINT32>(::wcslen(className)), &string);
  if (SUCCEEDED(result)) result = ::RoGetActivationFactory(string, identifier, object);
  ::WindowsDeleteString(string);
  return result;
}

struct overlay {
  ::HWND source;
  ::HWND gpuHost;
  ::HWND magHost;
  ::HWND magnifier;
  ::RECT previousBounds;
  ::RECT gpuBounds;
  ::RECT appliedGpuBounds;
  ::RECT appliedMagBounds;
  bool mainEditor;
  bool visible;
  bool gpuStarted;
  bool gpuFailed;
  bool gpuHasFrame;
  bool gpuAwaitingResizeFrame;
  bool magnifierConfigured;
  char const* magnifierFailureStage;
  ::DWORD magnifierLastError;
  unsigned long magnifierSourceRefreshes;
  bool hasAppliedMask;
  ::DWORD startTick;
  ::DWORD lastGoodFrame;
  unsigned long maskChanges;
  unsigned long maskHits;
  unsigned long gpuFrames;
  unsigned long zCorrections;
  unsigned long gpuFailures;
  ::HRESULT gpuError;
  ::std::vector<exclusion> appliedMasks;
  com_pointer<capture::IGraphicsCaptureItem> item;
  com_pointer<capture::IDirect3D11CaptureFramePool> pool;
  com_pointer<capture::IGraphicsCaptureSession> session;
  com_pointer<IDCompositionTarget> compositionTarget;
  com_pointer<IDCompositionVisual> compositionVisual;
  com_pointer<IDXGISwapChain1> swapChain;
  com_pointer<ID3D11RenderTargetView> renderTarget;
  com_pointer<ID3D11Texture2D> imageTexture;
  com_pointer<ID3D11ShaderResourceView> imageView;
  int frameWidth;
  int frameHeight;
  int swapWidth;
  int swapHeight;
  int poolWidth;
  int poolHeight;

  overlay(::HWND window, bool editor) : source(window), gpuHost(NULL), magHost(NULL), magnifier(NULL),
    mainEditor(editor), visible(false), gpuStarted(false), gpuFailed(false), gpuHasFrame(false), gpuAwaitingResizeFrame(false),
    magnifierConfigured(false), magnifierFailureStage("none"), magnifierLastError(0),
    magnifierSourceRefreshes(0), hasAppliedMask(false), startTick(::GetTickCount()), lastGoodFrame(0),
    maskChanges(0), maskHits(0), gpuFrames(0), zCorrections(0), gpuFailures(0), gpuError(S_OK),
    frameWidth(0), frameHeight(0), swapWidth(0), swapHeight(0), poolWidth(0), poolHeight(0) {
    ::SetRectEmpty(&previousBounds);
    ::SetRectEmpty(&gpuBounds);
    ::SetRectEmpty(&appliedGpuBounds);
    ::SetRectEmpty(&appliedMagBounds);
  }
  ~overlay() {
    // Hide the outgoing host before releasing the compositor's visual tree.
    // This destructor runs on explicit backend switches and window removal.
    if (gpuHost) ::ShowWindow(gpuHost, SW_HIDE);
    if (magHost) ::ShowWindow(magHost, SW_HIDE);
    // A session's IClosable.Close releases WGC's OS capture resources promptly.
    if (session) {
      com_pointer<ABI::Windows::Foundation::IClosable> closeSession;
      if (SUCCEEDED(session->QueryInterface(__uuidof(ABI::Windows::Foundation::IClosable),
                     reinterpret_cast<void**>(closeSession.address())))) closeSession->Close();
    }
    if (pool) {
      com_pointer<ABI::Windows::Foundation::IClosable> closePool;
      if (SUCCEEDED(pool->QueryInterface(__uuidof(ABI::Windows::Foundation::IClosable),
                     reinterpret_cast<void**>(closePool.address())))) closePool->Close();
    }
    session.reset();
    pool.reset();
    item.reset();
    // Commit AND wait for the outgoing DirectComposition root to detach.
    // Commit alone is asynchronous and can leave a stale GPU frame visible.
    if (compositionTarget) {
      compositionTarget->SetRoot(NULL);
      if (gpu.composition && SUCCEEDED(gpu.composition->Commit()))
        gpu.composition->WaitForCommitCompletion();
    }
    compositionVisual.reset();
    compositionTarget.reset();
    renderTarget.reset();
    imageView.reset();
    imageTexture.reset();
    swapChain.reset();
    if (gpuHost) ::DestroyWindow(gpuHost);
    if (magHost) ::DestroyWindow(magHost);
  }
};

static ::std::vector<overlay*> overlays;

static bool is_fireworks(::HWND window) {
  wchar_t className[128] = {};
  return window_alive(window) && ::GetClassNameW(window, className, 128) && ::wcscmp(className, MAIN_CLASS) == 0;
}

static overlay* lookup_overlay(::HWND source) {
  for (::std::size_t index = 0; index < overlays.size(); ++index)
    if (overlays[index]->source == source) return overlays[index];
  return NULL;
}

static BOOL CALLBACK list_windows(::HWND window, LPARAM argument) {
  ::std::vector< ::HWND>* candidates = reinterpret_cast< ::std::vector< ::HWND>*>(argument);
  if (!::IsWindowVisible(window) || ::IsIconic(window)) return TRUE;
  ::DWORD processId = 0;
  ::GetWindowThreadProcessId(window, &processId);
  if (processId == ::GetCurrentProcessId()) return TRUE;
  ::RECT rect = {};
  if (!::GetWindowRect(window, &rect) || !nonempty(rect)) return TRUE;
  BOOL cloaked = FALSE;
  if (SUCCEEDED(::DwmGetWindowAttribute(window, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked) return TRUE;
  if (is_fireworks(window)) candidates->push_back(window);
  return TRUE;
}

// Enumerate the entire Fireworks process's visible top-level window group.
// Third-party command plugins are not obligated to use OWL.*, #32768 or #32770,
// and some do not set GW_OWNER. Filtering by those class names misses dialogs.
// The explicit picker exception remains, as preserving selectable RGB is vital.
static BOOL CALLBACK list_popups(::HWND window, LPARAM argument) {
  ::std::vector< ::HWND>* candidates = reinterpret_cast< ::std::vector< ::HWND>*>(argument);
  if (!::IsWindowVisible(window) || ::IsIconic(window) || is_fireworks(window)) return TRUE;
  wchar_t className[128] = {};
  ::GetClassNameW(window, className, 128);
  if (::wcscmp(className, WINDOW_CLASS) == 0 ||
      ::wcscmp(className, L"tooltips_class32") == 0 ||
      ::wcscmp(className, L"IME") == 0 ||
      ::wcscmp(className, L"MSCTFIME UI") == 0) return TRUE;
  ::RECT rect = {};
  if (!::GetWindowRect(window, &rect) || !nonempty(rect) || width_of(rect) < 20 || height_of(rect) < 20) return TRUE;
  BOOL cloaked = FALSE;
  if (SUCCEEDED(::DwmGetWindowAttribute(window, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked) return TRUE;
  ::DWORD processId = 0;
  ::GetWindowThreadProcessId(window, &processId);
  ::HWND owner = ::GetWindow(window, GW_OWNER);
  ::HWND rootOwner = owner ? ::GetAncestor(owner, GA_ROOTOWNER) : NULL;
  bool belongsToFireworks = is_fireworks(rootOwner);
  for (::std::size_t index = 0; index < candidates->size() && !belongsToFireworks; ++index) {
    if (!is_fireworks((*candidates)[index])) continue;
    ::DWORD editorProcess = 0;
    ::GetWindowThreadProcessId((*candidates)[index], &editorProcess);
    belongsToFireworks = editorProcess != 0 && processId == editorProcess;
  }
  if (!belongsToFireworks) return TRUE;
  ++globalPopupCandidates;
  if (is_color_picker(window)) {
    ++globalPickerSkips;
    return TRUE;
  }
  candidates->push_back(window);
  return TRUE;
}

static bool layered_window(::HWND window) {
  return (::GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_LAYERED) != 0;
}

// Magnifier controls REQUIRE a layered host. An ordinary transparent WS_POPUP
// can receive a valid magnifier HWND yet display black or stale desktop pixels.
// See Microsoft's Magnification API overview, "Creating the Magnifier Control".
static bool fail_magnifier(overlay& item, char const* stage) {
  item.magnifierFailureStage = stage;
  item.magnifierLastError = ::GetLastError();
  ++globalMagnifierFailures;
  if (item.magHost) ::DestroyWindow(item.magHost);
  item.magHost = NULL;
  item.magnifier = NULL;
  item.magnifierConfigured = false;
  return false;
}

static bool create_mag_host(overlay& item) {
  if (!magnificationAvailable) return false;
  ::RECT bounds = {};
  if (!::GetWindowRect(item.source, &bounds) || !nonempty(bounds)) return fail_magnifier(item, "GetWindowRect");
  item.magHost = ::CreateWindowExW(WS_EX_NOACTIVATE | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED,
    WINDOW_CLASS, L"", WS_POPUP, bounds.left, bounds.top, width_of(bounds), height_of(bounds),
    item.source, NULL, ::GetModuleHandleW(NULL), NULL);
  if (!item.magHost) return fail_magnifier(item, "CreateWindowExW");
  if (!::SetLayeredWindowAttributes(item.magHost, 0, 255, LWA_ALPHA))
    return fail_magnifier(item, "SetLayeredWindowAttributes");
  item.magnifier = ::CreateWindowExW(0, WC_MAGNIFIER, L"", WS_CHILD | WS_VISIBLE,
    0, 0, width_of(bounds), height_of(bounds), item.magHost, NULL, ::GetModuleHandleW(NULL), NULL);
  if (!item.magnifier) return fail_magnifier(item, "CreateMagnifierControl");
  ::MAGTRANSFORM transform = {};
  transform.v[0][0] = transform.v[1][1] = transform.v[2][2] = 1.0f;
  if (!::MagSetWindowTransform(item.magnifier, &transform))
    return fail_magnifier(item, "MagSetWindowTransform");
  ::MAGCOLOREFFECT effect = {{
    -0.21528f, -0.21528f, -0.21528f, 0.0f, 0.0f,
    -0.42264f, -0.42264f, -0.42264f, 0.0f, 0.0f,
    -0.08208f, -0.08208f, -0.08208f, 0.0f, 0.0f,
     0.0f,      0.0f,      0.0f,     1.0f, 0.0f,
     0.82f,     0.82f,     0.82f,    0.0f, 1.0f
  }};
  if (!::MagSetColorEffect(item.magnifier, &effect))
    return fail_magnifier(item, "MagSetColorEffect");
  if (!::MagSetWindowSource(item.magnifier, bounds))
    return fail_magnifier(item, "MagSetWindowSource");
  item.magnifierConfigured = true;
  item.magnifierFailureStage = "none";
  ++item.magnifierSourceRefreshes;
  return true;
}

// Only one D3D11 device and shader pair are used by every editor, menu and dialog.
static HRESULT create_gpu_host(overlay& item) {
  if (!gpu.ready) return E_FAIL;
  ::RECT bounds = {};
  if (!::GetWindowRect(item.source, &bounds) || !nonempty(bounds)) return E_INVALIDARG;
  // HTTRANSPARENT only passes clicks to windows on the SAME thread. Fireworks
  // is a different process, so use the documented layered + transparent pair.
  // DirectComposition supports a layered HWND as a composition target. The
  // no-redirection-bitmap style is deliberately not combined with WS_EX_LAYERED.
  item.gpuHost = ::CreateWindowExW(WS_EX_NOACTIVATE | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED,
    WINDOW_CLASS, L"", WS_POPUP, bounds.left, bounds.top, width_of(bounds), height_of(bounds),
    item.source, NULL, ::GetModuleHandleW(NULL), NULL);
  if (!item.gpuHost) return HRESULT_FROM_WIN32(::GetLastError());
  if (!::SetLayeredWindowAttributes(item.gpuHost, 0, 255, LWA_ALPHA))
    return HRESULT_FROM_WIN32(::GetLastError());

  com_pointer<IGraphicsCaptureItemInterop> interop;
  HRESULT result = activation_factory(L"Windows.Graphics.Capture.GraphicsCaptureItem",
    __uuidof(IGraphicsCaptureItemInterop), reinterpret_cast<void**>(interop.address()));
  if (FAILED(result)) return result;
  result = interop->CreateForWindow(item.source, __uuidof(capture::IGraphicsCaptureItem),
                                     reinterpret_cast<void**>(item.item.address()));
  if (FAILED(result)) return result;
  ABI::Windows::Graphics::SizeInt32 size = {};
  result = item.item->get_Size(&size);
  if (FAILED(result)) return result;
  if (size.Width <= 0 || size.Height <= 0 || size.Width > 16000 || size.Height > 16000) return E_INVALIDARG;
  item.poolWidth = size.Width;
  item.poolHeight = size.Height;
  // Align DComp's HWND with WGC's actual captured area before attachment.
  // The Win32 resize border must never stretch the captured image.
  item.gpuBounds = gpu_screen_bounds(item.source, size.Width, size.Height);
  if (!::SetWindowPos(item.gpuHost, NULL, item.gpuBounds.left, item.gpuBounds.top,
      width_of(item.gpuBounds), height_of(item.gpuBounds),
      SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER)) return HRESULT_FROM_WIN32(::GetLastError());

  com_pointer<capture::IDirect3D11CaptureFramePoolStatics2> factory;
  result = activation_factory(L"Windows.Graphics.Capture.Direct3D11CaptureFramePool",
    __uuidof(capture::IDirect3D11CaptureFramePoolStatics2), reinterpret_cast<void**>(factory.address()));
  if (FAILED(result)) return result;
  result = factory->CreateFreeThreaded(gpu.captureDevice.get(),
    directx::DirectXPixelFormat::DirectXPixelFormat_B8G8R8A8UIntNormalized, 2,
    size, item.pool.address());
  if (FAILED(result)) return result;
  result = item.pool->CreateCaptureSession(item.item.get(), item.session.address());
  if (FAILED(result)) return result;

  // Do not capture the system cursor into the image if the OS supports this.
  com_pointer<capture::IGraphicsCaptureSession2> session2;
  if (SUCCEEDED(item.session->QueryInterface(__uuidof(capture::IGraphicsCaptureSession2),
       reinterpret_cast<void**>(session2.address())))) session2->put_IsCursorCaptureEnabled(false);

  DXGI_SWAP_CHAIN_DESC1 swapDescription = {};
  swapDescription.Width = static_cast<UINT>(size.Width);
  swapDescription.Height = static_cast<UINT>(size.Height);
  swapDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
  swapDescription.BufferCount = 2;
  swapDescription.SampleDesc.Count = 1;
  swapDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
  swapDescription.Scaling = DXGI_SCALING_STRETCH;
  swapDescription.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
  swapDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  result = gpu.factory->CreateSwapChainForComposition(gpu.device.get(), &swapDescription, NULL, item.swapChain.address());
  if (FAILED(result)) return result;
  item.swapWidth = size.Width;
  item.swapHeight = size.Height;
  result = gpu.composition->CreateTargetForHwnd(item.gpuHost, TRUE, item.compositionTarget.address());
  if (FAILED(result)) return result;
  result = gpu.composition->CreateVisual(item.compositionVisual.address());
  if (FAILED(result)) return result;
  result = item.compositionVisual->SetContent(item.swapChain.get());
  if (FAILED(result)) return result;
  result = item.compositionTarget->SetRoot(item.compositionVisual.get());
  if (FAILED(result)) return result;
  result = gpu.composition->Commit();
  if (FAILED(result)) return result;
  result = item.session->StartCapture();
  if (SUCCEEDED(result)) item.gpuStarted = true;
  return result;
}

static HRESULT resize_swapchain(overlay& item, int width, int height) {
  if (width <= 0 || height <= 0) return E_INVALIDARG;
  if (item.frameWidth == width && item.frameHeight == height && item.renderTarget) return S_OK;
  gpu.context->OMSetRenderTargets(0, NULL, NULL);
  item.renderTarget.reset();
  HRESULT result = S_OK;
  // Track the swap chain's actual allocation independently of the frame pool.
  // The pool can be recreated before the first frame, while the swap chain
  // still has its original allocation. Comparing against poolWidth is wrong.
  if (width != item.swapWidth || height != item.swapHeight) {
    result = item.swapChain->ResizeBuffers(0, static_cast<UINT>(width), static_cast<UINT>(height),
                                           DXGI_FORMAT_UNKNOWN, 0);
    if (FAILED(result)) return result;
    item.swapWidth = width;
    item.swapHeight = height;
  }
  com_pointer<ID3D11Texture2D> backbuffer;
  result = item.swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backbuffer.address()));
  if (SUCCEEDED(result)) result = gpu.device->CreateRenderTargetView(backbuffer.get(), NULL, item.renderTarget.address());
  if (SUCCEEDED(result)) {
    item.frameWidth = width;
    item.frameHeight = height;
  }
  return result;
}

// WGC frame textures can be larger than ContentSize during a resize. Always
// copy/render just the current content, never undefined/stale buffer margins.
static HRESULT render_frame(overlay& item, ID3D11Texture2D* source, int contentWidth, int contentHeight) {
  D3D11_TEXTURE2D_DESC description = {};
  source->GetDesc(&description);
  if (contentWidth <= 0 || contentHeight <= 0 ||
      description.Width < static_cast<UINT>(contentWidth) ||
      description.Height < static_cast<UINT>(contentHeight)) return E_INVALIDARG;
  HRESULT result = resize_swapchain(item, contentWidth, contentHeight);
  if (FAILED(result)) return result;
  if (!item.imageTexture) {
    D3D11_TEXTURE2D_DESC copyDescription = description;
    copyDescription.Width = static_cast<UINT>(contentWidth);
    copyDescription.Height = static_cast<UINT>(contentHeight);
    copyDescription.Usage = D3D11_USAGE_DEFAULT;
    copyDescription.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    copyDescription.CPUAccessFlags = 0;
    copyDescription.MiscFlags = 0;
    copyDescription.MipLevels = 1;
    copyDescription.ArraySize = 1;
    copyDescription.SampleDesc.Count = 1;
    result = gpu.device->CreateTexture2D(&copyDescription, NULL, item.imageTexture.address());
    if (FAILED(result)) return result;
    result = gpu.device->CreateShaderResourceView(item.imageTexture.get(), NULL, item.imageView.address());
    if (FAILED(result)) return result;
  } else {
    D3D11_TEXTURE2D_DESC oldDescription = {};
    item.imageTexture->GetDesc(&oldDescription);
    if (oldDescription.Width != static_cast<UINT>(contentWidth) ||
        oldDescription.Height != static_cast<UINT>(contentHeight)) {
      item.imageView.reset();
      item.imageTexture.reset();
      return render_frame(item, source, contentWidth, contentHeight);
    }
  }

  D3D11_BOX contentRegion = { 0, 0, 0, static_cast<UINT>(contentWidth), static_cast<UINT>(contentHeight), 1 };
  gpu.context->CopySubresourceRegion(item.imageTexture.get(), 0, 0, 0, 0, source, 0, &contentRegion);
  ID3D11RenderTargetView* renderTarget = item.renderTarget.get();
  gpu.context->OMSetRenderTargets(1, &renderTarget, NULL);
  D3D11_VIEWPORT viewport = {};
  viewport.Width = static_cast<FLOAT>(contentWidth);
  viewport.Height = static_cast<FLOAT>(contentHeight);
  viewport.MaxDepth = 1.0f;
  gpu.context->RSSetViewports(1, &viewport);
  gpu.context->IASetInputLayout(NULL);
  gpu.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  gpu.context->VSSetShader(gpu.vertexShader.get(), NULL, 0);
  gpu.context->PSSetShader(gpu.pixelShader.get(), NULL, 0);
  ID3D11ShaderResourceView* shaderImage = item.imageView.get();
  ID3D11SamplerState* sampler = gpu.sampler.get();
  gpu.context->PSSetShaderResources(0, 1, &shaderImage);
  gpu.context->PSSetSamplers(0, 1, &sampler);
  gpu.context->Draw(3, 0);
  shaderImage = NULL;
  gpu.context->PSSetShaderResources(0, 1, &shaderImage);
  gpu.context->OMSetRenderTargets(0, NULL, NULL);
  return item.swapChain->Present(1, 0);
}

// Recreating the pool invalidates its outstanding capture frames. Release the
// current frame before Recreate and wait for the new pool's first valid frame.
static HRESULT recreate_capture_pool(overlay& item, int width, int height) {
  if (width <= 0 || height <= 0 || width > 16000 || height > 16000) return E_INVALIDARG;
  ABI::Windows::Graphics::SizeInt32 size = {};
  size.Width = width;
  size.Height = height;
  HRESULT result = item.pool->Recreate(gpu.captureDevice.get(),
    directx::DirectXPixelFormat::DirectXPixelFormat_B8G8R8A8UIntNormalized, 2, size);
  if (SUCCEEDED(result)) {
    item.poolWidth = width;
    item.poolHeight = height;
    ++globalPoolRecreations;
  }
  return result;
}

static void synchronize_masks(overlay& item);

static HRESULT pump_capture(overlay& item) {
  if (!item.gpuStarted || !item.pool) return E_FAIL;
  com_pointer<capture::IDirect3D11CaptureFrame> frame;
  HRESULT result = item.pool->TryGetNextFrame(frame.address());
  if (FAILED(result) || !frame) return result;
  ABI::Windows::Graphics::SizeInt32 contentSize = {};
  result = frame->get_ContentSize(&contentSize);
  if (FAILED(result)) return result;
  if (contentSize.Width <= 0 || contentSize.Height <= 0 ||
      contentSize.Width > 16000 || contentSize.Height > 16000) return E_INVALIDARG;

  // The pool texture's allocation size does not necessarily match the latest
  // Fireworks window size. Do not present it first and resize afterwards:
  // that is precisely how an old window image survives a maximize/restore.
  if (contentSize.Width != item.poolWidth || contentSize.Height != item.poolHeight) {
    frame.reset();
    ++globalDroppedResizeFrames;
    item.gpuHasFrame = false;
    item.gpuAwaitingResizeFrame = true;
    return recreate_capture_pool(item, contentSize.Width, contentSize.Height);
  }

  // A location-change event may precede WGC's actual size notification.
  // Discard old-sized frames until GraphicsCaptureItem reports its new size.
  // Also reject stale captures after maximize/restore when the frame pool and
  // the previous capture still agree, but the actual visible window has grown.
  if (item.gpuAwaitingResizeFrame) {
    ::RECT matchingBounds = gpu_screen_bounds(item.source, contentSize.Width, contentSize.Height);
    if (item.mainEditor && nonempty(matchingBounds)) {
      // Accept either DWM-visible or Win32 outer bounds if the capture size
      // matches it; SDK/window combinations need not crop identically.
      int widthDifference = width_of(matchingBounds) - contentSize.Width;
      int heightDifference = height_of(matchingBounds) - contentSize.Height;
      if ((widthDifference < -8 || widthDifference > 8) ||
          (heightDifference < -8 || heightDifference > 8)) {
        ++globalDroppedResizeFrames;
        return S_OK;
      }
    }
    ABI::Windows::Graphics::SizeInt32 expectedSize = {};
    if (SUCCEEDED(item.item->get_Size(&expectedSize)) &&
        expectedSize.Width > 0 && expectedSize.Height > 0 &&
        (expectedSize.Width != contentSize.Width || expectedSize.Height != contentSize.Height)) {
      frame.reset();
      ++globalDroppedResizeFrames;
      if (expectedSize.Width != item.poolWidth || expectedSize.Height != item.poolHeight)
        return recreate_capture_pool(item, expectedSize.Width, expectedSize.Height);
      return S_OK;
    }
  }

  com_pointer<directx::Direct3D11::IDirect3DSurface> surface;
  result = frame->get_Surface(surface.address());
  if (FAILED(result)) return result;
  com_pointer< ::Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess> dxgiAccess;
  result = surface->QueryInterface(__uuidof(::Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess),
                                    reinterpret_cast<void**>(dxgiAccess.address()));
  if (FAILED(result)) return result;
  com_pointer<ID3D11Texture2D> texture;
  result = dxgiAccess->GetInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(texture.address()));
  if (FAILED(result)) return result;
  D3D11_TEXTURE2D_DESC textureDescription = {};
  texture->GetDesc(&textureDescription);
  if (textureDescription.Width < static_cast<UINT>(contentSize.Width) ||
      textureDescription.Height < static_cast<UINT>(contentSize.Height)) {
    texture.reset();
    dxgiAccess.reset();
    surface.reset();
    frame.reset();
    ++globalDroppedResizeFrames;
    item.gpuHasFrame = false;
    item.gpuAwaitingResizeFrame = true;
    return recreate_capture_pool(item, contentSize.Width, contentSize.Height);
  }
  // A resize can finish between geometry polls. Align the overlay to the
  // newly captured frame before presenting it, and reposition the RGB holes.
  ::RECT captureBounds = gpu_screen_bounds(item.source, contentSize.Width, contentSize.Height);
  if (!equal_rect(captureBounds, item.gpuBounds)) {
    item.gpuBounds = captureBounds;
    if (!::SetWindowPos(item.gpuHost, NULL, captureBounds.left, captureBounds.top,
        width_of(captureBounds), height_of(captureBounds),
        SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER)) return HRESULT_FROM_WIN32(::GetLastError());
    item.hasAppliedMask = false;
    synchronize_masks(item);
  }
  result = render_frame(item, texture.get(), contentSize.Width, contentSize.Height);
  if (FAILED(result)) return result;
  item.gpuHasFrame = true;
  item.gpuAwaitingResizeFrame = false;
  item.lastGoodFrame = ::GetTickCount();
  ++item.gpuFrames;
  ++globalCaptureFrames;
  return S_OK;
}

// A position-only move leaves WGC textures untouched; a size change must
// invalidate the old GPU presentation before its HWND is resized. The next
// correctly sized frame re-enables the overlay (no stretched stale image).
static void resize_hosts(overlay& item, ::RECT const& rectangle) {
  bool sourceMoved = !equal_rect(rectangle, item.previousBounds);
  bool sourceResized = width_of(rectangle) != width_of(item.previousBounds) ||
                       height_of(rectangle) != height_of(item.previousBounds);

  ABI::Windows::Graphics::SizeInt32 captureSize = {};
  bool capturedSizeKnown = item.item && SUCCEEDED(item.item->get_Size(&captureSize)) &&
                           captureSize.Width > 0 && captureSize.Height > 0 &&
                           captureSize.Width <= 16000 && captureSize.Height <= 16000;
  ::RECT gpuBounds = gpu_screen_bounds(item.source,
    capturedSizeKnown ? captureSize.Width : item.poolWidth,
    capturedSizeKnown ? captureSize.Height : item.poolHeight);
  bool gpuMoved = item.gpuHost && !equal_rect(gpuBounds, item.gpuBounds);
  bool gpuResized = gpuMoved && (width_of(gpuBounds) != width_of(item.gpuBounds) ||
                                 height_of(gpuBounds) != height_of(item.gpuBounds));
  bool poolSizeChanged = capturedSizeKnown && item.pool &&
    (captureSize.Width != item.poolWidth || captureSize.Height != item.poolHeight);
  if (!sourceMoved && !gpuMoved && !poolSizeChanged) return;

  if (sourceResized || gpuResized || poolSizeChanged) {
    ++globalSizeChanges;
    if (item.gpuHost && item.gpuStarted && !item.gpuFailed) {
      // A stale image must not stretch across a newly maximized/restored host.
      ::ShowWindow(item.gpuHost, SW_HIDE);
      item.visible = false;
      item.gpuHasFrame = false;
      item.gpuAwaitingResizeFrame = true;
      item.startTick = ::GetTickCount();
    }
  }
  if (gpuMoved) {
    item.gpuBounds = gpuBounds;
    ::SetWindowPos(item.gpuHost, NULL, gpuBounds.left, gpuBounds.top,
      width_of(gpuBounds), height_of(gpuBounds),
      SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
  }
  if (sourceMoved && item.magHost) {
    ::SetWindowPos(item.magHost, NULL, rectangle.left, rectangle.top,
      width_of(rectangle), height_of(rectangle),
      SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
  }
  if (sourceMoved && item.magnifier) {
    ::SetWindowPos(item.magnifier, NULL, 0, 0, width_of(rectangle), height_of(rectangle),
      SWP_NOZORDER | SWP_NOACTIVATE);
    if (::MagSetWindowSource(item.magnifier, rectangle)) {
      ++item.magnifierSourceRefreshes;
      if (sourceResized) ::RedrawWindow(item.magnifier, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    } else {
      item.magnifierFailureStage = "MagSetWindowSource(resize)";
      item.magnifierLastError = ::GetLastError();
      ++globalMagnifierFailures;
    }
  }
  item.previousBounds = rectangle;

  // Resize the capture pool even if the application hasn't emitted a new
  // frame yet. All capture/presentation calls run serially on this thread.
  if (poolSizeChanged && item.gpuStarted && !item.gpuFailed) {
    HRESULT result = recreate_capture_pool(item, captureSize.Width, captureSize.Height);
    if (FAILED(result)) {
      item.gpuError = result;
      lastGpuError = result;
      ++item.gpuFailures;
    }
  }
}

// Regions are expressed relative to the window on which they are installed.
// WGC and Magnification can have DIFFERENT top-left origins and sizes.
static ::HRGN compose_host_region(::RECT const& hostBounds, ::std::vector<exclusion> const& masks) {
  ::HRGN region = ::CreateRectRgn(0, 0, width_of(hostBounds), height_of(hostBounds));
  if (!region) return NULL;
  ::RECT localBounds = { 0, 0, width_of(hostBounds), height_of(hostBounds) };
  for (::std::size_t index = 0; index < masks.size(); ++index) {
    ::RECT relative = masks[index].screen;
    ::OffsetRect(&relative, -hostBounds.left, -hostBounds.top);
    ::RECT clipped = {};
    if (!::IntersectRect(&clipped, &relative, &localBounds)) continue;
    ::HRGN cutout = mask_region(clipped, masks[index].round);
    if (cutout) {
      ::CombineRgn(region, region, cutout, RGN_DIFF);
      ::DeleteObject(cutout);
    }
  }
  return region;
}

static void synchronize_masks(overlay& item) {
  ::RECT sourceBounds = {};
  if (!::GetWindowRect(item.source, &sourceBounds) || !nonempty(sourceBounds)) return;
  ::std::vector<exclusion> masks;
  read_exclusions(item.source, item.mainEditor, masks); // Screen-space rectangles
  ::RECT gpuBounds = item.gpuHost ? item.gpuBounds : ::RECT();
  if (item.gpuHost && !nonempty(gpuBounds)) gpuBounds = gpu_screen_bounds(item.source, item.poolWidth, item.poolHeight);
  ::RECT magBounds = item.magHost ? sourceBounds : ::RECT();
  if (item.hasAppliedMask && same_exclusions(item.appliedMasks, masks) &&
      equal_rect(item.appliedGpuBounds, gpuBounds) && equal_rect(item.appliedMagBounds, magBounds)) {
    ++item.maskHits;
    ++globalMasksReused;
    return;
  }
  bool applied = false;
  if (item.gpuHost && nonempty(gpuBounds)) {
    ::HRGN region = compose_host_region(gpuBounds, masks);
    if (region) {
      if (::SetWindowRgn(item.gpuHost, region, FALSE)) applied = true;
      else ::DeleteObject(region);
    }
  }
  if (item.magHost && nonempty(magBounds)) {
    ::HRGN region = compose_host_region(magBounds, masks);
    if (region) {
      if (::SetWindowRgn(item.magHost, region, FALSE)) applied = true;
      else ::DeleteObject(region);
    }
  }
  if (!applied) return;
  item.appliedMasks.swap(masks);
  item.appliedGpuBounds = gpuBounds;
  item.appliedMagBounds = magBounds;
  item.hasAppliedMask = true;
  ++item.maskChanges;
  ++globalRegionUpdates;
}

static ::HWND active_host(overlay const& item) {
  if (!item.visible) return NULL;
  if (item.gpuHost && ::IsWindowVisible(item.gpuHost)) return item.gpuHost;
  if (item.magHost && ::IsWindowVisible(item.magHost)) return item.magHost;
  return NULL;
}

static void correct_stack(overlay& item) {
  ::HWND host = active_host(item);
  if (!host || !::IsWindowVisible(item.source)) return;
  // Check real visible Z-order, ignoring our hidden backup overlay window.
  ::HWND previous = ::GetWindow(item.source, GW_HWNDPREV);
  while (previous && !::IsWindowVisible(previous)) previous = ::GetWindow(previous, GW_HWNDPREV);
  if (previous == host) return;
  // Do not put this overlay at HWND_TOPMOST or ahead of unrelated foreground apps.
  // Insert it immediately above its source, beneath whichever window preceded it.
  ::SetWindowPos(host, previous ? previous : HWND_TOP, 0, 0, 0, 0,
    SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
  ++item.zCorrections;
  ++globalZCorrections;
}

static void choose_visible_backend(overlay& item) {
  bool useGpu = preferGpu && item.gpuHost && item.gpuHasFrame && !item.gpuFailed;
  // Do not show a Magnification menu temporarily while GPU capture is merely
  // waiting for its first frame: all windows follow the chosen backend.
  bool useMag = !useGpu && (!preferGpu || item.gpuFailed || !item.gpuStarted) &&
                item.magHost && item.magnifierConfigured &&
                (!layered_window(item.source) || item.mainEditor);
  ::HWND wanted = useGpu ? item.gpuHost : (useMag ? item.magHost : NULL);
  if (wanted == active_host(item)) return;
  if (item.gpuHost && item.gpuHost != wanted) ::ShowWindow(item.gpuHost, SW_HIDE);
  if (item.magHost && item.magHost != wanted) ::ShowWindow(item.magHost, SW_HIDE);
  if (wanted) ::ShowWindow(wanted, SW_SHOWNOACTIVATE);
  item.visible = wanted != NULL;
  if (wanted) correct_stack(item);
  if (wanted == item.magHost && item.magnifier) {
    // A newly visible magnifier gets one explicit source refresh. Do not
    // repeatedly invalidate it on mouse clicks or Fireworks paint events.
    ::RECT sourceBounds = {};
    if (::GetWindowRect(item.source, &sourceBounds) &&
        ::MagSetWindowSource(item.magnifier, sourceBounds)) {
      ++item.magnifierSourceRefreshes;
      ::RedrawWindow(item.magnifier, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    } else {
      item.magnifierFailureStage = "MagSetWindowSource(show)";
      item.magnifierLastError = ::GetLastError();
      ++globalMagnifierFailures;
    }
  }
}

static void ensure_overlay(::HWND window) {
  if (lookup_overlay(window) || overlays.size() >= 32) return;
  overlay* item = new overlay(window, is_fireworks(window));
  if (!item) return;
  // Construct only the selected backend. The other is created on genuine
  // failure, not left hidden and compositing stale pixels under this HWND.
  if (preferGpu && gpu.ready) {
    HRESULT result = create_gpu_host(*item);
    if (FAILED(result)) {
      item->gpuFailed = true;
      item->gpuError = result;
      lastGpuError = result;
      ++globalGpuFallbacks;
      if (item->gpuHost) {
        ::DestroyWindow(item->gpuHost);
        item->gpuHost = NULL;
      }
    }
  }
  if ((!preferGpu || !gpu.ready || item->gpuFailed) && magnificationAvailable &&
      (!layered_window(window) || item->mainEditor)) create_mag_host(*item);
  if (!item->magHost && !item->gpuStarted) { delete item; return; }
  ::RECT bounds = {};
  ::GetWindowRect(window, &bounds);
  item->previousBounds = bounds;
  synchronize_masks(*item);
  overlays.push_back(item);
  // A GPU host becomes visible only after its first valid frame; otherwise
  // avoid an unrequested switch to Magnification while WGC starts.
  choose_visible_backend(*item);
}

static ::std::vector< ::HWND> previousFilterHosts;
static void refresh_magnifier_filter_list() {
  ::std::vector< ::HWND> hosts;
  for (::std::size_t index = 0; index < overlays.size(); ++index) {
    if (overlays[index]->gpuHost) hosts.push_back(overlays[index]->gpuHost);
    if (overlays[index]->magHost) hosts.push_back(overlays[index]->magHost);
  }
  if (hosts == previousFilterHosts) return;
  for (::std::size_t index = 0; index < overlays.size(); ++index) {
    if (!overlays[index]->magnifier) continue;
    if (::MagSetWindowFilterList(overlays[index]->magnifier, MW_FILTERMODE_EXCLUDE,
      static_cast<int>(hosts.size()), hosts.empty() ? NULL : &hosts[0])) {
      ++globalFilterUpdates;
    } else {
      overlays[index]->magnifierFailureStage = "MagSetWindowFilterList";
      overlays[index]->magnifierLastError = ::GetLastError();
      ++globalMagnifierFilterFailures;
    }
  }
  previousFilterHosts.swap(hosts);
}

static void scan_top_level_windows() {
  ++globalScanCount;
  ::std::vector< ::HWND> discovered;
  ::EnumWindows(list_windows, reinterpret_cast<LPARAM>(&discovered));
  if (!discovered.empty()) ::EnumWindows(list_popups, reinterpret_cast<LPARAM>(&discovered));
  for (::std::size_t index = overlays.size(); index > 0; --index) {
    overlay* item = overlays[index - 1];
    bool found = false;
    for (::std::size_t position = 0; position < discovered.size(); ++position)
      if (discovered[position] == item->source) { found = true; break; }
    if (!found || !window_alive(item->source)) {
      delete item;
      overlays.erase(overlays.begin() + (index - 1));
    }
  }
  for (::std::size_t index = 0; index < discovered.size(); ++index) ensure_overlay(discovered[index]);
  refresh_magnifier_filter_list();
}

// A renderer hotkey is intentionally a full transaction, not a visibility
// toggle. Stop WGC sessions, unroot DComp visuals, destroy both old HWNDs,
// then discover the same Fireworks windows under the newly chosen backend.
static void rebuild_all_backends() {
  // A true HWND replacement: never recycle the old capture host, magnifier,
  // or DirectComposition target when Ctrl+Alt+F7 is pressed.
  for (::std::size_t index = 0; index < overlays.size(); ++index) delete overlays[index];
  overlays.clear();
  previousFilterHosts.clear();
  // Wait for DWM to process all removed hosts before constructing replacements.
  ::DwmFlush();
  scan_top_level_windows();
}

// Refresh is a fresh graphics initialization, not merely a new exclusion
// region. Destroy all overlay HWNDs and captures before releasing the shared
// GPU device; recreate the selected renderer only after all old visuals retire.
static void refresh_everything(::HRESULT& winrtResult) {
  for (::std::size_t index = 0; index < overlays.size(); ++index) delete overlays[index];
  overlays.clear();
  previousFilterHosts.clear();
  ::DwmFlush();

  if (gpu.context) {
    gpu.context->ClearState();
    gpu.context->Flush();
  }
  gpu.captureDevice.reset();
  gpu.sampler.reset();
  gpu.pixelShader.reset();
  gpu.vertexShader.reset();
  gpu.composition.reset();
  gpu.factory.reset();
  gpu.dxgi.reset();
  gpu.context.reset();
  gpu.device.reset();
  gpu.ready = false;

  if (magnificationAvailable) ::MagUninitialize();
  magnificationAvailable = false;
  if (SUCCEEDED(winrtResult)) ::RoUninitialize();
  winrtResult = ::RoInitialize(RO_INIT_MULTITHREADED);
  magnificationAvailable = ::MagInitialize() != FALSE;
  ::HRESULT gpuResult = initialize_gpu();
  lastGpuError = SUCCEEDED(gpuResult) ? S_OK : gpuResult;

  // All runtime caches, capture sessions, regions and instrumentation reset.
  // Keep the tray icon, registered hotkeys and event hooks: they are the
  // application's control plane rather than graphics backend state.
  globalZCorrections = 0;
  globalRegionUpdates = 0;
  globalFilterUpdates = 0;
  globalPopupEvents = 0;
  globalGpuFallbacks = 0;
  globalTransitions = 0;
  globalMasksReused = 0;
  globalCaptureFrames = 0;
  globalPickerSkips = 0;
  globalPopupCandidates = 0;
  globalMagnifierFailures = 0;
  globalMagnifierFilterFailures = 0;
  globalScanCount = 0;
  globalResizeEvents = 0;
  globalSizeChanges = 0;
  globalPoolRecreations = 0;
  globalDroppedResizeFrames = 0;
  preferGpu = true; // Same preferred renderer as a newly launched process.
  ++globalRefreshes;
  ::std::printf("Full refresh %lu: WGC-D3D11=%s, Magnification=%s\n",
    globalRefreshes, gpu.ready ? "available" : "unavailable",
    magnificationAvailable ? "available" : "unavailable");
  if (!gpu.ready && !magnificationAvailable)
    ::std::fprintf(stderr, "Both backends unavailable; Refresh can retry. GPU HRESULT=0x%08lX\n",
      static_cast<unsigned long>(lastGpuError));
  scan_top_level_windows();
}

static void refresh_geometry() {
  for (::std::size_t index = 0; index < overlays.size(); ++index) {
    overlay& item = *overlays[index];
    if (!window_alive(item.source)) continue;
    ::RECT bounds = {};
    if (!::GetWindowRect(item.source, &bounds) || !nonempty(bounds)) continue;
    resize_hosts(item, bounds);
    synchronize_masks(item);
    // Ownership keeps the overlay with its source. No Z-order writes here:
    // clicking or painting in Fireworks must not restack top-level windows.
  }
}

// Make a real GPU failure switch to Magnification without leaving a stale
// composition surface. A newly created host needs its own region applied.
static void fallback_after_capture_error(overlay& item) {
  item.gpuFailed = true;
  if (!item.magHost && magnificationAvailable &&
      (!layered_window(item.source) || item.mainEditor) && create_mag_host(item)) {
    item.hasAppliedMask = false;
    synchronize_masks(item);
    refresh_magnifier_filter_list();
  }
  choose_visible_backend(item);
}

static void refresh_capture() {
  for (::std::size_t index = 0; index < overlays.size(); ++index) {
    overlay& item = *overlays[index];
    if (!item.gpuStarted || item.gpuFailed) continue;
    if (!preferGpu && item.gpuHasFrame) continue;
    HRESULT result = pump_capture(item);
    if (FAILED(result)) {
      item.gpuError = result;
      lastGpuError = result;
      ++item.gpuFailures;
      // A single missing/late frame is not a backend failure and never hides
      // the last presented image. Only sustained failures trigger fallback.
      if (item.gpuFailures >= 12) {
        ++globalGpuFallbacks;
        fallback_after_capture_error(item);
      }
    } else if (item.gpuHasFrame) {
      item.gpuFailures = 0;
      choose_visible_backend(item);
    } else if (static_cast<DWORD>(::GetTickCount() - item.startTick) > 3000) {
      item.gpuError = HRESULT_FROM_WIN32(ERROR_TIMEOUT);
      ++globalGpuFallbacks;
      fallback_after_capture_error(item);
    }
  }
}

struct diagnostic_window_scan {
  ::FILE* stream;
  ::std::vector< ::DWORD> fireworksProcesses;
};

static BOOL CALLBACK diagnostic_top_level_window(::HWND window, LPARAM parameter) {
  diagnostic_window_scan* report = reinterpret_cast<diagnostic_window_scan*>(parameter);
  if (!::IsWindowVisible(window)) return TRUE;
  ::DWORD processId = 0;
  ::GetWindowThreadProcessId(window, &processId);
  ::HWND owner = ::GetWindow(window, GW_OWNER);
  ::HWND rootOwner = owner ? ::GetAncestor(owner, GA_ROOTOWNER) : NULL;
  bool relevant = is_fireworks(rootOwner) || is_fireworks(window);
  for (::std::size_t index = 0; index < report->fireworksProcesses.size() && !relevant; ++index)
    relevant = report->fireworksProcesses[index] == processId;
  if (!relevant) return TRUE;
  wchar_t className[128] = {};
  ::GetClassNameW(window, className, 128);
  ::RECT bounds = {};
  ::GetWindowRect(window, &bounds);
  overlay* mapped = lookup_overlay(window);
  ::std::fprintf(report->stream,
    "TOPLEVEL HWND=%p PID=%lu OWNER=%p CLASS=%ls RECT=(%ld,%ld,%ld,%ld) TRACKED=%d PICKER=%d LAYERED=%d\n",
    window, static_cast<unsigned long>(processId), owner, className,
    bounds.left, bounds.top, bounds.right, bounds.bottom,
    mapped ? 1 : 0, is_color_picker(window) ? 1 : 0,
    (::GetWindowLongPtrW(window, GWL_EXSTYLE) & WS_EX_LAYERED) != 0 ? 1 : 0);
  return TRUE;
}

static void dump_diagnostics() {
  ::FILE* stream = NULL;
  if (::_wfopen_s(&stream, L"fireworks-dark-diagnostics.txt", L"w") != 0 || !stream) return;
  ::std::fprintf(stream, "Fireworks (Dark) v2.0.6 diagnostics\n");
  ::std::fprintf(stream, "NotificationIcon=%d Refreshes=%lu PreferredRenderer=%s\n",
    notificationIconPresent ? 1 : 0, globalRefreshes, preferGpu ? "WGC-D3D11" : "Magnification");
  ::std::fprintf(stream, "Preferred=%s overlays=%u scans=%lu capturedFrames=%lu\n",
    preferGpu ? "WGC-D3D11" : "Magnification", static_cast<unsigned>(overlays.size()), globalScanCount, globalCaptureFrames);
  ::std::fprintf(stream, "MaskChanges=%lu MaskUnchanged=%lu FilterUpdates=%lu ZOrderCorrections=%lu PopupEvents=%lu GpuFallbacks=%lu Switches=%lu LastHRESULT=0x%08lX\n",
    globalRegionUpdates, globalMasksReused, globalFilterUpdates, globalZCorrections, globalPopupEvents,
    globalGpuFallbacks, globalTransitions, static_cast<unsigned long>(lastGpuError));
  ::std::fprintf(stream, "ResizeEvents=%lu SizeChanges=%lu PoolRecreates=%lu DiscardedResizeFrames=%lu\n",
    globalResizeEvents, globalSizeChanges, globalPoolRecreations, globalDroppedResizeFrames);
  ::std::fprintf(stream, "PickerPopupSkipScans=%lu PopupCandidates=%lu CutoutCornerRadiusPx=5\n",
    globalPickerSkips, globalPopupCandidates);
  ::std::fprintf(stream, "MagnifierFailures=%lu MagnifierFilterFailures=%lu LayeredMagnifierHostRequired=1\n",
    globalMagnifierFailures, globalMagnifierFilterFailures);
  for (::std::size_t index = 0; index < overlays.size(); ++index) {
    overlay const& item = *overlays[index];
    ::RECT bounds = {};
    ::GetWindowRect(item.source, &bounds);
    ::std::fprintf(stream,
      "Overlay[%u] HWND=%p editor=%d sourceRECT=(%ld,%ld,%ld,%ld) backend=%s gpuStarted=%d gpuFrame=%d gpuFailed=%d frames=%lu maskChanges=%lu maskHits=%lu zCorrections=%lu gpuFailures=%lu HRESULT=0x%08lX inputLayered=%d\n",
      static_cast<unsigned>(index), item.source, item.mainEditor ? 1 : 0,
      bounds.left, bounds.top, bounds.right, bounds.bottom,
      item.gpuHost && ::IsWindowVisible(item.gpuHost) ? "WGC-D3D11" :
        (item.magHost && ::IsWindowVisible(item.magHost) ? "Magnification" : "None"),
      item.gpuStarted ? 1 : 0, item.gpuHasFrame ? 1 : 0, item.gpuFailed ? 1 : 0,
      item.gpuFrames, item.maskChanges, item.maskHits, item.zCorrections, item.gpuFailures,
      static_cast<unsigned long>(item.gpuError),
      item.gpuHost && (::GetWindowLongPtrW(item.gpuHost, GWL_EXSTYLE) & WS_EX_LAYERED) != 0 ? 1 : 0);
    ::RECT visibleBounds = gpu_screen_bounds(item.source, item.poolWidth, item.poolHeight);
    ::std::fprintf(stream, "  RESIZE awaitingGpuFrame=%d capturePool=(%d,%d) swapChainFrame=(%d,%d) visibleRECT=(%ld,%ld,%ld,%ld) gpuHostRECT=(%ld,%ld,%ld,%ld)\n",
      item.gpuAwaitingResizeFrame ? 1 : 0, item.poolWidth, item.poolHeight, item.frameWidth, item.frameHeight,
      visibleBounds.left, visibleBounds.top, visibleBounds.right, visibleBounds.bottom,
      item.gpuBounds.left, item.gpuBounds.top, item.gpuBounds.right, item.gpuBounds.bottom);
    ::std::fprintf(stream, "  GPU swapChainAllocation=(%d,%d)\n", item.swapWidth, item.swapHeight);
    ::std::fprintf(stream,
      "  MAG host=%p magnifier=%p layered=%d configured=%d sourceRefreshes=%lu failureStage=%s lastError=%lu\n",
      item.magHost, item.magnifier,
      item.magHost && (::GetWindowLongPtrW(item.magHost, GWL_EXSTYLE) & WS_EX_LAYERED) != 0 ? 1 : 0,
      item.magnifierConfigured ? 1 : 0, item.magnifierSourceRefreshes,
      item.magnifierFailureStage, static_cast<unsigned long>(item.magnifierLastError));
  }
  diagnostic_window_scan report = {};
  report.stream = stream;
  for (::std::size_t index = 0; index < overlays.size(); ++index)
    if (overlays[index]->mainEditor) {
      ::DWORD processId = 0;
      ::GetWindowThreadProcessId(overlays[index]->source, &processId);
      report.fireworksProcesses.push_back(processId);
    }
  ::EnumWindows(diagnostic_top_level_window, reinterpret_cast<LPARAM>(&report));
  ::std::fclose(stream);
  ::std::printf("Diagnostics: fireworks-dark-diagnostics.txt\n");
}

static void CALLBACK window_changed(::HWINEVENTHOOK, DWORD event, ::HWND window, LONG objectId, LONG childId,
                                    DWORD, DWORD) {
  if (!window || objectId != OBJID_WINDOW || childId != CHILDID_SELF || !coordinator) return;
  ::DWORD eventProcess = 0;
  ::GetWindowThreadProcessId(window, &eventProcess);
  ::HWND owner = ::GetWindow(window, GW_OWNER);
  bool matches = is_fireworks(window) ||
    (owner && is_fireworks(::GetAncestor(owner, GA_ROOTOWNER)));
  for (::std::size_t index = 0; index < overlays.size() && !matches; ++index) {
    ::DWORD process = 0;
    ::GetWindowThreadProcessId(overlays[index]->source, &process);
    matches = process != 0 && eventProcess == process;
  }
  if (!matches) return;
  if (event == EVENT_OBJECT_LOCATIONCHANGE) {
    if (::GetAncestor(window, GA_ROOT) != window) return;
    ++globalResizeEvents;
    ::PostMessageW(coordinator, WM_GEOMETRY, 0, 0);
    return;
  }
  if (event == EVENT_OBJECT_SHOW || event == EVENT_OBJECT_HIDE || event == EVENT_OBJECT_DESTROY ||
      event == EVENT_SYSTEM_FOREGROUND) {
    ++globalPopupEvents;
    ::PostMessageW(coordinator, WM_RESCAN, 0, 0);
  }
  // Ordinary control repaint, focus, selection and cursor events are ignored.
}

static ::LRESULT CALLBACK host_procedure(::HWND window, UINT message, ::WPARAM parameter, ::LPARAM argument) {
  if (window == coordinator) {
    if (taskbarCreatedMessage && message == taskbarCreatedMessage) {
      // Explorer recreates its notification area after a restart.
      notificationIconPresent = false;
      notification_add();
      return 0;
    }
    if (message == WM_TRAY_ICON) {
      UINT interaction = LOWORD(argument); // NOTIFYICON_VERSION_4
      if (interaction == WM_CONTEXTMENU || interaction == WM_RBUTTONUP ||
          interaction == NIN_SELECT || interaction == NIN_KEYSELECT || interaction == WM_LBUTTONUP)
        notification_menu();
      return 0;
    }
    if (message == WM_RESCAN) return 0;
  }
  // This remains a defensive hint; cross-process pass-through depends on
  // WS_EX_LAYERED | WS_EX_TRANSPARENT for the D3D11 host, not HTTRANSPARENT.
  if (message == WM_NCHITTEST) return HTTRANSPARENT;
  if (message == WM_MOUSEACTIVATE) return MA_NOACTIVATE;
  return ::DefWindowProcW(window, message, parameter, argument);
}

static BOOL WINAPI console_signal(DWORD signal) {
  if (signal == CTRL_C_EVENT || signal == CTRL_BREAK_EVENT || signal == CTRL_CLOSE_EVENT) {
    ::InterlockedExchange(&exiting, 1);
    if (coordinator) ::PostMessageW(coordinator, WM_NULL, 0, 0);
    return TRUE;
  }
  return FALSE;
}

int main() {
  // Keep DPI calculations in physical screen coordinates across monitors.
  HMODULE user32 = ::GetModuleHandleW(L"user32.dll");
  if (user32) {
    typedef BOOL (WINAPI *dpi_awareness)(DPI_AWARENESS_CONTEXT);
    dpi_awareness setDpi = reinterpret_cast<dpi_awareness>(::GetProcAddress(user32, "SetProcessDpiAwarenessContext"));
    if (setDpi) setDpi(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    else ::SetProcessDPIAware();
  }
  ::SetConsoleCtrlHandler(console_signal, TRUE);
  HRESULT winrtResult = ::RoInitialize(RO_INIT_MULTITHREADED);
  magnificationAvailable = ::MagInitialize() != FALSE;
  HRESULT gpuResult = initialize_gpu();
  if (FAILED(gpuResult)) lastGpuError = gpuResult;
  if (!gpu.ready && !magnificationAvailable) {
    ::std::fprintf(stderr, "No available renderer: D3D11 HRESULT=0x%08lX\n", static_cast<unsigned long>(gpuResult));
    if (SUCCEEDED(winrtResult)) ::RoUninitialize();
    return 1;
  }

  ::WNDCLASSEXW windowClass = {};
  windowClass.cbSize = sizeof(windowClass);
  windowClass.hInstance = ::GetModuleHandleW(NULL);
  windowClass.lpfnWndProc = host_procedure;
  windowClass.lpszClassName = WINDOW_CLASS;
  if (!::RegisterClassExW(&windowClass)) return 2;
  // A hidden top-level window is required for shell broadcasts (TaskbarCreated)
  // and notification callbacks; HWND_MESSAGE is not a broadcast recipient.
  coordinator = ::CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
    WINDOW_CLASS, L"", WS_OVERLAPPED, 0, 0, 0, 0,
    NULL, NULL, windowClass.hInstance, NULL);
  if (!coordinator) return 3;
  taskbarCreatedMessage = ::RegisterWindowMessageW(L"TaskbarCreated");
  notificationIcon = static_cast< ::HICON>(::LoadImageW(windowClass.hInstance, MAKEINTRESOURCEW(101),
    IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR));
  ownsNotificationIcon = notificationIcon != NULL;
  if (!notificationIcon) notificationIcon = ::LoadIconW(NULL, IDI_APPLICATION);
  notification_add();
  ::RegisterHotKey(NULL, HOTKEY_DIAGNOSTICS, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F6);
  ::RegisterHotKey(NULL, HOTKEY_BACKEND, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F7);
  ::RegisterHotKey(NULL, HOTKEY_REFRESH, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F8);
  ::RegisterHotKey(NULL, HOTKEY_EXIT, MOD_CONTROL | MOD_ALT | MOD_NOREPEAT, VK_F10);

  windowEventHook = ::SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, NULL, window_changed,
    0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
  ::HWINEVENTHOOK showHook = ::SetWinEventHook(EVENT_OBJECT_DESTROY, EVENT_OBJECT_HIDE, NULL, window_changed,
    0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
  ::HWINEVENTHOOK geometryHook = ::SetWinEventHook(EVENT_OBJECT_LOCATIONCHANGE, EVENT_OBJECT_LOCATIONCHANGE,
    NULL, window_changed, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
  ::std::printf("Fireworks (Dark) v2.0.6 - C++98\n");
  ::std::printf("Primary renderer: %s. Ctrl+Alt+F6 diagnostics; F7 renderer; F8 refresh; F10 exit.\n",
    gpu.ready ? "WGC-D3D11" : "Magnification");
  ::std::printf("Tray icon provides the same commands; Esc exits while this console is active.\n");
  ::std::printf("No injection. Fireworks may start before or after this process.\n");

  // Console input events are distinct from system-wide hotkeys. Reading Esc
  // here leaves Fireworks' own Esc shortcut untouched and works in Terminal.
  ::HANDLE consoleInput = ::GetStdHandle(STD_INPUT_HANDLE);
  ::DWORD consoleMode = 0;
  bool readConsoleKeys = consoleInput && consoleInput != INVALID_HANDLE_VALUE &&
    ::GetConsoleMode(consoleInput, &consoleMode) != FALSE;

  ::DWORD lastScan = 0;
  ::DWORD lastGeometry = 0;
  while (!::InterlockedCompareExchange(&exiting, 0, 0)) {
    ::MSG message = {};
    bool requestedScan = false;
    bool requestedGeometry = false;
    bool requestedRefresh = false;
    bool requestedBackend = false;
    bool requestedDiagnostics = false;
    while (::PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
      if (message.message == WM_HOTKEY || message.message == WM_TRAY_COMMAND) {
        ::WPARAM command = message.wParam;
        if (command == HOTKEY_EXIT || command == TRAY_QUIT)
          ::InterlockedExchange(&exiting, 1);
        else if (command == HOTKEY_DIAGNOSTICS || command == TRAY_DIAGNOSTICS)
          requestedDiagnostics = true;
        else if (command == HOTKEY_BACKEND || command == TRAY_BACKEND)
          requestedBackend = true;
        else if (command == HOTKEY_REFRESH || command == TRAY_REFRESH)
          requestedRefresh = true;
      } else if (message.message == WM_RESCAN) requestedScan = true;
      else if (message.message == WM_GEOMETRY) requestedGeometry = true;
      else if (message.message == WM_QUIT) ::InterlockedExchange(&exiting, 1);
      if (message.message != WM_HOTKEY && message.message != WM_TRAY_COMMAND) {
        ::TranslateMessage(&message);
        ::DispatchMessageW(&message);
      }
    }

    if (readConsoleKeys) {
      ::DWORD waiting = 0;
      if (::GetNumberOfConsoleInputEvents(consoleInput, &waiting) && waiting) {
        ::INPUT_RECORD records[32] = {};
        ::DWORD received = 0;
        if (::ReadConsoleInputW(consoleInput, records, waiting < 32 ? waiting : 32, &received)) {
          for (::DWORD index = 0; index < received; ++index)
            if (records[index].EventType == KEY_EVENT &&
                records[index].Event.KeyEvent.bKeyDown &&
                records[index].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
              ::InterlockedExchange(&exiting, 1);
        }
      }
    }
    if (::InterlockedCompareExchange(&exiting, 0, 0)) break;
    if (requestedRefresh) {
      refresh_everything(winrtResult);
      lastScan = lastGeometry = ::GetTickCount();
      requestedScan = requestedGeometry = false;
    } else if (requestedBackend) {
      preferGpu = !preferGpu;
      ++globalTransitions;
      ::std::printf("Renderer preference: %s\n", preferGpu ? "WGC-D3D11" : "Magnification");
      rebuild_all_backends();
      lastScan = lastGeometry = ::GetTickCount();
      requestedScan = requestedGeometry = false;
    }
    if (requestedDiagnostics) dump_diagnostics();
    ::DWORD now = ::GetTickCount();
    if (requestedScan || static_cast<DWORD>(now - lastScan) >= 1000) {
      scan_top_level_windows();
      lastScan = now;
    }
    if (requestedGeometry || static_cast<DWORD>(now - lastGeometry) >= 200) {
      refresh_geometry();
      lastGeometry = now;
    }
    if (preferGpu) refresh_capture();
    // Windows events wake the loop immediately; this short timeout only polls
    // WGC frame availability, not window positions or exclusion regions.
    ::MsgWaitForMultipleObjectsEx(0, NULL, preferGpu ? 16 : 65, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
  }

  if (geometryHook) ::UnhookWinEvent(geometryHook);
  if (showHook) ::UnhookWinEvent(showHook);
  if (windowEventHook) ::UnhookWinEvent(windowEventHook);
  ::UnregisterHotKey(NULL, HOTKEY_DIAGNOSTICS);
  ::UnregisterHotKey(NULL, HOTKEY_BACKEND);
  ::UnregisterHotKey(NULL, HOTKEY_REFRESH);
  ::UnregisterHotKey(NULL, HOTKEY_EXIT);
  for (::std::size_t index = 0; index < overlays.size(); ++index) delete overlays[index];
  overlays.clear();
  notification_remove();
  if (ownsNotificationIcon && notificationIcon) ::DestroyIcon(notificationIcon);
  notificationIcon = NULL;
  ::DestroyWindow(coordinator);
  if (magnificationAvailable) ::MagUninitialize();
  if (SUCCEEDED(winrtResult)) ::RoUninitialize();
  return 0;
}
