#include "Game.h"

Game::Game()
{
	key_moving = ' ';
	g_process=g_running = true;
	max_level = 5;
	count_P = 0;
	score = 5;
	level = 5;
	speed = 50;
	state_S = 1;
}


Game::Game(const short& width, const short& height, const wstring& title, const bool& cursor)
{
	Console_Game console;
	console.FixConsoleWindow();
	console.SetSize(width, height);
	console.SetCursor(cursor);
	console.QuickEdit(cursor);
	//console.SetBufferSize();
	SetConsoleTitleW(title.c_str());
	SetConsoleOutputCP(CP_UTF8);
	key_moving = ' ';
	g_process=g_running = true;
	max_level = 5;
	count_P = 0;
	score = 0;
	level = 1;
	speed = 100;
	state_S = 1;

}

void Game::DrawGameBoard(const COORD& pos, const Color& color)
{
	Console_Game console;
	gameboard = { pos.X,pos.Y,40 + 120,2 + 43 };

	system("cls");
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE),pos, "Graphic/Game_Board.txt", color);
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { short(pos.X + 135),pos.Y }, "Graphic/score.txt", color);
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { short(pos.X + 135),short(pos.Y+ 10) }, "Graphic/level.txt", color);
}


void Game::Create_Map()
{
	DrawGameBoard({ 40,2 }, Color::aqua);
}

void Game::Initialize_setting()
{
	Console_Game Console_G;
	Console_Game console;
	system("cls");
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 80,5 }, "Graphic/KhungSetting.txt", Color::blue);
}

void Game::Initialize_Cars()
{
	Clear_Cars();
	for (int i = 0; i < 3; i++)
	{
		List_car.push_back(new Car({ short(gameboard.left - 20),9 }, 19, 3, "Vehicle/Car.txt", 0, 0,gameboard,Color::red));
		List_carR.push_back(new Car({ short(gameboard.right + 20),14 }, 19, 3, "Vehicle/carReverse.txt", 1, 0, gameboard, Color::red));
	}
}
void Game::Initialize_Trucks()
{
	Clear_Trucks();
	for (int i = 0; i < 3; i++)
	{
		List_Truck.push_back(new Truck({ short(gameboard.left - 32),23 }, 31, 4, "Vehicle/Truck.txt", 0, 0, gameboard,Color::lightpurple));
	}
}
void Game::Initialize_Dogs()
{
	Clear_Dogs();
	for (int i = 0; i < 4; i++)
	{
		List_Dogs.push_back(new Dog({ short(gameboard.left -10),38 }, 9, 4, "Animal/Dog.txt", 0, 0, gameboard,Color::yellow));
	}
}
void Game::Initialize_Snakes()
{
	Clear_Snakes();
	for (int i = 0; i < 4; i++)
	{
		List_Snakes.push_back(new Snake({ short(gameboard.right + 11 ),34 }, 11, 3, "Animal/Snake.txt", 1, 0, gameboard,Color::green));
	}
}
void Game::Initialize_Characters()
{
	count_P = 0;
	Clear_People();
	for (int i = 0; i < 3; i++)
		People.push_back(Character({ 50,short(gameboard.bottom -2) }, 7, 4, "Graphic/Character.txt", 0,gameboard,Color::white));
	People[count_P].Alive();
	Human = People[count_P];
}
void Game::Initialize_Menu()
{
	Clear_Menu();
	menu = new Menu();
}

