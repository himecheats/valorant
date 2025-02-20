using namespace ImGui;
ImFont* font_main;
ImFont* font_menu;
bool eng = true;
bool rus = false;

ImFont* info2 = nullptr;
IDirect3DTexture9* logggo = nullptr;
ImFont* info_big = nullptr;
ImFont* two = nullptr;
ImFont* three = nullptr;
ImFont* tabsf = nullptr;
ImFont* ee = nullptr;
ImVec2 pos;
ImDrawList* draw;
#include "custom.h"
#include "ImGUI/imgui.h"
VOID ImGUI_Style()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	style->Alpha = 1.f;
	style->WindowRounding = 1.f;
	style->FramePadding = ImVec2(4, 3);
	style->WindowPadding = ImVec2(8, 8);
	style->ItemInnerSpacing = ImVec2(4, 4);
	style->ItemSpacing = ImVec2(8, 4);
	style->FrameRounding = 5.f;
	style->ScrollbarSize = 2.f;
	style->ScrollbarRounding = 12.f;

	colors[ImGuiCol_ChildBg] = ImColor(13, 11, 16);
	colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.11f, 0.50f);
	colors[ImGuiCol_FrameBg] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_Header] = ImColor(25, 25, 33, 255);
	colors[ImGuiCol_HeaderActive] = ImColor(28, 28, 36, 255);
	colors[ImGuiCol_HeaderHovered] = ImColor(30, 30, 38, 255);
	colors[ImGuiCol_PopupBg] = ImColor(35, 35, 45, 255);
}
static LPDIRECT3DDEVICE9        g_pd3dDevice2 = NULL;

void decorations()
{
	pos = ImGui::GetWindowPos();
	draw = ImGui::GetWindowDrawList();

	draw->AddRectFilled(ImVec2(pos), ImVec2(pos.x + 680, pos.y + 433), ImColor(13, 13, 13));
	draw->AddRectFilledMultiColor(ImVec2(pos), ImVec2(pos.x + 680, pos.y + 25), ImColor(23, 23, 23), ImColor(23, 23, 23), ImColor(13, 13, 13), ImColor(13, 13, 13));
	draw->AddRectFilled(ImVec2(pos.x + 14, pos.y + 30), ImVec2(pos.x + 670, pos.y + 423), ImColor(18, 18, 18));
	draw->AddRect(ImVec2(pos.x + 14, pos.y + 30), ImVec2(pos.x + 670, pos.y + 423), ImColor(5, 5, 5), 0.f, 0.f, 2.f);
	draw->AddRect(ImVec2(pos.x + 175, pos.y + 35), ImVec2(pos.x + 665, pos.y + 417), ImColor(5, 5, 5), 0, 0, 2.f);

	ImGui::SetCursorPos(ImVec2(22, 40));
}

static int tabs;
static int subtabs;


