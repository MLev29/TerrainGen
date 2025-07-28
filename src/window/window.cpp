#include "window.h"
#include "window/WindowHelperFunction.h"
#include "utility/GraphicsFunctions.h"

src::Window::Window(std::string const& wndName, int const width, int const height)
    : m_name(wndName.c_str())
{
    m_size = {width, height};
    m_aspectRatio = width / height;
    m_windowPtr = nullptr;
}

src::Window::~Window(void)
{
    // TODO: call destructor
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
    m_windowPtr = CreateWindow(m_name, m_size);
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
    Clear();

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
