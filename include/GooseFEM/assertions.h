/**
\file
\copyright Copyright 2017. Tom de Geus. All rights reserved.
\license This project is released under the GNU Public License (GPLv3).
*/

#ifndef GOOSEFEM_ASSERTIONS_H
#define GOOSEFEM_ASSERTIONS_H

#include "config.h"

namespace GooseFEM {

/**
Returns true is a list is unique (has not duplicate items).
\param arg Array-like.
\return `true` if `arg` is unique.
*/
template <class T>
inline bool is_unique(const T& arg)
{
    array_type::tensor<typename T::value_type, 1> flat = xt::ravel(arg);
    array_type::tensor<typename T::value_type, 1> unique = xt::unique(flat);
    array_type::tensor<typename T::value_type, 1> sorted = xt::sort(flat);

    if (unique.size() != sorted.size()) {
        return false;
    }

    return xt::all(xt::equal(unique, sorted));
}

} // namespace GooseFEM

#endif
