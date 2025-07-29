#include "input/InputHandler.h"
#include "input/InputCallbacks.h"

src::InputHandler* src::InputHandler::m_instance = nullptr;

int src::InputHandler::StartUp(void)
{
	// Register callbacks
	return src::callback::InitCallbacks();
}

int src::InputHandler::ShutDown(void)
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;

		return 0;
	}

	return -1;
}

void src::InputHandler::UpdateKeyState(void)
{
	if (GetInstance()->m_scrollUpdated == EScrollState::FIRST_FRAME)
		GetInstance()->m_scrollUpdated = EScrollState::SECOND_FRAME;
	else if (GetInstance()->m_scrollUpdated == EScrollState::SECOND_FRAME)
	{
		GetInstance()->m_scrollDelta = math::Vector2<double>::Zero();
		GetInstance()->m_scrollUpdated = EScrollState::NO_INPUT;
	}

	for (auto& input : GetInstance()->m_inputMap)
	{
		input.second.m_prevState = input.second.m_state;

		if (input.second.m_state == EInputState::STATE_PRESSED)
			input.second.m_state = EInputState::STATE_HELD;
		else if (input.second.m_state == EInputState::STATE_RELEASED)
			input.second.m_state = EInputState::STATE_UP;
	}

	GetInstance()->m_mousePosDelta = GetInstance()->m_mousePos - GetInstance()->m_prevMousePos;
	GetInstance()->m_prevMousePos = GetInstance()->m_mousePos;
}

void src::InputHandler::SetCursorMode(ECursorMode mode)
{
	callback::SetCursorMode(mode);
}

bool src::InputHandler::IsInputPressed(int keyCode)
{
	return GetInstance()->m_inputMap[keyCode].m_prevState == EInputState::STATE_PRESSED;
}

bool src::InputHandler::IsInputHeld(int keyCode)
{
	return GetInstance()->m_inputMap[keyCode].m_state == EInputState::STATE_HELD;
}

bool src::InputHandler::IsInputDown(int keyCode)
{
	return GetInstance()->m_inputMap[keyCode].m_state == EInputState::STATE_PRESSED ||
		GetInstance()->m_inputMap[keyCode].m_state == EInputState::STATE_HELD;
}

bool src::InputHandler::IsInputReleased(int keyCode)
{
	return GetInstance()->m_inputMap[keyCode].m_prevState == EInputState::STATE_RELEASED;
}

void src::InputHandler::KeyboardCallback(int key, int scanCode, int action, int mod)
{
	(void) scanCode;
	(void) mod;

	InputState input;
	input.m_state = static_cast<EInputState>(action);

	if (input.m_state == EInputState::STATE_PRESSED)
		input.m_prevState = EInputState::STATE_UP;
	else if (input.m_state == EInputState::STATE_HELD || input.m_state == EInputState::STATE_RELEASED)
		input.m_prevState = EInputState::STATE_HELD;
	else if (input.m_state == EInputState::STATE_UP)
		input.m_prevState = EInputState::STATE_UP;

	GetInstance()->m_inputMap[key] = input;
}

void src::InputHandler::MouseButtonCallback(int button, int action, int mods)
{
	(void) mods;

	InputState input;
	input.m_state = static_cast<EInputState>(action);

	if (input.m_state == EInputState::STATE_PRESSED)
		input.m_prevState = EInputState::STATE_UP;
	else if (input.m_state == EInputState::STATE_HELD || input.m_state == EInputState::STATE_RELEASED)
		input.m_prevState = EInputState::STATE_HELD;
	else if (input.m_state == EInputState::STATE_UP)
		input.m_prevState = EInputState::STATE_UP;

	GetInstance()->m_inputMap[button] = input;
}

void src::InputHandler::MouseScrollCallback(double xOffset, double yOffset)
{
	GetInstance()->m_scrollDelta = math::Vector2<double>(xOffset, yOffset);
	GetInstance()->m_scrollUpdated = EScrollState::FIRST_FRAME;
}

void src::InputHandler::CursorPosCallback(double xPos, double yPos)
{
	GetInstance()->m_mousePos = {xPos, yPos};
}

src::InputHandler::InputHandler(void)
	: m_mousePos(0.00), m_prevMousePos(0.00), m_scrollDelta(0.00),
	m_mousePosDelta(0.00), m_scrollUpdated(EScrollState::NO_INPUT)
{
}

src::InputHandler* src::InputHandler::GetInstance(void)
{
	if (!m_instance)
	{
		m_instance = new InputHandler();
	}

	return m_instance;
}