void Game::Clear_Cars()
{
	if (!List_car.empty())
	{
		for (auto& car : List_car)
		{
			delete car;
			car = nullptr;
		}
		List_car.clear();
	}
	if (!List_carR.empty())
	{
		for (auto& car : List_carR)
		{
			delete car;
			car = nullptr;
		}
		List_carR.clear();
	}
}
void Game::Clear_Trucks()
{
	if (!List_Truck.empty())
	{
		for (auto& truck : List_Truck)
		{
			delete truck;
			truck = nullptr;
		}
		List_Truck.clear();
	}
}
void Game::Clear_Dogs()
{
	if (!List_Dogs.empty())
	{
		for (auto& Dog : List_Dogs)
		{
			delete Dog;
			Dog = nullptr;
		}
		List_Dogs.clear();
	}
}
void Game::Clear_Snakes()
{
	if (!List_Snakes.empty())
	{
		for (auto& Snake : List_Snakes)
		{
			delete Snake;
			Snake = nullptr;
		}
		List_Snakes.clear();
	}
}
void Game::Clear_People()
{
	if (!People.empty())
	{
		People.clear();
	}
}
void Game::Clear_Menu()
{
	delete menu;
}


template<class T>
void Game::Object_Moving(vector<T*> Obj,const bool &con)
{
	for (int i = 0; i < Obj.size(); i++)
	{
		if (Obj[i]->isMoving()) Obj[i]->Moving();
		else
		{
			Obj[i]->Set_Moving(con);
			for (int j = 0; j < Obj.size(); j++)
			{
				if (Obj[j]->isMoving() && i != j)
				{
					if (abs(Obj[j]->GetX() - Obj[i]->GetX()) - Obj[j]->GetWidth() < 16)
					{
						Obj[i]->Stop();
						break;
					}
				}
			}
		}
	}
}

template<class T>
void Game::DrawStoping_Object(vector<T*> Obj)
{
	for (int i = 0; i < Obj.size(); i++)
	{
		Obj[i]->Draw();
	}
}

void Game::Update_Character()
{
	Human.Crashed(People);
	Human.Moving(key_moving);
	key_moving = ' ';
	if (Human.Character_ontop())
	{
		score = score + 100;
		if (count_P==2)
		{
			level++;
			speed -= 10;
			Create_Map();
			DrawStoping_Object(List_car);
			DrawStoping_Object(List_carR);
			DrawStoping_Object(List_Truck);
			Initialize_Characters();
		}
		else
		{
			People[count_P] = Human;
			count_P++;
			People[count_P].Alive();
			Human = People[count_P];
		}
	}
}

bool Game::WinGame()
{
	if (level > max_level)
		return true;
	return false;
}

bool Game::GameOver()
{
	if (Human.Crashed_veh(List_car) || Human.Crashed_veh(List_Truck) || Human.Crashed_animal(List_Snakes) || Human.Crashed_animal(List_Dogs) || Human.Crashed_veh(List_carR) )
	{
		return true;
	}
	return false;
}
void Game::Dead_Screen()
{
	Sound sound;
	Console_Game console;
	sound.Lose();
	system("cls");
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 70,3 }, "Graphic/CharacterDead.txt", Color::lightpurple);
	Sleep(3500);
	system("cls");
	console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 75,20 }, "Graphic/KhungChet.txt", Color::lightblue);
}


void Game::ResetGame()
{
	Create_Map();
	score = 0;
	level = 1;
	speed = 100;
	Initialize_Cars();
	Initialize_Trucks();
	Initialize_Dogs();
	Initialize_Snakes();

	Initialize_Characters();
	tf_car = TrafficLight({ short(gameboard.right ),7 }, 5, 6, "Vehicle/TracfficLight.txt",gameboard,1);
	tf_truck = TrafficLight({ short(gameboard.right ),22 }, 5, 6, "Vehicle/TracfficLight.txt", gameboard,0);
}
void Game::StartGame()
{
	while (g_running && !GameOver())
	{
		Update_Character();
		tf_car.Run();
		tf_truck.Run();
		if (tf_car.GetState() == true)
		{
			Object_Moving(List_car, 1);
			Object_Moving(List_carR, 1);
			
		}
		if (tf_truck.GetState() == true)
		{
			Object_Moving(List_Truck, 1);
		}
		
		Object_Moving(List_Snakes, 1);
		Object_Moving(List_Dogs, 1);
		Console_Game::GoToXY({ 40+ 143,5 });
		cout << score;
		Console_Game::GoToXY({ 40 +143,15 });
		cout << level;
		Sleep(speed);
	}

}

