import ctypes
import functools
import http.server
import os
import socket
import sys
import threading

# ...
ERROR_ALREADY_EXISTS = 183
EVENT_MODIFY_STATE   = 0x0002
EVENT_NAME           = r"Local\LapysDev.Localhost.Shutdown"
INFINITE             = 0xFFFFFFFF
MUTEX_NAME           = r"Local\LapysDev.Localhost.Instance"
PORT                 = 8000
ROOT_DIRECTORY       = r"C:\LapysDev"

kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)

# ...
class IPv4Server(http.server.ThreadingHTTPServer):
  address_family      = socket.AF_INET
  allow_reuse_address = True

class IPv6Server(http.server.ThreadingHTTPServer):
  address_family      = socket.AF_INET6
  allow_reuse_address = True

  def server_bind(self):
    self.socket.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 1)
    super().server_bind()

# ...
def shutdown():
  event = kernel32.OpenEventW(EVENT_MODIFY_STATE, False, EVENT_NAME)

  if not event:
    print("`localhost.py` is not running.")
    return 1

  try:
    if not kernel32.SetEvent(event):
      raise ctypes.WinError(ctypes.get_last_error())
  finally:
    kernel32.CloseHandle(event)

  print("`localhost.py` shutdown requested.")
  return 0

def main():
  mutex = kernel32.CreateMutexW(None, False, MUTEX_NAME)

  if not mutex:
    raise ctypes.WinError(ctypes.get_last_error())

  if ctypes.get_last_error() == ERROR_ALREADY_EXISTS:
    kernel32.CloseHandle(mutex)
    print("localhost.py is already running.")
    return 1

  event = kernel32.CreateEventW(None, True, False, EVENT_NAME)

  if not event:
    kernel32.CloseHandle(mutex)
    raise ctypes.WinError(ctypes.get_last_error())

  handler = functools.partial(http.server.SimpleHTTPRequestHandler, directory=ROOT_DIRECTORY)
  servers = []

  try:
    servers = [IPv4Server(("0.0.0.0", PORT), handler), IPv6Server(("::", PORT), handler)]

    for server in servers:
      threading.Thread(target=server.serve_forever, daemon=True).start()

    print("Serving: `", ROOT_DIRECTORY, "`")
    print("IPv4: `http://127.0.0.1:8000`")
    print("IPv6: `http://[::1]:8000`")

    kernel32.WaitForSingleObject(event, INFINITE)

  except KeyboardInterrupt:
    pass

  finally:
    for server in servers:
      server.shutdown()
      server.server_close()

    kernel32.CloseHandle(event)
    kernel32.CloseHandle(mutex)

  return 0

# ...
if __name__ == "__main__":
  sys.stderr = open(os.devnull, "w", encoding="utf-8") if sys.stderr is None else sys.stderr
  sys.stdout = open(os.devnull, "w", encoding="utf-8") if sys.stdout is None else sys.stdout

  if len(sys.argv) == 2 and sys.argv[1].lower() == "-shutdown":
    sys.exit(shutdown())

  if len(sys.argv) != 1:
    print("Usage: localhost.py [-shutdown]")
    sys.exit(2)

  sys.exit(main())
