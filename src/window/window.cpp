#include "window.h"
#include "window/WindowHelperFunction.h"
#include "utility/GraphicsFunctions.h"



src::Window::Window(const char* wndName, int const width, int const height)
    : m_name(wndName)
{
    m_size = {width, height};
    m_aspectRatio = float(width) / float(height);
    m_windowPtr = nullptr;
}

src::Window::~Window(void)
{
    src::CloseWindow(*this);
}

float src::Window::GetAspectRatio(void) const noexcept
{
    return m_aspectRatio;
}

void src::Window::SetSize(int width, int height)
{
    m_size = {width, height};
}

void src::Window::SetAspectRatio(float const& aspectRatio)
{
    m_aspectRatio = aspectRatio;
}

int src::Window::Init(void)
{
    // Init window lib (GLFW)
    if (InitWndLib())
        return -1;

    // Create window
    m_windowPtr = CreateWindow(m_name.c_str(), m_size);
    if (!m_windowPtr)
    {
        std::printf("Failed to create window, pointer is null.\n");
        return -1;
    }

    SetContext(m_windowPtr, this);

    // Init graphics framework (glad)
    if (InitGraphicsApi())
        return -1;

    return 0;
}

void src::Window::Update(void)
{
    //Clear();

    UpdateWindow(*this);
}

bool src::Window::ShouldWindowClose(void)
{
    return ShouldWndClose(m_windowPtr);
}

src::Window::operator GLFWwindow* (void)
{
    return m_windowPtr;
}

src::Window::operator GLFWwindow* (void) const
{
    return m_windowPtr;
}
