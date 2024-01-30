// Counter class with a friend function that we are going to
// define as the templates get instanciated
template <int i>
struct Counter {
    friend auto count(Counter<i>);
};

// Check if the `count` function was defined for a specfied integer value
// Here we have to rely on SFINAE - GCC throws an error if the value for the
// same concept changes between instantiations - and it will in this case
template <typename Who, int cnt, typename = int>
struct CountedTo { static constexpr bool value = false; };
template <typename Who, int cnt>
struct CountedTo<Who, cnt, decltype(count(Counter<cnt>{}))>
{ static constexpr bool value = true; };

// This class is needed only to check that our code works
template <int line, int cnt, typename = int>
struct CountedAt { static constexpr bool value = false; };
template <int line, int cnt>
struct CountedAt<line, cnt, decltype(count(Counter<cnt>{}))>
{ static constexpr bool value = true; };

// `Who` and `line` parameters are needed because for different template arguments
// and at different places in the source code the amount of available `count` overloads
// may be different - and we need to reinstantiate the class!

// Instantiating this class will increase the counter by one!
template <typename Source, int start = 0>
struct Increase { using Type = Increase<Source, start + 1>::Type; };
template <typename Source, int start>
requires ( !CountedTo<Source, start>::value )
struct Increase<Source, start>
{ using Type = void; friend auto count(Counter<start>) { return 0; } };

// Get counter value. You can put any unique value in `line` - but you might as well
// use __LINE__ :)
template <int line, int start = 0>
struct GetCount {
    static constexpr auto count = GetCount<line, start + 1>::count;
};
template <int line, int start>
requires ( !CountedAt<line, start>::value )
struct GetCount<line, start> {
    static constexpr auto count = start;
};

// It works! Every time we instantiate the template, the counter increases
// by one!
static_assert(GetCount<__LINE__>::count == 0);
template struct Increase<void>;
static_assert(GetCount<__LINE__>::count == 1);
template struct Increase<int>;
static_assert(GetCount<__LINE__>::count == 2);
template struct Increase<float>;
static_assert(GetCount<__LINE__>::count == 3);

int main() { return 0; }
