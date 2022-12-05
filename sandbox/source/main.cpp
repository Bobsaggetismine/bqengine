
#include <bq.hpp>
#include <iostream>

constexpr float APP_WIDTH = 1280;
constexpr float APP_HEIGHT = 720;

int main() {
	bq::window window(APP_WIDTH, APP_HEIGHT, "sandbox");
    auto proj = glm::ortho(0.0f, APP_WIDTH, 0.0f, APP_HEIGHT, -1.0f, 1.0f);
    bq::gl_renderer_2d renderer(&proj);

    bq::vec2 pos  = { 0.0f, 100.0f };
    bq::vec2 size = { 100.0f, 100.0f };

    bq::vec2 pos2 =  { 200.0f, 200.0f };
    bq::vec2 size2 = { 100.0f, 100.0f };

    bq::texture tx("res/textures/dick.png");
    bq::texture tx2("res/textures/dick2.png");
    while (!window.shouldClose()) {
        pos.x+=0.1f;
        //pos2.x += 0.01f;
        renderer.begin_batch();
        renderer.render_quad(pos,  size,  tx);
        renderer.render_quad(pos2, size2, tx2);
        renderer.end_batch();
        window.render();
        tx.unbind();
        tx2.unbind();
    }
}