# Phase > Initiate --- NOTE (Lapys) -> Program entry point.
initiate:
    # Constant > ... --- NOTE (Lapys) -> Places the `char` data consequently onto the program stack.
    .ascii "Hello, World!\0" # -> char const message[]

    # Text
    .text
        # Definition > ...
        .global _main # NOTE (Lapys) -> Compilation with some linkers require the main entry be well-defined and present.
        .def _main

        # [Main]
        _main:
            # Update > (Base, Stack) Pointer
            pushl %ebp
            movl %esp, %ebp

            subl $12, %esp # -> stack -= sizeof(int) + sizeof(char const[]) + sizeof(size_t); 22 bytes or 24 bytes?
            movl $1, (%esp) # -> *stack = int fileDescriptor;
            movl $initiate, 4(%esp) # -> *(stack + 1) = <initiate>;
            movl $13, 8(%esp) # -> *(stack + 2) = size_t length;

            # Write --- CODE (Lapys) -> write(int fileDescriptor, char const message[], size_t length)
            call _write
            leave

            # Update > Extended Arithmetic Register; Return
            movl $0, %eax # NOTE (Lapys) -> Prepare to return `0` from main entry routine.
            ret $0 # NOTE (Lapys) -> Return from main entry routine. -> EXIT_SUCCESS
