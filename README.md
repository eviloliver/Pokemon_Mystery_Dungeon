# Pokemon_Mystery_Dungeon
포켓몬스터 미스터리던전 모작

# 📦 외부 의존성
이 프로젝트는 다음 외부 라이브러리에 의존합니다: SDL2, SDL2_mixer
- SDL2는 멀티미디어 및 게임 개발을 위한 크로스 플랫폼 라이브러리입니다.
이 프로젝트에는 포함되어 있지 않으며, 사용자가 별도로 설치해야 합니다.

# 설치 방법
본인 OS(윈도우 / macOS / 리눅스)에 맞는 개발용 라이브러리 다운로드
개발 환경(IDE, 빌드 시스템)에서 include 및 lib 경로를 연결하도록 설정

⚠ 주의: 프로젝트 빌드 설정에서 요구하는 SDL2 버전과 일치하는지 반드시 확인하세요.
## 윈도우
### SDL2
1. SDL2 개발용 라이브러리 다운로드
    - SDL2 다운로드 페이지에서 SDL2-devel-2.0.x-VC.zip 파일 다운로드
2. 압축 해제 후 폴더 구성
    - include/ : 헤더 파일 (SDL.h 등)
    - lib/x86/ 또는 lib/x64/ : 정적/동적 라이브러리 파일
3. Visual Studio 설정
    - 프로젝트 > 속성 > C/C++ > 일반 > 추가 포함 디렉터리에 include 경로 추가
    - 프로젝트 > 속성 > 링커 > 일반 > 추가 라이브러리 디렉터리에 lib/x64 경로 추가
    - 프로젝트 > 속성 > 링커 > 입력 > 추가 종속성에 SDL2.lib, SDL2main.lib 추가
    - 실행 파일 위치에 SDL2.dll 복사

### SDL2_mixer
1. SDL2 개발용 라이브러리 다운로드
    - SDL2 다운로드 페이지에서 SDL2-devel-2.0.x-VC.zip 파일 다운로드
2. 압축 해제 후 폴더 구성
include/ : 헤더 파일 (SDL.h 등)
lib/x86/ 또는 lib/x64/ : 정적/동적 라이브러리 파일
3. Visual Studio 설정
    - 프로젝트 > 속성 > C/C++ > 일반 > 추가 포함 디렉터리에 include 경로 추가
    - 프로젝트 > 속성 > 링커 > 일반 > 추가 라이브러리 디렉터리에 lib/x64 경로 추가
    - 프로젝트 > 속성 > 링커 > 입력 > 추가 종속성에 SDL2.lib, SDL2main.lib 추가
    - 실행 파일 위치에 SDL2.dll 복사

# SDL2 다운로드 주소
- https://github.com/libsdl-org

# 설치 참고 영상
- SDL2: https://www.youtube.com/watch?v=bnPvxWrnq8I
- SDL2_mixer: https://www.youtube.com/watch?v=edBc9wN_HtA