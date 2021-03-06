# ð© Spine & SFML
- git clone git@github.com:jimboyeah/spine-sfml-demo.git

æ¬ä»£ç ä»åºç¨äºæä¾ Spine å¨ç»å¶ä½å SFML Framework å¥é¨çå­¦ä¹ ææã

Spine æ¯ä¸ä¸ªä¸ä¸ç 2D å¨ç»å¶ä½è½¯ä»¶ï¼åè½å¼ºå¤§ï¼è®¸å¤æ¸¸æå¨ç»å¶ä½é½æ¯åºäºå®å®ç°çã

SFML - Simple and Fast Multimedia æ¯ä¸ä¸ªè½»éçè·¨å¹³å°å¾å½¢ç¼ç¨æ¡æ¶ï¼å¯ä»¥ç»å OpenGL è¿è¡ç¸å¯¹åºå±ä½ä¸å¤ªéè¦äºè§£æä½ç³»ç»åºå±å¾å½¢è½åçç»èã

é¨åä»£ç æ¥èª [Spine runtimes](https://github.com/EsotericSoftware/spine-runtimes)ï¼åæ¬ C å CPPï¼è¿æ spine-cãspine-cpp ä¸¤ä¸ªç®å½ï¼å®ä»¬æ¯ Spine çè¿è¡æ¶å®ç°æºä»£ç ï¼ååºäº SFML å®ç°å¨ç»ç¤ºèãæä¾äº CMake èæ¬ï¼ä¼èªè¡ä¸è½½ SFML-2.4.1 ä¾èµåºï¼ä½æ¯ä¾èµè·¯å¾ç»è¿ä¿®æ¹ï¼ä½¿ç¨äº VC14-64-bit çæ¬ï¼

    set(DEPS_DIR "${PROJECT_SOURCE_DIR}/dependencies/")

ç¼è¯éè¦ä½¿ç¨çç¼è¯å¯ä»¥æ¯éè¿ä»¥ä¸è½¯ä»¶è·å¾ï¼

- Microsoft Visual Studio 2019 Community
- GNU GCC TDM/MinGW-w64


# ð© SFML Framework å¥é¨æç¨

## SFML CMake é¡¹ç®éç½®

- â[SFML CMake é¡¹ç®éç½®å¥é¨](./SFML-tutorials-cmake.md)
- â[CMakeLists.txt Demo](./SFML-tutorials-cmake.md#-cmakeliststxt-demo)
- â[Sublime Project](./SFML-tutorials-cmake.md#-sublime-project)

## SFML Framework å¥é¨æç¨

- â[Module Dependencies](./SFML-tuorials-modules.md)
- â[System Module](./SFML-tuorials-system.md)
- â¡[Window Module](./#-to-be-continue)
- â¡[Graphics Module](./#-to-be-continue)
- â¡[Audio Module](./#-to-be-continue)
- â¡[Network Module](./#-to-be-continue)

## OpenGL Shading Language

- â [The Graphics Rendering Pipeline](./SFML-tuorials-glsl.md#-The-Graphics-Rendering-Pipeline)
- â [OpenGL History & Core Profile](./SFML-tuorials-glsl.md#-OpenGL-History--Core-Profile)
- â [OpenGL API Loaders](./SFML-tuorials-glsl.md#-OpenGL-API-Loaders)
- â [GLUT & FreeGLUT](./SFML-tuorials-glsl.md#-GLUT--FreeGLUT)
- â [Shaders Language](./SFML-tuorials-glsl.md#-Shaders-Language)


## C++ ç¥è¯è¡¥å

- â[C++: Big forest ä¹¦å](/SFML-tuorials-Big-forest.md)
- â[C++ OOP é¢åå¯¹è±¡ç¼ç¨](./SFML-tuorials-cpp.md)

    - â[Inheritances ç»§æ¿](./SFML-tuorials-cpp.md#-Inheritances-ç»§æ¿)
    - â[Friend & Access Control](./SFML-tuorials-cpp.md#-Friend--Access-Control)
    - â[Override vs. Overwrite](./SFML-tuorials-cpp.md#-Override-vs-Overwrite)
    - â[Scope & Name-Hiding](./SFML-tuorials-cpp.md#-Scope--Name-Hiding)
    - â[CRTP Static Polymorphism éå¤æ](./SFML-tuorials-cpp.md#-CRTP-Static-Polymorphism-éå¤æ)
    - â[Virtual & Polymorphism èæä¸å¤ææºå¶](./SFML-tuorials-cpp.md#-Virtual--Polymorphism-èæä¸å¤ææºå¶)
    - â[Virtual and Multiple Inheritance](./SFML-tuorials-cpp.md#-Virtual-and-Multiple-Inheritance)
    - â[Class Layout ç±»æ°æ®ç»æå¸å±](./SFML-tuorials-cpp.md#-Class-Layout-ç±»æ°æ®ç»æå¸å±)

- â[C++ FAQs Virtual Functions](SFML-tuorials-cpp-faqs.md#-C++-FAQs-Virtual-Functions)

    - â[FAQ 8.05 virtual èå½æ°éåçè¯¥æå¼å¸¸è¿æ¯ no-op ä»ä¹ä¹ä¸åï¼](SFML-tuorials-cpp-faqs.md#-FAQ-805-virtual-èå½æ°éåçè¯¥æå¼å¸¸è¿æ¯-no-op-ä»ä¹ä¹ä¸å)
    - â[FAQ 19.10 ä¸ºä»ä¹ååä¸è½æ¯ virtualï¼](SFML-tuorials-cpp-faqs.md#-FAQ-1910-ä¸ºä»ä¹ååä¸è½æ¯-virtual)
    - â[FAQ 20.12 æ²¡æä»£ç ç virtual è§£æå¨å¦ä½å®ä¹?](SFML-tuorials-cpp-faqs.md#-FAQ-2012-æ²¡æä»£ç ç-virtual-è§£æå¨å¦ä½å®ä¹)
    - â[FAQ 20.13 åºç±»æé å¨è°ç¨ virtual å½æ°æ¶ä¸ºä½ä¸æ¯è°ç¨éåçæ¬?](SFML-tuorials-cpp-faqs.md#-FAQ-2013-åºç±»æé å¨è°ç¨-virtual-å½æ°æ¶ä¸ºä½ä¸æ¯è°ç¨éåçæ¬)
    - â[FAQ 21.07 virtual èæé å¨æ¯ä»ä¹ï¼](SFML-tuorials-cpp-faqs.md#-FAQ-2107-virtual-èæé å¨æ¯ä»ä¹)

- â[Smart Pointers æºè½æé](./SFML-tuorials-smart-pointer.md#-Smart-Pointers)

    - â[lvalue & rvalue reference å·¦å¼å³å¼å¼ç¨](./SFML-tuorials-smart-pointer.md#-lvalue--rvalue-reference)
    - â[Move Constructors ç§»å¨æé å½æ°](./SFML-tuorials-smart-pointer.md#-Move-Constructors)
    - â[auto_ptr to unique_ptr ç¬å æºè½æé](./SFML-tuorials-smart-pointer.md#-auto_ptr-to-unique_ptr)
    - â[shared_ptr & weak_ptr å±äº«æºè½æé](./SFML-tuorials-smart-pointer.md#-shared_ptr--weak_ptr-å±äº«æºè½æé)