void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
ImVec4 rgb_to_imvec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255, g / 255, b / 255, a / 255);
}
ImFont* Elements;
void RenderWatermark()
{
	float sWidth = Global::ScreenWidth;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, rgb_to_imvec4(255, 0, 0, 255));
	const char* _text = xorstr("Milisense | Beta | By kors22");
	ImGui::PushFont(Elements);
	ImGui::SetNextWindowPos(ImVec2(sWidth - 15 - ImGui::CalcTextSize(_text).x - 10, 10));
	ImGui::SetNextWindowSize(ImVec2(ImGui::CalcTextSize(_text).x + 10, 20));
	ImGui::Begin(xorstr("Watermark"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	{
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild(xorstr("##linerender"), ImVec2(ImGui::CalcTextSize(_text).x + 28, 5)); ImGui::EndChild();

		ImGui::SetCursorPos(ImVec2(5, 5));
		ImGui::Text(_text);
		ImGui::PopFont();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}

void tabss()
{
	ImGui::PushFont(info2);

	ImGui::SetCursorPos(ImVec2(19, 35));
	ImGui::BeginGroup();

	if (ImGui::tab("Aimbot", 0 == tabs))
		tabs = 0;
	if (ImGui::tab("Visuals", 1 == tabs))
		tabs = 1;
	if (ImGui::tab("Misc", 2 == tabs))
		tabs = 2;
	if (ImGui::tab("Color", 3 == tabs))
		tabs = 3;
	if (ImGui::tab("Settings", 4 == tabs))
		tabs = 4;

	ImGui::EndGroup();

	ImGui::PopFont();

	ImGui::PushFont(info2);

	//Aimbot
	if (tabs == 0)
	{
		ImGui::SetCursorPos(ImVec2(180, 30));
		ImGui::BeginChild("Ragebot", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 25));
			ImGui::BeginGroup();
			{
				ImGui::Checkbox(xorstr("Meleeatack"), &Misc::Meleeatack);
				ImGui::Checkbox(xorstr("Resolver"), &AimBot::AlwaysHeadshot);
				ImGui::Checkbox(xorstr("pSilent"), &AimBot::pSilent);
				ImGui::Checkbox(xorstr("AimAssist"), &AimBot::AimAssist);
				ImGui::Checkbox("Auto Shoot", &AimBot::AutoShoot);
				ImGui::Checkbox("Peek Assist Indicator", &Misc::PeekAssistIndicator);
				ImGui::Checkbox("Peek Assist", &Misc::PeekAssist);
				ImGui::Checkbox("Fastshot", &Misc::Fastshot);
				ImGui::Checkbox(xorstr("Anti-Aim"), &Misc::AntiAim);
				ImGui::Checkbox(xorstr("Fake-Lag"), &Misc::FakeLag);
				ImGui::Checkbox("CustomFov", &Misc::CustomFov);
				if (Misc::CustomFov) {
					ImGui::SliderFloat("CustomFov Value", &Misc::FovRange, 0.f, 200.f);
				}
				ImGui::Checkbox("Zoom", &Misc::Zoom);
				if (Misc::Zoom)
				{
					ImGui::SliderFloat("Zoom Value", &Misc::Zoomvalue, 10.f, 60.f);
					Hotkey("Zoom Key", &Misc::Zoomkey, ImVec2(150, 30));
				}
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
		ImGui::SameLine(0.f, 10.f);
		ImGui::BeginChild("LegitBot", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 25));
			ImGui::BeginGroup();
			{
				ImGui::Checkbox(xorstr("Activate Aimbot"), &AimBot::Activate);
				Hotkey(xorstr("AimKey"), &Keys::aimKey, ImVec2(120.f, 0));
				ImGui::Checkbox(xorstr("Show Fov"), &AimBot::DrawFov);
				ImGui::SliderFloat(xorstr("Set Fov"), &AimBot::Fov, 20.f, 100.f);
				ImGui::SliderFloat(xorstr("Aim Distance"), &AimBot::Range, 0.f, 400.f);
				ImGui::Checkbox(xorstr("NPC Check"), &AimBot::IgnoreNpc);
				ImGui::Checkbox(xorstr("Teammate Check"), &AimBot::IgnoreTeam);
				ImGui::Checkbox(xorstr("Sleeper Check"), &AimBot::IgnoreSleepers);
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}

	//visuals
	if (tabs == 1)
	{
		ImGui::SetCursorPos(ImVec2(180, 30));
		ImGui::BeginChild("Visual", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 20));
			ImGui::BeginGroup();
			{
				ImGui::Checkbox(xorstr("Name"), &PlayerEsp::name);
				ImGui::Checkbox(xorstr("Box"), &PlayerEsp::box);
				ImGui::Checkbox(xorstr("Fill Box"), &PlayerEsp::fillbox);
				ImGui::Checkbox(xorstr("Skeleton"), &PlayerEsp::skeleton);
				ImGui::Checkbox(xorstr("healthbar"), &PlayerEsp::healthbar);
				ImGui::Checkbox(xorstr("Weapon"), &PlayerEsp::weapon);
				ImGui::Checkbox(xorstr("Wounded"), &PlayerEsp::wounded);
				ImGui::Checkbox(xorstr("Distance"), &PlayerEsp::distance);
				ImGui::Checkbox(xorstr("Target Tracers"), &PlayerEsp::targetline);
				ImGui::Checkbox(xorstr("Ignore Sleepers"), &PlayerEsp::sleeperignore);
				ImGui::Text("Bot esp");
				ImGui::Checkbox(xorstr("Name [b]"), &BotsEsp::name);
				ImGui::Checkbox(xorstr("Box [b]"), &BotsEsp::box);
				ImGui::Checkbox(xorstr("Skeleton [b]"), &BotsEsp::skeleton);
				ImGui::Checkbox(xorstr("Health [b]"), &BotsEsp::health);
				ImGui::Checkbox(xorstr("Weapon [b]"), &BotsEsp::weapons);
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
		ImGui::SameLine(0.f, 10.f);
		ImGui::BeginChild("Resource", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 25));
			ImGui::BeginGroup();
			{

				if (ImGui::CollapsingHeader(xorstr("Ores")))
				{
					ImGui::Checkbox(xorstr("Stone"), &Ores::Stone);
					ImGui::Checkbox(xorstr("Sulfur"), &Ores::Sulfur);
					ImGui::Checkbox(xorstr("Metal"), &Ores::Metal);
					if (Ores::Sulfur || Ores::Stone || Ores::Metal)
					{
						ImGui::SliderFloat(xorstr("Ore ESP Distance"), &Ores::oreDrawDistance, 5.f, 400.f);
						ImGui::Checkbox(xorstr("Show Distance"), &Ores::showDistance);
					}
				}
				if (ImGui::CollapsingHeader(xorstr("Other")))
				{
					if (ImGui::CollapsingHeader(xorstr("Crates")))
					{
						ImGui::Checkbox(xorstr("Airdrops"), &Visuals::Supply);
						ImGui::Checkbox(xorstr("Chinook Crates"), &Visuals::Chinook);
						if (Visuals::Supply || Visuals::Chinook)
						{
							ImGui::SliderFloat(xorstr("Crate ESP Distance"), &Visuals::drawCrateDistance, 5.f, 3000.f);
							ImGui::Checkbox(xorstr("Show Distance "), &Visuals::crateDistance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr("Vehicles")))
					{
						ImGui::Checkbox(xorstr("Minicopters"), &Visuals::Minicopter);
						ImGui::Checkbox(xorstr("Scrap Helis"), &Visuals::ScrapHeli);
						ImGui::Checkbox(xorstr("Boats"), &Visuals::Boat);
						ImGui::Checkbox(xorstr("RHIB's"), &Visuals::RHIB);
						if (Visuals::Minicopter || Visuals::ScrapHeli || Visuals::Boat || Visuals::RHIB)
						{
							ImGui::SliderFloat(xorstr("Vehicle ESP Distance"), &Visuals::drawVehicleDistance, 5.f, 3000.f);
							ImGui::Checkbox(xorstr("Show Distance  "), &Visuals::vehicleDistance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr("Traps")))
					{
						ImGui::Checkbox(xorstr("Auto Turrets"), &Visuals::AutoTurret);
						ImGui::Checkbox(xorstr("Flame Turrets"), &Visuals::FlameTurret);
						ImGui::Checkbox(xorstr("Shotgun Traps"), &Visuals::ShotgunTurret);
						ImGui::Checkbox(xorstr("Landmines"), &Visuals::Landmine);
						ImGui::Checkbox(xorstr("Beartraps"), &Visuals::BearTrap);
						if (Visuals::AutoTurret || Visuals::FlameTurret || Visuals::ShotgunTurret || Visuals::Landmine || Visuals::BearTrap)
						{
							ImGui::SliderFloat(xorstr("Trap ESP Distance"), &Visuals::drawTrapDistance, 5.f, 400.f);
							ImGui::Checkbox(xorstr("Show Distance   "), &Visuals::trapDistance);
						}
					}
					if (ImGui::CollapsingHeader(xorstr("Misc ")))
					{
						ImGui::Checkbox(xorstr("Patrol Heli"), &Visuals::PatrolHeli);
						ImGui::Checkbox(xorstr("Hemp"), &Visuals::Hemp);
						ImGui::Checkbox(xorstr("Corpses"), &Visuals::Corpse);
						ImGui::Checkbox(xorstr("Stashes"), &Visuals::Stash);
						if (Visuals::Corpse || Visuals::Stash || Visuals::Hemp || Visuals::PatrolHeli)
						{
							ImGui::SliderFloat(xorstr("Misc ESP Distance"), &Visuals::drawOtherDistance, 5.f, 400.f);
							ImGui::Checkbox(xorstr("Show Distance    "), &Visuals::otherDistance);
						}
					}
				}
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}

	//misc
	if (tabs == 2)
	{
		ImGui::SetCursorPos(ImVec2(180, 30));
		ImGui::BeginChild("Movement", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 20));
			ImGui::BeginGroup();
			{
				ImGui::Checkbox(xorstr("AutoFarm"), &Misc::AutoFarm);
				if (Misc::AutoFarm)
				{
					ImGui::Checkbox(xorstr("AutoFarmTree"), &Misc::AutoFarmTree);
					ImGui::Checkbox(xorstr("AutoFarmOre"), &Misc::AutoFarmOre);
				}
				ImGui::Checkbox(xorstr("InfinityJump"), &Misc::InfJump);
				ImGui::Checkbox(xorstr("Fake-Admin"), &Misc::FakeAdmin);
				ImGui::Checkbox(xorstr("Always-Aiming"), &Weapons::jumpAim);
				ImGui::Checkbox(xorstr("Omni-Sprint"), &Misc::omniSprint);
				ImGui::Checkbox(xorstr("speedhack"), &Misc::speedhack);
				Hotkey(xorstr("speedKey"), &Keys::speedKey, ImVec2(145.f, 0));
				ImGui::Checkbox(xorstr("Spiderman"), &Misc::SpiderMan);
				ImGui::Checkbox(xorstr("No Colision"), &Misc::no_playercollision);

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
		ImGui::SameLine(0.f, 10.f);
		ImGui::BeginChild("Weapon", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 20));
			ImGui::BeginGroup();
			{
				ImGui::Checkbox(xorstr("No Recoil"), &Weapons::NoRecoil);
				ImGui::Checkbox(xorstr("No Spread"), &Weapons::AntiSpread);
				ImGui::Checkbox(xorstr("No Sway"), &Weapons::NoSway);
				ImGui::Checkbox(xorstr("Thick Bullet"), &Weapons::FatBullet);
				ImGui::Checkbox(xorstr("Hold Items Anywhere"), &Weapons::canHoldItems);
				ImGui::Checkbox(xorstr("SuperEoka"), &Weapons::SuperEoka);
				ImGui::Checkbox(xorstr("SuperBow"), &Weapons::SuperBow);
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}
	//colors
	if (tabs == 3)
	{
		ImGui::SetCursorPos(ImVec2(180, 30));
		ImGui::BeginChild("Others", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 25));
			ImGui::BeginGroup();
			{
				ImGui::ColorEdit4("Crosshair", ColorsNShit::Crosshair2);
				ImGui::ColorEdit4("Watermark", ColorsNShit::Watermark);
				ImGui::ColorEdit4("Ambient", ColorsNShit::Ambient);
				ImGui::ColorEdit4("Fov", ColorsNShit::Fov);
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
		ImGui::SameLine(0.f, 10.f);
		ImGui::BeginChild("Playercolor", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 25));
			ImGui::BeginGroup();
			{

			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}
	//Settings
	if (tabs == 4)
	{
		ImGui::SetCursorPos(ImVec2(180, 30));
		ImGui::BeginChild("cfg", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 20));
			ImGui::BeginGroup();
			{
				ImGui::InputText("", Global::ConfigName, 0x100);
				if (ImGui::Button(xorstr("Save"), ImVec2(100.f, 0))) {
					SaveCFG(Global::ConfigName);
					Other::cfgSaved = true;
				}
				ImGui::SameLine();
				if (ImGui::Button(xorstr("Load"), ImVec2(100.f, 0))) {
					LoadCFG(Global::ConfigName);
				}
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
		ImGui::SameLine(0.f, 10.f);
		ImGui::BeginChild("Other", ImVec2(235, 382));
		{
			ImGui::SetCursorPos(ImVec2(10, 15));
			ImGui::BeginGroup();
			{
				ImGui::Checkbox(xorstr("Defolt Crosshair"), &AimBot::Crosshair);
				ImGui::Checkbox(xorstr("Custom Crosshair"), &AimBot::CustomCrosshair);
				if (AimBot::CustomCrosshair)
				{
					ImGui::SliderFloat(xorstr("Gap"), &AimBot::Gap, 1.f, 50.f);
					ImGui::SliderFloat(xorstr("Longht"), &AimBot::Longht, 1.f, 50.f);
				}
				ImGui::Checkbox(xorstr("Watermark"), &Visuals::Watermark);
				ImGui::Checkbox(xorstr("Keybinds"), &Visuals::Keybinds);
				ImGui::Checkbox(xorstr("Ambient"), &Visuals::NightMode);
				if (Hit::HitSound) {
					if (ImGui::BeginCombo("HitSounds", "Chose Hit Sound")) {

						Checkbox(("Bell"), &Hit::HitSound1);
						Checkbox(("Smert"), &Hit::HitSound2);
						Checkbox(("Ban gta"), &Hit::HitSound3);
						Checkbox(("Custom"), &Hit::CustomHitSound);
						End();
					}
				}
			}
			ImGui::EndGroup();
		}
		ImGui::EndChild();
	}
	ImGui::PopFont();
}

float dpi_scale = 1.f;
void Menucheat() {

	ImGui::Begin("Milisense", nullptr, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_HorizontalScrollbar);
	{
		static int x = 680 * dpi_scale, y = 433 * dpi_scale;
		pos = ImGui::GetWindowPos();
		draw = ImGui::GetWindowDrawList();
		ImGui::SetWindowSize(ImVec2(ImFloor(x * dpi_scale), ImFloor(y * dpi_scale)));

		decorations();
		tabss();

	}
	ImGui::End();
}

#define PUSH_BIND( m_Variable, Name )
struct Bind_t
{
	std::string m_szName = "";
	float_t m_flAlphaPercent = 0.0f;
};
std::map < uint32_t, Bind_t > m_BindList;
ImFont* m_LogFont = nullptr;
ImFont* m_MenuIcons = nullptr;
static inline ImDrawList* GetOverlayDrawList2() { return GetForegroundDrawList(); }
void DrawKeybindList()
{
	int m_Last = 0;
	PUSH_BIND(AimBot::pSilent, "pSilent");
	//PUSH_BIND(g_Settings->m_aDoubleTap, "Double tap");
	//PUSH_BIND(g_Settings->m_aSlowwalk, "Slow walk");
	//PUSH_BIND(g_Settings->m_aHideShots, "Hide shots");
	//PUSH_BIND(g_Settings->m_aSafePoint, "Safe points");
	//PUSH_BIND(g_Settings->m_aInverter, "Invert side");
	//PUSH_BIND(g_Settings->m_aAutoPeek, "Auto peek");
	//PUSH_BIND(g_Settings->m_aMinDamage, "Damage override");

	int32_t iCount = 0;
	for (auto& Bind : m_BindList)
	{
		if (Bind.second.m_szName.length())
			iCount++;
	}

	if (iCount <= 0)
		return;

	int nAdvancedFlag = 0;

	ImGui::SetNextWindowSize(ImVec2(190, m_BindList.empty() ? 0 : 35 + (21.5f * iCount)));
	ImGui::Begin(xorstr("Keybind List"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | nAdvancedFlag);
	{
		int32_t x = ImGui::GetCurrentWindow()->Pos.x + 4.5f;
		int32_t y = ImGui::GetCurrentWindow()->Pos.y;

		GetOverlayDrawList2()->AddRectFilled(ImVec2(x, y), ImVec2(x + 181, y + 22), ImColor(24.0f / 255.0f, 31.0f / 255.0f, 44.0f / 255.0f, 1.0f));
		GetOverlayDrawList2()->AddRectFilled(ImVec2(x, y + 22), ImVec2(x + 181, y + 22.27f), ImColor(0.0f, 115.0f / 255.0f, 222.0f / 255.0f, 1.0f));
		GetOverlayDrawList2()->AddRectFilled(ImVec2(x, y + 22.27f), ImVec2(x + 181, y + 22.30f), ImColor(0.0f, 115.0f / 255.0f, 222.0f / 255.0f, 0.65f));

		ImGui::PushFont(m_MenuIcons);
		GetOverlayDrawList2()->AddText(ImVec2(x + 5, y + 2), ImColor(71, 163, 255), xorstr("a"));
		ImGui::PopFont();

		ImGui::PushFont(m_LogFont);
		GetOverlayDrawList2()->AddText(ImVec2(x + 26, y + 2), ImColor(255, 255, 255), xorstr("Keybind list"));
		ImGui::PopFont();

		for (auto& Bind : m_BindList)
		{
			if (!Bind.second.m_szName.length())
				continue;

			ImGui::PushFont(m_LogFont);
			GetOverlayDrawList2()->AddText(ImVec2(x + 2, 27 + (y + 16 * m_Last)), ImColor(255, 255, 255, static_cast <int>(Bind.second.m_flAlphaPercent * 255.0f)), Bind.second.m_szName.c_str());
			GetOverlayDrawList2()->AddText(ImVec2(x + 160, 27 + (y + 16 * m_Last)), ImColor(255, 255, 255, static_cast <int>(Bind.second.m_flAlphaPercent * 255.0f)), xorstr("On"));
			ImGui::PopFont();

			m_Last++;
		}

	}
	ImGui::End();
}
