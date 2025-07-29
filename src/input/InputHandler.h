#pragma once

#include "input/InputData.h"

#include <LibMath/VariableType.hpp>
#include <LibMath/vector/Vector2.h>
#include <unordered_map>

namespace src
{
	enum EInputState
	{
		STATE_UP = KEY_STATE_NONE,
		STATE_RELEASED = KEY_STATE_RELEASED,
		STATE_PRESSED = KEY_STATE_PRESSED,
		STATE_HELD = KEY_STATE_HELD
	};

	enum ECursorMode
	{
		MODE_NORMAL = CURSOR_MODE_NORMAL,
		MODE_HIDDEN = CURSOR_MODE_HIDDEN,
		MODE_DISABLED = CURSOR_MODE_DISABLED,
		MODE_CAPTURED = CURSOR_MODE_CAPTURED
	};

	// Mouse scroll delta callback called to late (right before reset)
	// so we're keeping scroll through the next frame
	enum class EScrollState
	{
		NO_INPUT, // No input detected
		FIRST_FRAME, // Frame at which scroll delta is available
		SECOND_FRAME, // Reset scroll delta
	};

	struct InputState
	{
		EInputState m_state = EInputState::STATE_UP;
		EInputState m_prevState = EInputState::STATE_UP;

	};

	class InputHandler
	{
		public:
			static int StartUp(void);
			static int ShutDown(void);
			static void UpdateKeyState(void);
			static void SetCursorMode(ECursorMode mode);

			static bool IsInputPressed(int keyCode);
			static bool IsInputHeld(int keyCode);
			static bool IsInputDown(int keyCode);
			static bool IsInputReleased(int keyCode);

			static void KeyboardCallback(int key, int scanCode, int action, int mod);
			static void MouseButtonCallback(int button, int action, int mods);
			static void MouseScrollCallback(double xOffset, double yOffset);
			static void CursorPosCallback(double xPos, double yPos);

			template <math::math_type::NumericType Type>
			static math::Vector2<Type> GetCursorPosition(void);

			template <math::math_type::NumericType Type>
			static math::Vector2<Type> GetCursorDeltaPosition(void);
			
			template <math::math_type::NumericType Type>
			static math::Vector2<Type> GetScrollDelta(void);

		private:
			InputHandler(void);
			InputHandler(InputHandler const&) = delete;

			static InputHandler* GetInstance(void);

			static InputHandler* m_instance;

			std::unordered_map<int, InputState> m_inputMap;
			math::Vector2<double> m_mousePos;
			math::Vector2<double> m_prevMousePos;
			math::Vector2<double> m_mousePosDelta;
			math::Vector2<double> m_scrollDelta;
			EScrollState m_scrollUpdated;
	};
	template<math::math_type::NumericType Type>
	inline math::Vector2<Type> InputHandler::GetCursorPosition(void)
	{
		return math::Vector2<Type>();
	}
	template<math::math_type::NumericType Type>
	inline math::Vector2<Type> InputHandler::GetCursorDeltaPosition(void)
	{
		return math::Vector2<Type>();
	}
	template<math::math_type::NumericType Type>
	inline math::Vector2<Type> InputHandler::GetScrollDelta(void)
	{
		return math::Vector2<Type>();
	}
}