#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

int main() {
    int Frame = 800;
    float Screen_X = 1000;//ȭ�� â X�� ����
    float Screen_Y = 800;//ȭ�� â Y�� ����
    float circle_r = 15.0f;//Ball ������
    float Brick_X = 10.0f;//Player ���� X�� ����
    float Brick_Y = 100.0f;//Player ���� X�� ����

    // ȭ�� ��ü ���� + ȭ�� ������ �� ����
    RenderWindow window(VideoMode(Screen_X, Screen_Y), "BallTest");
    window.setFramerateLimit(Frame);

    // �� ���� => �ϴ� �ϳ��� ����(Vector ��� x)
    CircleShape ball(circle_r*2);
    ball.setFillColor(Color::White);
    ball.setPosition(Screen_X/2 - circle_r, Screen_Y/2 + circle_r); // ���߾� ��ġ

    // ���� ���� => Vector�� ����
    vector<RectangleShape> player(2);

    // ���� ũ��
    for (int i = 0; i < player.size(); i++) {
        player[i].setSize(Vector2f(Brick_X, Brick_Y));
    }

    // Player1_���� ��ġ
    player[0].setPosition(Vector2f(Screen_X/10, Screen_Y/2 - Brick_Y/2));
    player[0].setFillColor(Color::White);

    // Player2_���� ��ġ
    player[1].setPosition(Vector2f((Screen_X*9) / 10, Screen_Y / 2 - Brick_Y / 2));
    player[1].setFillColor(Color::White);

    // ���� �ʱ� �ӵ�
    float ball_speed = 1.0f;
    float ball_m_x = 1.0f;
    float ball_m_y = 1.0f;

    float brick_speed = 5.0f;


    // ȭ�� �۵� ���� 
    while (window.isOpen()) {
        // Key���� �޾��ִ� event ��ü ����
        Event event;
        // Key�� window ��ü�� �������ִ� �޼ҵ�
        // Key ó�� �ϴ� �κ�
        while (window.pollEvent(event)) { // window â �۵��ϴ� ������ ��� key ���� ���� �����ش�.
            Vector2f p1_pos = player[0].getPosition();
            Vector2f p2_pos = player[1].getPosition();

            switch (event.type) {
            case Event::Closed: // â�ݱ⸦ ���� ��� || ESC�� ������ ���
                window.close();
                break;
            case Event::KeyPressed:
                // Player1�� ���� ������ ����
                if (Keyboard::isKeyPressed(Keyboard::W) == true) {
                    if (p1_pos.y > 0) { // ���׵θ� �����϶���, ������ ������ �� �ֵ��� �Ѵ�.
                        player[0].move(0, brick_speed - Frame / 10);
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::S) == true) {
                    if (p1_pos.y < Screen_Y - Brick_Y) {
                        player[0].move(0, -brick_speed + Frame / 10);
                    }
                }
                // Player2�� ���� ������ ����
                if (Keyboard::isKeyPressed(Keyboard::Up) == true) {
                    if (p2_pos.y > 0) {
                        player[1].move(0, brick_speed - Frame / 10);
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Down) == true) {
                    if (p2_pos.y < Screen_Y - Brick_Y) {
                        player[1].move(0, -brick_speed + Frame / 10);
                    }
                }
                break;
            default:
                break;
            }
        }

        // Ball�� ��ġ�� ��� Ȯ��
        Vector2f ball_pos = ball.getPosition();

        if (ball_pos.x <= 0) { // �޺��� ������ �� => Player2 1�� ȹ��
            ball_m_x *= -ball_speed;
        }
        else if (ball_pos.x >= 1000 - 60) { // �������� ������ �� => Player1 1�� ȹ��
            ball_m_x *= -ball_speed;
        }

        if (ball_pos.y <= 0) { // ����
            ball_m_y *= -ball_speed;
        }
        else if (ball_pos.y >= 800 - 60) { // �Ʒ���
            ball_m_y *= -ball_speed;
        }

        // ���� ������ �浹 ����
        FloatRect ballBounds = ball.getGlobalBounds();
        for (auto& p : player) {
            if (ballBounds.intersects(p.getGlobalBounds())) {
                ball_m_x *= -1.001f; // ���� �ӵ��� �ణ ������Ű�� ����
                break;
            }
        }

        ball.move(ball_m_x, ball_m_y);

        // ��
        window.clear();

        // ��ü ���� �׸���
        window.draw(ball);
        window.draw(player[0]);
        window.draw(player[1]);

        window.display();
        // �� ���� �ڵ�� ������ ���������
    }

    return 0;
}
