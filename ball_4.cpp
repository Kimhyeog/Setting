#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

int main() {
    int Frame = 200;
    float Screen_X = 1000; // ȭ�� â X�� ����
    float Screen_Y = 800; // ȭ�� â Y�� ����
    float circle_r = 10.0f; // Ball ������
    float Player_X = 10.0f; // Player ���� X�� ����
    float Player_Y = 100.0f; // Player ���� X�� ����
    float Brick_x = 30.0f; // Brick X�� ����
    float Brick_y = 90.0f; // Brick Y�� ����
    float Brick_itv = 10.0f; // ���� ���̿� ����
    float Brick_row_gap = 1.5f * Brick_x; // �� ���� ����
    bool p1_w, p2_w;//player1�� ���� ����, player2�� ���п���
    p1_w = p2_w = false;





    // ȭ�� ��ü ���� + ȭ�� ������ �� ����
    RenderWindow window(VideoMode(Screen_X, Screen_Y), "BallTest");
    window.setFramerateLimit(Frame);

    // �� ���� => �ϴ� �ϳ��� ����(Vector ��� x)
    CircleShape ball(circle_r * 2);
    ball.setFillColor(Color::White);
    ball.setPosition(Screen_X / 2 - circle_r, Screen_Y / 2 + circle_r); // ���߾� ��ġ

    // ���� ���� => Vector�� ����
    vector<RectangleShape> player(2);

    // �߾ӿ� ������ ����(���ع�) => Vector�� ����
    vector<RectangleShape> Brick;

    // Brick ũ�� �� ��ġ ����
    int rows = 8;
    int bricks_per_row = 3;
    float total_height = rows * Brick_y + (rows - 1) * Brick_itv;
    float start_y = (Screen_Y - total_height) / 2;
    for (int row = 0; row < rows; row++) {
        for (int i = 0; i < bricks_per_row; i++) {
            RectangleShape brick;
            brick.setSize(Vector2f(Brick_x, Brick_y));
            brick.setPosition((Screen_X - (bricks_per_row * (Brick_x + Brick_row_gap) - Brick_row_gap)) / 2 + i * (Brick_x + Brick_row_gap), start_y + row * (Brick_y + Brick_itv));
            brick.setFillColor(Color::Red);
            Brick.push_back(brick);
        }
    }

    // Player ũ��
    for (int i = 0; i < player.size(); i++) {
        player[i].setSize(Vector2f(Player_X, Player_Y));
        player[i].setFillColor(Color::Red);
    }

    // Player1 ���� ��ġ
    player[0].setPosition(Vector2f(Screen_X / 10, Screen_Y / 2 - Player_Y / 2));
    player[0].setFillColor(Color::White);

    // Player2 ���� ��ġ
    player[1].setPosition(Vector2f((Screen_X * 9) / 10, Screen_Y / 2 - Player_Y / 2));
    player[1].setFillColor(Color::White);

    // ���� �ʱ� �ӵ�
    float initial_ball_speed = 1.0f;
    float ball_speed = initial_ball_speed;
    float ball_m_x = ball_speed;
    float ball_m_y = ball_speed;

    float brick_speed = 5.0f;

    // ���� �ʱ� ��ġ�� �ӵ��� �缳���ϴ� �Լ�
    auto resetBall = [&]() {
        Vector2f p2_pos = player[1].getPosition();
        Vector2f p1_pos = player[0].getPosition();
        if (p1_w) {
            ball.setPosition(p2_pos.x - Player_X * 2 - 20.0f, p2_pos.y + Player_Y / 2 - circle_r);
            //p1_�� ������� => p2�� �����տ� ���̵��� �Ѵ�.
            p1_w = false;
        }
        else if (p2_w) {
            ball.setPosition(p1_pos.x + Player_X + 0.05f, p1_pos.y + Player_Y / 2 - circle_r);
            //p2_�� ������� => p1�� �����տ� ���̵��� �Ѵ�.
            p2_w = false;
        }
        ball_speed = initial_ball_speed;
        ball_m_x = ball_speed;
        ball_m_y = ball_speed;
     };

    // ȭ�� �۵� ���� 
    while (window.isOpen()) {
        //ball�� ��ġ ��� �����ޱ�
        Vector2f ball_pos = ball.getPosition();


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
                    if (p1_pos.y < Screen_Y - Player_Y) {
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
                    if (p2_pos.y < Screen_Y - Player_Y) {
                        player[1].move(0, -brick_speed + Frame / 10);
                    }
                }
                break;
            default:
                break;
            }
        }

        // Ball�� ��ġ�� ��� Ȯ��
        

        if (ball_pos.x <= 0) { // �޺��� ������ �� => Player2 1�� ȹ��
            p2_w = true;
            resetBall();
            
        }
        else if (ball_pos.x >= Screen_X - 2 * circle_r) { // �������� ������ �� => Player1 1�� ȹ��
            p1_w = true;

            resetBall();
        }

        if (ball_pos.y <= 0) { // ����
            ball_m_y *= -1.0f;
        }
        else if (ball_pos.y >= Screen_Y - 2 * circle_r) { // �Ʒ���
            ball_m_y *= -1.0f;
        }

        // ���� Player�� �浹 ����
        FloatRect ballBounds = ball.getGlobalBounds();
        for (auto& p : player) {
            if (ballBounds.intersects(p.getGlobalBounds())) {
                ball_m_x *= -1.001f; // ���� �ӵ��� �ణ ������Ű�� ����
                break;
            }
        }

        // ���� Brick�� �浹 ����
        for (int i = 0; i < Brick.size(); i++) {
            if (ballBounds.intersects(Brick[i].getGlobalBounds())) {
                ball_m_x *= -1.0f; // ���� �ӵ��� �ణ ������Ű�� ����
                Brick.erase(Brick.begin() + i); // ���� ����
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

        for (auto& b : Brick) {
            window.draw(b);
        }

        window.display();
        // �� ���� �ڵ�� ������ ���������
    }

    return 0;
}