void Game::Draw_Setting_S()
{
	Console_Game console;
	if (state_S == 1)
	{
		console.Draw_Text("<", { 110,short(10 + state_S * 7) }, Color::red);
		console.Draw_Text(" ", { 110,short(10 + (state_S + 1) * 7) }, Color::red);
		console.Draw_Text(" ", { 105,short(10 + (4) * 7) }, Color::red);
	}
	else if (state_S == 4)
	{
		console.Draw_Text(" ", { 110,short(10 + 1 * 7) }, Color::red);
		console.Draw_Text("<", { 105,short(10 + state_S * 7) }, Color::red);
		console.Draw_Text(" ", { 110,short(10 + (state_S - 1) * 7) }, Color::red);
	}
	else if (state_S==3)
	{
		console.Draw_Text(" ", { 105,short(10 + (state_S + 1) * 7) }, Color::red);
		console.Draw_Text("<", { 110,short(10 + state_S * 7) }, Color::red);
		console.Draw_Text(" ", { 110,short(10 + (state_S - 1) * 7) }, Color::red);
	}
	else if (state_S == 2)
	{
		console.Draw_Text(" ", { 110,short(10 + (state_S + 1) * 7) }, Color::red);
		console.Draw_Text("<", { 110,short(10 + state_S * 7) }, Color::red);
		console.Draw_Text(" ", { 110,short(10 + (state_S - 1) * 7) }, Color::red);
	}
}

void Game::Gameplay()
{
	if(profile_load.empty())
		ResetGame();
	Run_Game = thread(&Game::StartGame, this);
	Console_Game console;
	Sound sound;
	char _key=' ', choice, key_setting;
	while (g_process)
	{
		if (GameOver()) // LOSE
		{
			if (g_running)
			{
				g_running = false;
				Run_Game.join();
			}
			Dead_Screen();
			while (true)
			{
				choice = toupper(_getch());
				if (choice == 'Y')
				{

					ResetGame();
					g_running = true;
					Run_Game = std::thread(&Game::StartGame, this);
					break;
				}
				if (choice == 'N')
				{
					system("cls");
					g_process = false;
					break;
				}
			}
		}
		if (WinGame())
		{
			
			if (g_running)
			{
				g_running = false;
				Run_Game.join();
			}
			system("cls");
			console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 50,10 }, "Graphic/Victory.txt", Color::yellow);
			sound.Victory();
			Sleep(3500);
			system("cls");
			console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 80,20 }, "Graphic/KhungChet.txt", Color::brightwhite);
			while (true)
			{
				choice = toupper(_getch());
				if (choice == 'Y')
				{

					ResetGame();
					g_running = true;
					Run_Game = std::thread(&Game::StartGame, this);
					break;
				}
				if (choice == 'N')
				{
					system("cls");
					g_process = false;
					break;
				}
			}
		}
		if (_kbhit())
		{
			_key = toupper(_getch());
			if (_key == 'P')
			{
				PauseGame();
			}
			else if (_key == 'R')
			{
				if (g_running)
				{
					g_running = false;
					Run_Game.join();
				}
				system("cls");
				ResetGame();
				g_running = true;
				Run_Game = std::thread(&Game::StartGame, this);
			}
			else if (GetAsyncKeyState(VK_ESCAPE)) // Setting
			{
				if (g_running)
				{
					g_running = false;
					Run_Game.join();
				}
				Initialize_setting();
				Draw_Setting_S();
				key_setting = ' ';
				while (true)
				{
					if (_kbhit())
					{
						key_setting = toupper(_getch());
						switch (key_setting)
						{
						case 'W':
							state_S--;
							break;
						case 'S':
							state_S++;
							break;
						}
						if (state_S == 0)
							state_S = 4;
						else if (state_S == 5)
							state_S = 1;
						Draw_Setting_S();
					}
					if (key_setting == char(13))
						break;
				}
				switch (state_S)
				{
				case 1:
					g_running = true;
					Create_Map();
					for (int i = 0; i < count_P; i++)
					{
						People[i].Draw();
					}
					DrawStoping_Object(List_car);
					DrawStoping_Object(List_carR);
					DrawStoping_Object(List_Truck);
					Run_Game = thread(&Game::StartGame, this);
					break;
				case 2:
				{
					string name;
					FlushConsoleInputBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
					system("cls");
					console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 80,20 }, "Graphic/save.txt", Color::yellow);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
					Console_Game::GoToXY({ 90,23 });
					
					cout << "> Enter your save name: ";
					getline(cin, name);
					SaveGame(name);
					system("cls");
					Create_Map();
					for (int i = 0; i < count_P; i++)
					{
						People[i].Draw();
					}
					DrawStoping_Object(List_car);
					DrawStoping_Object(List_carR);
					DrawStoping_Object(List_Truck);
					g_running = true;
					Run_Game = thread(&Game::StartGame, this);
					break;
				}
				case 3: 
				{
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					system("cls");
					string user_name;
					console.DrawGraphics(GetStdHandle(STD_OUTPUT_HANDLE), { 80,20 }, "Graphic/Load.txt", Color::yellow);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(11));
					Console_Game::GoToXY({ 90, 23 });
					cout << "> Enter your file name: ";
					getline(cin, user_name);

					LoadGame(user_name);
					g_running = true;
					Run_Game = thread(&Game::StartGame, this);
					break;
				}
				case 4:
					g_process = false;
					system("cls");

					break;
				}
			}
			else if (g_running)
			{
				key_moving = _key;
			}
		}
	}
	if (Run_Game.joinable())
		Run_Game.join();
}

