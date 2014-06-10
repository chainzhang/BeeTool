# BeeSqlite



`BeeSqlite`はシングルトンクラスです。`getInstance()`でインスタンスを取得します。

##基本の使い方：

###データベースを作成
	
	// データベースを保存するパス
	std::string dbPath = FileUtils::getInstance()->getWritablePath() + "test.db";
	
	// setDBはまずデータベース存在するかどうかを判断し
	// 存在しなければ新規作成する。
    Sqlite::getInstance()->setDB(dbPath.c_str());


### フェッチ
BeeSqliteのフェッチは`SqliteFetch`というオブジェクトと組み合わせて使います。
	
	//フェッチを作成
	auto fetch = new SqliteFetch("SELECT * FROM table");
	
	//フェッチした結果を受け取る関数を設置
	//（行単位でループされる）
	fetch->get = [](std::map<std::string, std::string>table)
	{
		CCLOG("data:%f, %f", table["col1"], table["col2"]);
	};
	
	//フェッチします。
	Sqlite::getInstance()->fetch(fetch);

更新中...