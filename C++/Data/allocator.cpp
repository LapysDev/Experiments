/* Import */
#if defined(__APPLE__) || defined(__bsdi__) || defined(__CYGWIN__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__gnu_linux__) || defined(__linux) || defined(__linux__) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(linux) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
# include <pthread.h>
# include <unistd.h>

pthread_t ::pthread_self()
#elif defined(__NT__) || defined(__TOS_WIN__) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN16) || defined(_WIN32) || defined(_WIN32_WCE) || defined(_WIN64)
# include <windows.h>
DWORD ::GetCurrentThreadId()
#endif

// // Fixed-size allocations are sorted in buckets, not generalized
// // `Memory::allocate(…)` evaluates to `class MemoryBuffer` which decays to a pointer — there´s also `Memory::instantiate<>(…)`
// // Page align for bigger allocation blocks
// #include <climits>
// #include <cstddef>
// #include <cstdio>
// #include <cstdlib>
// #include <new>
// #include <stdint.h>
// #ifdef _MSVC_LANG
// # if _MSVC_LANG >= 202002L
// #   include <version>
// # endif
// #elif __cplusplus >= 202002L
// # include <version>
// #elif defined(__clang__) || defined(__CUDACC_VER_BUILD__) || defined(__CUDACC_VER_MAJOR__) || defined(__CUDACC_VER_MINOR__) || defined(__GNUC__) || defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER) || defined(__NVCC__) || defined(__NVCOMPILER)
// # include <version>
// #endif

// #if defined(__APPLE__) || defined(__bsdi__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
// # include <stdlib.h>             // -->   ::aligned_alloc(...), ::free(...), ::memalign(...), ::posix_memalign(...), ::realloc(...)
// #elif defined(_MSC_VER)          //
// # include <malloc.h>             // -->   ::_aligned_free(...), ::_aligned_malloc(...), ::_aligned_realloc(...)
// #elif __cplusplus >= 201703L     // ->> With `_MSC_VER` not defined, a `_MSVC_LANG` check becomes unnecessary
// # include <cstdlib>              // -->   std::aligned_alloc(...), std::free(...), std::realloc(...)
// #elif defined(__cpp_aligned_new) // --> 201606L
// # include <new>                  // -->   ::delete(...), ::new(...)
// #else                            //
// # include <cstdlib>              // -->   std::free(...), std::malloc(...), std::realloc(...)
// # include <memory>               // -->   std::align(...)
// # include <stddef.h>             // -->   ::max_align_t
// #endif

// /* Class > Memory ->> `uintptr_t` must be defined */
// // Can `MemoryMetadata` size be ignored for certain `MemoryBucket`s?
// class Memory /* final */ {
//   public:
//     // ... ->> Array of `MemoryBucket`s
//     class MemoryAllocator /* final */ {
//       private:
//         MemoryBucket  bucket; // --> ::size == 1zu
//         MemoryBucket *buckets;
//         std::size_t   capacity;
//         std::size_t   length;

//       public:
//         /* constexpr */ inline MemoryAllocator() /* noexcept */ {}
//     };

//     // ... ->> View into contiguous storage
//     template <typename base = void>
//     class MemoryBuffer /* final */ {
//       public:
//         base       *value; // ->> Storage address
//         std::size_t size;  // ->> Storage address capacity

//         /* ... */
//         /* constexpr */ inline MemoryBuffer(base* const value, std::size_t const size) /* noexcept */ :
//           value(value),
//           size (size)
//         {}

//         /* constexpr */ inline MemoryBuffer(void const volatile* const value, std::size_t const size) /* noexcept */ :
//           value(NULL != value ? static_cast<base*>(const_cast<void*>(value)) : NULL),
//           size (size)
//         {}

//         /* ... */
//         inline operator base               *() const /* noexcept */ { return this -> value; }
//         inline operator base const         *() const /* noexcept */ { return this -> value; }
//         inline operator base const volatile*() const /* noexcept */ { return this -> value; }
//         inline operator base       volatile*() const /* noexcept */ { return this -> value; }

//         template <typename type>
//         inline operator type*() const /* noexcept */ {
//           return static_cast<type*>(static_cast<void*>(this -> value));
//         }
//     };

//     template <typename base> class MemoryBuffer<base const>          /* final */ : public MemoryBuffer<base> {};
//     template <typename base> class MemoryBuffer<base const volatile> /* final */ : public MemoryBuffer<base> {};
//     template <typename base> class MemoryBuffer<base volatile>       /* final */ : public MemoryBuffer<base> {};

