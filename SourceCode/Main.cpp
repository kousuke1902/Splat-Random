#include <Siv3D.hpp> // OpenSiv3D v0.3.2
#include <list>
#include <iterator>

#define MAX_SORT 4
#define MAX_MATCH 6

using namespace std;

void Main()
{

	Window::Resize(1184, 666);
	Window::SetTitle(U"Splat Random(64-bit)");
	Graphics::SetBackground(Color(171, 255, 147));

	char RandPage = Random(0, 11);//最大ページ
	char RandWep = Random(0, 6);//最終ページのブキ数
	char RandSort = Random(0, MAX_SORT-1);//ソート初期値
	char RandMatch = Random(0, MAX_MATCH-1);//対戦形式
	char MaxPage = 11;//最大ページ
	char MaxWep = 6;//最終ページのブキ数
	char SelectPage = 11;//最大ページ選択
	char SelectWep = 6;//最終ページのブキの数選択
	bool SortLock[MAX_SORT];
	bool MatchLock[MAX_MATCH];
	list<char> SortBox;
	list<char> MatchBox;
	const Texture Box(U"Img/Box.png");
	const Texture Stop(U"Img/Stop.png");
	const Texture PageRange(U"Img/PageRange.png");
	const Texture WepRange(U"Img/WepRange.png");
	const Texture Page(U"Img/page.png");
	const Texture Pointer(U"Img/Pointer.png");
	const Texture Update(U"Img/Update.png");
	Texture Num[12];
	Texture Sort[MAX_SORT];
	Texture Match[MAX_MATCH];
	Texture Arrow[4];
	Color Lamp(255, 192, 0);
	
	//初期化
	//ソート
	for (int i = 0; i < MAX_SORT; ++i)
	{
		String Filename = Format(U"Img/Sort", i, U".png");
		Texture tmp(Filename);
		Sort[i] = tmp;
		SortLock[i] = true;
		SortBox.push_back(i);
	}

	//ナンバー
	for (int i = 0; i < 12; ++i)
	{
		String Filename = Format(U"Img/Num", i + 1, U".png");
		Texture tmp(Filename);
		Num[i] = tmp;
	}

	//対戦形式
	for (int i = 0; i < MAX_MATCH; ++i)
	{
		String Filename = Format(U"Img/Match", i, U".png");
		Texture tmp(Filename);
		Match[i] = tmp;
		MatchLock[i] = true;
		MatchBox.push_back(i);
	}

	//矢印
	for (int i = 0; i < 4; ++i)
	{
		String Filename = Format(U"Img/Arrow", i, U".png");
		Texture tmp(Filename);
		Arrow[i] = tmp;

	}

	//メインループ
	while (System::Update())
	{

		if (SortBox.empty() || MatchBox.empty())Lamp = Color(230);
		else Lamp = Color(255, 192, 0);

		//乱数生成
		if (RoundRect(380, 10, 80, 80, 20).draw(Lamp).leftClicked() && Lamp == Color(255, 192, 0))
		{
			//乱数生成
			MaxPage = SelectPage;
			MaxWep = SelectWep;
			int buf = Random(0, (int)SortBox.size()-1);
			auto itr = SortBox.begin();
			advance(itr, buf);
			RandSort = *itr;
			RandPage = Random(0, (int)MaxPage);
			RandWep = (RandPage != MaxPage ? Random(0, 11) : Random(0, (int)MaxWep));
			buf = Random(0, (int)MatchBox.size()-1);
			itr = MatchBox.begin();
			advance(itr, buf);
			RandMatch = *itr;
		}

		Update.scaled(0.6).drawAt(420, 50);
		
		//形式選択
		//ソート形式選択
		RoundRect(810, 100, 170, 210, 20).draw(Color(50));
		Line(730, 70, 840, 130).draw(20, Color(50));

		for (int i = 0; i < MAX_SORT; ++i)
		{
		
			if (Sort[i].scaled(0.5).drawAt(890, 130+i*50).leftClicked())
			{
				SortLock[i] = !SortLock[i];
				if (SortLock[i] == false)
				{
					for (auto itr = SortBox.begin(); itr != SortBox.end();)
						if (*itr == i)itr = SortBox.erase(itr);
						else  ++itr;
				}

				else SortBox.push_back(i);
			}
	
			if(!SortLock[i])Stop.scaled(0.3).drawAt(890, 130+i*50);
		}



		//試合形式選択
		RoundRect(985, 100, 170, 210, 20).draw(Color(50));
		Line(1070, 90, 1070, 100).draw(20, Color(50));

		for (int i = 0; i < MAX_MATCH; ++i)
		{
			if (Match[i].scaled(0.4).drawAt(1070, 130+i*30).leftClicked())
			{
				MatchLock[i] = !MatchLock[i];
				if (MatchLock[i] == false)
				{
					for (auto itr = MatchBox.begin(); itr != MatchBox.end();)
						if (*itr == i)itr = MatchBox.erase(itr);
						else ++itr;
				}
				else MatchBox.push_back(i);
			}
			if(!MatchLock[i])Stop.scaled(0.3).drawAt(1070, 130+i*30);
		}


		//最大値選択
		//最大ページ数
		RoundRect(810, 320, 350, 80, 20).draw(Color(50));
		PageRange.scaled(0.8).drawAt(980, 360);
		RoundRect(920, 405, 125, 70, 20).draw(Color(255));
		Num[SelectPage].scaled(0.5).drawAt(980, 440);
		if (Arrow[0].scaled(0.6).drawAt(1080, 440).leftClicked() && SelectPage != 11)++SelectPage;
		if (Arrow[1].scaled(0.6).drawAt(880, 440).leftClicked() && SelectPage != 0)--SelectPage;

		//最終ページのブキの数
		RoundRect(810, 490, 350, 80, 20).draw(Color(50));
		WepRange.scaled(0.6).drawAt(980, 530);
		RoundRect(920, 575, 125, 70, 20).draw(Color(255));
		Num[SelectWep].scaled(0.5).drawAt(980, 610);
		if (Arrow[2].scaled(0.6).drawAt(880, 610).leftClicked() && SelectWep != 0)--SelectWep;
		if (Arrow[3].scaled(0.6).drawAt(1080, 610).leftClicked() && SelectWep != 11)++SelectWep;

		//表示
		//ページ
		Num[RandPage].scaled(0.8).drawAt(120, 50);
		Page.scaled(0.5).draw(150, 50);

		//ソート
		RoundRect(510, 10, 250, 80, 20).draw(Color(50));
		Sort[RandSort].scaled(0.8).drawAt(635, 50);

		//武器表示背景
		RoundRect(50, 100, 710, 550, 40).draw(Color(50));

		//ブキ表示
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 3; ++j)
			{
				Box.scaled(0.5).drawAt(170*i+150, 175*j+200);
				if (RandPage == MaxPage && MaxWep == i*3+j)goto BOX_END;
			}
BOX_END:

		//武器ポインタ
		Pointer.scaled(0.5).draw(170*(RandWep/3)+50, 175*(RandWep%3)+70);

		//ブキ番号
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 3; ++j)
			{
				Num[i * 3 + j].scaled(0.8).drawAt(170*i+150, 175*j+200);
				if (RandPage == MaxPage && MaxWep == i*3+j)goto NUM_END;
			}
NUM_END:

		//試合形式
		RoundRect(810, 10, 350, 80, 20).draw(Color(50));
		Match[RandMatch].scaled(0.8).drawAt(990, 50);

	}

}
