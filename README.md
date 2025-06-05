# 🌙 Forgotten
> **고립된 공간 속, 잊혀진 기억을 되짚는 1인칭 감성 게임**  
> *Developed with Unreal Engine 4.27*

---

## ✨ 주요 기능

### 🎯 **인터랙션 시스템 (Interaction System)**

플레이어의 시선에 반응하는 직관적인 상호작용 시스템

<div align="center">
  <img src="/Image/Interaction_1.png" width="400" alt="인터랙션 시스템 1">
  <img src="/Image/Interaction_2.png" width="400" alt="인터랙션 시스템 2">
</div>

- 🔍 **바라보기**: 상호작용 가능한 오브젝트 하이라이트
- ⌨️ **F키 입력**: 상황에 맞는 액션 실행
- 🚪 **다양한 액션**: 문 열기, 메모 읽기, 의자 앉기 등

| 기능 | 상세 |
|------|------|
| 문 열기/닫기 | 자연스러운 애니메이션과 사운드 |
| 메모 확인 | 스토리 진행에 중요한 정보 획득 |
| 의자 앉기 | 몰입감 향상을 위한 상호작용 |

**🔧 기술적 특징**
- C++ 기반 라인트레이스 및 입력 처리
- 확장성 높은 구조로 새로운 오브젝트 쉽게 추가 가능
- 레벨 디자이너도 코드 수정 없이 기능 추가 → **협업 효율성 극대화**

