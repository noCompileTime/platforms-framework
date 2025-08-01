#include <core/platform.hpp>

auto main() -> int
{
    const auto factory = core::Platform::create_factory();

    const auto window  = factory->create_window();

    window->create({ }, { });
    window->show();

    window->destroy();

    return 0;
}