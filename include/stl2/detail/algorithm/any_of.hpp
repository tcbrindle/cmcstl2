// cmcstl2 - A concept-enabled C++ standard library
//
//  Copyright Andrew Sutton 2014
//  Copyright Gonzalo Brito Gadeschi 2014
//  Copyright Casey Carter 2015
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/caseycarter/cmcstl2
//
#ifndef STL2_DETAIL_ALGORITHM_ANY_OF_HPP
#define STL2_DETAIL_ALGORITHM_ANY_OF_HPP

#include <stl2/detail/concepts/callable.hpp>
#include <stl2/detail/range/concepts.hpp>

////////////////////////////////////////////////////////////////////////////////
// any_of [alg.any_of]
//
STL2_OPEN_NAMESPACE {
	struct __any_of_fn : private __niebloid {
		template<input_iterator I, sentinel_for<I> S, class Proj = identity,
			indirect_unary_predicate<projected<I, Proj>> Pred>
		constexpr bool operator()(I first, S last, Pred pred, Proj proj = {}) const {
			for (; first != last; ++first) {
				if (__stl2::invoke(pred, __stl2::invoke(proj, *first))) {
					return true;
				}
			}
			return false;
		}

		template<input_range R, class Proj = identity,
			indirect_unary_predicate<projected<iterator_t<R>, Proj>> Pred>
		constexpr bool operator()(R&& rng, Pred pred, Proj proj = {}) const {
			return (*this)(begin(rng), end(rng), __stl2::ref(pred), __stl2::ref(proj));
		}
	};

	inline constexpr __any_of_fn any_of {};
} STL2_CLOSE_NAMESPACE

#endif
