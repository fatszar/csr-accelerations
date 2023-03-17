cmake -E make_directory build &&
cd build &&
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. &&
cmake --build . &&
./csrlib
