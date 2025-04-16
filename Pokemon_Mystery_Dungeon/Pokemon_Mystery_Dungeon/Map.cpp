#include "Map.h"  
#include <algorithm> 
#include <random>
#include "Image.h"

//�ִ� �� ����
const int MAX_ROOMS = 8;

const int MIN_WIDTH = 6;
const int MAX_WIDTH = 10;

const int MIN_HEIGHT = 6;
const int MAX_HEIGHT = 10;
random_device rd;
default_random_engine dre(rd());

uniform_int_distribution uidWidth{ MIN_WIDTH, MAX_WIDTH };
uniform_int_distribution uidHeight{ MIN_HEIGHT, MAX_HEIGHT };
uniform_int_distribution uidDist{ 0,1 };

HRESULT Map::Init()
{
    sampleTile = ImageManager::GetInstance()->AddImage(
        "smapleTile", L"Image/SceneImage/TiniWoods3.bmp",
        525, 600, SAMPLE_TILE_X, SAMPLE_TILE_Y,
        true, RGB(255, 0, 255));

    stairs = ImageManager::GetInstance()->AddImage(
        "stairs", L"Image/SceneImage/stairs.bmp",
        24, 24, 1, 1,
        true, RGB(255, 0, 255)
    );
    floorTiles.clear();
    wallTiles.clear();
    pathTiles.clear();

    Generate();
    ClassifyTiles();
    TileDesign();


    //��� ��ġ ����
    if (!floorTiles.empty()) {
        uniform_int_distribution<int> floorDist(0, floorTiles.size() - 1);
        stairPos = floorTiles[floorDist(dre)];
    }

    return S_OK;
}

void Map::Release()
{
}

void Map::Update()
{
}

void Map::Render(HDC hdc)
{

    //// �̵����� Ÿ��
    for (const POINT& pt : pathTiles) {
        sampleTile->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, 1, 1, 0, 1);
    }
    //// �̵����� Ÿ��
    for (const POINT& pt : floorTiles) {
        sampleTile->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, 13, 1, 0, 1);
    }

    // �̵��Ұ� Ÿ��
    for (const POINT& pt : wallTiles) {
        const auto& index = tileIndex[pt.y][pt.x];
        sampleTile->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, index.first, index.second, 0, 1);
    }
   
    stairs->FrameRender(hdc, stairPos.x * TILE_SIZE, stairPos.y * TILE_SIZE,0,0); //�߾Ӻ��� �׸����� �ϴ� FrameRender��
}

void Map::Generate() {  
    for (int y = 0; y < TILE_Y; ++y) {
        for (int x = 0; x < TILE_X; ++x) {
			tiles[y][x] = TILE_WALL;
        }
   }

   rooms.clear();  


   for (int i = 0; i < MAX_ROOMS; ++i) {  
       Room newRoom;  
       newRoom.width = uidWidth(dre);
       newRoom.height = uidHeight(dre);
       newRoom.x = rand() % (TILE_X - newRoom.width - 1);  
       newRoom.y = rand() % (TILE_Y - newRoom.height - 1);  

       bool overlapped = false;  
       for (const auto& r : rooms) {  
           if (newRoom.Intersects(r)) {  
               overlapped = true;  
               break;  
           }  
       }  

       if (!overlapped) {
           CreateRoom(newRoom);

           if (!rooms.empty()) {
               ConnectRooms(rooms.back(), newRoom);
           }
           rooms.push_back(newRoom);  
       }  
   }  
}  

void Map::Draw(HDC hdc) {  //���� ����� �ұ� ������
    for (int y = 0; y < TILE_Y; ++y) {
        for (int x = 0; x < TILE_X; ++x) {
            RECT rc = { x * TILE_SIZE, y * TILE_SIZE, (x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE };
            HBRUSH brush = (tiles[y][x] == TILE_FLOOR) ? (HBRUSH)GetStockObject(WHITE_BRUSH) : (HBRUSH)GetStockObject(BLACK_BRUSH);
            FillRect(hdc, &rc, brush);
        }
    }
}  

void Map::CreateRoom(const Room& room)
{
    for (int y = room.y; y < room.y + room.height; ++y) {
        for (int x = room.x; x < room.x + room.width; ++x) {
            tiles[y][x] = TILE_FLOOR;
        }
    }
}

void Map::ConnectRooms(const Room& a, const Room& b)
{
    int x1 = a.CenterX(), y1 = a.CenterY();
    int x2 = b.CenterX(), y2 = b.CenterY();

    if (uidDist(dre)) {
        for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
            if (tiles[y1][x] != TILE_FLOOR) {
				tiles[y1][x] = TILE_PATH;
            }
        }
        for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
            if (tiles[y][x2] != TILE_FLOOR) {
				tiles[y][x2] = TILE_PATH;
			}
        }
    }
    else {
        for (int y = min(y1, y2); y <= max(y1, y2); ++y){
            if (tiles[y][x1] != TILE_FLOOR) {
				tiles[y][x1] = TILE_PATH;
            }
        }
        for (int x = min(x1, x2); x <= max(x1, x2); ++x){
            if (tiles[y2][x] != TILE_FLOOR) {
				tiles[y2][x] = TILE_PATH;
            }
        }
    }
}

void Map::ClassifyTiles()
{
    for (int y = 0; y < TILE_Y; ++y) {
        for (int x = 0; x < TILE_X; ++x) {
            if (tiles[y][x] == TILE_FLOOR){
                floorTiles.push_back({ x, y });
            }
            else if (tiles[y][x] == TILE_WALL){
                wallTiles.push_back({ x, y });
            }
            else if (tiles[y][x] == TILE_PATH) {
                pathTiles.push_back({ x,y });
            }
        }
    }
}

void Map::TileDesign()  
{  
   tileIndex.clear();  
   tileIndex.resize(TILE_Y, vector<pair<int, int>>(TILE_X, { 4, 1 })); // �⺻ ��  

   int dx[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };  
   int dy[8] = { 1, -1, 0, 0, -1, -1, 1, 1 };  

   for (int y = 0; y < TILE_Y; ++y) {  
       for (int x = 0; x < TILE_X; ++x) {  
           if (tiles[y][x] != TILE_WALL) continue;  

           for (int i = 0; i < 8; ++i) {  
               int nx = x + dx[i];  
               int ny = y + dy[i];  

               if (nx >= 0 && nx < TILE_X && ny >= 0 && ny < TILE_Y && tiles[ny][nx] == TileType::TILE_FLOOR) {  
                   switch (i) {  
                   case 0: tileIndex[y][x] = { 4, 3 }; break; // ��  
                   case 1: tileIndex[y][x] = { 4, 3 }; break; // �Ʒ�  
                   case 2: tileIndex[y][x] = { 3, 4 }; break; // ����  
                   case 3: tileIndex[y][x] = { 3, 4 }; break; // ������  
                   case 4: tileIndex[y][x] = { 5, 5 }; break; // ����  
                   case 5: tileIndex[y][x] = { 3, 5 }; break; // ����  
                   case 6: tileIndex[y][x] = { 5, 3 }; break; // �޹�  
                   case 7: tileIndex[y][x] = { 3, 3 }; break; // ����  
                   }  
                   break; 
               }  
           }  
       }  
   }  
}