//   private:
//     // ... ->> Array of similarly aligned allocations provided using `Memory::allocate(...)` (or `Memory::reallocate(...)`)
//     class MemoryBucket /* final */ {
//       friend class Memory;

//       /* ... */
//       void       *value;     //
//       std::size_t capacity;  // ->> Size      of array
//       std::size_t size;      // ->> Size      of allocated objects
//       std::size_t alignment; // ->> Alignment of allocated objects
//       uintptr_t   former;    // ->> Alternate (and safely persistent) representation of `MemoryBucket::value` prior to its modification
//     };

//     // ... ->> Information on allocated storage provided using `Memory::allocate(...)` (or `Memory::reallocate(...)`)
//     class MemoryMetadata /* final */ {
//       friend class Memory;

//       /* ... */
//     };

//     /* ... */
//     static MemoryAllocator allocator;
// };

// MemoryAllocator{}.allocate(420u, alignof(int));
// Memory::allocator.allocate(420u, alignof(int));
// Memory::          allocate(420u, alignof(int));
// MemoryAllocator{}.instantiate<int>(...);
// Memory::allocator.instantiate<int>(...);
// Memory::          instantiate<int>(...);

// class Memory /* final */ {
//     // ... ->> Information on `MemoryBuffer` (allocated storage) provided using `Memory::allocate(...)` (or `Memory::reallocate(...)`)
//     class MemoryMetadata /* final */ {
//       friend class Memory;

//       /* ... */
//       std::size_t    size;     // ->> Size of (overall) storage
//       std::ptrdiff_t offset;   // ->> Number of bytes ahead of starting address of storage or preceding `MemoryMetadata`
//       bool           preceded; // ->> `MemoryMetadata` has a preceding `MemoryMetadata`
//       bool           reserved; // ->> Storage is re-usable

//       /* ... */
//       // ... ->> Start of storage address range this `MemoryMetadata` represents
//       /* constexpr */ inline unsigned char const* begin() const /* noexcept */ {
//         MemoryMetadata const &metadata = this -> get();
//         return reinterpret_cast<unsigned char const*>(&metadata) - metadata.offset;
//       }

//       // ... ->> Determines if `MemoryMetadata` can be stored within allocated storage
//       /* constexpr */ inline static bool canInstall(std::size_t const space, std::size_t const size) /* noexcept */ {
//         return 0u != space && size <= SIZE_MAX - space;
//       }

//       // ... ->> End of storage address range this `MemoryMetadata` represents
//       /* constexpr */ inline unsigned char const* end() const /* noexcept */ {
//         MemoryMetadata const &metadata = this -> get();
//         return (reinterpret_cast<unsigned char const*>(&metadata) - metadata.offset) + metadata.size;
//       }

//       // ... ->> Traverse sparse lists of `MemoryMetadata` instances
//       /* constexpr */ inline MemoryMetadata const& get() const /* noexcept */ {
//         MemoryMetadata const *metadata = this;

//         // ...
//         while (metadata -> preceded)
//         metadata =
//           #ifdef __cpp_lib_launder // --> 201606L
//             std::launder
//           #endif
//         (reinterpret_cast<MemoryMetadata const*>(reinterpret_cast<unsigned char const*>(metadata) - metadata -> offset));

//         // ...
//         return *metadata;
//       }

//       // ... --> alignof MemoryMetadata
//       /* constexpr */ inline static std::size_t getAlignment() /* noexcept */ {
//         return
//           #if defined(_MSVC_LANG) || __cplusplus >= 201103L
//             alignof(MemoryMetadata)
//           #else
//             sizeof(MemoryMetadata)
//           #endif
//         ;
//       }

//       // ... ->> Retrieve `MemoryMetadata` from `address` evaluated from `Memory::allocate(...)` (or `Memory::reallocate(...)`)
//       inline static MemoryMetadata* getInstall(void* const address) /* noexcept */ {
//         for (unsigned char *iterator = static_cast<unsigned char*>(address) - sizeof(MemoryMetadata); ; --iterator)
//         if (0u == (static_cast<unsigned char*>(address) - iterator) % MemoryMetadata::getAlignment()) {
//           return (MemoryMetadata*) &
//             #ifdef __cpp_lib_launder // --> 201606L
//               std::launder
//             #endif
//           (reinterpret_cast<MemoryMetadata*>(iterator)) -> get();
//         }
//       }

