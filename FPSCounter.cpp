#include "FPSCounter.h"

    FPSCounter::FPSCounter() {
        lastTime = std::chrono::high_resolution_clock::now();
        frameCount = 0;
        fps = 0;
    }

    void FPSCounter::frameRendered() {
        frameCount++;
    }

    bool FPSCounter::update() {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();

        if (elapsed >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastTime = now;
            return true; // fps updated
        }
        return false;
    }

    int FPSCounter::getFPS() const {
        return fps;
    }
