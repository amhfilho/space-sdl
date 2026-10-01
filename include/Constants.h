#pragma once

namespace   Constants {
    namespace Window {
        inline constexpr const char* Title = "SDL3 Space Invaders";
        inline constexpr int Width = 800;
        inline constexpr int Height = 800;
    }

namespace Space {
        inline constexpr float Height = Window::Height - 100.0f;
    }

    namespace Ship {
        inline constexpr float BaseWidth = 50.0f;
        inline constexpr float BaseHeight = 10.0f;
        // Bottom middle of the window (position is the top-left of the base)
        inline constexpr float BaseStartX = (Window::Width - BaseWidth) / 2.0f;
        inline constexpr float BaseStartY = Space::Height - BaseHeight;
        inline constexpr float PartHeight = 5.0f;
        inline constexpr float ShipHeight = PartHeight * 6;
        inline constexpr float Speed = 250.0f; // pixels per second
    }


    namespace Laser {
        inline constexpr float Width = 2.0f;
        inline constexpr float Height = 10.0f;
        inline constexpr float Speed = 600.0f; // pixels per second
    }

    namespace Block {
        inline constexpr float Width = 3.0f;
        inline constexpr float Height = 3.0f;
    }

    namespace Obstacle {
        inline constexpr float Bottom = Window::Height - (19 * Block::Height) ;
    }

    namespace Alien {
        inline constexpr float Width = 38.0f;
        inline constexpr float Height = 34.0f;
        //inline constexpr float Speed = 50.0f; // pixels per second
    }
}