//       // ... ->> Retrieve `MemoryMetadata` from `MemoryBucket::value`
//       inline static MemoryMetadata* getInstall(void* const bucket, void* const bucketEnd) /* noexcept */ {
//         for (unsigned char *iterator = static_cast<unsigned char*>(bucket); iterator != static_cast<unsigned char*>(bucketEnd); ++iterator)
//         if (0u == (bucket -> alignment + (iterator - static_cast<unsigned char*>(bucket))) % MemoryMetadata::getAlignment()) {
//           return (MemoryMetadata*) &
//             #ifdef __cpp_lib_launder // --> 201606L
//               std::launder
//             #endif
//           (reinterpret_cast<MemoryMetadata*>(iterator)) -> get();
//         }

//         return NULL;
//       }

//       // ... ->> Estimates space required to store `MemoryMetadata` within theoretically infinite storage of specific `alignment`;
//       //         Evaluates to `0zu` if the space required is not representable within a `std::size_t`
//       /* constexpr */ inline static std::size_t getInstallSpace(std::size_t const alignment, bool const bucketed) /* noexcept */ {
//         std::size_t const padding = alignment > MemoryMetadata::getAlignment() ? MemoryMetadata::getAlignment() - alignment : alignment - MemoryMetadata::getAlignment();
//         std::size_t const size    = sizeof(MemoryMetadata) * (bucketed + 1u);
//         std::size_t const space   = padding + size;

//         // ...
//         if (padding > SIZE_MAX - size)
//         return 0u;

//         if (alignment >= space)
//         return alignment;

//         if (
//           SIZE_MAX             == space / alignment
//           SIZE_MAX - alignment < (space / alignment) * alignment
//         ) return 0u;

//         // ...
//         return alignment * ((space / alignment) + 1u);
//       }

//       // ... ->> Stores a `MemoryMetadata` (or two when `bucketed`) object(s) within allocated storage
//       inline static void* install(std::size_t const space, void* const address, std::size_t const size, std::size_t const alignment, bool const bucketed) /* noexcept */ {
//         if (NULL == address)
//         return NULL;

//         /* ... */
//         unsigned char *const subaddress           = static_cast<unsigned char*>(address) + space;
//         unsigned char       *metadataAddresses[2] = {static_cast<unsigned char*>(address), subaddress - sizeof(MemoryMetadata)};
//         MemoryMetadata      *metadata;

//         // ... ->> Search for suitably-aligned address from the start of `address` and preceding the start of `subaddress`
//         while (0u != (alignment + (metadataAddresses[0] - static_cast<unsigned char*>(address))) % MemoryMetadata::getAlignment()) ++metadataAddresses[0];
//         while (0u != (alignment + (subaddress           - metadataAddresses[1]))                 % MemoryMetadata::getAlignment()) --metadataAddresses[1];

//         // ... ->> Allocate (or install) `MemoryMetadata` objects onto provided `address`
//         if (bucketed || metadataAddresses[0] < metadataAddresses[1]) {
//           metadata             = ::new (metadataAddresses[1]) MemoryMetadata();
//           metadata -> offset   = metadataAddresses[1] - metadataAddresses[0];
//           metadata -> preceded = true;
//         }

//         metadata             = ::new (*metadataAddresses) MemoryMetadata();
//         metadata -> offset   = *metadataAddresses - static_cast<unsigned char*>(address);
//         metadata -> preceded = false;
//         metadata -> reserved = true;
//         metadata -> size     = size + space;

//         // ...
//         return subaddress;
//       }
//     };

//     /* ... */
//     static MemoryBucket *buckets;
//     static std::size_t   bucketsCapacity;
//     static std::size_t   bucketsLength;

//     /* ... */
//     static MemoryBuffer<unsigned char> allocate(std::size_t const count, std::size_t const size, std::size_t const alignment) /* noexcept */ {
//       MemoryBucket *bucket          = NULL;
//       bool const    bucketResizable =
//         #if __cplusplus >= 201703L || defined(_MSC_VER) || (defined(__APPLE__) || defined(__bsdi__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS))
//           true
//         #else
//           false
//         #endif
//       ;

//       // ... ->> Assert `alignment` is a power of two
//       for (std::size_t value = 1u; alignment != value; value *= 2u)
//       if (alignment < value) return MemoryBuffer<unsigned char>(NULL, 0u);

