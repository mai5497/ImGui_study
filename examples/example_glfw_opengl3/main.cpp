//********************************************************************************************:
//
//  ImGUI練習中
//  【作成者】
//      伊地田真衣
//  【開発履歴】
//      2022/06/09 作成
//
//********************************************************************************************:

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
//#if defined(IMGUI_IMPL_OPENGL_ES2)
//#include <GLES2/gl2.h>
//#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

/*イベント
 *  ある処理の実行のきっかけとなる出来事をイベントと呼ぶ
 *  発生したイベントに対応する処理の実行方法には、画面表示の度に
 *  glfwWaitEvents()関数やglfwPollEvents()関数を用いてイベントを取り出す方法(ポーリング方式)と
 *  特定のイベントが発生したときに実行する関数をあらかじめ登録しておく方法(コールバック方式)がある
 */

/*関数名
 *  関数名がgl～で始まるものはOpenGLのAPI。
 *  関数名がglfw～で始まるものはGLFWの関数。
 */
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**) {
    // ウィンドウ設定
    glfwSetErrorCallback(glfw_error_callback);  // OpenGL内でエラーが発生したときに呼ばれる
    if (!glfwInit()) {    // glfwInit()...GLFWの初期化
        return -1;
    }

    /*
     *  OpenGLのバージョンやプロファイルを指定してウィンドウを作成します
     *  これはglfwCreateWindow()でウィンドウを作成する前に、glfwWindowHint()関数を用いて行う
     */
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // glfwCreateWindow...ウィンドウを作成する
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui", NULL, NULL);
    if (!window) {
        glfwTerminate();    // ウィンドウが閉じたら終了処理を行う
        return -1;
    }

    // 作成したwindowをOpenGLの処理対象にする
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // glfwWindowShouldClose...ウィンドウが開いている間繰り返し描画する
    while (!glfwWindowShouldClose(window)) {
        /*
         *  最後に、このプログラムが次に何をすべきかを判断するために、
         *  この時点で発生しているイベントを調査する。
         *  glfwWindowShouldClose()によるウィンドウをとじるべきかどうかの判断も
         *  このイベントの調査に基づいて行う。
         *
         *  イベントの調査にはマウスなどで操作するアプリケーションソフトウェアの場合は、
         *  イベントが発生するまで待つglfwWaitEvents()関数を用いる。
         *  ※glfwWaitEventsはメインのループ以外で実行すべきではない
         *  対して、連続して画面表示を更新するアプリケーションの場合は
         *  イベントの発生を待たないglfwPollEvents()関数を用いる（ゲームはこっち）
         */
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ImGui::Begin("Hello world");
        ImGui::End();


        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.8f, 0.8f, 0.8f, 0.0f);   // 背景色の指定
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 画面消去
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);    // ダブルバッファリングのバッファの入れ替えを行う
    }

    // クリーンアップ
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    /*glfwTerminate
     *  GLFWの終了処理を行う。glfwInit()関数でGLFWの初期化に成功した場合は、
     *  プログラムを終了する前に、この関数を実行する必要があります。
     *  この関数はGLFWで作成したすべてのウィンドウを閉じ、確保したすべてのリソースを
     *  解放して、プログラムの状態をglfwInit()で初期化する前に戻す。
     *  この後にGLFWの機能を使用するには再度glfwInitを実行しなければならない
     */
    glfwTerminate(); 
    return 0;
}
