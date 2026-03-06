ECC (Electronic Creative Clock) - Raspi System複合創造実験にて製作中の「枕型目覚ましデバイス」のRaspberry Pi実装用リポジトリ。枕に内蔵された圧力（重量）センサと連動し、起床状態を判定しながらアラームを制御するシステム。1. 実装環境・ハードウェア仕様ターゲットデバイスRaspberry Pi (4 / 5 推奨)OS: Raspberry Pi OS (64-bit 推奨)ハードウェア構成 (Hardware Specs)コード内の設定（hardware_config.hpp等）に基づく構成は以下の通り。重量センサ (圧力センサ):接続: MCP3208 (12bit ADC) を介してSPI通信SPIデバイス: /dev/spidev0.0ADCチャネル: 0アラーム出力 (ブザー等):接続: ハードウェアPWMPWMチップ: 0PWMチャネル: 0表示・操作インターフェース:GUI: SFMLを使用したウィンドウ表示 (1280x720)操作: キーボード (Escで終了)2. 依存関係 (Dependencies)本プロジェクトでは以下のライブラリを使用している。ライブラリ名概要取得方法SFML 3.0.0グラフィックス表示・ウィンドウ管理CMake内で自動取得 (FetchContent)csv-parserアラームリスト(CSV)の解析CMake内で自動取得 (FetchContent)libgpiodcxxGPIO制御 (C++バインディング)システムにインストールが必要OpenGL / MesaSFMLの描画バックエンドシステムにインストールが必要3. セットアップ・インストールシステムライブラリのインストールまず、ビルドに必要なシステムパッケージとSFMLの依存関係をインストールする。プロジェクト内のスクリプトを利用可能。chmod +x install/sfml-setup.sh
./install/sfml-setup.sh
また、GPIO制御用のライブラリも追加でインストールする。sudo apt install libgpiod-dev libgpiodcxx-dev
4. ビルド方法 (Build)標準的なCMakeビルドフローを採用している。# プロジェクトルート (Raspiディレクトリ) に移動
cd Raspi

# ビルド用ディレクトリの作成
mkdir -p build
cd build

# プロジェクトの構成
cmake ..

# ビルド実行
make
ビルドが成功すると、buildディレクトリ内に実行ファイル ECC_device が生成される。5. デプロイと実行方法実行ハードウェア（SPI/PWM）へのアクセス権限が必要なため、通常は sudo もしくは適切なグループ設定が必要。sudo ./ECC_device
データディレクトリシステムは実行時に以下のパスにデータを保存・参照しようとする。ディレクトリ: /var/lib/ECC_device/アラーム設定ファイル: alarm_list.csv初回起動時にディレクトリが存在しない場合は、自動的に作成を試みる仕様。6. 実装の概要本システムはマルチスレッド構成で動作しており、以下のタスクが並列で実行される。Main Thread (GUI):SFMLを用いた描画および入力イベント（終了処理など）のハンドル。Clock System Thread:std::chrono を使用した現在時刻の継続的な取得と保持。Alarm System Thread:設定されたアラーム時刻と現在時刻を照合し、フラグを管理。Hardware System Thread:SPIを介した重量センサ値の読み取りと、起床判定・ブザー制御。7. ディレクトリ構造Raspi/
├── CMakeLists.txt      # ビルド設定
├── main.cpp            # エントリーポイント・スレッド管理
├── config/             # システム定数・設定、エラー定義
├── inc/                # ヘッダーファイル群
│   ├── app_tasks/      # アプリケーションロジック (時計・アラーム)
│   ├── hardware/       # ハードウェア制御抽象化
│   └── helper/         # ファイルシステム等の補助機能
├── src/                # 実装ファイル (.cpp)
└── install/            # 環境構築用スクリプト
