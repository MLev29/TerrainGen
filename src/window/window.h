#pragma once

#include "LibMath/vector/Vector2.h"
#include "LibMath/VariableType.hpp"

#include <string>

struct GLFWwindow;

namespace src
{
	class Window
	{
		public:
			Window(void) = delete;
			Window(const char* wndName, int const width, int const height);
			~Window(void);

			
			template <math::math_type::NumericType Type>
			math::Vector2<Type> GetSize(void) const noexcept;

			template <math::math_type::NumericType Type>
			Type GetWidth(void) const noexcept;
			
			template <math::math_type::NumericType Type>
			Type GetHeight(void) const noexcept;

			float GetAspectRatio(void) const noexcept;

			void SetSize(int width, int height);
			void SetAspectRatio(float const& aspectRatio);

			int Init(void);
			void Update(void);
			bool ShouldWindowClose(void);
			
			operator GLFWwindow*(void);
			operator GLFWwindow*(void) const;

		private:
			std::string m_name;
			GLFWwindow* m_windowPtr;
			math::Vector2<int> m_size;
			float m_aspectRatio;

	};

	template<math::math_type::NumericType Type>
	inline math::Vector2<Type> src::Window::GetSize(void) const noexcept
	{
		return math::Vector2<Type>(
			static_cast<Type>(m_size[0]),
			static_cast<Type>(m_size[1])
		);
	}

	template<math::math_type::NumericType Type>
	inline Type src::Window::GetWidth(void) const noexcept
	{
		return static_cast<Type>(m_size[0]);
	}

	template<math::math_type::NumericType Type>
	inline Type src::Window::GetHeight(void) const noexcept
	{
		return static_cast<Type>(m_size[1]);
	}
}