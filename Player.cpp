
#include "Player.h"

Player::Player(float width, float height, float screen_x, float screen_y)
    : width(width), height(height), screen_x(screen_x), screen_y(screen_y) {
    // ������ 2�� �����Ͽ� �ʱ�ȭ
    shapes.resize(2);
    for (auto& shape : shapes) {
        shape.setSize(sf::Vector2f(width, height));// Player_���� ũ�� ����
        shape.setFillColor(sf::Color::White); //Player_���� ũ�� ����
    }

    // Player1_���� ��ġ
    setPosition(0, screen_x / 10, screen_y / 2 - height / 2); 

    // Player2_���� ��ġ
    setPosition(1, (screen_x * 9) / 10, screen_y / 2 - height / 2);
}

void Player::move(int index, float offset_y) {
    if (index < 0 || index >= shapes.size()) return;

    sf::Vector2f pos = shapes[index].getPosition();// ���� ��ġ ��������

    // �̵��� ��ġ�� ȭ�� ������ ����� �ʵ��� ��
    if (pos.y + offset_y >= 0 && pos.y + offset_y <= screen_y - height) {
        shapes[index].move(0, offset_y);
    }
}

// ���� ��ġ�� �����ϴ� �Լ�
void Player::setPosition(int index, float x, float y) {
   
    if (index < 0 || index >= shapes.size()) return; // ��ȿ�� �ε������� Ȯ��
    
    shapes[index].setPosition(x, y);// ���� ��ġ ����
}

// ���� ���͸� ��ȯ�ϴ� �Լ�
std::vector<sf::RectangleShape>& Player::getShapes() {
    return shapes;// ���� ���� ��ȯ
}
