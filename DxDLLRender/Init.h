
void InitCheat()
{
	Vector2 kek = Render::Object.CanvasSize();
	Global::ScreenWidth = kek.x;
	Global::ScreenHigh = kek.y;
	if (AimBot::Crosshair) {
		float xs = Global::ScreenWidth / 2, ys = Global::ScreenHigh / 2;
		Render::Object.Line(Vector2{ xs, ys }, Vector2{ xs + 4, ys + 4 }, D2D1::ColorF::White, 0.7f);
		Render::Object.Line(Vector2{ xs, ys }, Vector2{ xs + 4, ys - 4 }, D2D1::ColorF::White, 0.7f);
		Render::Object.Line(Vector2{ xs, ys }, Vector2{ xs - 4, ys - 4 }, D2D1::ColorF::White, 0.7f);
		Render::Object.Line(Vector2{ xs, ys }, Vector2{ xs - 4, ys + 4 }, D2D1::ColorF::White, 0.7f);

		Render::Object.Line(Vector2{ xs + 4, ys + 4 }, Vector2{ xs + 4 + 4, ys + 4 + 4 }, FLOAT4TOD3DCOLOR(ColorsNShit::Crosshair3), 0.7f);
		Render::Object.Line(Vector2{ xs + 4, ys - 4 }, Vector2{ xs + 4 + 4, ys - 4 - 4 }, FLOAT4TOD3DCOLOR(ColorsNShit::Crosshair3), 0.7f);
		Render::Object.Line(Vector2{ xs - 4, ys - 4 }, Vector2{ xs - 4 - 4, ys - 4 - 4 }, FLOAT4TOD3DCOLOR(ColorsNShit::Crosshair3), 0.7f);
		Render::Object.Line(Vector2{ xs - 4, ys + 4 }, Vector2{ xs - 4 - 4, ys + 4 + 4 }, FLOAT4TOD3DCOLOR(ColorsNShit::Crosshair3), 0.7f);
	}
	if (AimBot::CustomCrosshair)
	{
		float xs = Global::ScreenWidth / 2, ys = Global::ScreenHigh / 2;
		Render::Object.Line(Vector2{ xs, ys - AimBot::Gap }, Vector2{ xs , ys + AimBot::Gap }, D2D1::ColorF::Red);
		Render::Object.Line(Vector2{ xs - AimBot::Longht, ys }, Vector2{ xs + AimBot::Longht, ys }, D2D1::ColorF::Red);

	}

	if (AimBot::DrawFov) {
		float xs = Global::ScreenWidth / 2, ys = Global::ScreenHigh / 2;
		Render::Object.Ñircle(Vector2{ xs, ys }, D2D1::ColorF::Red, AimBot::Fov, 1.f);
		if (AimBot::FillFov) {
			Render::Object.FillCircle(Vector2{ xs, ys }, D2D1::ColorF(0, 0, 0, 0.45), AimBot::Fov / AimBot::FillFov);
		}
		
	}
	if (Storage::closestPlayer != NULL)
	{
		auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
		static float screenX = GetSystemMetrics(SM_CXSCREEN);
		static float screenY = GetSystemMetrics(SM_CYSCREEN);
		static Vector2 startPos = Vector2(screenX / 2.f, screenY - 0.f);
		Vector2 ScreenPos;
		if (PlayerEsp::targetline)
		{
			float xs = Global::ScreenWidth / 2, ys = Global::ScreenHigh / 2;
			wchar_t name[64];
			auto* target = reinterpret_cast<BasePlayer*>(Storage::closestPlayer);
			if (Storage::closestPlayer != NULL)
			{
				_swprintf(name, L"%s", target->GetName());
			}
			else
			{
				_swprintf(name, L"No target");
			}
			Vector2 ScreenPos;
			if (Storage::closestPlayer != NULL && !LocalPlayer.BasePlayer->IsTeamMate(target->GetSteamID()))
			{
				if (!(target->GetBoneByID(spine1).x == 0 && target->GetBoneByID(spine1).y == 0 && target->GetBoneByID(spine1).z == 0)) {
					if (LocalPlayer.WorldToScreen(target->GetBoneByID(head), ScreenPos))
					{
						Render::Object.Line(Vector2{ xs - 0, ys + 600.f }, ScreenPos, D2D1::ColorF::Black, 2.f);
						Render::Object.Line(Vector2{ xs - 0, ys + 600.f }, ScreenPos, D2D1::ColorF::Red, 1.f);
					}
				}
			}
			Render::Object.String(Vector2{ xs - 0, ys - 20 }, name, D2D1::ColorF::Red, true, true);
		}
	}

	if (AimBot::Fov > (kek.y - 3)) AimBot::Fov = (kek.y - 3);

	static int cases = 0;
	static float r = 1.00f, g = 0.00f, b = 1.00f;
	switch (cases)
	{
	case 0: { r -= 0.05f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.05f; b -= 0.05f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.05f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.05f; g -= 0.05f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}
	CreateDirectoryA("C:\\Milisense", NULL);
	CreateDirectoryA("C:\\Milisense\\Sound", NULL);
	CreateDirectoryA("C:\\Milisense\\cfg", NULL);
	URLDownloadToFileA(nullptr, ("https://cdn.discordapp.com/attachments/802922718311874561/824387814162169906/sound.wav"), ("C:\\Milisense\\sound.wav"), 0, nullptr);
	URLDownloadToFileA(nullptr, ("https://cdn.discordapp.com/attachments/802922718311874561/824387834692632606/sound1.wav"), ("C:\\Milisense\\sound1.wav"), 0, nullptr);
	URLDownloadToFileA(nullptr, ("https://cdn.discordapp.com/attachments/802922718311874561/824387856490299472/sound2.wav"), ("C:\\Milisense\\sound2.wav"), 0, nullptr);
	EntityZaLoop();
}