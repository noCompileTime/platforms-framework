#include <core/platform.hpp>
#include <core/window_manager.hpp>

auto main() -> int32_t
{
                 auto window_closed { false };
    core::window_size window_size;
                      window_size.resize(2048, 1024);

    const auto factory = core::Platform::create_factory();

    core::WindowManager::instance().init(factory, { { "Platforms Framework", window_size }, { } });
    core::WindowManager::instance().window_events().on_close = [&window_closed]
    {
        window_closed = true;
    };

    core::WindowManager::instance().window().show();

    while (!window_closed)
    {
        core::WindowManager::instance().update();
    }

    core::WindowManager::instance().release();

    return 0;
}