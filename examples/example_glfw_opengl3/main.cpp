//********************************************************************************************:
//
//  ImGUI���K��
//  �y�쐬�ҁz
//      �ɒn�c�^��
//  �y�J�������z
//      2022/06/09 �쐬
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

/*�C�x���g
 *  ���鏈���̎��s�̂��������ƂȂ�o�������C�x���g�ƌĂ�
 *  ���������C�x���g�ɑΉ����鏈���̎��s���@�ɂ́A��ʕ\���̓x��
 *  glfwWaitEvents()�֐���glfwPollEvents()�֐���p���ăC�x���g�����o�����@(�|�[�����O����)��
 *  ����̃C�x���g�����������Ƃ��Ɏ��s����֐������炩���ߓo�^���Ă������@(�R�[���o�b�N����)������
 */

/*�֐���
 *  �֐�����gl�`�Ŏn�܂���̂�OpenGL��API�B
 *  �֐�����glfw�`�Ŏn�܂���̂�GLFW�̊֐��B
 */
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**) {
    // �E�B���h�E�ݒ�
    glfwSetErrorCallback(glfw_error_callback);  // OpenGL���ŃG���[�����������Ƃ��ɌĂ΂��
    if (!glfwInit()) {    // glfwInit()...GLFW�̏�����
        return -1;
    }

    /*
     *  OpenGL�̃o�[�W������v���t�@�C�����w�肵�ăE�B���h�E���쐬���܂�
     *  �����glfwCreateWindow()�ŃE�B���h�E���쐬����O�ɁAglfwWindowHint()�֐���p���čs��
     */
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // glfwCreateWindow...�E�B���h�E���쐬����
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui", NULL, NULL);
    if (!window) {
        glfwTerminate();    // �E�B���h�E��������I���������s��
        return -1;
    }

    // �쐬����window��OpenGL�̏����Ώۂɂ���
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // glfwWindowShouldClose...�E�B���h�E���J���Ă���ԌJ��Ԃ��`�悷��
    while (!glfwWindowShouldClose(window)) {
        /*
         *  �Ō�ɁA���̃v���O���������ɉ������ׂ����𔻒f���邽�߂ɁA
         *  ���̎��_�Ŕ������Ă���C�x���g�𒲍�����B
         *  glfwWindowShouldClose()�ɂ��E�B���h�E���Ƃ���ׂ����ǂ����̔��f��
         *  ���̃C�x���g�̒����Ɋ�Â��čs���B
         *
         *  �C�x���g�̒����ɂ̓}�E�X�Ȃǂő��삷��A�v���P�[�V�����\�t�g�E�F�A�̏ꍇ�́A
         *  �C�x���g����������܂ő҂�glfwWaitEvents()�֐���p����B
         *  ��glfwWaitEvents�̓��C���̃��[�v�ȊO�Ŏ��s���ׂ��ł͂Ȃ�
         *  �΂��āA�A�����ĉ�ʕ\�����X�V����A�v���P�[�V�����̏ꍇ��
         *  �C�x���g�̔�����҂��Ȃ�glfwPollEvents()�֐���p����i�Q�[���͂������j
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
        glClearColor(0.8f, 0.8f, 0.8f, 0.0f);   // �w�i�F�̎w��
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ��ʏ���
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);    // �_�u���o�b�t�@�����O�̃o�b�t�@�̓���ւ����s��
    }

    // �N���[���A�b�v
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    /*glfwTerminate
     *  GLFW�̏I���������s���BglfwInit()�֐���GLFW�̏������ɐ��������ꍇ�́A
     *  �v���O�������I������O�ɁA���̊֐������s����K�v������܂��B
     *  ���̊֐���GLFW�ō쐬�������ׂẴE�B���h�E����A�m�ۂ������ׂẴ��\�[�X��
     *  ������āA�v���O�����̏�Ԃ�glfwInit()�ŏ���������O�ɖ߂��B
     *  ���̌��GLFW�̋@�\���g�p����ɂ͍ēxglfwInit�����s���Ȃ���΂Ȃ�Ȃ�
     */
    glfwTerminate(); 
    return 0;
}
