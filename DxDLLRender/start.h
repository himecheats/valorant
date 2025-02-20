IDirect3DDevice9* pDevice2 = NULL;
IDirect3DTexture9* m_pTexture;

#include "iconfont.hpp"
#include "icons.hpp"
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	auto style = &ImGui::GetStyle();
	ImGui::StyleColorsDark();

	style->Alpha = 1.f;
	style->WindowRounding = 12.f;
	style->FramePadding = ImVec2(4, 3);
	style->WindowPadding = ImVec2(8, 8);
	style->ItemInnerSpacing = ImVec2(4, 4);
	style->ItemSpacing = ImVec2(8, 5);
	style->FrameRounding = 4.f;
	style->ScrollbarSize = 2.f;
	style->ScrollbarRounding = 12.f;
	style->PopupRounding = 5.f;


	ImVec4* colors = ImGui::GetStyle().Colors;

	//colors[ImGuiCol_ChildBg] = ImColor(24, 29, 59, 0);
	//colors[ImGuiCol_Border] = ImVec4(255, 255, 255, 0);
	//colors[ImGuiCol_FrameBg] = ImColor(25, 25, 33, 255);
	//colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 33, 255);
	//colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 33, 255);
	//colors[ImGuiCol_Header] = ImColor(43, 55, 227, 255);
	//colors[ImGuiCol_HeaderActive] = ImColor(43, 55, 227, 255);
	//colors[ImGuiCol_HeaderHovered] = ImColor(43, 55, 227, 255);
	//colors[ImGuiCol_PopupBg] = ImColor(43, 55, 227, 255);
	//colors[ImGuiCol_Button] = ImColor(160, 30, 30, 255);
	//colors[ImGuiCol_ButtonHovered] = ImColor(190, 45, 35, 255);
	//colors[ImGuiCol_ButtonActive] = ImColor(220, 60, 40, 255);
	Elements = io.Fonts->AddFontFromMemoryTTF(&Gilroy, sizeof Gilroy, 13, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	m_MenuIcons = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Icons_compressed_data, Icons_compressed_size, 18.0f);
    m_LogFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(xorstr("C:/windows/fonts/seguisb.ttf"), 16.0f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
	//D3DPRESENT_PARAMETERS pp = {};
	//D3DXCreateTextureFromFileInMemoryEx(pDevice2, texture, sizeof(texture), 4096, 4096, D3DX_DEFAULT, NULL, pp.BackBufferFormat, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, &m_pTexture);
}
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			Beep(500, 125);
			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		show = !show;
	}
	if (!Global::Panic) {
		if (Render::Object.NewFrame(pSwapChain))
		{
			InitCheat();
		}
		Render::Object.EndFrame();
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		Render::Object.EndFrame();
		if (Visuals::Watermark) {RenderWatermark();}
		if (Visuals::Keybinds) { DrawKeybindList(); }
		if (show)
		{
			Menucheat();
		}
		ImGui::End();
		ImGui::Render();
		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}
int MultisampleCount = 1;
LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }
DWORD __stdcall Start(LPVOID)
{
	Storage::gBase = (DWORD64)GetModuleHandleA("GameAssembly.dll");
	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle(L"dxgi.dll");
		Sleep(4000);
	} while (!hDXGIDLL);
	Sleep(100);
	IDXGISwapChain* pSwapChain;
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);
	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = MultisampleCount;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	UINT createFlags = 0;
#ifdef _DEBUG
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	IDXGISwapChain* d3dSwapChain = 0;
	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)))
	{
		MessageBox(hWnd, L"Failed to create directX device and swapchain!", L"Error", MB_ICONERROR);
		return NULL;
	}
	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];
	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];
	phookD3D11Present = (D3D11PresentHook)(DWORD_PTR*)pSwapChainVtable[8];
	phookD3D11ResizeBuffers = (D3D11ResizeBuffersHook)(DWORD_PTR*)pSwapChainVtable[13];
	phookD3D11PSSetShaderResources = (D3D11PSSetShaderResourcesHook)(DWORD_PTR*)pContextVTable[8];
	phookD3D11Draw = (D3D11DrawHook)(DWORD_PTR*)pContextVTable[13];
	phookD3D11DrawIndexed = (D3D11DrawIndexedHook)(DWORD_PTR*)pContextVTable[12];
	phookD3D11DrawIndexedInstanced = (D3D11DrawIndexedInstancedHook)(DWORD_PTR*)pContextVTable[20];
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)phookD3D11Present, (PBYTE)hookD3D11Present);
	DetourTransactionCommit();
	InitHook();
	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);
	while (true) {
		Sleep(10);
	}
	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();
	return NULL;
}