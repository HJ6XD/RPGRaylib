#include "raylib.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "LLNode.h"
#include "LinkedList.h"
#include "Inventory.h"
#include "Item.h"
#include "PlayerCharacter.h"
#include "Stack.h"
#include "Queue.h"
#include "PanelMensaje.h"
#include <fstream>
#include "EnemyCharacter.h"
#include "Prop.h"
#include "Heap.h"
#include "HeapNode.h"

extern "C" {
	#include "md5.h"
}

typedef std::vector<std::vector<int>> Map2D;
typedef HeapNode<std::string> StringNode;

void LoadMap(Map2D& _map, size_t _x, size_t _y, std::string filename)
{
	std::ifstream filemap(filename);
	if (filemap.is_open()) {
		char c;
		for (size_t j = 0; j < _y; j++) {
			for (size_t i = 0; i < _x; i++) {
				filemap.get(c);
				if (filemap.eof()) {
					std::cout << "final inesperado del archivo de mapa" << std::endl;
					return;
				}
				_map[j][i] = c - '0';
			}
			filemap.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	else
	{
		std::cout << "no se pudo abrir el archivo de mapa" << std::endl;
		return;
	}
}

Music LoadBGM() {
	const char* default = "TECNO1.XM";
	std::fstream configfile("config.ini");
	if (configfile.is_open()) {
		std::string linea;
		char buffer[64];
		while (  std::getline(configfile, linea)  )
		{
			std::cout << "linea leida: " << linea << std::endl;
			char* llave = strtok((char*)linea.c_str(), "=");
			if (strcmp("music", llave) == 0) {
				char* valor = strtok(NULL, "=");
				std::cout << "se encontro la llave music y su valor es: " << valor <<std::endl;
			}
		}
	}
	else {
		std::cout << "no jalo el archivo de configuracion" << std::endl;
		return LoadMusicStream("TECNO1.XM");
	}
}

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	int tileSize = 64;

	int maxTilesH = 15;
	int maxTilesV = 10;

	// Create the window and OpenGL context
	InitWindow(tileSize * maxTilesH, tileSize * maxTilesV, "Ejercicio Tiles");

	//Mapa2D con std::vector
	Map2D mapa(maxTilesV, std::vector<int>(maxTilesH, 0));

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	//Seleccion de mapa
	std::vector<std::string> mapName;
	mapName.push_back("map1.txt");
	mapName.push_back("map2.txt");
	mapName.push_back("map3.txt");

	bool mapSelected = false;
	int mapaSeleccionado = 0;

	//Prueba de Inventorio
	Inventory* inventario = new Inventory();
	inventario->AddItem(new Item("Espada", 1));
	inventario->AddItem(new Item("Arco", 2));
	inventario->AddItem(new Item("Panucho", 3));
	inventario->debugPrintContents();
	std::cout << inventario->GetCurrentItemName();

	std::vector<GameObject*> gameObjects;

	//crear al jugador
	PlayerCharacter* player = new PlayerCharacter("Jose Jose");
	//player->inventory = inventario;
	player->Start();
	player->inventory->AddItem(new Item("EspaDA DEL AUGUERIO", 1));
	player->inventory->AddItem(new Item("Espada", 2));
	player->inventory->AddItem(new Item("Arco", 3));
	player->inventory->AddItem(new Item("Panucho", 4));
	//inventario->AddItem(new Item("Arco", 2));
	//inventario->AddItem(new Item("Panucho", 3));
	player->inventory->debugPrintContents();
	player->inventory->GetCurrentItemName();

	player->printUID();
	gameObjects.push_back(player);

	std::cout << player->inventory->GetCurrentItemName();

	//crear enemigos
	EnemyCharacter* ted = new EnemyCharacter("Ted", player, 10, 10);
	gameObjects.push_back(ted);
	ted->Start();
	EnemyCharacter* fred = new EnemyCharacter("Fred", player, 100, 10);
	gameObjects.push_back(fred);
	fred->Start();
	EnemyCharacter* ned = new EnemyCharacter("Ned", player, 10, 100);
	gameObjects.push_back(ned);
	ned->Start();


	//panel de mensaje
	PanelMensaje* panel = new PanelMensaje(GetScreenWidth() - 210, 200, 50, 2);
	//para la prueba simularemos que obtiene muvhos logors
	panel->show("thief");
	panel->show("gosip");
	panel->show("fisher");
	panel->show("hoarder");

	//props
	Prop* mesa1 = new Prop("mesa", 120, 300, 20, player);
	gameObjects.push_back(mesa1);
	Prop* mesa2 = new Prop("mesa", 320, 100, 50, player);
	gameObjects.push_back(mesa2);

	//Heap
	Heap<std::string>* warningHeap = new Heap<std::string>();
	Heap<const char*>* warningH2 = new Heap<const char*>();

	Heap<int>* heapInt = new Heap<int>();
	heapInt->insert(65427, 2);
	heapInt->insert(7682, 8);
	heapInt->insert(12345, 10);



	std::string warning1 = "recibiste dano!";
	const char* cwar1 = "recibiste dano!";
	warningHeap->insert(warning1, 10);
	warningH2->insert(cwar1, 10);

	std::string warning2 = "agarraste una moneda!";
	const char* cwar2 = "agarraste una moneda";
	warningH2->insert(cwar2, 2);
	warningHeap->insert(warning2, 2);
	warningH2->insert("warning3", 3);
	warningH2->insert("warning4", 4);
	warningH2->insert("warning5", 5);

	//std::cout << warningH2->extract() << std::endl;

	std::string warning3 = "golpeaste un enemigo!";
	warningHeap->insert(warning3, 5);

	std::string warning4 = "te estrellaste!";
	
	warningHeap->insert(warning4, 12);

	PanelMensaje* warnings = new PanelMensaje(GetScreenWidth() /2 - 60, 120, 50, 2);

	

	while (!mapSelected && !WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKGREEN);
		DrawText("Para Elegir pulsa 1, 2 o 3 en tu teclado",  GetScreenWidth() / 2 - 200, 100, 20, WHITE);
		DrawText("Mapa 1 (1)", GetScreenWidth() / 2 -80, 150, 16, YELLOW);
		DrawText("Mapa 2 (2)",  GetScreenWidth() / 2 -80, 190, 16, YELLOW);
		DrawText("Mapa 3 (3)",  GetScreenWidth() / 2 -80, 230, 16, YELLOW);
		EndDrawing();
		if (IsKeyPressed(KEY_ONE)) {
			mapaSeleccionado = 0;
			mapSelected = true;
		}
		if (IsKeyPressed(KEY_TWO)) {
			mapaSeleccionado = 1;
			mapSelected = true;
		}
		if (IsKeyPressed(KEY_THREE)) {
			mapaSeleccionado = 2;
			mapSelected = true;
		}
	}
	LoadMap(mapa, maxTilesH, maxTilesV, mapName[mapaSeleccionado]);

	// Cargar nuestros tiles
	enum TileType {
		naranja, blanca, morada, azul
	};
	Texture tiles[4];

	tiles[0] = LoadTexture("Naranja.png");
	tiles[1] = LoadTexture("Blanca.png");
	tiles[2] = LoadTexture("Morada.png");
	tiles[3] = LoadTexture("Azul.png");


	// Audio
	std::vector<std::string> musicName;
	musicName.push_back("TECNO1.XM");
	musicName.push_back("ILUETNI.XM");
	musicName.push_back("LIRIUM.XM");

	InitAudioDevice();
	Music bgm = LoadMusicStream(musicName[mapaSeleccionado].c_str());
	PlayMusicStream(bgm);

	char buffer[64];

	// game loop
	while (mapSelected && !WindowShouldClose())
	{
		panel->update();
		warnings->update();

		//updtae de enemigos
		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i]->getEnable() == true)
				gameObjects[i]->Update();
			else
				continue;
		}

		UpdateMusicStream(bgm);

		if (IsKeyPressed(KeyboardKey::KEY_G)) {
			panel->show("mondongo");
		}
		if (IsKeyPressed(KeyboardKey::KEY_T)) {
			std::string s = std::string( warningHeap->extract());
			std::cout << s << std::endl;
			warnings->show( s);
		}

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(SKYBLUE);

		for (int i = 0; i < maxTilesV; i++) { 
			for (int j = 0; j < maxTilesH; j++) {
				DrawTexture(tiles[mapa[i][j]], j * tileSize - player->cameraOffset.x, i * tileSize - player->cameraOffset.y, WHITE);
			}
		}		

		panel->draw();
		warnings->draw();
		for (int i = 0; i < gameObjects.size(); i++) {
			if (gameObjects[i]->getEnable() == true)
				gameObjects[i]->Draw();
			else
				continue;
		}

		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(player->texture);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
