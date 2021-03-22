#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "tetris.h"

int main(int, char **)
{
	// g++ -c main.cpp tetris.cpp tetris.h tetris_const.h && g++ main.o tetris.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system
	Tetris::Tetris tetris;

	while (tetris.GetWindow().isOpen())
	{
		if (tetris.AbilityGenerate())
		{
			tetris.Input();
			tetris.GetWindow().clear(sf::Color::White);
			tetris.Update();
			tetris.Draw();
			//tetris.Move();
			tetris.CleaningLine();
			tetris.Display();
		}
		else
		{
			while (tetris.GetWindow().pollEvent(tetris.GetEvent()))
			{
				if (tetris.GetEvent().key.code == sf::Keyboard::Key::Escape ||
					tetris.GetEvent().type == sf::Event::Closed)
				{
					tetris.GetWindow().close();
				}
			}
			tetris.GetWindow().clear(sf::Color::White);
			tetris.Draw();
			tetris.Display();
		}
	}

	return EXIT_SUCCESS;

	std::vector<std::vector<std::vector<int16_t>>> f{
		{{0, 0, 0, 0},
		 {1, 1, 1, 1},
		 {0, 0, 0, 0},
		 {0, 0, 0, 0}},
		{{0, 1, 1},
		 {1, 1, 0},
		 {0, 0, 0}},
		{{1, 1, 0},
		 {0, 1, 1},
		 {0, 0, 0}},
		{{0, 0, 1},
		 {1, 1, 1},
		 {0, 0, 0}},
		{{1, 0, 0},
		 {1, 1, 1},
		 {0, 0, 0}},
		{{0, 1, 0},
		 {1, 1, 1},
		 {0, 0, 0}},
		{{1, 1},
		 {1, 1}}};

	return EXIT_SUCCESS;
}

//using namespace sf;
//
//const int M = 20;
//const int N = 10;
//
//int field[M][N] = { 0 };
//
//struct Point
//{
//    int x, y;
//} a[4], b[4];
//
//int figures[7][4] =
//{
//    1,3,5,7, // I
//    2,4,5,7, // Z
//    3,5,4,6, // S
//    3,5,4,7, // T
//    2,3,5,7, // L
//    3,5,7,6, // J
//    2,3,4,5, // O
//};
//
//bool check()
//{
//    for (int i = 0; i < 4; i++) {
//        if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) {
//            return 0;
//        }
//        else if (field[a[i].y][a[i].x]) {
//            return 0;
//        }
//    }
//    return 1;
//};
//
//
//int main()
//{
//    srand(time(0));
//
//    RenderWindow window(VideoMode(320, 480), "The Game!");
//
//    Texture t1, t2, t3;
//    t1.loadFromFile("tetris/tiles.png");
//    t2.loadFromFile("tetris/background.png");
//    t3.loadFromFile("tetris/frame.png");
//
//    Sprite s(t1), background(t2), frame(t3);
//
//    int dx = 0;
//    bool rotate = 0;
//    int colorNum = 1;
//    float timer = 0, delay = 0.3;
//
//    Clock clock;
//
//    while (window.isOpen())
//    {
//        float time = clock.getElapsedTime().asSeconds();
//        clock.restart();
//        timer += time;
//
//        Event e;
//        while (window.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//                window.close();
//
//            if (e.type == Event::KeyPressed)
//                if (e.key.code == Keyboard::Up) rotate = true;
//                else if (e.key.code == Keyboard::Left) dx = -1;
//                else if (e.key.code == Keyboard::Right) dx = 1;
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
//
//        //// <- Move -> ///
//        for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
//        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
//
//        //////Rotate//////
//        if (rotate)
//        {
//            Point p = a[1]; //center of rotation
//            for (int i = 0; i < 4; i++)
//            {
//                int x = a[i].y - p.y;
//                int y = a[i].x - p.x;
//                a[i].x = p.x - x;
//                a[i].y = p.y + y;
//            }
//            if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
//        }
//
//        ///////Tick//////
//        if (timer > delay)
//        {
//            for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
//
//            if (!check())
//            {
//                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
//
//                colorNum = 1 + rand() % 7;
//                int n = rand() % 7;
//                for (int i = 0; i < 4; i++)
//                {
//                    a[i].x = figures[n][i] % 2;
//                    a[i].y = figures[n][i] / 2;
//                }
//            }
//
//            timer = 0;
//        }
//
//        ///////check lines//////////
//        int k = M - 1;
//        for (int i = M - 1; i > 0; i--)
//        {
//            int count = 0;
//            for (int j = 0; j < N; j++)
//            {
//                if (field[i][j]) count++;
//                field[k][j] = field[i][j];
//            }
//            if (count < N) k--;
//        }
//
//        dx = 0; rotate = 0; delay = 0.3;
//
//        /////////draw//////////
//        window.clear(Color::White);
//        window.draw(background);
//
//        for (int i = 0; i < M; i++)
//            for (int j = 0; j < N; j++)
//            {
//                if (field[i][j] == 0) continue;
//                s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
//                s.setPosition(j * 18, i * 18);
//                s.move(28, 31); //offset
//                window.draw(s);
//            }
//
//        for (int i = 0; i < 4; i++)
//        {
//            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
//            s.setPosition(a[i].x * 18, a[i].y * 18);
//            s.move(28, 31); //offset
//            window.draw(s);
//        }
//
//        window.draw(frame);
//        window.display();
//    }
//
//    return 0;
//}

