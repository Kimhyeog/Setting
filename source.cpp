#include <SFML/Graphics.hpp> 
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
//우리가 지정한 include의 SFML폴더 안에 Graphics.hpp를 헤더지정한 것이다.

using namespace sf;
//std를 사용하듯이, sf의 namespace 사용

using namespace std;
//vector를 사용하기 위해

int main() {

	

	//화면창을 열어주는 RenderWindow클래스
	RenderWindow window(VideoMode(640, 480), "Hello SFML");
	
	//프로그램 프레임 수 조절 == 속도조절 
	// => RenderWindow의 멤버함수setFramerateLimit()
	window.setFramerateLimit(100);

	//사용자 : 원

	//원을 만들어주는 클래스와 원하나 객체 생성
	CircleShape shape(100.0f,5);
	
	shape.setFillColor(Color::Green);//->만든 모양 객체의 색깔 정해주는 함수 
	shape.setPosition(320.0f-50.0f,240.0f-50.0f);
	//모양의 위치를 설정하는 메소드
	//shape을 감싸는 정사각형의 ★좌상단이 죄표이다.

	//초기에는 대각 ↘이동

	float offset_x = 1.0f;
	float offset_y = 1.0f;

	//NPC : 사각형

	RectangleShape r(Vector2f(70.0f,70.0f));
	//매개변수 : vector2f : vector + 2개의 float
	r.setFillColor(Color::Cyan);
	r.setPosition(100, 100);

	//NPC 여러마리 만들기
	//1_ 객체 생성 + 생김새
	vector <RectangleShape> npcs(4);
	int value = 0;
	for (auto& _e : npcs) {

		//npc: 크기 조정
		_e.setSize(Vector2f(70.0f, 70.0f));

		//npc : 색깔 조정
		_e.setFillColor(Color::Cyan);

		//위치 조정
		_e.setPosition(20+value , 40+ value);

		value += 30;
		value *= -1;
	}




	//화면 작동법★(암기)
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			switch (event.type) {
			case Event::Closed://창을 닫았을때,
				window.close();
				//window 창 닫아주기
				break;
			case Event::KeyPressed://창 닫기 이외, 키보드를 입력했을 때,
				
				//x좌표 변경
				if (Keyboard::isKeyPressed(Keyboard::Left) == true) {//왼쪽 키
					shape.move(-5, 0);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right) == true) {//오른쪽 키
					shape.move(5, 0);
				}
				//y좌표 변경
				else if (Keyboard::isKeyPressed(Keyboard::Up) == true) {//위 키
					shape.move(0, -5);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Down) == true) {//아래 키
					shape.move(0, +5);
				}


				break;
			default:
				// 어떤 case에도 해당하지 않는 경우 실행할 코드
				break;
			}


		}




	// NPC인 사각형 움직임 조정
		// 1_ 임시 좌표 저장하기
		Vector2f pos = r.getPosition();

		// 2_ 테두리 안에만 움직이도록 하기
		if (pos.y <= 0) { // 위 벽에 닿았을 때
			offset_y = 1.0f;
		}
		else if (pos.y >= 480 - 70) { // 아래 벽에 닿았을 때
			offset_y = -1.0f;
		}

		if (pos.x <= 0) { // 왼쪽 벽에 닿았을 때
			offset_x = 1.0f;
		}
		else if (pos.x >= 640 - 70) { // 오른쪽 벽에 닿았을 때
			offset_x = -1.0f;
		}

		// 4_NPC 움직이기
		r.move(offset_x, offset_y);


		//vector 객체들 모두 움직임

		for (auto& _e : npcs) {
			Vector2f pos = _e.getPosition();

			if (pos.y <= 0) { // 위 벽에 닿았을 때
				offset_y = 1.0f;
			}
			else if (pos.y >= 480 - 70) { // 아래 벽에 닿았을 때
				offset_y = -1.0f;
			}

			if (pos.x <= 0) { // 왼쪽 벽에 닿았을 때
				offset_x = 1.0f;
			}
			else if (pos.x >= 640 - 70) { // 오른쪽 벽에 닿았을 때
				offset_x = -1.0f;
			}

			// 4_NPC 움직이기
			_e.move(offset_x, offset_y);
		}

		window.clear();

		
		window.draw(shape);
	
		window.draw(r);

		//2_ NPC 그려주기
		for (auto& _e : npcs) {
			window.draw(_e);
		}



		window.display();



	}
	

	return 0;
}
