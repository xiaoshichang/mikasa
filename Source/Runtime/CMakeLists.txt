
FILE(GLOB_RECURSE EngineSrc "*.cpp" "*.mm" "*.h")

add_library(${EngineDllName} ${EngineSrc})