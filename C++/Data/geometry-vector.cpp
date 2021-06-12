#include <cstdio>

/* ... */
template <typename, unsigned char, bool = false> struct Vector;

template <typename type> struct Vector<type, 0u, false> {};
template <typename type> struct Vector<type, 0u, true> {};

template <typename type, unsigned char size> struct Vector<type, size, false> : Vector<type, size - 1u, 1> { type data[size]; };
template <typename type, unsigned char size> struct Vector<type, size, true> : Vector<type, size - 1u, 1> {};

template <typename type> struct Vector<type, 1u, false>                          { union { type data[1]; union { type x; }; }; };
template <typename type> struct Vector<type, 2u, false> : Vector<type, 1u, true> { union { type data[2]; union { type x, y; }; }; };
template <typename type> struct Vector<type, 3u, false> : Vector<type, 2u, true> { union { type data[3]; union { type x, y, z; }; }; };
template <typename type> struct Vector<type, 4u, false> : Vector<type, 3u, true> { union { type data[4]; union { type x, y, z, w; }; }; };

// ...
template <typename type> struct Vector1D : Vector<type, 1u> {};
template <typename type> struct Vector2D : Vector<type, 2u> {};
template <typename type> struct Vector3D : Vector<type, 3u> {};
template <typename type> struct Vector4D : Vector<type, 4u> {};

/* Main */
int main(void) {
  std::printf("[1]: %i"             "\r\n",                                                          Vector1D<int>().x);
  std::printf("[2]: %i, %i"         "\r\n",                                       Vector2D<int>().x, Vector2D<int>().y);
  std::printf("[3]: %i, %i, %i"     "\r\n",                    Vector3D<int>().x, Vector3D<int>().y, Vector3D<int>().z);
  std::printf("[4]: %i, %i, %i, %i" "\r\n", Vector4D<int>().x, Vector4D<int>().y, Vector4D<int>().z, Vector4D<int>().w);

  typedef Vector<int, 4u> Vector5Di;
  std::printf("[5]: %i, %i, %i, %i, %i", Vector5Di().data[0], Vector5Di().data[1], Vector5Di().data[2], Vector5Di().data[3], Vector5Di().data[4]);
}
