# FteamGorogoro
BasecrossのFチームのゲームプロジェクト


コーティング規約
クラス名は大文字から始める
クラス変数名は　＿小文字
変数が多くなる場合は構造体変数にする
例）		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;

デザインパターンを意識


命名規則
プライベートメンバ変数は頭に＿をつける
変数は型名を先頭につける　例）bool型→bhit
