message: .string "Hello, World!"

.text
.global put
put:
  # write(0x1, message, 13)
  mov $1, %eax

  mov $1, %edi
  mov $message, %esi
  mov $13, %edx
  syscall

  ret
