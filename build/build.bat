rem python waf distclean
rem python waf configure --ndk C:\android-ndk-r8e
rem python waf configure
python waf build_debug_windows_x86_msvc
rem python waf build_release_windows_x86_msvc
python waf build_debug_windows_x86_gcc
rem python waf build_release_windows_x86_gcc
python waf build_debug_android9_armv7_ndk
rem python waf build_release_android9_armv7_ndk
python waf build_debug_browser_js_emcc
rem python waf build_release_browser_js_emcc
