#include "Map.h"  
#include <algorithm> 
#include <random>
#include "Image.h"

//�ִ� �� ����
const int MAX_ROOMS = 8;

const int MIN_WIDTH = 4;
const int MAX_WIDTH = 6;

const int MIN_HEIGHT = 4;
const int MAX_HEIGHT = 6;
random_device rd;
default_random_engine dre(rd());

uniform_int_distribution uidWidth{ MIN_WIDTH, MAX_WIDTH };
uniform_int_distribution uidHeight{ MIN_HEIGHT, MAX_HEIGHT };
uniform_int_distribution uidDist{ 0,1 };

HRESULT Map::Init()
{
    {

        tiniWoods = ImageManager::GetInstance()->AddImage(
            "TiniWoods3", L"Image/SceneImage/TiniWoods3.bmp",
            525, 600, SAMPLE_TILE_X, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));

        sea1 = ImageManager::GetInstance()->AddImage(
            "Sea1", L"Image/SceneImage/Sea1.bmp",
            525, 600, 18, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));

        sea2 = ImageManager::GetInstance()->AddImage(
            "Sea3", L"Image/SceneImage/Sea3.bmp",
            450, 600, 18, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));


        magma1 = ImageManager::GetInstance()->AddImage(
            "MagmaCave1", L"Image/SceneImage/MagmaCave1.bmp",
            525, 600, 21, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));


        ice1 = ImageManager::GetInstance()->AddImage(
            "IceMountain1", L"Image/SceneImage/IceMountain1.bmp",
            675, 600, 27, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));

        ice2 = ImageManager::GetInstance()->AddImage(
            "IceMountain2", L"Image/SceneImage/IceMountain2.bmp",
            675, 600, 27, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));
        //--
        magma2 = ImageManager::GetInstance()->AddImage(
            "MagmaCave2", L"Image/SceneImage/MagmaCave2.bmp",
            750, 600, 30, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));
        tiniMeadow = ImageManager::GetInstance()->AddImage(
            "TinyMeadow", L"Image/SceneImage/TinyMeadow.bmp",
            750, 600, 30, SAMPLE_TILE_Y,
            true, RGB(255, 0, 255));
        //--

        stairs = ImageManager::GetInstance()->AddImage(
            "stairs", L"Image/SceneImage/stairs.bmp",
            24, 24, 1, 1,
            true, RGB(255, 0, 255));
    }

    floorTiles.clear();
    wallTiles.clear();
    pathTiles.clear();

    Generate();
    ClassifyTiles();

    TileDesign();
    RandomTileDesign();

    //���
    if (!floorTiles.empty()) {
        uniform_int_distribution<int> floorDist(0, floorTiles.size() - 1);
        stairPos = floorTiles[floorDist(dre)];
    }

    tileImage = tiniWoods;

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
        tileImage->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, 13, 1, 0, 1);
    }
    //// �̵����� Ÿ��
    for (const POINT& pt : floorTiles) {
        if (tileIndex[pt.y][pt.x] != make_pair(12, 0) and 
            tileIndex[pt.y][pt.x] != make_pair(13, 2) and 
            tileIndex[pt.y][pt.x] != make_pair(14, 1)) {
			tileImage->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, 13, 1, 0, 1);
        }
        else {
            const auto& index = tileIndex[pt.y][pt.x];
            tileImage->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, index.first, index.second, 0, 1);
        }
    }

    // �̵��Ұ� Ÿ��
    for (const POINT& pt : wallTiles) {
        const auto& index = tileIndex[pt.y][pt.x];
        tileImage->FrameRender(hdc, pt.x * TILE_SIZE, pt.y * TILE_SIZE, index.first, index.second, 0, 1);
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
	tileIndex.resize(TILE_Y, vector<pair<int, int>>(TILE_X, { 4, 1 })); // �⺻ �� Ÿ��

	auto InBounds = [](int x, int y) {
		return x >= 0 && x < TILE_X && y >= 0 && y < TILE_Y;
		};

	auto IsPathOrFloor = [&](int x, int y) {
		return tiles[y][x] == TileType::TILE_PATH || tiles[y][x] == TileType::TILE_FLOOR;
		};

    // ���� �� �Լ�
    auto MatchPattern = [](const WildPattern& pattern, const vector<int>& current) -> bool {
        for (int i = 0; i < DIR_COUNT; ++i) {
            if (pattern[i] == -1) continue;
            if (pattern[i] != current[i]) return false;
        }
        return true;
        };

	vector<WildTilePattern> tilePatterns = {
		// {����, ��, ����, ��, ��, �޾�, �Ʒ�, ���Ʒ�}  1:floor, 0:wall
        { { 1, 1, -1,
            1,    0,
           -1, 0,  0 }, {3, 0} },
        
        { { 1, 1, 1, 0, 0, 0, 0, 0 }, {4, 0} },
        
        { { 1, 1, 0, 0, 0, 0, 0, 0 }, {4, 0} },
        { { 0, 1, 1, 0, 0, 0, 0, 0 }, {4, 0} },
        
        { { -1, 1, 1,
             0,    1,
             0, 0, -1 }, {5, 0} },
        
        { { 1, 0, 0, 1, 0, 1, 0, 0 }, {3, 1} },
        { { 0, 0, 0, 1, 0, 1, 0, 0 }, {3, 1} },
        { { 1, 0, 0, 1, 0, 0, 0, 0 }, {3, 1} },
        { { 0, 0, 0, 0, 0, 0, 0, 0 }, {4, 1} },
        
        { { 0, 0, 1, 0, 1, 0, 0, 1 }, {5, 1} },
        { { 0, 0, 0, 0, 1, 0, 0, 1 }, {5, 1} },
        { { 0, 0, 1, 0, 1, 0, 0, 0 }, {5, 1} },
        
        { { -1, 0, 0,
             1,    0,
             1, 1, -1 }, {3, 2} },
        
        { { 0, 0, 0, 0, 0, 1, 1, 1 }, {4, 2} },
        { { 0, 0, 0,
             0,    0,
             0, 1, 1 }, {4, 2} },
        { { 0, 0, 0, 0, 0, 1, 1, 0 }, {4, 2} },
        
        { { 0, 0, -1,
             0,    1,
            -1, 1, 1 }, {5, 2} },
        
        { { 1, 1, 1, 1, 0, 1, 0, 1 }, {3, 3} },
        
        { { -1, 1, -1,
              0,    0,
             -1, 1, -1 }, {4, 3} },
        
        { { 1, 1, 1, 0, 1, 1, 0, 1 }, {5, 3} },
        
        { { -1, 0, -1,
              1,    1,
             -1, 0, -1 }, {3, 4} },
        
        { { 1, 1, 1, 1, 1, 1, 1, 1 }, {4, 4} },
        
        { { 1, 0, 1, 1, 0, 1, 1, 1 }, {3, 5} },
        
        { { 1, 0, 1, 0, 1, 1, 1, 1 }, {5, 5} },
        
        { { 1, 1, 1, 1, 1, -1, 0, -1 }, {4, 6} },
        
        { { 1, 1, 1, 1, 0, 1, 1, -1 }, {3, 7} },
        { { 1, 0, 1, 0, 0, 1, 0, 1 }, {4, 7} },
        { { 1, 1, 1, 0, 1, -1, 1, 1 }, {5, 7} },
        
        { { 1, 0, 1, 1, 1, 1, 1, 1 }, {4, 8} },
        
        { { 1, 1, 1, 0, 0, 1, 0, 1 }, {4, 9} },
        
        { { 1, 0, 1, 1, 0, 1, 0, 1 }, {3, 10} },
        
        { { 1, 0, 1, 0, 1, 1, 0, 1 }, {5, 10} },
        
        { { 1, 0, 1, 0, 0, 1, 1, 1 }, {4, 11} },
        
        { { 0, 0, 0, 0, 0, 1, 0, 1 }, {4, 12} },
        
        { { 0, 0, 1, 0, 0, 0, 0, 1 }, {3, 13} },
        
        { { 1, 0, 0, 0, 0, 1, 0, 0 }, {5, 13} },
        
        { { 1, 0, 1, 0, 0, 0, 0, 0 }, {4, 14} },
        
        { { 0, 0, 0, 0, 0, 0, 0, 1 }, {3, 15} },
        { { 0, 0, 0, 0, 0, 1, 0, 0 }, {4, 15} },
        
        { { 0, 0, 1, 0, 0, 0, 0, 0 }, {3, 16} },
        { { 1, 0, 0, 0, 0, 0, 0, 0 }, {4, 16} },
        
        { { 1, 0, 0, 1, 0, 1, 0, 1 }, {3, 17} },
        { { 0, 0, 1, 0, 1, 1, 0, 1 }, {4, 17} },
        
        { { 1, 0, 1, 1, 0, 1, 0, 0 }, {3, 18} },
        { { 1, 0, 1, 0, 1, 0, 0, 1 }, {4, 18} },
        
        { { 1, 1, 1, 0, 0, 0, 0, 1 }, {3, 19} },
        { { 1, 1, 1, 0, 0, 1, 0, 0 }, {4, 19} },
        
        { { 0, 0, 1, 0, 0, -1, 1, 1 }, {3, 20} },
        { { 1, 0, 0, 0, 0, 1, 1, 1 }, {4, 20} },
        
        { { 1, 0, 1, 0, 0, 1, 0, 0 }, {3, 21} },
        { { 1, 0, 1, 0, 0, 0, 0, 1 }, {4, 21} },
        
        { { 1, 0, 0, 0, 0, 1, 0, 1 }, {3, 22} },
        { { 0, 0, 1, 0, 0, 1, 0, 1 }, {4, 22} },
        
        { { 1, 0, 0, 0, 0, 0, 0, 1 }, {3, 23} },
        { { 0, 0, 1, 0, 0, 1, 0, 0 }, {4, 23} },
	};


    for (int y = 0; y < TILE_Y; ++y) {
        for (int x = 0; x < TILE_X; ++x) {
            //if (tiles[y][x] != TILE_WALL) continue;

            vector<int> currentPattern(DIR_COUNT, 0);

            for (int dir = 0; dir < DIR_COUNT; ++dir) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (InBounds(nx, ny) && IsPathOrFloor(nx, ny)) {
                    currentPattern[dir] = 1;
                }
            }

            bool matched = false;
            for (const auto& pattern : tilePatterns) {
                if (MatchPattern(pattern.pattern, currentPattern)) {
                    tileIndex[y][x] = pattern.tileIndex;
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                tileIndex[y][x] = { 4, 1 };
            }
        }
    }
}


void Map::RandomTileDesign() {
    
    //floor���κ� ������
    for (int y = 1; y < TILE_Y; ++y) {
        for (int x = 1; x <TILE_X; ++x) {
            if (tileIndex[y][x] == make_pair(3, 15)) {
                tileIndex[y + 1][x + 1] = { 12,0 };
            }
            if (tileIndex[y][x] == make_pair(4, 0)) {
                tileIndex[y - 1][x] = { 13,2 };
            }
            if (tileIndex[y][x] == make_pair(3, 1)) {
                tileIndex[y][x - 1] = { 14,1 };
            }

        }
    }
}