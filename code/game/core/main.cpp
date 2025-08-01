#include <core/platform.hpp>

auto main() -> int
{
    auto window = core::Platform::create_factory()->create_window();

    window->create({ }, { });
    window->show();

    window->destroy();

    return 0;
}