//int main(int argc, char** argv)
//{
//	sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
//	sf::Texture tiles;
//	if (!tiles.loadFromFile("tetris\\tiles.png"))
//	{
//		std::cerr << "Could not load tiles.png" << std::endl;
//	}
//	sf::Sprite tiles_sprite(tiles);
//	tiles_sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));
//
//	int16_t dx = 0;
//	bool rotate = false;
//	int16_t color_num = 1;
//	float timer{ 0.f };
//	float delay{ 0.f };
//	sf::Clock clock;
//
//	window.setSize(sf::Vector2u(1,2));
//	while (window.isOpen())
//	{
//		float time = clock.getElapsedTime().asSeconds();
//		clock.restart();
//		timer += time;
//
//
//		sf::Event ev;
//		while (window.pollEvent(ev))
//		{
//			if (ev.type == sf::Event::Closed
//				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
//			{
//				window.close();
//			}
//			if (ev.type == sf::Event::KeyPressed)
//			{
//				if (ev.key.code == sf::Keyboard::Up)
//				{
//					rotate = true;
//				}
//				else if (ev.key.code == sf::Keyboard::Left)
//				{
//					dx = -1;
//				}
//				else if (ev.key.code == sf::Keyboard::Right)
//				{
//					dx = 1;
//				}
//			}
//		}
//
//		// move
//
//		for (int16_t i = 0; i < 4; ++i)
//		{
//			a[i].x += dx;
//		}
//
//		// rotate
//		if (rotate)
//		{
//			Point p = a[1];
//			for (int16_t i = 0; i < 4; ++i)
//			{
//				int16_t x = a[i].y - p.y;
//				int16_t y = a[i].x - p.x;
//				a[i].x = p.x - x;
//				a[i].y = p.y + y;
//			}
//		}
//
//		// tick
//		if (timer > delay)
//		{
//			for (int16_t i = 0; i < 4; ++i)
//			{
//				a[i].y += 0.1;
//			}
//			timer = 0;
//		}
//
//		int16_t n{ 3 };
//		if (a[0].x == 0)
//		{
//			for (int16_t i = 0; i < 4; ++i)
//			{
//				a[i].x = figures[n][i] % 2;
//				a[i].y = figures[n][i] / 2;
//			}
//		}
//
//		dx = 0; rotate = 0;
//
//		window.clear(sf::Color::Magenta);
//
//		for (int16_t i = 0; i < 4; ++i)
//		{
//			tiles_sprite.setPosition(a[i].x * 18, a[i].y * 18);
//			window.draw(tiles_sprite);
//
//		}
//		window.display();
//	}
//
//
//
//
//	return 0;
//}

