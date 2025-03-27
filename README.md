# 🕹️ Jelly Run🪱

![MFC](https://img.shields.io/badge/MFC-GameApp-indigo)
![C++](https://img.shields.io/badge/C%2B%2B-GameLogic-blueviolet)
![MouseEvent](https://img.shields.io/badge/Input-Mouse%20Click-yellowgreen)
![2DGame](https://img.shields.io/badge/Game-2D%20Platformer-lightblue)
![Team](https://img.shields.io/badge/Team-2%20People-brightgreen)

---

## 📌 프로젝트 개요  
**Jelly Run**은 MFC를 기반으로 구현된 **러너 게임**입니다.  
사용자는 마우스 클릭으로 캐릭터를 조작하며 장애물을 피하는 게임을 즐길 수 있으며,  
인트로 화면 → 사용자 입력 → 게임 화면으로 전환되는 구조로 되어 있습니다.

---

## 🛠️ 주요 기술 스택
- **언어**: C++ (Visual Studio)
- **프레임워크**: Microsoft Foundation Class (MFC)
- **입력 방식**: 마우스 클릭 이벤트
- **개발 도구**: Visual Studio 2022

---

## 🚀 주요 기능

1. **마우스 클릭 기반 점프 액션**
   - 사용자가 클릭할 때마다 캐릭터가 점프하여 장애물을 회피

2. **인트로 → 사용자 입력 → 게임 화면 전환**
   - Start 버튼 클릭 시 사용자 이름을 입력하는 창이 뜨고,  
     입력 후 본격적인 게임이 시작됨

3. **MFC 기반 UI**
   - 윈도우 기반 GUI 구성, 버튼 이벤트 및 타이머 기반 애니메이션 처리

4. **게임 플레이 요소**
   - 충돌 시 게임 종료 또는 재시작 기능(옵션에 따라 추가 가능)

---

## 🎮 게임 플레이 방법

1. 프로그램 실행 후 인트로 화면이 출력됩니다  
2. **Start** 버튼 클릭 → 사용자 이름 입력  
3. 게임 화면으로 전환되고 캐릭터 등장  
4. **마우스를 클릭할 때마다 캐릭터가 점프**  
5. 장애물을 피하면서 최대한 오래 살아남는 것이 목표입니다

---

## 📁 프로젝트 구조 (예시)

```
📦 JellyRun
├── StartDlg.cpp / .h        # 인트로 화면
├── NameInputDlg.cpp / .h    # 닉네임 입력 화면
├── JellyRunDlg.cpp / .h           # 메인 게임 화면
├── LevelUpDlg.cpp / .h           # 레벨업 화면
├── Level2Dlg.cpp / .h           # 레벨2 게임 화면
├── Level3Dlg.cpp / .h           # 레벨3 게임 화면
├── GameOverDlg.cpp / .h           # 게임 오버 화면
├── GameClearDlg.cpp / .h           # 게임 클리어 화면
├── Background.cpp / .h          # 배경 화면 및 배경 스크롤 구현
├── Character.cpp / .h          # 캐릭터 점프 및 위치 처리
├── Obstacle.cpp / .h          # 장애물
├── ObstacleManager.cpp / .h          # 장애물 관리
├── Score.cpp / .h          # 점수 요소
├── ScoreManager.cpp / .h          # 점수 요소 관리
├── JellyRun.cpp / .h          # MFC 메인 엔트리
├── JellyRunView.cpp / .h          # MFC 메인 엔트리 화면
├── Resource.h / .rc            # 리소스 정의
└── README.md                   # 설명 문서
```

---

## 👩‍💻 팀원 소개

| 이름     | 역할   | 담당 업무                                | GitHub |
|----------|--------|-------------------------------------------|--------|
| **배나혜** | 개발자 | 인트로 화면 구성, 닉네임 입력 화면, 캐릭터 점프 기능 구현, 생명 시스템, bgm, UI 구성     | [![GitHub](https://img.shields.io/badge/GitHub-NAHYE-black?logo=github)](https://github.com/nahyebae)|
| **이은비** | 개발자 | 게임 로직 구현, 점수 시스템, 레벨 시스템, 게임 오버 화면, 게임 클리어 화면, UI 구성        | [![GitHub](https://img.shields.io/badge/GitHub-EUNBEE-black?logo=github)]((https://github.com/eummbee)) |

---

## 📑 플로우 차트
![image](https://github.com/user-attachments/assets/1f9eb873-930f-4819-ade4-458569e0c671)

## 💡 배운 점
- MFC를 활용한 이벤트 기반 UI 구성 방식 이해
- 마우스 이벤트 및 타이머 처리 방식 학습
- 게임 로직과 윈도우 기반 UI의 결합 구현 경험
- 협업을 위한 분할 구현과 프로젝트 병합 경험

---

## 🔮 향후 개선 계획
- 효과음 추가
- 점수 랭킹 시스템 구현
- 장애물 다양화 환
