#pragma once

#include <cstddef>
#include <functional>

struct GridPosition {
    int x;
    int y;

    bool operator==(const GridPosition&) const = default;
};

template <>
struct std::hash<GridPosition> {
    std::size_t operator()(const GridPosition& position) const noexcept {
        const std::size_t xHash = std::hash<int>{}(position.x);
        const std::size_t yHash = std::hash<int>{}(position.y);
        return xHash ^ (yHash + 0x9e3779b9U + (xHash << 6) + (xHash >> 2));
    }
};