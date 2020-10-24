#include <stdio.h>

typedef int coord_t;
union Coords1D { coord_t points[1]; struct { coord_t x; }; };
union Coords2D { coord_t points[2]; struct { coord_t x, y; }; };
union Coords3D { coord_t points[3]; struct { coord_t x, y, z; }; };
union Coords4D { coord_t points[4]; struct { coord_t x, y, z, w; }; };

int main(void) {
  constexpr Coords1D point = {0};
  constexpr Coords2D area = {1, 2};
  constexpr Coords3D volume = {3, 4, 5};
  constexpr Coords4D space = {6, 7, 8, 9};

  ::printf("[1D]: (%zu) {%i}" "\n",             sizeof(Coords1D), point.x);
  ::printf("[2D]: (%zu) {%i, %i}" "\n",         sizeof(Coords2D), area.x, area.y);
  ::printf("[3D]: (%zu) {%i, %i, %i}" "\n",     sizeof(Coords3D), volume.x, volume.y, volume.z);
  ::printf("[4D]: (%zu) {%i, %i, %i, %i}" "\n", sizeof(Coords4D), space.x, space.y, space.z, space.w);
}
