# CMake generated Testfile for 
# Source directory: /home/user/Work/Projects/WL_2D_MASS/1.0/Tools
# Build directory: /home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/Tools
# 
# This file includes the relevent testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(Tools.ShearInversions_test "/usr/bin/python" "/opt/euclid/Elements/3.8/InstallArea/x86_64-co7-gcc48-o2g/cmake/scripts/env.py" "--xml" "/home/user/Work/Projects/WL_2D_MASS/1.0/build.x86_64-co7-gcc48-o2g/WL_2D_MASSBuildEnvironment.xml" "ShearInversions_test")
SET_TESTS_PROPERTIES(Tools.ShearInversions_test PROPERTIES  LABELS "UnitTest;Tools;Binary;Boost" WORKING_DIRECTORY ".")