[📹 인터랙션 시연 영상 보기](https://drive.google.com/file/d/1gtxcre9C_XyS08V4t_5uRduxFIclNjuO/view?usp=sharing)

---

### 💬 **자막 시스템**

상황과 행동에 반응하는 동적 자막 생성

<div align="center">
  <img src="/Image/Dialogue_1.png" width="400" alt="자막 시스템 1">
  <img src="/Image/Dialogue_2.png" width="400" alt="자막 시스템 2">
</div>

- 🎯 **조건부 실행**: 특정 조건 만족 시 자동 트리거
- 🤝 **인터랙션 연동**: 오브젝트 상호작용 시 관련 자막 표시
- 📖 **스토리텔링**: 플레이어의 감정 몰입도 향상

---

### 🖥️ **모니터 UI 시스템**

게임의 핵심이 되는 실감나는 컴퓨터 인터페이스

<div align="center">
  <img src="/Image/Monitor_1.png" width="400" alt="모니터 UI 1">
  <img src="/Image/Monitor_2.png" width="400" alt="모니터 UI 2">
</div>

- 💻 **실제 컴퓨터 시뮬레이션**: 현실적인 조작감
- 🔄 **동적 변화**: 스토리 진행에 따른 UI 변화
- 🎮 **게임 내 게임**: 몰입감을 극대화하는 메타 요소

---

### 💾 **세이브 시스템**

안정적이고 유연한 게임 진행 관리

<div align="center">
  <img src="/Image/SaveGame_1.png" width="500" alt="세이브 시스템">
</div>

- 🔄 **이어하기**: 저장된 게임 파일 자동 감지 및 로드
- 💾 **수동 저장**: 게임 중간 언제든 진행 상황 저장
- 🛡️ **데이터 보호**: 안전한 세이브 파일 관리

---

### 🎬 **챕터 시스템**

몰입감 있는 스토리 진행과 연출

#### **📈 스토리 진행 단계**

<div align="center">
  <img src="/Image/Chapter_1.png" width="350" alt="챕터 1">
  <img src="/Image/Chapter_2.png" width="350" alt="챕터 2">
</div>

| 챕터 | 트리거 조건 | 주요 변화 |
|------|-------------|-----------|
| **Chapter 1** | 게임 시작 | 기본 탐사 모드 |
| **Chapter 2** | 1챕터 조사 완료 | 🔌 정전 → 모니터 UI 변경 |
| **Chapter 3** | 2챕터 조사 완료 | ⚠️ 게임 강제 종료 |
| **Final** | 게임 재실행 | 🎭 특별 연출 모드 |

<div align="center">
  <img src="/Image/Chapter_3.png" width="500" alt="2챕터 조사 완료 시 게임 강제 종료">
  <p><em>2챕터 조사 완료 시 게임 강제 종료</em></p>
</div>

#### **🎭 특별 연출 시스템**

**게임 재실행 시 특별한 경험:**

<div align="center">
  <img src="/Image/Chapter_4.png" width="300" alt="이어하기 버튼만 남은 메뉴">
  <img src="/Image/Chapter_5.png" width="300" alt="세이브 파일 리셋">
  <img src="/Image/Chapter_6.png" width="300" alt="페이드 아웃 연출">
</div>

- 🎮 **메뉴 변화**: 이어하기 버튼만 남은 미니멀한 메뉴
- 🔄 **세이브 리셋**: 자동으로 새로운 게임 경험 시작
- 🌅 **페이드 연출**: 부드러운 화면 전환과 감성적 자막

<p align="center"><em>게임 재실행 시 이어하기 버튼만 남고, 이어하기 선택 시 세이브 파일 리셋 후 자막과 페이드 아웃 연출</em></p>

---

## 🛠️ **개발 정보**

- **엔진**: Unreal Engine 4.27
- **장르**: 1인칭 퍼즐/어드벤처
- **테마**: 심리적 스릴러, 감성적 스토리텔링
- **개발 언어**: C++ + Blueprint

---

## 📦 사용한 에셋 및 라이선스 정보

### 1. Dirty Wood Floor (낡은 나무 바닥)
- 출처: https://ambientcg.com/view?id=WoodFloor044
- 라이선스: CC0 1.0 (퍼블릭 도메인)
- 제작자: [ambientCG](https://ambientcg.com/)

### 2. Painted Plaster Wall (낡고 얼룩진 벽 질감)
- 출처: https://ambientcg.com/view?id=PaintedWall002
- 라이선스: CC0 1.0 (퍼블릭 도메인)
- 제작자: [ambientCG](https://ambientcg.com/)

### 3. Concrete Ceiling (얼룩진 시멘트 천장)
- 출처: https://ambientcg.com/view?id=ConcreteDirty008
- 라이선스: CC0 1.0 (퍼블릭 도메인)
- 제작자: [ambientCG](https://ambientcg.com/)

### 4. Bathroom Wall Tile (욕실 벽 타일)
- 출처: https://ambientcg.com/view?id=Tiles133C
- 라이선스: CC0 1.0 (퍼블릭 도메인)
- 제작자: [ambientCG](https://ambientcg.com/)

### 5. Bathroom Floor Tile (욕실 바닥 타일)
- 출처: https://ambientcg.com/view?id=Tiles001
- 라이선스: CC0 1.0 (퍼블릭 도메인)
- 제작자: [ambientCG](https://ambientcg.com/)

### 6. Free Furniture Pack (가구 에셋 모음)
- 출처: [Unreal Engine Marketplace](https://fab.com/s/30988ec34e44)  
- 라이선스: 언리얼 엔진 프로젝트 내에서 사용 가능 (Epic Games Marketplace 이용 약관 준수)  
- 제작자: [Next Level 3D](https://www.fab.com/sellers/Next%20Level%203D)

### 7. Door with Handle (문 오브젝트)
- 출처: https://fab.com/s/767112c50c61
- 라이선스: CC BY 4.0 (저작자 표시 필수)
- 제작자: [SvrMx](https://www.fab.com/sellers/SvrMx)

### 8. Advanced Glass Material Pack (거울)
- 출처: [Unreal Engine Marketplace](https://www.fab.com/listings/aa73c72c-0eb9-4745-88ff-34e82e32551d)  
- 라이선스: 언리얼 엔진 프로젝트 내에서 사용 가능 (Epic Games Marketplace 이용 약관 준수)
- 제작자: [UV](https://www.fab.com/sellers/UB)

---

## 🎞️ 애니메이션 출처

다음 애니메이션은 [Mixamo](https://www.mixamo.com)에서 다운로드되었으며, Adobe의 상업용 라이선스 조건에 따라 사용되었습니다:

- **Lying Down (눕기)**  
- **Idle (대기)**  
- **Stand To Sit (서서 앉기)**

모든 애니메이션은 언리얼 엔진 4.27에서 커스텀 스켈레톤에 맞춰 리타겟팅되었습니다.  
Mixamo 애니메이션은 Adobe 계정이 있는 경우, 개인 및 상업 프로젝트에서 자유롭게 사용할 수 있습니다.  
추가적인 저작권 표시는 필수가 아니지만, 명확한 출처 표기를 위해 여기에 포함하였습니다.

---

## 🎨 이미지 출처

### 1. 모니터 UI 배경 이미지
- 출처: 생성형 AI 이미지 (ChatGPT, 2025.04)
- 라이선스: 제한 없음 (상업적/비상업적 사용 가능)
- 제작자: OpenAI (이미지 생성 도구 기반)

---

## ⚖️ 요약

- 본 프로젝트에서 사용된 외부 에셋은 다음 조건을 만족합니다:
  - CC0 또는 퍼블릭 도메인으로 자유롭게 사용 가능한 소재
  - 언리얼 엔진 사용자라면 자유롭게 사용할 수 있는 메가스캔(Megascans) 에셋
- 저작권이 있는 자료는 별도의 허락 없이 사용하지 않았습니다.
