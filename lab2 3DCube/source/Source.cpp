
//#define GLFW_INCLUDE_GLU

#include <iostream>

// 이 순서가 바뀌면 안됨
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "MyGlWindow.h"
#include <memory>

std::unique_ptr<MyGlWindow> win; //modern c++

// -------------------- 마우스 상태 전역 변수 --------------------
bool lbutton_down = false;
bool rbutton_down = false;
bool mbutton_down = false;
double m_lastMouseX = 0.0;
double m_lastMouseY = 0.0;
double cx = 0.0, cy = 0.0;
// -------------------------------------------------------------

// 창 크기 바뀔 때
void window_size_callback(GLFWwindow* window, int width, int height)
{
    if (win)
    {
        win->setSize(width, height);
        win->setAspect(static_cast<float>(width) / static_cast<float>(height));
    }
}

// 키보드
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// 마우스 위치
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    cx = xpos;
    cy = ypos;
}

// 마우스 버튼
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) {
        glfwGetCursorPos(window, &m_lastMouseX, &m_lastMouseY);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        lbutton_down = (action == GLFW_PRESS);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        rbutton_down = (action == GLFW_PRESS);
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        mbutton_down = (action == GLFW_PRESS);
    }
}

// 드래그 중 카메라 조작
void mouseDragging(int width, int height)
{
    if (!win) return;

    Viewer* viewer = win->getViewer();
    if (!viewer) return;

    float fractionChangeX = static_cast<float>(cx - m_lastMouseX) / static_cast<float>(width);
    float fractionChangeY = static_cast<float>(m_lastMouseY - cy) / static_cast<float>(height);

    if (lbutton_down) {
        // 회전
        viewer->rotate(fractionChangeX, fractionChangeY);
    }
    else if (mbutton_down) {
        // 줌
        viewer->zoom(fractionChangeY);
    }
    else if (rbutton_down) {
        // 평행 이동
        viewer->translate(-fractionChangeX, -fractionChangeY, true);
    }

    m_lastMouseX = cx;
    m_lastMouseY = cy;
}

// ============================ main ============================
int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Error" << std::endl;
        return 0;
    }

    //오픈gl 버전 지정
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 800;
    int height = 800;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL FrameWork", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //opengl 컨텍스트 생성
    glfwMakeContextCurrent(window);

    //헬퍼초기화
    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return -1;
    }
    if (!gl3wIsSupported(3, 2)) {
        fprintf(stderr, "OpenGL 3.2 not supported\n");
        return -1;
    }
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
        glGetString(GL_SHADING_LANGUAGE_VERSION));

    //vsync
    glfwSwapInterval(1);

    // MyGlWindow 객체 생성
    win = std::make_unique<MyGlWindow>(width, height);

    // ----- 콜백 등록 -----
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetKeyCallback(window, key_callback);
    // ---------------------

    // 메인 루프
    while (!glfwWindowShouldClose(window))
    {
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        // 매 프레임 draw
        win->draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // 마우스 드래그 처리
        mouseDragging(display_w, display_h);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


