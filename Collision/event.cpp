/*************************************************************************
 * event.cpp for project Collision
 * Author : lzh
 * Modifier : lzh
 * Description : Source file including functions to process mouse events
 * and keyboard events.
 ************************************************************************/

// Inclusion of global header
#include "global.hpp"

void EventInit()
{
    for (int i = 0; i < 3; i++)
        npButtonState[i] = 0;
    mModelTransformMat = glm::mat4(1.0);
    dLastMouseX = FLT_MAX;
    dLastMouseY = FLT_MAX;
    return ;
}

void MouseMotionEvent(GLFWwindow* w, double x, double y)
{
    int npState[3];
    float d = sqrt(
        (float)((x-dLastMouseX) * (x-dLastMouseX))
        +(float)((y-dLastMouseY) * (y-dLastMouseY))
    ), theta;
    int nWindowWidth, nWindowHeight;
    npState[0] = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT);
    npState[1] = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_MIDDLE);
    npState[2] = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT);
    if (dLastMouseX == FLT_MAX || dLastMouseY == FLT_MAX)
        ;
    else if (dLastMouseX == x && dLastMouseY == y)
        ;
    else if (
        (npState[0] == GLFW_PRESS) && 
        (npState[1] == GLFW_RELEASE) &&
        (npState[2] == GLFW_RELEASE)
    )
    {
        mModelTransformMat = glm::rotate(glm::mat4(1.0), d*fRotateSpeed ,
            glm::vec3(
                ((float)(y-dLastMouseY)) / d,
                ((float)(x-dLastMouseX)) / d,
                0.0
            )
        ) * mModelTransformMat;
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mModelTransformMat));
    }
    else if (
        (npState[0] == GLFW_RELEASE) && 
        (npState[1] == GLFW_RELEASE) &&
        (npState[2] == GLFW_PRESS)
    )
    {
        mModelTransformMat = glm::translate(glm::mat4(1.0),
            glm::vec3(
                ((float)(x-dLastMouseX)) * fTranslateSpeed,
                -((float)(y-dLastMouseY)) * fTranslateSpeed,
                0.0
            )
        ) * mModelTransformMat;
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mModelTransformMat));
    }
    else if (
        (npState[0] == GLFW_RELEASE) && 
        (npState[1] == GLFW_PRESS) &&
        (npState[2] == GLFW_RELEASE)
    )
    {
        glfwGetWindowSize(w, &nWindowWidth, &nWindowHeight);
        theta = atan2(
            (float)x - 
            ((float)(nWindowWidth/2) + 0.5),
            ((float)(nWindowHeight/2) + 0.5) 
            - (float)y
        );
        theta -= atan2(
            (float)dLastMouseX - 
            ((float)(nWindowWidth/2) + 0.5),
            ((float)(nWindowHeight/2) + 0.5) 
            - (float)dLastMouseY
        );
        mModelTransformMat = glm::rotate(glm::mat4(1.0),
            -theta,
            glm::vec3(0.0, 0.0, 1.0)
        ) * mModelTransformMat;
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(mModelTransformMat));
    }
    dLastMouseX = x;
    dLastMouseY = y;
    GameMove(w, x, y);
    return ;
}

void MouseWheelEvent(GLFWwindow* w, double x, double y)
{
    mModelTransformMat = glm::translate(glm::mat4(1.0),
        glm::vec3(0.0, 0.0, (float)y*fScrollSpeed)
    ) * mModelTransformMat;
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(mModelTransformMat));
    return ;
}

void MouseDropEvent(GLFWwindow* w, int c, const char** p)
{
    GameDrag(w, c, p);
    return ;
}

void KeyEvent(GLFWwindow *w, int key, int scancode, int action, int mods)
{
    if (action != GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_UP:
                // +6dB
                fEffVol *= 2;
                break;
            case GLFW_KEY_DOWN:
                // -6dB
                fEffVol /= 2;
                break;
            case GLFW_KEY_LEFT:
                fBGMVol /= 2;
                break;
            case GLFW_KEY_RIGHT:
                fBGMVol *= 2;
                break;
        }
    }
    Audio::GetAudio()->SetVolume();
    return ;
}