void Game::PauseGame()
{
	if (g_running)
	{
		g_running = false;
		Run_Game.join();
	}
	else
	{
		g_running = true;
		Run_Game = thread(&Game::StartGame, this);
	}
}

void Game::SaveGame(string filename)
{
	fstream out;
	out.open("save/" + filename + ".txt", ios::out);
	out << level << endl;
	out << score << endl;
	out << speed << endl;
	out << count_P << endl;

	out << "Character: " << endl;
	for (int i = 0; i < count_P; i++)
	{
		out << People[i].GetX() << " " << People[i].GetY() << endl;
	}
	out << Human.GetX() << " " << Human.GetY() << endl;

	out << "Trucks: " << endl;
	for (int i = 0; i < List_Truck.size(); i++)
	{
		out << List_Truck[i]->isMoving() << endl;
		out << List_Truck[i]->GetX() << " " << List_Truck[i]->GetY() << endl;
	}
	out << "Cars: " << endl;
	for (int i = 0; i < List_car.size(); i++)
	{
		out << List_car[i]->isMoving() << endl;
		out << List_car[i]->GetX() << " " << List_car[i]->GetY() << endl;
	}
	out << "CarsR: " << endl;
	for (int i = 0; i < List_carR.size(); i++)
	{
		out << List_carR[i]->isMoving() << endl;
		out << List_carR[i]->GetX() << " " << List_carR[i]->GetY() << endl;
	}
	out << "Dogs: " << endl;
	for (int i = 0; i < List_Dogs.size(); i++)
	{
		out << List_Dogs[i]->isMoving() << endl;
		out << List_Dogs[i]->GetX() << " " << List_Dogs[i]->GetY() << endl;
	}
	out << "Snakes: " << endl;
	for (int i = 0; i < List_Snakes.size(); i++)
	{
		
		out << List_Snakes[i]->isMoving() << endl;
		out << List_Snakes[i]->GetX() << " " << List_Snakes[i]->GetY() << endl;
	}
	out << "TracfficLight: " << endl;
	out << tf_car.GetState() << endl;
	out << tf_truck.GetState() << endl;

	out.close();

}

