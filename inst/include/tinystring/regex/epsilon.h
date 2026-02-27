#pragma once

#include <cstddef>
#include <functional>


const std::function<bool(const std::byte&)> EPSILON = [](const std::byte&) -> bool {
    return false;
};
