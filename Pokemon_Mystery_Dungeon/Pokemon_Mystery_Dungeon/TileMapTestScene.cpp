#include "TileMapTestScene.h"

#include "CommonFunction.h"
#include "DungeonScene.h"
#include "Image.h"
#include "ImageGDIPlus.h"
#include "TilemapTool.h"

#define SQUARESIZE_X 954
#define SQUARESIZE_Y 714

HRESULT TileMapTestScene::Init()
{
    SetClientRect(g_hWnd, WINSIZE_X, WINSIZE_Y);

    backGround = new Image();
    redFlower = new Image();
    yellowFlower = new Image();
    river = new Image();

    // Size : 954, 714
    backGround = ImageManager::GetInstance()->AddImage(
        "SquareBackGround", L"Image/SceneImage/Square3.bmp", SQUARESIZE_X, SQUARESIZE_Y,
        1, 1, 0, RGB(255, 0, 255));

    // 210,41
    river = ImageManager::GetInstance()->AddImage(
        "river", L"Image/SceneImage/river.bmp", 210, 41, 6, 1, 0,
        RGB(200, 224, 168));

    // 33,144
    yellowFlower = ImageManager::GetInstance()->AddImage(
        "�����", L"Image/SceneImage/YellowFlower.bmp", 33, 144, 1, 6, 0,
        RGB(184, 240, 120));

    redFlower = ImageManager::GetInstance()->AddImage(
        "������", L"Image/SceneImage/RedFlower.bmp", 33, 144, 1, 6, 0,
        RGB(184, 240, 120));

    redPositions = {
        {545, 128}, {452, 164}, {455, 567}, {42, 239}, {103, 243},
        {85, 266},  {320, 589}, {856, 443}, {76, 293}, {261, 355},
    };
    yellowPositions = {
        // �߾� ���� 3��
        {477, 77},
        {477, 110},
        {477, 143},

        // ������ ���� 4��
        {545, 95},
        {545, 128},
        {545, 161},
        {545, 194},

        // ��Ÿ ���� ��ġ
        {353, 578},
        {388, 291},
        {854, 377},
        {710, 489},
        {738, 524},
        {455, 246},
        {341, 611},
    };

    /* ------------------------------------------------------------------------
     */
    // ī�޶� �ʱ�ȭ �߰�
    CameraManager::GetInstance()->Init(GameViewSize_X, GameViewSize_Y,
                                       backGround->GetWidth(),
                                       backGround->GetHeight());
    /* ------------------------------------------------------------------------
     */

    elapsedTime = 0;
    return S_OK;
}

void TileMapTestScene::Release()
{
}

void TileMapTestScene::Update()
{
    /* ------------------------------------------------------------------------
     */
    // ���콺 ��ǥ�� �����ͼ� ī�޶� ��ġ ����
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient(g_hWnd, &mouse);
    CameraManager::GetInstance()->SetCameraPos(mouse.x, mouse.y);
    /* ------------------------------------------------------------------------
     */

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1))
    {
        SceneManager::GetInstance()->ChangeScene("TileMapTool");
    }

    elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
    if (elapsedTime > 0.3f)
    {
        currAnimaionFrame++;
        if (currAnimaionFrame >= yellowFlower->GetMaxFrameY())
        {
            currAnimaionFrame = 0;
        }
        elapsedTime = 0;
    }

    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F6))
    {
        SceneManager::GetInstance()->ChangeScene("DungeonScene");
    }
}

void TileMapTestScene::Render(HDC hdc)
{
    /* ------------------------------------------------------------------------
     */
    // ��� �׸��� ��� ImageGDIPlus -> Image�� ���� (GDI+�� GDI�� ���� �и�)
    // RenderBackground()�� Image�� �ű� ���� :
    //		��κ� Scene���� ImageŬ������ ����ϱ� ����
    //		�ű��� ������ �ҽ��ڵ带 �ʹ� ���� �����ؾ�����..
    if (backGround)
    {
        backGround->RenderBackground(hdc);
    }
    /* ------------------------------------------------------------------------
     */

    if (yellowFlower)
    {
        RenderFlowers(hdc, yellowFlower, yellowPositions, currAnimaionFrame);
    }
    if (redFlower)
    {
        RenderFlowers(hdc, redFlower, redPositions, currAnimaionFrame);
    }

    RECT cam = CameraManager::GetInstance()->GetViewPos();

    if (river)
    {
        /* ------------------------------------------------------------------------
         */

        // ���� ��ġ ī�޶� ���󰡰� ����
        // river->FrameRender(hdc, 64 - cam.left, 54 - cam.top,
        // currAnimaionFrame, 0, 0); river->FrameRender(hdc, 64 - cam.left, 104
        // - cam.top, currAnimaionFrame, 0, 0); river->FrameRender(hdc, 152 -
        // cam.left, 273 - cam.top, currAnimaionFrame, 0, 0);
        // river->FrameRender(hdc, 152 - cam.left, 400 - cam.top,
        // currAnimaionFrame, 0, 0); river->FrameRender(hdc, 152 - cam.left, 460
        // - cam.top, currAnimaionFrame, 0, 0);
        /* ------------------------------------------------------------------------
         */
    }

    TimerManager::GetInstance()->Render(hdc);

    wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), g_ptMouse.x, g_ptMouse.y);
    TextOut(hdc, 300, 60, szText, wcslen(szText));
}

void TileMapTestScene::RenderFlowers(HDC hdc, Image* flower,
                                     const std::vector<POINT>& positions,
                                     int currFrame)
{
    RECT cam = CameraManager::GetInstance()->GetViewPos();

    for (const auto& pos : positions)
    {
        /* ------------------------------------------------------------------------
         */
        // �� ��ġ ī�޶� ���󰡰� ����
        int flowerX = pos.x - cam.left;
        int flowerY = pos.y - cam.top;

        flower->FrameRender(hdc, flowerX, flowerY, 0, currFrame, 0);

        /* ------------------------------------------------------------------------
         */
    }
}
