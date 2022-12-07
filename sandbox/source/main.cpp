
#include <bq.hpp>
#include <iostream>

constexpr unsigned APP_WIDTH = 1280;
constexpr unsigned APP_HEIGHT = 720;

constexpr float CAMERA_SPEED = 0.20f;
bq::vec2 camera_movement = { 0,0 };

void handle_events(int key, int action)
{
    if (key == GLFW_KEY_W)
    {
        if (action == GLFW_PRESS)
        {
            camera_movement.y += -CAMERA_SPEED;
        }
        if (action == GLFW_RELEASE)
        {
            camera_movement.y -= -CAMERA_SPEED;
        }
    }
    else if (key == GLFW_KEY_A)
    {
        if (action == GLFW_PRESS)
        {
            camera_movement.x += CAMERA_SPEED;
        }
        if (action == GLFW_RELEASE)
        {
            camera_movement.x -= CAMERA_SPEED;
        }
    }
    else if (key == GLFW_KEY_S)
    {
        if (action == GLFW_PRESS)
        {
            camera_movement.y += CAMERA_SPEED;
        }
        if (action == GLFW_RELEASE)
        {
            camera_movement.y -= CAMERA_SPEED;
        }
    }
    else if (key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS)
        {
            camera_movement.x += -CAMERA_SPEED;
        }
        if (action == GLFW_RELEASE)
        {
            camera_movement.x -= -CAMERA_SPEED;
        }
    }
}


int main()
{
    bq::window::create(1280, 720, "sandbox");
    bq::window::instance().set_event_callback(&handle_events);
    bq::vec2 pos = { 100.0f, 100.0f };
    bq::vec2 pos2 = { 200.0f, 200.0f };
    bq::vec2 pos3 = { 300.0f, 300.0f };
   
    bq::vec2 size = { 100.0f, 100.0f };
    bq::vec2 size2 = { 100.0f, 100.0f };
    bq::vec2 size3 = { 100.0f, 100.0f };

    bq::texture texture ("res/textures/dick.png");
    bq::texture texture2("res/textures/dick2.png");
    bq::texture texture3("res/textures/dick.png");

    while (!bq::window::instance().should_close())
    {
        bq::window::instance().renderer().move_camera(camera_movement.x, camera_movement.y);

        bq::window::instance().renderer().begin_batch();
        bq::window::instance().renderer().render_quad(pos, size, texture);
        bq::window::instance().renderer().render_quad(pos2, size2, texture2);
        bq::window::instance().renderer().render_quad(pos3, size3, texture3);
        bq::window::instance().renderer().end_batch();
        bq::window::instance().render();
        bq::window::instance().handle_events();
    }
    bq::window::destroy();
}