//       // ... ->> Assert `count` is non-zero
//       if (0u == count)
//       return MemoryBuffer<unsigned char>(NULL, 0u);

//       // ... ->> Only use `MemoryBucket`s if their allocations can be resized
//       if (bucketResizable) {
//         // ... ->> Acquire a `MemoryBucket` of compatible `alignment`
//         for (MemoryBucket *iterator = Memory::buckets + Memory::bucketsLength; iterator != Memory::buckets; ) {
//           MemoryBucket *const subbucket =
//             #ifdef __cpp_lib_launder // --> 201606L
//               std::launder
//             #endif
//           (--iterator);

//           // ...
//           if (0u == subbucket -> alignment % alignment && subbucket -> size == count) {
//             bucket = subbucket;
//             break;
//           }
//         }

//         // ... ->> Otherwise allocate a `new MemoryBucket`
//         if (NULL == bucket) {
//           if (Memory::bucketsCapacity == Memory::bucketsLength) {
//             void       *allocation = NULL;
//             std::size_t length     = 0u == Memory::bucketsLength ? 1u : Memory::bucketsLength;

//             // ...
//             for (; NULL == allocation && 0u != length; length /= 2u) {
//               if (Memory::bucketsLength > (SIZE_MAX - 1u) - length) continue; // --> Memory::bucketsCapacity < SIZE_MAX - 1u ->> `... - 1u` because `-1zu` carries distinct meaning
//               allocation = NULL == Memory::buckets ? std::malloc((length + Memory::bucketsLength) * sizeof(MemoryBucket)) : std::realloc(Memory::buckets, (length + Memory::bucketsLength) * sizeof(MemoryBucket));
//             }

//             if (NULL != allocation) {
//               Memory::bucketsCapacity = length + Memory::bucketsLength;
//               Memory::buckets        = static_cast<MemoryBucket*>(allocation);

//               // ... ->> Scrub the allocation of possible prior data (ideally optimized to a `memset` operation)
//               for (unsigned char
//                 *iterator  = static_cast<unsigned char*>(allocation) + (Memory::bucketsLength   * sizeof(MemoryBucket)),
//                 *const end = static_cast<unsigned char*>(allocation) + (Memory::bucketsCapacity * sizeof(MemoryBucket))
//               ; iterator != end; ) {
//                 if (sizeof(uintmax_t) <= static_cast<std::size_t>(end - iterator)) {
//                   (void) ::new (iterator) uintmax_t(0u);
//                   iterator += sizeof(uintmax_t);

//                   continue;
//                 }

//                 *(iterator++) = 0x00u;
//               }
//             }
//           }

//           if (NULL != Memory::buckets) {
//             bucket              = ::new (Memory::bucketsLength++ + Memory::buckets) MemoryBucket();
//             bucket -> alignment = alignment;
//             bucket -> capacity  = 0u;
//             bucket -> former    = reinterpret_cast<uintptr_t>(static_cast<void*>(NULL));
//             bucket -> size      = size;
//             bucket -> value     = NULL;
//           }
//         }
//       }

//       // ... ->> Allocate `MemoryBuffer` onto a compatible `MemoryBucket`
//       if (NULL != bucket) {
//         if (NULL == bucket -> value) {
//           MemoryBuffer<unsigned char> const buffer = Memory::allocator(count, bucket -> alignment, true);

//           // ...
//           bucket -> capacity = buffer.size;
//           bucket -> value    = buffer.value;

//           // ...
//           return buffer;
//         }

//         /* ... ->> Re-use `MemoryBuffer` of a compatible `MemoryBucket` */
//         void           *bucketReallocation         = NULL;
//         std::size_t     bucketReallocationCapacity = bucket -> capacity;
//         uintptr_t const bucketValue                = reinterpret_cast<uintptr_t>(bucket -> value);

//         // ... ->> Find non-`MemoryMetadata::reserved` `MemoryBuffer`
//         for (MemoryMetadata *metadata = reinterpret_cast<MemoryMetadata*>(bucket -> value); ; metadata = (MemoryMetadata*) metadata -> end()) {
//           metadata = MemoryMetadata::getInstall((void*) metadata, bucket -> value + bucket -> capacity);
//           if (NULL == metadata) break;

//           if (false == metadata -> reserved) {
//             //
//             break;
//           }
//         }

