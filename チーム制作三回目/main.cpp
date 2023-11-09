#include <Novice.h>
#include<Vector2.h>
#define USE_MATH_DEFINE
#include <math.h>
#include <time.h>
#include <stdio.h>
const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//構造体

	struct Pl {
		Vector2 pos;
		Vector2 velocity;
		Vector2 acceleration;

	};


	Pl pl{
		{400.0f,200.0f},{0.0f,0.0f},{0.0f,0.8f},
	};

	//フラグ
	int isPlJump = 0;



	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int speed = 5;
	float radius = 30;

	//アイテム
	int POSX[10] = { 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500 };
	int POSY[10] = { 510, 550, 500, 400, 440, 520, 480, 370, 420, 360 };

	bool flag[10] = { true, true, true, true, true, true, true, true, true, true };


	//スクリーン座標
	int scrollx[6] = { 0,1280,2560,3840,5120,6400 };

	//消費期限のタイマー
	bool Timer[12] = { false,false,false,false,false,false,false,false,false,false,false,false };
	int time[12] = { 100,100,100,100,100,100,100,100,100,100,100,100 };
	int width = 0;
	//int width[12] = { 50,100,150,200,250,300,350,400,450,500,550,600 };
	

	//自機の当たり判定宣言
	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;
	int cake = Novice::LoadTexture("./cake.png");

	//アイテム1の当たり判定宣言
	int LEFT[10] = { 0 };
	int RIGHT[10] = { 0 };
	int TOP[10] = { 0 };
	int BOTTOM[10] = { 0 };
	int itigo[10] = { Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png") };
	bool take = false;


	enum Game {
		TITLE,
		START,
		GAMEOVER,
		GAMECLEAR
	};
	Game game = TITLE;

	//スコア
	int score = 0;

	//タイトル
	int taitoru = Novice::LoadTexture("./title.png");
	//背景
	int haikei = Novice::LoadTexture("./haikei.png");
	//ゲームオーバー
	int over = Novice::LoadTexture("./gameover.png");
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
		switch (game) {
		case TITLE:

			printf("SPACE");
			if (keys[DIK_SPACE]) {
				game = START;
			}
			break;
		case START:
			if (keys[DIK_A]) {
				pl.pos.x -= speed;
			}

			if (keys[DIK_D]) {
				pl.pos.x += speed;
			}
			take = false;
			//自機の当たり判定の処理
			left = (int)pl.pos.x;
			right = (int)pl.pos.x + 80;
			top = (int)pl.pos.y;
			bottom = (int)pl.pos.y + 80;

			for (int i = 0; i < 10; i++) {
				LEFT[i] = POSX[i];
				RIGHT[i] = POSX[i] + 32;
				TOP[i] = POSY[i];
				BOTTOM[i] = POSY[i] + 32;
			}

			//アイテムの当たり判定の処理
			for (int i = 0; i < 10; i++) {
				if (LEFT[i] <= right && RIGHT[i] >= left && TOP[i] <= bottom && BOTTOM[i] >= top) {
					flag[i] = false;
				}
			}

			for (int i = 0; i < 10; i++) {
				if (flag[i] == false) {
					score = +20;
					take = true;
				}
			}
			
			if (take == true) {
				width -= 50;
			}

			//スクロール処理(右)
			if (pl.pos.x > 640 && (keys[DIK_D])) {
				pl.pos.x -= speed;


				for (int i = 0; i < 6; i++) {
					scrollx[i] -= speed;

				}

				for (int i = 0; i < 10; i++) {
					POSX[i] -= speed;

				}



				if (scrollx[0] < -4000) {
					scrollx[0] = -4000;
					game = GAMECLEAR;
				}
			}

			//スクロール処理(左)
			if (pl.pos.x < 640 && (keys[DIK_A])) {
				pl.pos.x += speed;
				for (int i = 0; i < 6; i++) {
					scrollx[i] += speed;
				}

				for (int i = 0; i < 10; i++) {
					POSX[i] += speed;

				}

				if (scrollx[0] > 0) {
					scrollx[0] = 0;
					scrollx[1] = 1280;
					scrollx[2] = 2560;
					scrollx[3] = 3840;
					scrollx[4] = 5120;
					scrollx[5] = 6400;
					pl.pos.x -= speed;
					for (int i = 0; i < 10; i++) {
						POSX[i] -= speed;
					}
				}
			}

			if (pl.pos.x < 0 + radius) {
				pl.pos.x = radius;
			}

			if (pl.pos.x > 1280 - radius) {
				pl.pos.x = 1280 - radius;
			}



			if (Timer[0] == false) {
				time[0] -= 1;
				if (0 > time[0]) {
					width += 50;
					Timer[0] = true;
				}
			}

			if (Timer[0] == true) {
				if (Timer[1] == false) {
					time[1] -= 1;
					if (0 > time[1]) {
						width += 50;
						Timer[1] = true;
					}
				}
			}

			if (Timer[1] == true) {
				if (Timer[2] == false) {
					time[2] -= 1;
					if (0 > time[2]) {
						width += 50;
						Timer[2] = true;
					}
				}
			}

			if (Timer[2] == true) {
				if (Timer[3] == false) {
					time[3] -= 1;
					if (0 > time[3]) {
						width += 50;
						Timer[3] = true;
					}
				}
			}

			if (Timer[3] == true) {
				if (Timer[4] == false) {
					time[4] -= 1;
					if (0 > time[4]) {
						width += 50;
						Timer[4] = true;
					}
				}
			}

			if (Timer[4] == true) {
				if (Timer[5] == false) {
					time[5] -= 1;
					if (0 > time[5]) {
						width += 50;
						Timer[5] = true;
					}
				}
			}

			if (Timer[5] == true) {
				if (Timer[6] == false) {
					time[6] -= 1;
					if (0 > time[6]) {
						width += 50;
						Timer[6] = true;
					}
				}
			}

			if (Timer[6] == true) {
				if (Timer[7] == false) {
					time[7] -= 1;
					if (0 > time[7]) {
						width += 50;
						Timer[7] = true;
					}
				}
			}

			if (Timer[7] == true) {
				if (Timer[8] == false) {
					time[8] -= 1;
					if (0 > time[8]) {
						width += 50;
						Timer[8] = true;
					}
				}
			}

			if (Timer[8] == true) {
				if (Timer[9] == false) {
					time[9] -= 1;
					if (0 > time[9]) {
						width += 50;
						Timer[9] = true;
					}
				}
			}

			if (Timer[9] == true) {
				if (Timer[10] == false) {
					time[10] -= 1;
					if (0 > time[10]) {
						width += 50;
						Timer[10] = true;
					}
				}
			}

			if (Timer[10] == true) {
				if (Timer[11] == false) {
					time[11] -= 1;
					if (0 > time[11]) {
						width += 50;
						Timer[11] = true;

					}
				}
			}

			if (Timer[11] == true) {
				game = GAMEOVER;
			}

			break;
		case GAMEOVER:

			break;
		case GAMECLEAR:

			break;
		}

		///自機 

		if (isPlJump == 0 && preKeys[DIK_RETURN] == 0 && keys[DIK_RETURN]) {
			pl.velocity.y = -20.0f;
			isPlJump = 1;
		}



		pl.velocity.y += pl.acceleration.y;
		pl.pos.y += pl.velocity.y;



		if (pl.pos.y >= 530) {
			pl.pos.y = 530;
			isPlJump = 0;

		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (game) {
		case TITLE:

			Novice::DrawSprite(0, 0, taitoru, 1.0f, 1.0f, 0.0f, WHITE);

			printf("SPACE");
			if (keys[DIK_SPACE]) {
				game = START;
			}
			break;
		case START:

			Novice::DrawSprite(scrollx[0], 0, haikei, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(scrollx[1], 0, haikei, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(scrollx[2], 0, haikei, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(scrollx[3], 0, haikei, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(scrollx[4], 0, haikei, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(scrollx[5], 0, haikei, 1, 1, 0.0f, WHITE);

			//自機
			Novice::DrawSprite((int)pl.pos.x, (int)pl.pos.y, cake, 1.0f, 1.0f, 0.0f, WHITE);

			//アイテム
			for (int i = 0; i < 10; i++) {
				if (flag[i] == true) {
					Novice::DrawSprite(POSX[i], POSY[i], itigo[i], 1.0f, 1.0f, 0.0f, WHITE);
				}
			}




			//スコア
			Novice::ScreenPrintf(30, 60, "SCORE:%d", score);

			//ゲージ
			Novice::DrawBox((int)pl.pos.x, 30, 600, 50, 0.0f, BLACK, kFillModeSolid);

			for (int i = 0; i < 11; i++) {
				if (Timer[i] == true) {
					Novice::DrawBox((int)pl.pos.x, 30, width, 50, 0.0f, RED, kFillModeSolid);
				}
			}


			break;
		case GAMEOVER:
			Novice::DrawSprite(0, 0, over, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case GAMECLEAR:

			break;
		}
		

		Novice::ScreenPrintf(0, 50, "%d", width);




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
