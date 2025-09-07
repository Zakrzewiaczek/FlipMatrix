Import("env")

env.Append(
    CPPPATH=[
        "#/applications_user/FlipMatrix/lib/max7219",
    ]
)

lib_sources = env.GlobRecursive("*.c", "lib")

lib = env.StaticLibrary("${BUILD_DIR}/lib/flipmatrix_max7219", lib_sources)
env.Install("${LIB_DIST_DIR}", lib)
Return("lib")
