template <int... n>
void put() { put<n..., n...>(); }

int main() {
  put<0>();
}
