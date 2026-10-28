#pragma once

#include <atomic>
#include <cstddef>

struct SharedState {
    std::atomic<size_t> numCrossingSago2MonkeyGrass;
    std::atomic<size_t> numCrossingMonkeyGrass2Sago;
    std::atomic<bool> debug;
    std::atomic<bool> running;
};

