# Visiontollbox

🎯 Qt6 + OpenCV 기반 멀티페이지 이미지 편집 툴
이후 확장성을 위하여 가장 기본적인 기능들만 있으며 이후 구조 확장에 용이하게 설계해둠
## 주요 기능
- 이미지 로딩 / 저장
- 뷰어 ↔ 에디터 페이지 전환 (StackedWidget)
- 필터 기능 (Grayscale 등)
- 로그 출력

## 사용 기술
- Qt6 (Widgets, Designer, Signals/Slots)
- OpenCV (이미지 처리)
- Visual Studio 2022

## 🖼️ 화면 구성 (UI Layout)

```plaintext
MainWindow
└── stackedWidget
    ├── viewerPage
    │   ├── btnLoad / btnSave / btnEdit
    │   ├── imgLabel (이미지 표시)
    │   └── textEdit (로그)
    └── editorPage
        ├── btnGrayscale / btnBack / btnOriginal
        └── imgEditLabel (편집 중 이미지 표시)

