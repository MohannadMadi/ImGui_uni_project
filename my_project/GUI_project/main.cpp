// Dear ImGui: standalone example application for DirectX 10
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx10.h"
#include <d3d10_1.h>
#include <d3d10.h>
#include <tchar.h>
#include "student.cpp"
#include "student.h"
 
// Data
static ID3D10Device*            g_pd3dDevice = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D10RenderTargetView*  g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"moodle", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX10_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    
    bool show_start_window = true;
    bool show_student_registration_window = false;
    bool show_CPG_student_registration_window = false;
    bool show_Course_registration_window = false;



    ImVec4 clear_color = ImColor(30,30,30);
    // My variables
    bool start = true;
    //Auth_login
    char *StudentUserName = "\0";
    char* StudentPassword = "\0";
        //students_courses

        int n_students = 0;
        int n_courses = 0;
        int n_CPG_students = 0;
        int current_student_index = 0;
        int current_CPG_student_index = 0;
        int current_course_index = 0;
        CStudent* students = new CStudent[10000];
        CCourse* courses = new CCourse[10000];
        CPG_Student gradStudents[22] = {};


        char nameOfStudent[100] = "\0";
        char emailUserOfStudent[100] = "\0";
        char emailPassOfStudent[100] = "\0";
        int idOfStudent = 0;
        char majorOfStudent[100] = "\0";
        float gradesOfStudent[5]= { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
        float scoreOfStudent = 0;
        int fullySubmitted = 1;
        //CPG
        char gSjobTitle[100] = "\0";
        //C_Course
        char nameOfCourse[100]="\0";
        char codeOfCourse[100]="\0";
        float costOfCourse = 0;
    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX10_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (show_start_window)
        {
            ImGui::SetNextWindowSize(ImVec2(400, 200));
            if (ImGui::Begin("Student registration form ", NULL))
            {
                ImGui::Text("Enter number of students");
                ImGui::InputInt("##numberOfStudents", &n_students);

                ImGui::Text("Enter number of grad students ");
                ImGui::InputInt("##numberOfGradStudents", &n_CPG_students);

                ImGui::Text("Enter number of courses");
                ImGui::InputInt("##numberOfcourses", &n_courses);
                if (ImGui::Button("Register "))
                {
                    if ( n_students > 0)
                    {
                        show_student_registration_window = true;
                        show_start_window = false;
                    }
                    else if (n_CPG_students > 0)
                    {
                        show_CPG_student_registration_window = true;
                        show_start_window = false;
                    }
                    else if (n_courses > 0)
                    {
                        show_Course_registration_window = true;
                        show_start_window = false;
                    }
                    else
                    {
                        ImGui::Text("Nothing to register  ");
                    }
                }
                
            }
            ImGui::End();
        }
        
        //Register students
        if (show_student_registration_window)
        {

            if (n_students > 0 && current_student_index < n_students)
            {

                ImGui::SetNextWindowSize(ImVec2(500, 600));
                if (ImGui::Begin("Fill in students info"))
                {
                    ImGui::Text("Student %d info  ", (current_student_index + 1));
                    students[current_student_index].registerStudent(nameOfStudent, emailUserOfStudent, emailPassOfStudent, &idOfStudent, majorOfStudent, gradesOfStudent, scoreOfStudent, &fullySubmitted, &current_student_index, gSjobTitle);
                    ImGui::Text("%d ", current_student_index);
                }
                ImGui::End();
            }
            else
            {
                show_student_registration_window = false;
                show_CPG_student_registration_window = true;
            }
        }


            //Register grad students
            if (show_CPG_student_registration_window)
            {
                if (n_CPG_students>0 && current_CPG_student_index < n_CPG_students)
                {
                    ImGui::SetNextWindowSize(ImVec2(500, 600));
                    if (ImGui::Begin("Fill in grad students info "))
                    {
                        ImGui::Text("Student %d info ", (current_CPG_student_index + 1));
                        gradStudents[current_CPG_student_index].registerStudent(nameOfStudent, emailUserOfStudent, emailPassOfStudent, &idOfStudent, majorOfStudent, gradesOfStudent, scoreOfStudent, &fullySubmitted, &current_CPG_student_index, gSjobTitle);
                    }
                    ImGui::End();
                    
                }
                else
                {

                    show_CPG_student_registration_window = false;
                    show_Course_registration_window = true;
                }
            }
            //Register courses                
            if (show_Course_registration_window)
            {
                if (n_courses > 0 && current_course_index < n_courses)
                {
                    ImGui::SetNextWindowSize(ImVec2(500, 600));
                    if (ImGui::Begin("Fill in course info "))
                    {
                        ImGui::Text("course %d info ", (current_course_index + 1));
                        courses[current_course_index].registerCourses(nameOfCourse, codeOfCourse, &costOfCourse, &fullySubmitted,&current_course_index);
                    }
                    ImGui::End();

                }
                else
                {
                    show_Course_registration_window = false;
                }
            }

            
        

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDevice->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDevice->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX10_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    ImGui_ImplDX10_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
    HRESULT res = D3D10CreateDeviceAndSwapChain(nullptr, D3D10_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D10CreateDeviceAndSwapChain(nullptr, D3D10_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D10Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
