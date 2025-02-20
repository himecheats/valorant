void WeaponPatch() {
	USHORT Hash = 0;
	WeaponData* Weapon = LocalPlayer.BasePlayer->GetActiveWeapon();
	if (Weapon) Hash = Weapon->GetNameHash();
	switch (Hash) {
	case 0x5A9F:
		if (Weapons::SuperBow)
			Weapon->SuperBow();
		break;
	case 0x435E:
		Weapon->SuperEoka();
	case 0x2333:
		if (Misc::LongHand) {
			Weapon->FatHand();
			Weapon->LongHand();
			Weapon->RunOnHit();
		} break;
	}
}

void MiscFuncs() {
	LocalPlayer.BasePlayer->SetFov();
	if (Misc::SpiderMan)
		LocalPlayer.BasePlayer->SpiderMan();
	if (Misc::flyindocatos)
	LocalPlayer.BasePlayer->Flyy();

	if (Misc::CustomFov)
		LocalPlayer.BasePlayer->SetFov();
	if (Misc::Zoom)
		LocalPlayer.BasePlayer->Zoom();
	if (Misc::InfJump) {
		if (GetAsyncKeyState(VK_SPACE)) {
			LocalPlayer.BasePlayer->InfinityJump();
		}
	}
	if (Weapons::NoSway)
		LocalPlayer.BasePlayer->NoSway();
	if (Misc::FakeAdmin)
		LocalPlayer.BasePlayer->FakeAdmin();
	if (Weapons::NoRecoil)
		LocalPlayer.BasePlayer->SetRA();
	if (Misc::LongNeck && GetAsyncKeyState(Misc::longKey))
		LocalPlayer.BasePlayer->LongNeck();
	if (Misc::LongNeckright && GetAsyncKeyState(Misc::LongNeckkey))
		LocalPlayer.BasePlayer->LongNeckright();
	if (Misc::LongNeckLeft && GetAsyncKeyState(Misc::LongNeckkeyLongNeckLeft))
		LocalPlayer.BasePlayer->LongNeckrLeft();
}
