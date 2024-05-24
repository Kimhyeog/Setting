#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

int main() {
    int Frame = 800;
    float Screen_X = 1000;//화면 창 X축 길이
    float Screen_Y = 800;//화면 창 Y축 길이
    float circle_r = 15.0f;//Ball 반지름
    float Brick_X = 10.0f;//Player 벽동 X축 길이
    float Brick_Y = 100.0f;//Player 벽동 X축 길이

    // 화면 객체 생성 + 화면 프레임 수 조절
    RenderWindow window(VideoMode(Screen_X, Screen_Y), "BallTest");
    window.setFramerateLimit(Frame);

    // 공 생성 => 일단 하나만 생성(Vector 사용 x)
    CircleShape ball(circle_r*2);
    ball.setFillColor(Color::White);
    ball.setPosition(Screen_X/2 - circle_r, Screen_Y/2 + circle_r); // 정중앙 위치

    // 벽돌 생성 => Vector로 생성
    vector<RectangleShape> player(2);

    // 벽돌 크기
    for (int i = 0; i < player.size(); i++) {
        player[i].setSize(Vector2f(Brick_X, Brick_Y));
    }

    // Player1_벽돌 위치
    player[0].setPosition(Vector2f(Screen_X/10, Screen_Y/2 - Brick_Y/2));
    player[0].setFillColor(Color::White);

    // Player2_벽돌 위치
    player[1].setPosition(Vector2f((Screen_X*9) / 10, Screen_Y / 2 - Brick_Y / 2));
    player[1].setFillColor(Color::White);

    // 공의 초기 속도
    float ball_speed = 1.0f;
    float ball_m_x = 1.0f;
    float ball_m_y = 1.0f;

    float brick_speed = 5.0f;


    // 화면 작동 구현 
    while (window.isOpen()) {
        // Key값들 받아주는 event 객체 선언
        Event event;
        // Key값 window 객체에 적용해주는 메소드
        // Key 처리 하는 부분
        while (window.pollEvent(event)) { // window 창 작동하는 동안은 계속 key 값을 적용 시켜준다.
            Vector2f p1_pos = player[0].getPosition();
            Vector2f p2_pos = player[1].getPosition();

            switch (event.type) {
            case Event::Closed: // 창닫기를 했을 경우 || ESC를 눌렀을 경우
                window.close();
                break;
            case Event::KeyPressed:
                // Player1의 벽돌 움직임 구현
                if (Keyboard::isKeyPressed(Keyboard::W) == true) {
                    if (p1_pos.y > 0) { // ★테두리 내부일때만, 움직임 구현될 수 있도록 한다.
                        player[0].move(0, brick_speed - Frame / 10);
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::S) == true) {
                    if (p1_pos.y < Screen_Y - Brick_Y) {
                        player[0].move(0, -brick_speed + Frame / 10);
                    }
                }
                // Player2의 벽돌 움직임 구현
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

        // Ball의 위치를 계속 확인
        Vector2f ball_pos = ball.getPosition();

        if (ball_pos.x <= 0) { // 왼벽과 만났을 시 => Player2 1점 획득
            ball_m_x *= -ball_speed;
        }
        else if (ball_pos.x >= 1000 - 60) { // 오른벽과 만났을 시 => Player1 1점 획득
            ball_m_x *= -ball_speed;
        }

        if (ball_pos.y <= 0) { // 위벽
            ball_m_y *= -ball_speed;
        }
        else if (ball_pos.y >= 800 - 60) { // 아래벽
            ball_m_y *= -ball_speed;
        }

        // 공과 벽돌의 충돌 감지
        FloatRect ballBounds = ball.getGlobalBounds();
        for (auto& p : player) {
            if (ballBounds.intersects(p.getGlobalBounds())) {
                ball_m_x *= -1.001f; // 공의 속도를 약간 증가시키며 반전
                break;
            }
        }

        ball.move(ball_m_x, ball_m_y);

        // ★
        window.clear();

        // 객체 모양들 그리기
        window.draw(ball);
        window.draw(player[0]);
        window.draw(player[1]);

        window.display();
        // ★ 여기 코드는 순서를 지켜줘야함
    }

    return 0;
}
