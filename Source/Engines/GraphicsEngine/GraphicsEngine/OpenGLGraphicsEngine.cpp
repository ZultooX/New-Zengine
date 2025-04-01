#include <GraphicsEngine/GraphicsEngine.h>

#include <OpenGL/glfw3.h>

#ifdef USE_OPENGL
bool OpenGLGraphicsEngine::Initialize()
{

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

	return false;
}

void OpenGLGraphicsEngine::Present()
{
}

bool OpenGLGraphicsEngine::PreUpdate()
{
	return false;
}

bool OpenGLGraphicsEngine::MainUpdate()
{
	return false;
}

bool OpenGLGraphicsEngine::PostUpdate()
{
	return false;
}
#endif // USEOPENGL