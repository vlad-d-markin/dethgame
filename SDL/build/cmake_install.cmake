# Install script for directory: C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SDL2")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/build/libSDL2.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/build/libSDL2.dll.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/build/libSDL2.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSDL2.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSDL2.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/MinGW/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSDL2.dll")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/build/libSDL2main.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/begin_code.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/close_code.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_assert.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_atomic.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_audio.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_bits.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_blendmode.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_clipboard.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_android.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_iphoneos.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_macosx.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_minimal.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_pandora.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_psp.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_windows.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_winrt.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_config_wiz.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_copying.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_cpuinfo.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_egl.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_endian.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_error.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_events.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_filesystem.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_gamecontroller.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_gesture.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_haptic.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_hints.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_joystick.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_keyboard.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_keycode.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_loadso.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_log.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_main.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_messagebox.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_mouse.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_mutex.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_name.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengl.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengles.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengles2.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengles2_gl2.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengles2_gl2ext.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengles2_gl2platform.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengles2_khrplatform.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_opengl_glext.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_pixels.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_platform.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_power.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_quit.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_rect.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_render.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_revision.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_rwops.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_scancode.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_shape.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_stdinc.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_surface.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_system.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_syswm.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_assert.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_common.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_compare.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_crc32.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_font.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_fuzzer.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_harness.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_images.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_log.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_md5.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_test_random.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_thread.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_timer.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_touch.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_types.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_version.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/include/SDL_video.h"
    "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/build/include/SDL_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Eagle Owl/Desktop/dethgame/dethgame/SDL/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
