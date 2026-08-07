# 개발 환경 세팅 (2026.08.07) - 윈도우 

## WSL2 + Ubuntu 설치
- 관리자 PowerShell에서`wsl --install`
- Ubuntu 계정 생성 (username: myandue)

## 개발 도구 설치
- 패키지 목록 업데이트 `sudo apt update`
- 컴파일러 + 디버거 + git 설치 `sudo apt install -y build-essential gdb git`
- 확인 `g++ --version && git --version && make --version`

## VS Code + WSL 연결
- VS Code 설치 (code.visualstudio.com)
    - 자꾸 폴더 권한 막혀서 code.visualstudio.com/download에서 "System Installer X64"로 다운받음 
- WSL 확장 설치
    - VS Code 열기 -> Extensions -> WSL (Microsoft) Install
- WSL에서 VS Code 열어보기
    - Ubuntu 터미널에서 `cd ~ && code .`
 
## hello.cpp 컴파일
- VS Code 에서 새 파일 만들기 `/home/myandue/hello.cpp`
  ```
  #include <iostream>

  int main() {
      std::cout << "Hello, server!" << std:endl;
      return 0;
  }
  ```
- VS Code 안에서 터미널 열기 (Ctrl + \`)
- 컴파일 `g++ hello.cpp -o hello && ./hello`

## git 설정 + TIL에 setup.md 올리기
- git 신원 설정 (WSL 터미널에서)
  - `git config --global user.name "myandue"
  - `git config --global user.email "hyunju1041@naver.com"
- TIL 저장소 가져오기
  - `cd ~ && git clone https://github.com/myandue/TIL.git && cd TIL`
- setup.md 만들기
- 커밋
  - `git add setup.md && git commit -m "docs: 개발 환경 세팅 기록 추가"`