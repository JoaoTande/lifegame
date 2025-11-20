#include <chrono>

class FPSCounter {
public:
    FPSCounter();
    void frameRendered();
    bool update();
    int getFPS() const;

private:
    int frameCount = 0;
    int fps = 0;
    std::chrono::high_resolution_clock::time_point lastTime;
};
