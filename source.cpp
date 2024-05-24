#include <SFML/Graphics.hpp> 
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
//�츮�� ������ include�� SFML���� �ȿ� Graphics.hpp�� ��������� ���̴�.

using namespace sf;
//std�� ����ϵ���, sf�� namespace ���

using namespace std;
//vector�� ����ϱ� ����

int main() {

	

	//ȭ��â�� �����ִ� RenderWindowŬ����
	RenderWindow window(VideoMode(640, 480), "Hello SFML");
	
	//���α׷� ������ �� ���� == �ӵ����� 
	// => RenderWindow�� ����Լ�setFramerateLimit()
	window.setFramerateLimit(100);

	//����� : ��

	//���� ������ִ� Ŭ������ ���ϳ� ��ü ����
	CircleShape shape(100.0f,5);
	
	shape.setFillColor(Color::Green);//->���� ��� ��ü�� ���� �����ִ� �Լ� 
	shape.setPosition(320.0f-50.0f,240.0f-50.0f);
	//����� ��ġ�� �����ϴ� �޼ҵ�
	//shape�� ���δ� ���簢���� ���»���� ��ǥ�̴�.

	//�ʱ⿡�� �밢 ���̵�

	float offset_x = 1.0f;
	float offset_y = 1.0f;

	//NPC : �簢��

	RectangleShape r(Vector2f(70.0f,70.0f));
	//�Ű����� : vector2f : vector + 2���� float
	r.setFillColor(Color::Cyan);
	r.setPosition(100, 100);

	//NPC �������� �����
	//1_ ��ü ���� + �����
	vector <RectangleShape> npcs(4);
	int value = 0;
	for (auto& _e : npcs) {

		//npc: ũ�� ����
		_e.setSize(Vector2f(70.0f, 70.0f));

		//npc : ���� ����
		_e.setFillColor(Color::Cyan);

		//��ġ ����
		_e.setPosition(20+value , 40+ value);

		value += 30;
		value *= -1;
	}




	//ȭ�� �۵�����(�ϱ�)
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			switch (event.type) {
			case Event::Closed://â�� �ݾ�����,
				window.close();
				//window â �ݾ��ֱ�
				break;
			case Event::KeyPressed://â �ݱ� �̿�, Ű���带 �Է����� ��,
				
				//x��ǥ ����
				if (Keyboard::isKeyPressed(Keyboard::Left) == true) {//���� Ű
					shape.move(-5, 0);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) == true) {//������ Ű
					shape.move(5, 0);
				}
				//y��ǥ ����
				else if (Keyboard::isKeyPressed(Keyboard::Up) == true) {//�� Ű
					shape.move(0, -5);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) == true) {//�Ʒ� Ű
					shape.move(0, +5);
				}


				break;
			default:
				// � case���� �ش����� �ʴ� ��� ������ �ڵ�
				break;
			}


		}




	// NPC�� �簢�� ������ ����
		// 1_ �ӽ� ��ǥ �����ϱ�
		Vector2f pos = r.getPosition();

		// 2_ �׵θ� �ȿ��� �����̵��� �ϱ�
		if (pos.y <= 0) { // �� ���� ����� ��
			offset_y = 1.0f;
		}
		else if (pos.y >= 480 - 70) { // �Ʒ� ���� ����� ��
			offset_y = -1.0f;
		}

		if (pos.x <= 0) { // ���� ���� ����� ��
			offset_x = 1.0f;
		}
		else if (pos.x >= 640 - 70) { // ������ ���� ����� ��
			offset_x = -1.0f;
		}

		// 4_NPC �����̱�
		r.move(offset_x, offset_y);


		//vector ��ü�� ��� ������

		for (auto& _e : npcs) {
			Vector2f pos = _e.getPosition();

			if (pos.y <= 0) { // �� ���� ����� ��
				offset_y = 1.0f;
			}
			else if (pos.y >= 480 - 70) { // �Ʒ� ���� ����� ��
				offset_y = -1.0f;
			}

			if (pos.x <= 0) { // ���� ���� ����� ��
				offset_x = 1.0f;
			}
			else if (pos.x >= 640 - 70) { // ������ ���� ����� ��
				offset_x = -1.0f;
			}

			// 4_NPC �����̱�
			_e.move(offset_x, offset_y);
		}

		window.clear();

		
		window.draw(shape);
	
		window.draw(r);

		//2_ NPC �׷��ֱ�
		for (auto& _e : npcs) {
			window.draw(_e);
		}



		window.display();



	}
	

	return 0;
}