//         bucket -> capacity

//         for (; NULL == bucketReallocation && 0u != bucketReallocationCapacity; bucketReallocationCapacity /= 2u) {
//           if (bucket -> capacity > SIZE_MAX - bucketReallocationCapacity) continue;
//           bucketReallocation =
//             #if defined(__APPLE__) || defined(__bsdi__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
//               ::realloc(bucket -> value, bucketReallocationCapacity + bucket -> capacity)
//             #elif defined(_MSC_VER)
//               ::_aligned_realloc(bucket -> value, bucketReallocationCapacity + bucket -> capacity, bucket -> alignment)
//             #else
//               std::realloc(bucket -> value, bucketReallocationCapacity + bucket -> capacity)
//             #endif
//           ;
//         }

//         if (NULL != bucketReallocation) {
//           if (
//             bucketValue     != reinterpret_cast<uintptr_t>(bucketReallocation) || // ->> Partial                                    guarantee that reallocation moved storage
//             bucket -> value != bucketReallocation                                 // ->> Full (but possibly behaviorally undefined) guarantee that reallocation moved storage
//           ) bucket -> former = bucketValue;

//           bucket -> value + bucket -> capacity;
//           bucket -> capacity += bucketReallocationCapacity;

//           [][content]
//           []..[][content][]..[][content]
//           MemoryBuffer<unsigned char> const buffer = Memory::reallocator(bucket -> value, bucket -> capacity + size, alignment, true);

//           // ...
//           bucket -> capacity = buffer.size;
//           bucket -> value    = buffer.value;

//           // ...
//           return bucket -> value;
//         }
//       }

//       // ... ->> Allocate `MemoryBuffer` stand-alone if there's no available `MemoryBucket` (incompatible `alignment`, out-of-memory allocation, or non-resizable allocation)
//       return Memory::allocator(count, alignment, false);
//     }

//   /* ... */
//   public:
//     // ... ->> Allocate `size` bytes of bounded `alignment`
//     static MemoryBuffer<unsigned char> allocate(std::size_t const size, std::size_t const alignment) /* noexcept */ {
//       return Memory::allocate(size, sizeof(unsigned char), alignment);
//     }

//     // ...
//     static bool deallocate(void* const) /* noexcept */ {
//       return true;
//     }

//     // ...
//     template <typename type>
//     type instantiate(type const& copy) /* noexcept */ {
//       void *const allocation =
//         #if defined(_MSVC_LANG) || __cplusplus >= 201103L
//           Memory::allocate(sizeof(type), alignof(type))
//         #else
//           Memory::allocate(sizeof(type), sizeof(type))
//         #endif
//       ;

//       // ...
//       return NULL != allocation : ::new (allocation) type(copy) : NULL;
//     }

//     // ...
//     static MemoryBuffer<unsigned char> reallocate(void* const, std::size_t const, std::size_t const) /* noexcept */ {
//       return MemoryBuffer<unsigned char>(NULL, 0u);
//     }

//   private:
//     static MemoryBuffer<> allocator  (std::size_t, std::size_t, bool const);
//     static bool           deallocator(void*);
//     static void*          reallocator(void*, std::size_t, std::size_t, bool const);
// };
//   Memory::MemoryBucket *Memory::buckets         = NULL;
//   std::size_t           Memory::bucketsCapacity = 0u;
//   std::size_t           Memory::bucketsLength   = 0u;