//int main()
//{
//	srand(static_cast<unsigned>(time(0)));
//
//
//	Platformer pl;
//	while (pl.getWindow().isOpen())
//	{
//		pl.update();
//		pl.render();
//	}
//	return EXIT_SUCCESS;
//	using namespace sf;
//	RenderWindow window(VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Mario");
//
//	Texture background;
//	background.loadFromFile("background.jpg");
//	Sprite sprite_background;
//	sprite_background.setTexture(background);
//	sprite_background.setTextureRect(sf::IntRect(300, 300, 1280, 800));
//	Font font;
//	font.loadFromFile("C:\\Windows\\Fonts\\times.ttf");
//	Text text[3]{ {"", font, 25}, {"", font, 25}, {"", font, 25} };
//	text[0].setPosition(10, 10);
//	text[1].setPosition(10, 50);
//	text[2].setPosition(10, 90);
//
//	sf::RectangleShape Map(sf::Vector2f(WIDTH_WINDOW / WIDTH_MAP, HEIGHT_WINDOW / HEIGHT_MAP));
//
//	pPlayer person("robo_character.png"), person_2("robo_character.png");
//	Clock ClockTact, ClockFPS;
//
//	float fps{ 0 };
//	while (window.isOpen()) {
//		sf::Int64 time = ClockTact.getElapsedTime().asMicroseconds();
//		float time_ms = ClockFPS.getElapsedTime().asSeconds();
//		if (time_ms > 0.5f) {
//			ClockFPS.restart();
//			text[2].setString("Current frame: " + std::to_string(person.GetCurrentFrame()));
//		}
//
//		ClockTact.restart();
//		time /= 1000;
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//				window.close();
//		}
//		if (!AnyKeyPressed(sf::Keyboard::Left, sf::Keyboard::Right,
//			sf::Keyboard::Up, sf::Keyboard::Down)) {
//			text[0].setString("Pressed key: none");
//			person.ChangeCurrentFrame(SPEED_FRAME * time);
//			if (person.GetCurrentFrame() > NUM_FRAME_STAND) {
//				person.ChangeCurrentFrame(-NUM_FRAME_STAND);
//			}
//			person.ChangeSprite(IntRect(320 *
//				static_cast<int>(person.GetCurrentFrame()), 0, 320, 330));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Left)) {
//			text[0].setString("Pressed key: LEFT");
//			person.SetDX(-SPEED_CHARACTER);
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::Right)) {
//			text[0].setString("Pressed key: RIGHT");
//			person.SetDX(SPEED_CHARACTER);
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Up)) {
//			text[0].setString("Pressed key: UP");
//			if (person.GetGround()) {
//				person.SetDY(-ACCELERATION_FALL);
//				person.SetGround(false);
//			}
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Down)) {
//			text[0].setString("Pressed key: DOWN");
//			if (!person.GetGround()) {
//				person.SetDY(ACCELERATION_FALL * FALL);
//				person.SetGround(false);
//			}
//		}
//
//		/*if (!AnyKeyPressed(sf::Keyboard::A, sf::Keyboard::D,
//			sf::Keyboard::W, sf::Keyboard::S)) {
//			person_2.ChangeCurrentFrame(SPEED_FRAME * time);
//			if (person_2.GetCurrentFrame() > NUM_FRAME_STAND) {
//				person_2.ChangeCurrentFrame(-NUM_FRAME_STAND);
//			}
//			person_2.ChangeSprite(IntRect(320 *
//				static_cast<int>(person_2.GetCurrentFrame()), 0, 320, 330));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::W)) {
//			if (person_2.GetGround()) {
//				person_2.SetDY(ACCELERATION_FALL);
//				person_2.SetGround(false);
//			}
//		}
//		if (Keyboard::isKeyPressed(Keyboard::A)) {
//			person_2.SetDX(-SPEED_CHARACTER);
//		}
//		if (Keyboard::isKeyPressed(Keyboard::D)) {
//			person_2.SetDX(SPEED_CHARACTER);
//		}*/
//		/*if (Keyboard::isKeyPressed(Keyboard::Up)) {
//			text.setString("KEY UP");
//			person.MovePerson(0, -SPEED_CHARACTER * time);
//			person.ChangeCurrentFrame(SPEED_FRAME * time);
//			if (person.GetCurrentFrame() > NUM_FRAME) {
//				person.ChangeCurrentFrame(-NUM_FRAME);
//			}
//			person.ChangeSprite(IntRect(205 *
//				static_cast<int>(person.GetCurrentFrame()), 850, 195, 240));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Down)) {
//			text.setString("KEY DOWN");
//			person.MovePerson(0, SPEED_CHARACTER * time);
//			person.ChangeCurrentFrame(SPEED_FRAME * time);
//			if (person.GetCurrentFrame() > NUM_FRAME) {
//				person.ChangeCurrentFrame(-NUM_FRAME);
//			}
//			person.ChangeSprite(IntRect(205 *
//				static_cast<int>(person.GetCurrentFrame()), 50, 195, 240));
//		}*/
//		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
//			return EXIT_SUCCESS;
//		}
//		person.update(time);
//		//person_2.update(time);
//		text[1].setString(std::to_string(person.GetDY()));
//		window.clear(sf::Color::Cyan);
//
//		try {
//			for (int16_t i{ 0 }; i < HEIGHT_MAP; ++i) {
//				for (int16_t j{ 0 }; j < WIDTH_MAP; ++j) {
//					if (TileMap_[i][j] == 'B') Map.setFillColor(sf::Color::Yellow);
//					if (TileMap_[i][j] == ' ') Map.setFillColor(sf::Color::Green);
//					Map.setPosition(j * W_BLOCK_SIZE, i * H_BLOCK_SIZE);
//					window.draw(Map);
//				}
//			}
//		}
//		catch (std::exception& err) {
//			std::cerr << "Draw block" << std::endl;
//			std::cerr << err.what() << std::endl;
//		}
//		//window.draw(sprite_background);
//		window.draw(person.GetSprite());
//		//window.draw(person_2.GetSprite());
//		//window.draw(text[0]);
//		//window.draw(text[1]);
//		//window.draw(text[2]);
//		window.display();
//	}
//
//	/*Texture t;
//	t.loadFromFile("retro_character.png");
//	float CurrentFrame{ 0.f };
//	Sprite s;
//
//	auto reset = [&]() mutable {
//		s.setTexture(t);
//		s.setTextureRect(IntRect(205, 40, 210, 240));
//		s.setPosition(50, 100);
//		CurrentFrame = 0;
//	};
//	reset();
//	while (window.isOpen())
//	{
//		Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//				window.close();
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::Left)) {
//			text.setString("KEY LEFT");
//			s.move(-SPEED_CHARACTER, 0);
//			CurrentFrame += SPEED_FRAME;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			s.setTextureRect(IntRect(205 * static_cast<int>(CurrentFrame),
//				565, 195, 270));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Right)) {
//			text.setString("KEY RIGHT");
//			if (Keyboard::isKeyPressed(Keyboard::Up) ||
//				Keyboard::isKeyPressed(Keyboard::Down))
//				CurrentFrame += SPEED_FRAME/2;
//			else
//				CurrentFrame += SPEED_FRAME;
//			s.move(SPEED_CHARACTER, 0);
//
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			s.setTextureRect(IntRect(205 * static_cast<int>(CurrentFrame),
//				290, 195, 270));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Up)) {
//			text.setString("KEY UP");
//			s.move(0, -SPEED_CHARACTER);
//			CurrentFrame += SPEED_FRAME;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			s.setTextureRect(IntRect(205 * static_cast<int>(CurrentFrame),
//				850, 195, 270));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Down)) {
//			text.setString("KEY DOWN");
//			s.move(0, SPEED_CHARACTER);
//			CurrentFrame += SPEED_FRAME;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			s.setTextureRect(IntRect(205 * static_cast<int>(CurrentFrame),
//				50, 195, 240));
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
//			return EXIT_SUCCESS;
//		}
//		if (Keyboard::isKeyPressed(Keyboard::Tilde)) {
//			reset();
//		}
//
//		text.setPosition(10, 10);
//
//		window.clear();
//		window.draw(s);
//		window.draw(text);
//		window.display();
//	}*/
//
//	return EXIT_SUCCESS;
//}
