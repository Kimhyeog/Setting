#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

int main() {
    int Frame = 200;
    float Screen_X = 1000; // 화면 창 X축 길이
    float Screen_Y = 800; // 화면 창 Y축 길이
    float circle_r = 10.0f; // Ball 반지름
    float Player_X = 10.0f; // Player 벽동 X축 길이
    float Player_Y = 100.0f; // Player 벽동 X축 길이
    float Brick_x = 30.0f; // Brick X축 길이
    float Brick_y = 90.0f; // Brick Y축 길이
    float Brick_itv = 10.0f; // 벽돌 사이에 간격
    float Brick_row_gap = 1.5f * Brick_x; // 행 간의 간격
    bool p1_w, p2_w;//player1의 승패 여부, player2의 승패여부
    p1_w = p2_w = false;





    // 화면 객체 생성 + 화면 프레임 수 조절
    RenderWindow window(VideoMode(Screen_X, Screen_Y), "BallTest");
    window.setFramerateLimit(Frame);

    // 공 생성 => 일단 하나만 생성(Vector 사용 x)
    CircleShape ball(circle_r * 2);
    ball.setFillColor(Color::White);
    ball.setPosition(Screen_X / 2 - circle_r, Screen_Y / 2 + circle_r); // 정중앙 위치

    // 벽돌 생성 => Vector로 생성
    vector<RectangleShape> player(2);

    // 중앙에 벽돌들 생성(방해물) => Vector로 생성
    vector<RectangleShape> Brick;

    // Brick 크기 및 위치 설정
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

    // Player 크기
    for (int i = 0; i < player.size(); i++) {
        player[i].setSize(Vector2f(Player_X, Player_Y));
        player[i].setFillColor(Color::Red);
    }

    // Player1 벽돌 위치
    player[0].setPosition(Vector2f(Screen_X / 10, Screen_Y / 2 - Player_Y / 2));
    player[0].setFillColor(Color::White);

    // Player2 벽돌 위치
    player[1].setPosition(Vector2f((Screen_X * 9) / 10, Screen_Y / 2 - Player_Y / 2));
    player[1].setFillColor(Color::White);

    // 공의 초기 속도
    float initial_ball_speed = 1.0f;
    float ball_speed = initial_ball_speed;
    float ball_m_x = ball_speed;
    float ball_m_y = ball_speed;

    float brick_speed = 5.0f;

    // 공을 초기 위치와 속도로 재설정하는 함수
    auto resetBall = [&]() {
        Vector2f p2_pos = player[1].getPosition();
        Vector2f p1_pos = player[0].getPosition();
        if (p1_w) {
            ball.setPosition(p2_pos.x - Player_X * 2 - 20.0f, p2_pos.y + Player_Y / 2 - circle_r);
            //p1_이 졌을경우 => p2의 벽돌앞에 놓이도록 한다.
            p1_w = false;
        }
        else if (p2_w) {
            ball.setPosition(p1_pos.x + Player_X + 0.05f, p1_pos.y + Player_Y / 2 - circle_r);
            //p2_이 졌을경우 => p1의 벽돌앞에 놓이도록 한다.
            p2_w = false;
        }
        ball_speed = initial_ball_speed;
        ball_m_x = ball_speed;
        ball_m_y = ball_speed;
     };

    // 화면 작동 구현 
    while (window.isOpen()) {
        //ball의 위치 계속 정보받기
        Vector2f ball_pos = ball.getPosition();


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
                    if (p1_pos.y < Screen_Y - Player_Y) {
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
                    if (p2_pos.y < Screen_Y - Player_Y) {
                        player[1].move(0, -brick_speed + Frame / 10);
                    }
                }
                break;
            default:
                break;
            }
        }

        // Ball의 위치를 계속 확인
        

        if (ball_pos.x <= 0) { // 왼벽과 만났을 시 => Player2 1점 획득
            p2_w = true;
            resetBall();
            
        }
        else if (ball_pos.x >= Screen_X - 2 * circle_r) { // 오른벽과 만났을 시 => Player1 1점 획득
            p1_w = true;

            resetBall();
        }

        if (ball_pos.y <= 0) { // 위벽
            ball_m_y *= -1.0f;
        }
        else if (ball_pos.y >= Screen_Y - 2 * circle_r) { // 아래벽
            ball_m_y *= -1.0f;
        }

        // 공과 Player의 충돌 감지
        FloatRect ballBounds = ball.getGlobalBounds();
        for (auto& p : player) {
            if (ballBounds.intersects(p.getGlobalBounds())) {
                ball_m_x *= -1.001f; // 공의 속도를 약간 증가시키며 반전
                break;
            }
        }

        // 공과 Brick의 충돌 감지
        for (int i = 0; i < Brick.size(); i++) {
            if (ballBounds.intersects(Brick[i].getGlobalBounds())) {
                ball_m_x *= -1.0f; // 공의 속도를 약간 증가시키며 반전
                Brick.erase(Brick.begin() + i); // 삭제 구현
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

        for (auto& b : Brick) {
            window.draw(b);
        }

        window.display();
        // ★ 여기 코드는 순서를 지켜줘야함
    }

    return 0;
}
