#ifndef TEST_GENERATOR_METAFUNCTIONS_H
#define TEST_GENERATOR_METAFUNCTIONS_H

#include <type_traits>
#include <random>

namespace tg::mtf {

template <bool Condition, typename Then, typename Else>
struct If;

template <typename Then, typename Else>
struct If<true, Then, Else> {
  using type = Then;
};

template <typename Then, typename Else>
struct If<false, Then, Else> {
  using type = Else;
};

template <typename T>
using distribution_type =
        typename If<std::is_floating_point_v<T>,
                std::uniform_real_distribution<>,
                std::uniform_int_distribution<>>::type;

}

#endif //TEST_GENERATOR_METAFUNCTIONS_H
