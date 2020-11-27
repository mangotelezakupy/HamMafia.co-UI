#include "includes.h"
#include "IconsFontAwesome5.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

ImFont* normal;
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);

	io.Fonts->AddFontDefault();

	// merge in icons from Font Awesome
	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	normal = io.Fonts->AddFontFromFileTTF("C:/Users/Admin/Desktop/icons.ttf", 16, &icons_config, icons_ranges);




}



LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
static bool menu_show = false;
static int tabs = 0;
bool init = false;
static bool shbypass = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{


	if (shbypass)
	{

		uintptr_t fiveBase = (uintptr_t)CustomAPI::GetModuleA("gta-core-five.dll");

		*(bool*)(fiveBase + 0xDA948) = 1;

	}


	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}


	if (GetAsyncKeyState(VK_F8) & 1) {
		menu_show = !menu_show;
		return 0;
	}

	if (menu_show) {

		ImGui::GetMouseCursor();
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		ImGui::GetIO().WantCaptureMouse = menu_show;
		ImGui::GetIO().MouseDrawCursor = menu_show;
	

		ImColor mainColor = ImColor(246, 89, 55, 255);
		ImColor bodyColor = ImColor(25, 25, 25, 255);
		ImColor bodyColor1 = ImColor(63, 70, 96, 255);
		ImColor bodyColor12 = ImColor(101, 110, 139, 255);
		ImColor fontColor = ImColor(255, 255, 255, 255);
		ImVec4 mainColorHovered = ImVec4(mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w);
		ImVec4 mainColorActive = ImVec4(mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w);
		ImVec4 menubarColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f);
		ImVec4 frameBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .1f);
		ImVec4 tooltipBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f);

		ImGuiStyle& style = ImGui::GetStyle();

		
		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2(8, 8);
		style.WindowMinSize = ImVec2(32, 32);
		style.WindowRounding = 0.f;
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

		style.FramePadding = ImVec2(6.5, 6.5);
		style.FrameRounding = 0.0f;
		style.ItemSpacing = ImVec2(4, 9);
		style.ItemInnerSpacing = ImVec2(8, 8);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 3.0f;
		style.ScrollbarSize = 14.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 0.0f;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.DisplayWindowPadding = ImVec2(22, 22);
		style.DisplaySafeAreaPadding = ImVec2(4, 4);
		style.AntiAliasedLines = true;

		style.CurveTessellationTol = 1.25f;

		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
		style.Colors[ImGuiCol_WindowBg] = ImColor(15, 14, 15, 255);
		style.Colors[ImGuiCol_ChildBg] = ImColor(25, 25, 25, 255); 
		style.Colors[ImGuiCol_Border] = ImColor(64, 64, 64, 0);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
		style.Colors[ImGuiCol_TitleBg] = mainColor;
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = mainColor; 
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(205, 92, 92, 175);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255); 
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);

		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.15f, 0.15f, 0.15f, 0.40f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);

		style.Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.15f, 0.15f, 0.97f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);



		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		static bool menu_show = true;
		static TextEditor		 editor;

	
		ImGui::Begin("Hammafia", &menu_show, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar);
		ImGui::SetWindowSize(ImVec2(750, 380), ImGuiCond_Always);

		ImGui::Columns(2);

		ImGui::SetColumnOffset(1, 223.4);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + -9); //
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + -9); //
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(200 / 255.f, 200 / 255.f, 200 / 255.f, 0.0f));
		if (ImGui::BeginChild("wondoa", ImVec2(223.4, 380)))
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 9); //
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 13); //
			if (ImGui::Button(ICON_FA_CODE  "  Executor", ImVec2(200, 37)))
			{
				tabs = 0;
			}

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 13); //
			if (ImGui::Button(ICON_FA_DOWNLOAD  "  Dumper", ImVec2(200, 37)))
			{
				tabs = 1;
			}
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 13); //
			if (ImGui::Button(ICON_FA_BUG  "  Blocker", ImVec2(200, 37)))
			{
				tabs = 2;
			}

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 13); //
			if (ImGui::Button(ICON_FA_BOOK  "  Menus", ImVec2(200, 37)))
			{
				tabs = 3;
			}

	
			ImGui::EndChild();

		}
		
		ImGui::PopStyleColor();
		
		
		ImGui::NextColumn();
		


		if (tabs == 0) {

			

			editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
			editor.SetShowWhitespaces(false);
			editor.SetPalette(TextEditor::GetFakePalette());
			editor.SetReadOnly(false);

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5); //
			if (ImGui::Button(ICON_FA_FILE  "  Execute From File", ImVec2(155, 28)))
			{
				
			}
			ImGui::SameLine();
			if (ImGui::Button("Isolated", ImVec2(80, 28)))
			{

			}

			ImGui::SameLine();
			ImGui::Checkbox("Shbypass", &shbypass);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5); //
			editor.Render("TextEditor", ImVec2(510, 262), false);
			static const char* current_resource = NULL;

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8); //
			ImGui::PushItemWidth(405);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5); //
			if (ImGui::BeginCombo("##cheatlist", current_resource))
			{



			}

			ImGui::SameLine();

			if (ImGui::Button(ICON_FA_CHECK "  Execute", ImVec2(100, 28)))
			{
		
			};




		}

		if (tabs == 1)
		{


			ImGui::Text("Ur gay");
		}

		if (tabs == 2) {


			ImGui::Text("Ur gay");
		}

		if (tabs == 3) {
			
			ImGui::Text("Ur gay");
			



		}





		ImGui::End();

		ImGui::Render();

		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
