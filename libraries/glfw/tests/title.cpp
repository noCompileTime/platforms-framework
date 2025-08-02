//========================================================================
// UTF-8 window title test
// Copyright (c) Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//
// This test sets a UTF-8 window title
//
//========================================================================

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include <opengl/commands.hpp>
#include <opengl/functions.hpp>

#include <opengl/constants/commands.hpp>

auto main() -> int
{
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    const auto window = glfwCreateWindow(400, 400, "English 日本語 русский язык 官話", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    opengl::Functions::init();

    while (!glfwWindowShouldClose(window))
    {
        opengl::Commands::clear(opengl::constants::color_buffer);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}