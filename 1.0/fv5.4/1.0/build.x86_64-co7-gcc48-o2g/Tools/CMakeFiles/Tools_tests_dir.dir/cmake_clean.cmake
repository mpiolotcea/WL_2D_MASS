FILE(REMOVE_RECURSE
  "../lib/libTools.so.dbg"
  "../bin/ShearInversions_test.dbg"
  "CMakeFiles/Tools_tests_dir"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/Tools_tests_dir.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
