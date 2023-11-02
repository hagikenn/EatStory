#include <Novice.h>

const char kWindowTitle[] = "LC1D_22_ハギワラ_ケンタ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};



	//自機の座標などの初期化
	int posX = 100;
	int posY = 557;
	int speed = 5;
	int radius = 30;
	//背景のリソース
	int haikei = Novice::LoadTexture("./haikei.png");
	//スクリーン座標
	int scrollx[6] = {0,1280,2560,3840,5120,6400};



	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_A]) {
			posX -= speed;
		}

		if (keys[DIK_D]) {
			posX += speed;
		}


		//スクロール処理(右)
		if (posX > 640 && (keys[DIK_D])) {
			posX -= speed;
			scrollx[0] -= speed;
			scrollx[1] -= speed;
			scrollx[2] -= speed;
			scrollx[3] -= speed;
			scrollx[4] -= speed;
			scrollx[5] -= speed;

			

			if (scrollx[0] < -6200) {
				scrollx[0] = -6200;
				speed=0;
			}
		}

		//スクロール処理(左)
		if (posX < 640 && (keys[DIK_A])) {
			posX += speed;
			scrollx[0] += speed;
			scrollx[1] += speed;
			scrollx[2] += speed;
			scrollx[3] += speed;
			scrollx[4] += speed;
			scrollx[5] += speed;

			if (scrollx[0] > 0) {
				scrollx[0] = 0;
				posX -= speed;
			}
		}


		if (posX < 0 + radius) {
			posX = radius;
		}

		if (posX > 1280 - radius) {
			posX = 1280 - radius;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawSprite(scrollx[0], 0, haikei, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(scrollx[1], 0, haikei, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(scrollx[2], 0, haikei, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(scrollx[3], 0, haikei, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(scrollx[4], 0, haikei, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(scrollx[5], 0, haikei, 1, 1, 0.0f, WHITE);


		Novice::DrawEllipse(posX + speed, posY + speed, radius, radius, 0.0f, WHITE, kFillModeSolid);

		Novice::ScreenPrintf(10, 10, "scrollx[0]:%d", scrollx[0]);
		

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
