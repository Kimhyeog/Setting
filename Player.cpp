
#include "Player.h"

Player::Player(float width, float height, float screen_x, float screen_y)
    : width(width), height(height), screen_x(screen_x), screen_y(screen_y) {
    // 벽돌을 2개 생성하여 초기화
    shapes.resize(2);
    for (auto& shape : shapes) {
        shape.setSize(sf::Vector2f(width, height));// Player_벽돌 크기 설정
        shape.setFillColor(sf::Color::White); //Player_벽돌 크기 설정
    }

    // Player1_벽돌 위치
    setPosition(0, screen_x / 10, screen_y / 2 - height / 2); 

    // Player2_벽돌 위치
    setPosition(1, (screen_x * 9) / 10, screen_y / 2 - height / 2);
}

void Player::move(int index, float offset_y) {
    if (index < 0 || index >= shapes.size()) return;

    sf::Vector2f pos = shapes[index].getPosition();// 현재 위치 가져오기

    // 이동할 위치가 화면 범위를 벗어나지 않도록 함
    if (pos.y + offset_y >= 0 && pos.y + offset_y <= screen_y - height) {
        shapes[index].move(0, offset_y);
    }
}

// 벽돌 위치를 설정하는 함수
void Player::setPosition(int index, float x, float y) {
   
    if (index < 0 || index >= shapes.size()) return; // 유효한 인덱스인지 확인
    
    shapes[index].setPosition(x, y);// 벽돌 위치 설정
}

// 벽돌 벡터를 반환하는 함수
std::vector<sf::RectangleShape>& Player::getShapes() {
    return shapes;// 벽돌 벡터 반환
}
