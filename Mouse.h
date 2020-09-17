//
// Created by szymon on 14.04.2020.
//

#ifndef OPENGL_MOUSE_H
#define OPENGL_MOUSE_H

const float SENSITIVITY = 0.5f;

class Mouse final {

private:
    bool xInit, yInit;
    float curX;
    float curY;
    float sensitivity;

public:
    Mouse() : sensitivity(SENSITIVITY) {
        curY = 0.0f;
        curX = 0.0f;
        xInit = false;
        yInit = false;
    }

    float getXdiff(float x) {
        if (!xInit) {
            curX = x;
            xInit = true;
        }


        float xOffset = x - curX;
        curX = x;
        xOffset *= sensitivity;

        return xOffset;
    }

    float getYdiff(float y) {
        if (!yInit) {
            curY = y;
            yInit = true;
        }
        float yOffset = y - curY;
        curY = y;
        yOffset *= sensitivity;

        return yOffset;
    }
};


#endif //OPENGL_MOUSE_H
