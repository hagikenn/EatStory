#include <Novice.h>
#include<Vector2.h>
#define USE_MATH_DEFINE
#include <math.h>
#include <time.h>
#include <stdio.h>
const char kWindowTitle[] = "LC1D_21_ハギワラ_ケンタ";

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

	//イチゴ
	int POSX[10] = { 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500 };
	int POSY[10] = { 510, 550, 500, 400, 440, 520, 480, 370, 420, 360 };

	bool flag[10] = { true, true, true, true, true, true, true, true, true, true };

	//ホイップ
	int POS2X[10] = { 650, 750, 850, 950, 1050, 1150, 1250, 1350, 1450, 1550 };
	int POS2Y[10] = { 510, 550, 500, 400, 440, 520, 480, 370, 420, 360 };

	bool flag2[10] = { true, true, true, true, true, true, true, true, true, true };


	//スクリーン座標
	int scrollx[6] = { 0,1280,2560,3840,5120,6400 };

	//消費期限のタイマー
	bool Timer[12] = { false,false,false,false,false,false,false,false,false,false,false,false };
	int time = 1440;
	int width = 0;

	//自機の当たり判定宣言
	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;
	int cake = Novice::LoadTexture("./cake.png");

	//イチゴの当たり判定宣言
	int LEFT[10] = { 0 };
	int RIGHT[10] = { 0 };
	int TOP[10] = { 0 };
	int BOTTOM[10] = { 0 };
	int itigo[10] = { Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png"), Novice::LoadTexture("./itigo.png") };

	//ホイップの当たり判定宣言
	int LEFT2[10] = { 0 };
	int RIGHT2[10] = { 0 };
	int TOP2[10] = { 0 };
	int BOTTOM2[10] = { 0 };
	int hoippu[10] = { Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png"), Novice::LoadTexture("./hoippu.png") };

	enum Game {
		TITLE,
		START,
		GAMEOVER,
		GAMECLEAR
	};
	Game game = TITLE;

	//スコアの宣言
	int eachnumber[6] = { 0 };
	int score = 0;
	int hiscore = 0;
	int number = 0;
	int number2 = 0;
	bool scoreflag = true;
	int numgh[10] = {
		Novice::LoadTexture("./suuzi0(end).png"),
		Novice::LoadTexture("./suuzi1(end).png"),
		Novice::LoadTexture("./suuzi2(end).png"),
		Novice::LoadTexture("./suuzi3(end).png"),
		Novice::LoadTexture("./suuzi4(end).png"),
		Novice::LoadTexture("./suuzi5(end).png"),
		Novice::LoadTexture("./suuzi6(end).png"),
		Novice::LoadTexture("./suuzi7(end).png"),
		Novice::LoadTexture("./suuzi8(end).png"),
		Novice::LoadTexture("./suuzi9(end).png")
	};

	int eachnumber4[6] = { 0 };
	int numgh4[10] = {
		Novice::LoadTexture("./suuzi0(end).png"),
		Novice::LoadTexture("./suuzi1(end).png"),
		Novice::LoadTexture("./suuzi2(end).png"),
		Novice::LoadTexture("./suuzi3(end).png"),
		Novice::LoadTexture("./suuzi4(end).png"),
		Novice::LoadTexture("./suuzi5(end).png"),
		Novice::LoadTexture("./suuzi6(end).png"),
		Novice::LoadTexture("./suuzi7(end).png"),
		Novice::LoadTexture("./suuzi8(end).png"),
		Novice::LoadTexture("./suuzi9(end).png")
	};


	int scoreSave = 0;

	//タイトル
	int taitoru = Novice::LoadTexture("./title.png");

	//背景
	int haikei = Novice::LoadTexture("./haikei.png");

	//ゲームオーバー
	int over = Novice::LoadTexture("./gameover.png");

	//ゲームクリア
	int kuria = Novice::LoadTexture("./clear.png");

	bool take = false;
	

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

			//自機の当たり判定の処理
			left = (int)pl.pos.x;
			right = (int)pl.pos.x + 80;
			top = (int)pl.pos.y;
			bottom = (int)pl.pos.y + 80;

			//イチゴの当たり判定の処理
			for (int i = 0; i < 10; i++) {
				LEFT[i] = POSX[i];
				RIGHT[i] = POSX[i] + 32;
				TOP[i] = POSY[i];
				BOTTOM[i] = POSY[i] + 32;
			}

			//ホイップの当たり判定の処理
			for (int i = 0; i < 10; i++) {
				LEFT2[i] = POS2X[i];
				RIGHT2[i] = POS2X[i] + 32;
				TOP2[i] = POS2Y[i];
				BOTTOM2[i] = POS2Y[i] + 32;
			}

			//イチゴの当たり判定の処理
			for (int i = 0; i < 10; i++) {
				if (flag[i] == true) {
					if (LEFT[i] <= right && RIGHT[i] >= left && TOP[i] <= bottom && BOTTOM[i] >= top && flag[i] == true) {
						flag[i] = false;
						take = true;

						scoreflag = true;
						if (scoreflag == true) {
							score += 100;
							scoreflag = false;
						}


					}
				}
			}

			//ホイップの当たり判定の処理
			for (int i = 0; i < 10; i++) {
				if (flag2[i] == true) {
					if (LEFT2[i] <= right && RIGHT2[i] >= left && TOP2[i] <= bottom && BOTTOM2[i] >= top && flag2[i] == true) {
						flag2[i] = false;
						take = true;

						scoreflag = true;
						if (scoreflag == true) {
							score += 20;
							scoreflag = false;
						}
					}






				}
			}




			if (take == true) {
				take = false;
				width -= 50;
				time += 120;
			}

			if (time > 1440) {
				time = 1440;
			}

			if (width <= 0) {
				width = 0;
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

				for (int i = 0; i < 10; i++) {
					POS2X[i] -= speed;

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

				//イチゴ
				for (int i = 0; i < 10; i++) {
					POSX[i] += speed;

				}

				//ホイップ
				for (int i = 0; i < 10; i++) {
					POS2X[i] += speed;

				}

				if (scrollx[0] > 0) {
					scrollx[0] = 0;
					scrollx[1] = 1280;
					scrollx[2] = 2560;
					scrollx[3] = 3840;
					scrollx[4] = 5120;
					scrollx[5] = 6400;
					pl.pos.x -= speed;

					//イチゴ
					for (int i = 0; i < 10; i++) {
						POSX[i] -= speed;
					}

					//ホイップ
					for (int i = 0; i < 10; i++) {
						POS2X[i] -= speed;
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
				time -= 1;
				if (1320 > time) {
					width += 50;
					Timer[0] = true;
				}
			}

			if (Timer[0] == true) {
				if (Timer[1] == false) {
					time -= 1;
					if (1200 > time) {
						width += 50;
						Timer[1] = true;
					}
				}
			}

			if (Timer[1] == true) {
				if (Timer[2] == false) {
					time -= 1;
					if (1080 > time) {
						width += 50;
						Timer[2] = true;
					}
				}
			}

			if (Timer[2] == true) {
				if (Timer[3] == false) {
					time -= 1;
					if (960 > time) {
						width += 50;
						Timer[3] = true;
					}
				}
			}

			if (Timer[3] == true) {
				if (Timer[4] == false) {
					time -= 1;
					if (840 > time) {
						width += 50;
						Timer[4] = true;
					}
				}
			}

			if (Timer[4] == true) {
				if (Timer[5] == false) {
					time -= 1;
					if (720 > time) {
						width += 50;
						Timer[5] = true;
					}
				}
			}

			if (Timer[5] == true) {
				if (Timer[6] == false) {
					time -= 1;
					if (600 > time) {
						width += 50;
						Timer[6] = true;
					}
				}
			}

			if (Timer[6] == true) {
				if (Timer[7] == false) {
					time -= 1;
					if (480 > time) {
						width += 50;
						Timer[7] = true;
					}
				}
			}

			if (Timer[7] == true) {
				if (Timer[8] == false) {
					time -= 1;
					if (360 > time) {
						width += 50;
						Timer[8] = true;
					}
				}
			}

			if (Timer[8] == true) {
				if (Timer[9] == false) {
					time -= 1;
					if (240 > time) {
						width += 50;
						Timer[9] = true;
					}
				}
			}

			if (Timer[9] == true) {
				if (Timer[10] == false) {
					time -= 1;
					if (120 > time) {
						width += 50;
						Timer[10] = true;
					}
				}
			}

			if (Timer[10] == true) {
				if (Timer[11] == false) {
					time -= 1;
					if (0 > time) {
						width += 50;
						game = GAMEOVER;
						Timer[11] = true;

					}
				}
			}

			

			//スコア表示

			eachnumber[0] = number / 100000;
			number = score % 100000;
			eachnumber[1] = number / 10000;
			number = score % 10000;
			eachnumber[2] = number / 1000;
			number = score % 1000;
			eachnumber[3] = number / 100;
			number = score % 100;
			eachnumber[4] = number / 10;
			number = score % 10;
			eachnumber[5] = number / 1;
			number = score % 1;

			if (score > hiscore) {
				scoreSave = score;
				hiscore = scoreSave;

			}//ハイスコアを保存している

			break;
		case GAMEOVER:
			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				game = TITLE;
				POSX[0] = { 600 };
				POSX[1] = { 700 };
				POSX[2] = { 800 };
				POSX[3] = { 900 };
				POSX[4] = { 1000 };
				POSX[5] = { 1100 };
				POSX[6] = { 1200 };
				POSX[7] = { 1300 };
				POSX[8] = { 1400 };
				POSX[9] = { 1500 };

				POSY[0] = { 510 };
				POSY[1] = { 550 };
				POSY[2] = { 500 };
				POSY[3] = { 400 };
				POSY[4] = { 440 };
				POSY[5] = { 520 };
				POSY[6] = { 480 };
				POSY[7] = { 370 };
				POSY[8] = { 420 };
				POSY[9] = { 360 };

				for (int i = 0; i < 10; i++) {
					flag[i] = { true };
				}

				//ホイップ
				POS2X[0] = { 650 };
				POS2X[1] = { 750 };
				POS2X[2] = { 850 };
				POS2X[3] = { 950 };
				POS2X[4] = { 1050 };
				POS2X[5] = { 1150 };
				POS2X[6] = { 1250 };
				POS2X[7] = { 1350 };
				POS2X[8] = { 1450 };
				POS2X[9] = { 1550 };

				POS2Y[0] = { 510 };
				POS2Y[1] = { 550 };
				POS2Y[2] = { 500 };
				POS2Y[3] = { 400 };
				POS2Y[4] = { 440 };
				POS2Y[5] = { 520 };
				POS2Y[6] = { 480 };
				POS2Y[7] = { 370 };
				POS2Y[8] = { 420 };
				POS2Y[9] = { 360 };

				for (int i = 0; i < 10; i++) {
					flag2[i] = { true };
				}

				//スクリーン座標
				scrollx[0] = { 0 };
				scrollx[1] = { 1280 };
				scrollx[2] = { 2560 };
				scrollx[3] = { 3840 };
				scrollx[4] = { 5120 };
				scrollx[5] = { 6400 };

				//消費期限のタイマー
				for (int i = 0; i < 10; i++) {
					Timer[i] = { false };
				}
				time = 1440;



				

			}
			break;
		case GAMECLEAR:
			eachnumber4[0] = number2 / 100000;
			number2 = hiscore % 100000;

			eachnumber4[1] = number2 / 10000;
			number2 = hiscore % 10000;

			eachnumber4[2] = number2 / 1000;
			number2 = hiscore % 1000;

			eachnumber4[3] = number2 / 100;
			number2 = hiscore % 100;

			eachnumber4[4] = number2 / 10;
			number2 = hiscore % 10;

			eachnumber4[5] = number2 / 1;
			number2 = hiscore % 1;

			if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {
				game = TITLE;
			}
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
		//float PltransposY = (pl.pos.y * directionY) + originposY;

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

			//イチゴ
			for (int i = 0; i < 10; i++) {
				if (flag[i] == true) {
					Novice::DrawSprite(POSX[i], POSY[i], itigo[i], 1.0f, 1.0f, 0.0f, WHITE);
				}
			}

			//ホイップ
			for (int i = 0; i < 10; i++) {
				if (flag2[i] == true) {
					Novice::DrawSprite(POS2X[i], POS2Y[i], hoippu[i], 1.0f, 1.0f, 0.0f, WHITE);
				}
			}


			//スコア
			Novice::DrawSprite(0, -10, numgh[eachnumber[1]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(80, -10, numgh[eachnumber[2]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(160, -10, numgh[eachnumber[3]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(240, -10, numgh[eachnumber[4]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(320, -10, numgh[eachnumber[5]], 1, 1, 0.0f, WHITE);

			//ゲージ
			Novice::DrawBox(600, 30, 600, 50, 0.0f, BLACK, kFillModeSolid);

			Novice::ScreenPrintf(0, 400, "time:%d", time);

			Novice::DrawBox(600, 30, width, 50, 0.0f, RED, kFillModeSolid);


			break;
		case GAMEOVER:
			Novice::DrawSprite(0, 0, over, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		case GAMECLEAR:
			Novice::DrawSprite(0, -10, numgh4[eachnumber4[1]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(80, -10, numgh4[eachnumber4[2]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(160, -10, numgh4[eachnumber4[3]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(240, -10, numgh4[eachnumber4[4]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(320, -10, numgh4[eachnumber4[5]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(0, 0, kuria, 1.0f, 1.0f, 0.0f, WHITE);
			break;
		}
		
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
