#include <d3d9.h>
#include "../ImGUI/imgui_internal.h"
D3DCOLOR rainbow() {

	static float x = 0, y = 0;
	static float r = 0, g = 0, b = 0;

	if (y >= 0.0f && y < 255.0f) {
		r = 255.0f;
		g = 0.0f;
		b = x;
	}
	else if (y >= 255.0f && y < 510.0f) {
		r = 255.0f - x;
		g = 0.0f;
		b = 255.0f;
	}
	else if (y >= 510.0f && y < 765.0f) {
		r = 0.0f;
		g = x;
		b = 255.0f;
	}
	else if (y >= 765.0f && y < 1020.0f) {
		r = 0.0f;
		g = 255.0f;
		b = 255.0f - x;
	}
	else if (y >= 1020.0f && y < 1275.0f) {
		r = x;
		g = 255.0f;
		b = 0.0f;
	}
	else if (y >= 1275.0f && y < 1530.0f) {
		r = 255.0f;
		g = 255.0f - x;
		b = 0.0f;
	}

	x += Visuals::time;//скорость изменения цветов
	if (x >= 255.0f)
		x = 0.0f;

	y += Visuals::time; //скорость изменения цветов
	if (y > 1530.0f)
		y = 0.0f;


	return D3DCOLOR_ARGB((int)r, (int)g, (int)b, 255);
}

D3DCOLOR FLOAT4TOD3DCOLOR(float Col[])
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}

void Skeleton(BasePlayer* BasePlayer)
{
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos
	for (int j = 0; j < 15; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}
	if ((int)BasePlayer->GetHealth() > 0)
	{
		if (LocalPlayer.BasePlayer->IsTeamMate(BasePlayer->GetSteamID()))
		{
			for (int j = 0; j < 15; j += 3) {
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Black, 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Magenta);
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Black, 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Magenta);
			}

			//draw add lines
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Magenta);
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Magenta);
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Magenta);
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Magenta);
		}
		else
		{
			for (int j = 0; j < 15; j += 3) {
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
				Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			}

			//draw add lines
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor), 0.5f);
			Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(ColorsNShit::SkeletonColor));
		}

	}
	else
	{
		for (int j = 0; j < 15; j += 3) {
			Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Black, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Magenta);
			Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Black, 0.5f);
			Render::Object.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Magenta);
		}

		//draw add lines
		Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Magenta);
		Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Magenta);
		Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Magenta);
		Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, 0.5f);
		Render::Object.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Magenta);
	}
	//draw main lines

	//draw main lines
}
inline void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color)
{
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f, Entity_y }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f, Entity_y }, color);
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, color);

	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y }, color);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, color);

	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h }, color);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, color);

	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f, Entity_y + Entity_h }, color);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::Black, 3.f);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, color);
	if (PlayerEsp::fillbox)
		Render::Object.FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0.33, 0.33, 0.33, 0.5));
}

namespace string
{

	inline char buffer[512];

	inline const char* format(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		LI_FIND(vsnprintf)(buffer, 512, fmt, args);
		va_end(args);
		return buffer;
	}
}

namespace Vars1 {
	namespace Radar {
		bool ShowRadarNpc = false;
		bool Enable = false;
		bool ShowRadarBackground = false;
		bool ShowRadarPlayer = false;
		bool ShowRadarSleeper = false;
		float Pos_X = 0;
		float Pos_Y = 0;
		float Radar_Size = 500.f;
		float Radar_Range = 300.f;
		bool EnableDinamicRadar = false;
		bool ShowRadarNpcname = false;
	}
}

inline void PlayerBoxK(float Entity_x, float Entity_y, float Entity_w, float Entity_h)
{
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 1.f,Entity_y }, D2D1::ColorF::Black);
	Render::Object.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 1.f }, D2D1::ColorF::Red);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 1.f,Entity_y }, D2D1::ColorF::Black);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 1.f }, D2D1::ColorF::Red);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 1.f,Entity_y + Entity_h }, D2D1::ColorF::Black);
	Render::Object.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 1.f }, D2D1::ColorF::Red);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 1.f,Entity_y + Entity_h }, D2D1::ColorF::Black);
	Render::Object.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 1.f }, D2D1::ColorF::Red);
	if (PlayerEsp::fillbox)
		Render::Object.FillRectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF(0.33, 0.33, 0.33, 0.5));

}

double deg2rad(double degrees) {
	return degrees * 4.0 * atan(1.0) / 180.0;
}

inline D2D1::ColorF ConverToRGB(float R, float G, float B)
{
	return (D2D1::ColorF::ColorF(R / 255.f, G / 255.f, B / 255.f));
}