// // ... ->> Defines `allocate(...)`, `deallocate(...)`, and `reallocate(...)` functions in the design of `std::aligned_alloc(...)`
// #if defined(__APPLE__) || defined(__bsdi__) || defined(__DragonFly__) || defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || defined(__FreeBSD__) || defined(__FreeBSD_version) || defined(__MACH__) || defined(__NETBSD__) || defined(__NETBSD_version) || defined(__OpenBSD__) || defined(__OS400__) || defined(__QNX__) || defined(__QNXNTO__) || defined(__sun) || defined(__SVR4) || defined(__svr4__) || defined(__sysv__) || defined(__unix) || defined(__unix__) || defined(__VMS) || defined(__VMS_VER) || defined(_NTO_VERSION) || defined(_POSIX_SOURCE) || defined(_SYSTYPE_SVR4) || defined(_XOPEN_SOURCE) || defined(NetBSD0_8) || defined(NetBSD0_9) || defined(NetBSD1_0) || defined(OpenBSD2_0) || defined(OpenBSD2_1) || defined(OpenBSD2_2) || defined(OpenBSD2_3) || defined(OpenBSD2_4) || defined(OpenBSD2_5) || defined(OpenBSD2_6) || defined(OpenBSD2_7) || defined(OpenBSD2_8) || defined(OpenBSD2_9) || defined(OpenBSD3_0) || defined(OpenBSD3_1) || defined(OpenBSD3_2) || defined(OpenBSD3_3) || defined(OpenBSD3_4) || defined(OpenBSD3_5) || defined(OpenBSD3_6) || defined(OpenBSD3_7) || defined(OpenBSD3_8) || defined(OpenBSD3_9) || defined(OpenBSD4_0) || defined(OpenBSD4_1) || defined(OpenBSD4_2) || defined(OpenBSD4_3) || defined(OpenBSD4_4) || defined(OpenBSD4_5) || defined(OpenBSD4_6) || defined(OpenBSD4_7) || defined(OpenBSD4_8) || defined(OpenBSD4_9) || defined(sun) || defined(unix) || defined(VMS)
// # if _ISOC11_SOURCE
//     MemoryBuffer<unsigned char> Memory::allocator(std::size_t const size, std::size_t const alignment, bool const bucketed) /* noexcept */ {
//       std::size_t const space = MemoryMetadata::getInstallSpace(alignment, bucketed);
//       return MemoryMetadata::canInstall(space, size) && 0u == (size + space) % alignment ? MemoryMetadata::install(space, ::aligned_alloc(alignment, size + space), size, alignment, bucketed) : NULL;
//     }

//     // ...
//     void Memory::deallocator(void* const address) /* noexcept */ {
//       if (NULL == address)
//       return NULL;

//       reinterpret_cast<MemoryMetadata*>(address) - 1
//       ::free(address);
//     }

//     // ...
//     void* Memory::reallocator(void* const address, std::size_t const size, std::size_t const alignment) /* noexcept */ {}

//     ::aligned_alloc(std::size_t alignment, std::size_t size); // ->> `alignment` must be a power of two and `size` should be a multiple of `alignment`
//     ::realloc(void* address, std::size_t size);               // ->> Possibly moves
//     ::free(void* address);
// # elif _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
//     ::posix_memalign(void** pointer, std::size_t alignment, std::size_t size); // `alignment` must be a power of two and a multiple of `sizeof void*`
//     ::realloc(void* address, std::size_t size);                                // ->> This allowed?
//     ::free(void* address);
// # else
// #   include <malloc.h>
//     ::memalign(std::size_t alignment, std::size_t size); // ->> `alignment` must be a power of two
//     ::realloc(void* address, std::size_t size);          // ->> This allowed?
//     ::free(void* address);
// # endif
// #elif (defined(__ICC) || defined(__INTEL_COMPILER) || defined(__INTEL_LLVM_COMPILER)) && /* ->> Not ICX (Intel oneAPI C++ Compiler) */ false == defined(__clang__)
//   _mm_malloc(size, alignment);
//   _mm_free(address);
// #elif defined(_MSC_VER)
//   ::_aligned_malloc(std::size_t size, std::size_t alignment);
//   ::_aligned_realloc(void* address, std::size_t size, std::size_t alignment); // ->> Possibly moves
//   ::_aligned_free(void* address);
// #elif __cplusplus >= 201703L // ->> With `_MSC_VER` undefined, `_MSVC_LANG` check becomes unnecessary
//   std::aligned_alloc(std::size_t alignment, std::size_t size);
//   std::realloc(void* address, std::size_t size); // ->> Possibly moves
//   std::free(void* address);
// #elif defined(__cpp_aligned_new) // --> 201606L
//   ::new(std::size_t size, std::align_val_t alignment, std::nothrow_t const&);
//   ::delete(void* address, std::align_val_t alignment, std::nothrow_t const&);
// #else
//   std::malloc(std::size_t size);
//   // ->> Use stack allocator first
//   // ->> Align with `std::align(…)` or manual byte-shifting for `alignment < alignof ::max_align_t`
//   // ->> Do not align on `0`
//   // --> alignof ::max_align_t % alignment
//   // --> max(sizeof uintmax_t, sizeof long double, sizeof void*, sizeof void (*)()) % alignment
// #endif

// /* Main */
// int main(int, char*[]) /* noexcept */ {}
