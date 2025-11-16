#pragma once

namespace cosmos
{
	namespace utils
	{
		struct Color
		{
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a = 255;

			static const Color BLACK;
			static const Color RED;
			static const Color GREEN;
			static const Color BLUE;
			static const Color WHITE;
		};

		inline const Color Color::BLACK = { 0, 0, 0, 0 };
		inline const Color Color::RED = { 255, 0, 0, 255 };
		inline const Color Color::GREEN = { 0, 255, 0, 255 };
		inline const Color Color::BLUE = { 0, 0, 255, 255 };
		inline const Color Color::WHITE = { 255, 255, 255, 255 };

	}
}