inline void RadarPlayer(BasePlayer* player)
{
	if (LocalPlayer.BasePlayer && Vars1::Radar::Enable && (Vars1::Radar::ShowRadarPlayer || Vars1::Radar::ShowRadarSleeper))
	{
		if (!player->IsDead() && player->GetHealth() >= 0.2f)
		{
			ImGui::SetNextWindowSize(ImVec2(Vars1::Radar::Radar_Size, Vars1::Radar::Radar_Size));
			ImGui::Begin("Dezz1337", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
			if (Radar::ShowRadarBackground)
				Render::Object.FillCircle({ Radar::Pos_X + Radar::Radar_Size / 2, Radar::Pos_Y + Radar::Radar_Size / 2 }, D2D1::ColorF(0, 0, 0, 0.5), Radar::Pos_Y + Radar::Radar_Size / 2);
			Render::Object.Сircle({ Radar::Pos_X + Radar::Radar_Size / 2, Radar::Pos_Y + Radar::Radar_Size / 2 }, D2D1::ColorF(0, 0, 0), Radar::Pos_Y + Radar::Radar_Size / 2, 1.f);
			ImVec2 pos = ImGui::GetWindowPos();
			const Vector3 LocalPos = LocalPlayer.BasePlayer->GetPosition();
			const Vector3 PlayerPos = player->GetPosition();
			const float Distance = Math::Calc3D_Dist(LocalPos, PlayerPos);
			const float y = LocalPos.x - PlayerPos.x;
			const float x = LocalPos.z - PlayerPos.z;
			Vector3 LocalEulerAngles;
			if (Vars1::Radar::EnableDinamicRadar)
			{
				LocalEulerAngles = LocalPlayer.BasePlayer->GetBoneByID(l_eye);
			}
			else
			{
				LocalEulerAngles = LocalPlayer.BasePlayer->GetPosition();
			}
			const float num = atan2(y, x) * 57.29578f - 270.f - LocalEulerAngles.y;
			float PointPos_X = Distance * cos(num * 0.0174532924f);
			float PointPos_Y = Distance * sin(num * 0.0174532924f);
			PointPos_X = PointPos_X * (Vars1::Radar::Radar_Size / Vars1::Radar::Radar_Range) / 2.f;
			PointPos_Y = PointPos_Y * (Vars1::Radar::Radar_Size / Vars1::Radar::Radar_Range) / 2.f;
			if (!player->HasFlags(16) && Radar::ShowRadarPlayer)
			{
				if (Distance <= Radar::Radar_Range)
				{
					Render::Object.Сircle({ Radar::Pos_X + Radar::Radar_Size / 2.f + PointPos_X - 3.f, Radar::Pos_Y + Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF(97, 250, 227, 0.7), 1.f);
				}
			}

			/*	if (Vars::Radar::ShowRadarBackground)
				{
					GUI::Render.FillCircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, D2D1::ColorF(Vars::BotsRGBA::BR / 0.f, Vars::BotsRGBA::BG / 0.f, Vars::BotsRGBA::BB / 0.f, Vars::BotsRGBA::BA / 55.f), Rad / 2);
					GUI::Render.Сircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, ConverToRGB(20, 15, 52), Rad / 2);
				}*/

			else if (player->HasFlags(16) && Radar::ShowRadarSleeper)
			{
				if (Distance <= Radar::Radar_Range)
				{
					Render::Object.Сircle({ Radar::Pos_X + Radar::Radar_Size / 2.f + PointPos_X - 3.f, Radar::Pos_Y + Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF(255, 36, 36, 0.7), 1.f);
				}
			}
			ImGui::End();
		}
	}
}



void ESP(BasePlayer* BP, BasePlayer* LP)
{
	bool PlayerSleeping = BP->HasFlags(16);
	bool PlayerWounded = BP->HasFlags(64);
	if (PlayerEsp::sleeperignore && PlayerSleeping)
		return;

	if (PlayerEsp::skeleton && !BP->IsNpc())
		Skeleton(BP);

	Vector2 tempFeetR, tempFeetL;

	if (LocalPlayer.WorldToScreen(BP->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GetBoneByID(l_foot), tempFeetL))
	{
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;

		Vector2 ScreenPos;
		Vector2 tempHead;
		if (LocalPlayer.WorldToScreen(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead))
		{
			Vector2 leftTopCorner = tempHead - Vector2(0.4f, 0.f);
			Vector2 rightBottomCorner = tempFeetR;


			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			bool PlayerWounded = BP->HasFlags(64);
			Vector3 middlePointWorld = BP->GetBoneByID(l_foot).midPoint(BP->GetBoneByID(r_foot));
			int CurPos = 0;
			auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
			if (LocalPlayer.WorldToScreen(middlePointWorld + Vector3(0, 2, 0), middlePointPlayerTop) && LocalPlayer.WorldToScreen(middlePointWorld, middlePointPlayerFeet))
			{
				if (PlayerEsp::box && !BP->IsNpc())
				{
					PlayerBoxK(Entity_x, Entity_y, Entity_w, Entity_h);
				}
				if (PlayerEsp::healthbar && !BP->IsNpc())
				{
					float maxheal = 100.f;
					int health = BP->GetHealth();
					if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 300)
					{
						if ((int)BP->GetHealth() <= 33)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF::Red);
						}
						if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF::Yellow);
						}
						if ((int)BP->GetHealth() >= 67)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF::GreenYellow);
						}
					}
				}
				if (PlayerEsp::name && !BP->IsNpc())
				{
					int health = (int)BP->GetHealth();
					wchar_t name[64];
					_swprintf(name, L"%s", BP->GetName());
					Render::Object.String(Vector2{middlePointPlayerTop.x, middlePointPlayerTop.y}, name, D2D1::ColorF::Red, true, true);

					CurPos += 15;
				}

				if (PlayerEsp::weapon && !BP->IsNpc())
				{
					int health = (int)BP->GetHealth();
					const wchar_t* ActiveWeaponName;
					WeaponData* ActWeapon = BP->GetActiveWeapon();
					ActiveWeaponName = ActWeapon->GetName();
					if (!ActWeapon)
					{

						ActiveWeaponName = L"----";
					}
					else
					{
						ActiveWeaponName = ActWeapon->GetName();
					}

					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 10.f }, ActiveWeaponName, D2D1::ColorF::Red, true, true);

				}
				if (PlayerEsp::distance && !BP->IsNpc())
				{
					wchar_t Distance[64];
					_swprintf(Distance, L"%d M", (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)));			
					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 25.f }, Distance, D2D1::ColorF::Red, true, true);
					CurPos += 15;
				}
				if (PlayerEsp::tracers && !PlayerSleeping && !BP->IsNpc() < 300)
				{
					static float screenX = GetSystemMetrics(SM_CXSCREEN);
					static float screenY = GetSystemMetrics(SM_CYSCREEN);
					static Vector2 startPos = Vector2(screenX / 2.0f, screenY - 200.f);
					if ((int)BP->GetHealth() > 0)
					{
						if (LocalPlayer.BasePlayer->IsTeamMate(BP->GetSteamID()))
						{
							Render::Object.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::LimeGreen, 0.5f);
						}
						else
						{
							Render::Object.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::White, 0.5f);
						}
					}
					else
					{
						Render::Object.Line(startPos, Vector2{ Entity_x + Entity_w / 2.f, Entity_y }, D2D1::ColorF::Red, 0.5f);
					}
				}
				// GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY 
				// GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY GAY

				if (BotsEsp::box && BP->IsNpc())
				{
					CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::Magenta);
				}
				if (BotsEsp::name && BP->IsNpc())
				{
					wchar_t name[64];
					_swprintf(name, L"%s [%d]", BP->GetName(), (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head)));
					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 40.f }, name, D2D1::ColorF::Orange, true, true);
					CurPos += 15;
				}
				if (BotsEsp::health && BP->IsNpc())
				{
					int health = (int)BP->GetHealth();
					float maxheal = 300.f;
					wchar_t healtht[64];
					_swprintf(healtht, L"%d HP", (int)BP->GetHealth());
					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 55.f }, healtht, D2D1::ColorF::Orange, true, true);
					CurPos += 15;
					if (BotsEsp::healthbar)
					{
						if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head)) < 201)
						{
							Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF::Orange);
							Render::Object.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
				}
				if (BotsEsp::weapons && BP->IsNpc())
				{
					const wchar_t* ActiveWeaponName;
					WeaponData* ActWeapon = BP->GetActiveWeapon();
					ActiveWeaponName = ActWeapon->GetName();
					if (!ActWeapon)
					{

						ActiveWeaponName = L"";
					}
					else
					{
						ActiveWeaponName = ActWeapon->GetName();
					}

					Render::Object.String(Vector2{ middlePointPlayerFeet.x, middlePointPlayerFeet.y + 25.f }, ActiveWeaponName, D2D1::ColorF::Orange, true, true);

				}

			}
		}
	}
}