void Game::LoadGame(string filename)
{
	string name_Obj;
	short X, Y;
	bool state;
	fstream inp;
	inp.open("save/" + filename + ".txt", ios::in);
	if (inp.fail()) {

		inp.close();
		Console_Game::GoToXY({ 90,24 });
		cout << "Cannot load your save !";
		Sleep(3500);
		system("cls");
		Create_Map();
		if(profile_load==filename)
			ResetGame();
		
		return;
	}
	Clear_Cars();
	Clear_Trucks();
	Clear_Dogs();
	Clear_Snakes();
	Clear_People();
	Console_Game::RemoveArea({ 0,0 }, { 150,48 });

	Create_Map();
	inp >> level;
	inp >> score;
	inp >> speed;
	inp >> count_P;
	inp >> name_Obj;

	for (int i = 0; i < 3; i++)
	{
		People.push_back(Character({ 50,short(gameboard.bottom - 2) }, 7, 4, "Graphic/Character.txt", 0, gameboard, Color::white));
	}
	for (int i = 0; i < count_P; i++)
	{
		inp >> X >> Y;
		People[i].SetPos({ X,Y });
		People[i].Draw();
	}			
	inp >> X >> Y;
	People[count_P].SetPos({ X,Y });
	People[count_P].Alive();
	Human = People[count_P];

	inp >> name_Obj;
	for (int i = 0; i < 3; i++)
	{
		inp >> state;
		inp >> X >> Y;
		List_Truck.push_back(new Truck({ X,Y }, 31, 4, "Vehicle/Truck.txt", 0, state, gameboard,Color::lightpurple));
		List_Truck[i]->SetPos({ short(gameboard.left - 32),23 });
		List_Truck[i]->Draw();
	}
	inp >> name_Obj;
	for (int i = 0; i < 3; i++)
	{
		inp >> state;
		inp >> X >> Y;
		List_car.push_back(new Car({ X,Y }, 19, 3, "Vehicle/Car.txt", 0, state, gameboard,Color::red));
		List_car[i]->SetPos({ short(gameboard.left - 20),9 });
		List_car[i]->Draw();
	}
	inp >> name_Obj;
	for (int i = 0; i < 3; i++)
	{
		inp >> state;
		inp >> X >> Y;
		List_carR.push_back(new Car({ X,Y }, 19, 3, "Vehicle/carReverse.txt", 1, state, gameboard, Color::red));
		List_carR[i]->SetPos({ short(gameboard.right + 20),14 });
		List_carR[i]->Draw();
	}
	inp >> name_Obj;
	for (int i = 0; i < 4; i++)
	{
		inp >> state;
		inp >> X >> Y;
		List_Dogs.push_back(new Dog({ X,Y }, 9, 4, "Animal/Dog.txt", 0, state, gameboard,Color::yellow));
		List_Dogs[i]->SetPos({ short(gameboard.left - 10),38 });
		List_Dogs[i]->Draw();
	}
	inp >> name_Obj;
	for (int i = 0; i < 4; i++)
	{
		inp >> state;
		inp >> X >> Y;
		List_Snakes.push_back(new Snake({ X,Y }, 11, 3, "Animal/Snake.txt", 1, state, gameboard,Color::green));
		List_Snakes[i]->SetPos({ short(gameboard.right + 11),34 });
		List_Snakes[i]->Draw();
	}
	inp >> name_Obj;
	inp >> state;
	tf_car = TrafficLight({ short(gameboard.right),7 }, 5, 6, "Vehicle/TracfficLight.txt", gameboard, state);
	inp >> state;
	tf_truck= TrafficLight({ short(gameboard.right),22 }, 5, 6, "Vehicle/TracfficLight.txt", gameboard, state);
	inp.close();

}

void Game::Processing()
{
	Initialize_Menu();
	while (!menu->IsQuit())
	{
		menu->Choose_Menu();
		if (menu->IsPlay())
		{
			g_process = true;
			g_running = true;
			Gameplay();
		}
		else if (menu->IsLoad())
		{
			profile_load = menu->Load();
			if (!profile_load.empty())
			{
				LoadGame(profile_load);
			}
			else
				ResetGame();
			g_process = true;
			g_running = true;
			Gameplay();
		}
		menu->setbool();
	}
}



