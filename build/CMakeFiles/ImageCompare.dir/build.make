# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cris/Frameworks/Gpu-Midas-Journal-800

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cris/Frameworks/Gpu-Midas-Journal-800/build

# Include any dependencies generated for this target.
include CMakeFiles/ImageCompare.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ImageCompare.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ImageCompare.dir/flags.make

CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o: CMakeFiles/ImageCompare.dir/flags.make
CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o: ../ImageCompare.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cris/Frameworks/Gpu-Midas-Journal-800/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o -c /home/cris/Frameworks/Gpu-Midas-Journal-800/ImageCompare.cxx

CMakeFiles/ImageCompare.dir/ImageCompare.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImageCompare.dir/ImageCompare.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cris/Frameworks/Gpu-Midas-Journal-800/ImageCompare.cxx > CMakeFiles/ImageCompare.dir/ImageCompare.cxx.i

CMakeFiles/ImageCompare.dir/ImageCompare.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImageCompare.dir/ImageCompare.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cris/Frameworks/Gpu-Midas-Journal-800/ImageCompare.cxx -o CMakeFiles/ImageCompare.dir/ImageCompare.cxx.s

CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.requires:

.PHONY : CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.requires

CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.provides: CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.requires
	$(MAKE) -f CMakeFiles/ImageCompare.dir/build.make CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.provides.build
.PHONY : CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.provides

CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.provides.build: CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o


# Object files for target ImageCompare
ImageCompare_OBJECTS = \
"CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o"

# External object files for target ImageCompare
ImageCompare_EXTERNAL_OBJECTS =

ImageCompare: CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o
ImageCompare: CMakeFiles/ImageCompare.dir/build.make
ImageCompare: /usr/local/lib/libitkdouble-conversion-4.12.a
ImageCompare: /usr/local/lib/libitksys-4.12.a
ImageCompare: /usr/local/lib/libitkvnl_algo-4.12.a
ImageCompare: /usr/local/lib/libitkvnl-4.12.a
ImageCompare: /usr/local/lib/libitkv3p_netlib-4.12.a
ImageCompare: /usr/local/lib/libitknetlib-4.12.a
ImageCompare: /usr/local/lib/libitkvcl-4.12.a
ImageCompare: /usr/local/lib/libITKCommon-4.12.a
ImageCompare: /usr/local/lib/libitkNetlibSlatec-4.12.a
ImageCompare: /usr/local/lib/libITKStatistics-4.12.a
ImageCompare: /usr/local/lib/libITKTransform-4.12.a
ImageCompare: /usr/local/lib/libITKLabelMap-4.12.a
ImageCompare: /usr/local/lib/libITKMesh-4.12.a
ImageCompare: /usr/local/lib/libitkzlib-4.12.a
ImageCompare: /usr/local/lib/libITKMetaIO-4.12.a
ImageCompare: /usr/local/lib/libITKSpatialObjects-4.12.a
ImageCompare: /usr/local/lib/libITKPath-4.12.a
ImageCompare: /usr/local/lib/libITKQuadEdgeMesh-4.12.a
ImageCompare: /usr/local/lib/libITKIOImageBase-4.12.a
ImageCompare: /usr/local/lib/libITKOptimizers-4.12.a
ImageCompare: /usr/local/lib/libITKPolynomials-4.12.a
ImageCompare: /usr/local/lib/libITKBiasCorrection-4.12.a
ImageCompare: /usr/local/lib/libITKBioCell-4.12.a
ImageCompare: /usr/local/lib/libITKDICOMParser-4.12.a
ImageCompare: /usr/local/lib/libITKEXPAT-4.12.a
ImageCompare: /usr/local/lib/libITKIOXML-4.12.a
ImageCompare: /usr/local/lib/libITKIOSpatialObjects-4.12.a
ImageCompare: /usr/local/lib/libITKFEM-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmDICT-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmMSFF-4.12.a
ImageCompare: /usr/local/lib/libITKznz-4.12.a
ImageCompare: /usr/local/lib/libITKniftiio-4.12.a
ImageCompare: /usr/local/lib/libITKgiftiio-4.12.a
ImageCompare: /usr/local/lib/libitkhdf5_cpp.a
ImageCompare: /usr/local/lib/libitkhdf5.a
ImageCompare: /usr/local/lib/libITKIOBMP-4.12.a
ImageCompare: /usr/local/lib/libITKIOBioRad-4.12.a
ImageCompare: /usr/local/lib/libITKIOCSV-4.12.a
ImageCompare: /usr/local/lib/libITKIOGDCM-4.12.a
ImageCompare: /usr/local/lib/libITKIOIPL-4.12.a
ImageCompare: /usr/local/lib/libITKIOGE-4.12.a
ImageCompare: /usr/local/lib/libITKIOGIPL-4.12.a
ImageCompare: /usr/local/lib/libITKIOHDF5-4.12.a
ImageCompare: /usr/local/lib/libitkjpeg-4.12.a
ImageCompare: /usr/local/lib/libITKIOJPEG-4.12.a
ImageCompare: /usr/local/lib/libitktiff-4.12.a
ImageCompare: /usr/local/lib/libITKIOTIFF-4.12.a
ImageCompare: /usr/local/lib/libITKIOLSM-4.12.a
ImageCompare: /usr/local/lib/libITKIOMRC-4.12.a
ImageCompare: /usr/local/lib/libITKIOMesh-4.12.a
ImageCompare: /usr/local/lib/libITKIOMeta-4.12.a
ImageCompare: /usr/local/lib/libITKIONIFTI-4.12.a
ImageCompare: /usr/local/lib/libITKNrrdIO-4.12.a
ImageCompare: /usr/local/lib/libITKIONRRD-4.12.a
ImageCompare: /usr/local/lib/libitkpng-4.12.a
ImageCompare: /usr/local/lib/libITKIOPNG-4.12.a
ImageCompare: /usr/local/lib/libITKIOSiemens-4.12.a
ImageCompare: /usr/local/lib/libITKIOStimulate-4.12.a
ImageCompare: /usr/local/lib/libITKTransformFactory-4.12.a
ImageCompare: /usr/local/lib/libITKIOTransformBase-4.12.a
ImageCompare: /usr/local/lib/libITKIOTransformHDF5-4.12.a
ImageCompare: /usr/local/lib/libITKIOTransformInsightLegacy-4.12.a
ImageCompare: /usr/local/lib/libITKIOTransformMatlab-4.12.a
ImageCompare: /usr/local/lib/libITKIOVTK-4.12.a
ImageCompare: /usr/local/lib/libITKKLMRegionGrowing-4.12.a
ImageCompare: /usr/local/lib/libITKOptimizersv4-4.12.a
ImageCompare: /usr/local/lib/libITKVTK-4.12.a
ImageCompare: /usr/local/lib/libITKVideoCore-4.12.a
ImageCompare: /usr/local/lib/libITKVideoIO-4.12.a
ImageCompare: /usr/local/lib/libITKVtkGlue-4.12.a
ImageCompare: /usr/local/lib/libITKWatersheds-4.12.a
ImageCompare: /usr/local/lib/libITKIOXML-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmMSFF-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmDICT-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmIOD-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmDSED-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmCommon-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmjpeg8-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmjpeg12-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmjpeg16-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmopenjpeg-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmcharls-4.12.a
ImageCompare: /usr/local/lib/libitkgdcmuuid-4.12.a
ImageCompare: /usr/local/lib/libITKIOTIFF-4.12.a
ImageCompare: /usr/local/lib/libitktiff-4.12.a
ImageCompare: /usr/local/lib/libitkjpeg-4.12.a
ImageCompare: /usr/local/lib/libITKgiftiio-4.12.a
ImageCompare: /usr/local/lib/libITKEXPAT-4.12.a
ImageCompare: /usr/local/lib/libITKMetaIO-4.12.a
ImageCompare: /usr/local/lib/libITKniftiio-4.12.a
ImageCompare: /usr/local/lib/libITKznz-4.12.a
ImageCompare: /usr/local/lib/libITKNrrdIO-4.12.a
ImageCompare: /usr/local/lib/libitkpng-4.12.a
ImageCompare: /usr/local/lib/libITKIOIPL-4.12.a
ImageCompare: /usr/local/lib/libitkhdf5_cpp.a
ImageCompare: /usr/local/lib/libitkhdf5.a
ImageCompare: /usr/local/lib/libitkzlib-4.12.a
ImageCompare: /usr/local/lib/libITKIOTransformBase-4.12.a
ImageCompare: /usr/local/lib/libITKTransformFactory-4.12.a
ImageCompare: /usr/local/lib/libITKOptimizers-4.12.a
ImageCompare: /usr/local/lib/libITKIOImageBase-4.12.a
ImageCompare: /usr/local/lib/libITKVideoCore-4.12.a
ImageCompare: /usr/local/lib/libITKVTK-4.12.a
ImageCompare: /usr/local/lib/libvtkRenderingOpenGL2-7.1.so.1
ImageCompare: /usr/lib/x86_64-linux-gnu/libSM.so
ImageCompare: /usr/lib/x86_64-linux-gnu/libICE.so
ImageCompare: /usr/lib/x86_64-linux-gnu/libX11.so
ImageCompare: /usr/lib/x86_64-linux-gnu/libXext.so
ImageCompare: /usr/lib/x86_64-linux-gnu/libXt.so
ImageCompare: /usr/local/lib/libvtkIOImage-7.1.so.1
ImageCompare: /usr/local/lib/libvtkDICOMParser-7.1.so.1
ImageCompare: /usr/local/lib/libvtkmetaio-7.1.so.1
ImageCompare: /usr/local/lib/libvtkpng-7.1.so.1
ImageCompare: /usr/local/lib/libvtktiff-7.1.so.1
ImageCompare: /usr/local/lib/libvtkjpeg-7.1.so.1
ImageCompare: /usr/lib/x86_64-linux-gnu/libm.so
ImageCompare: /usr/local/lib/libvtkglew-7.1.so.1
ImageCompare: /usr/local/lib/libvtkRenderingFreeType-7.1.so.1
ImageCompare: /usr/local/lib/libvtkfreetype-7.1.so.1
ImageCompare: /usr/local/lib/libvtkzlib-7.1.so.1
ImageCompare: /usr/local/lib/libvtkInteractionStyle-7.1.so.1
ImageCompare: /usr/local/lib/libvtkRenderingCore-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonColor-7.1.so.1
ImageCompare: /usr/local/lib/libvtkFiltersGeometry-7.1.so.1
ImageCompare: /usr/local/lib/libvtkFiltersSources-7.1.so.1
ImageCompare: /usr/local/lib/libvtkFiltersExtraction-7.1.so.1
ImageCompare: /usr/local/lib/libvtkFiltersGeneral-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonComputationalGeometry-7.1.so.1
ImageCompare: /usr/local/lib/libvtkFiltersCore-7.1.so.1
ImageCompare: /usr/local/lib/libvtkFiltersStatistics-7.1.so.1
ImageCompare: /usr/local/lib/libvtkImagingFourier-7.1.so.1
ImageCompare: /usr/local/lib/libvtkalglib-7.1.so.1
ImageCompare: /usr/local/lib/libvtkImagingSources-7.1.so.1
ImageCompare: /usr/local/lib/libvtkImagingCore-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonExecutionModel-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonDataModel-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonTransforms-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonMisc-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonMath-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonSystem-7.1.so.1
ImageCompare: /usr/local/lib/libvtkCommonCore-7.1.so.1
ImageCompare: /usr/local/lib/libvtksys-7.1.so.1
ImageCompare: /usr/local/lib/libITKStatistics-4.12.a
ImageCompare: /usr/local/lib/libitkNetlibSlatec-4.12.a
ImageCompare: /usr/local/lib/libITKSpatialObjects-4.12.a
ImageCompare: /usr/local/lib/libITKMesh-4.12.a
ImageCompare: /usr/local/lib/libITKTransform-4.12.a
ImageCompare: /usr/local/lib/libITKPath-4.12.a
ImageCompare: /usr/local/lib/libITKCommon-4.12.a
ImageCompare: /usr/local/lib/libitkdouble-conversion-4.12.a
ImageCompare: /usr/local/lib/libitksys-4.12.a
ImageCompare: /usr/local/lib/libITKVNLInstantiation-4.12.a
ImageCompare: /usr/local/lib/libitkvnl_algo-4.12.a
ImageCompare: /usr/local/lib/libitkvnl-4.12.a
ImageCompare: /usr/local/lib/libitkv3p_netlib-4.12.a
ImageCompare: /usr/local/lib/libitknetlib-4.12.a
ImageCompare: /usr/local/lib/libitkvcl-4.12.a
ImageCompare: CMakeFiles/ImageCompare.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cris/Frameworks/Gpu-Midas-Journal-800/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ImageCompare"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ImageCompare.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ImageCompare.dir/build: ImageCompare

.PHONY : CMakeFiles/ImageCompare.dir/build

CMakeFiles/ImageCompare.dir/requires: CMakeFiles/ImageCompare.dir/ImageCompare.cxx.o.requires

.PHONY : CMakeFiles/ImageCompare.dir/requires

CMakeFiles/ImageCompare.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ImageCompare.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ImageCompare.dir/clean

CMakeFiles/ImageCompare.dir/depend:
	cd /home/cris/Frameworks/Gpu-Midas-Journal-800/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cris/Frameworks/Gpu-Midas-Journal-800 /home/cris/Frameworks/Gpu-Midas-Journal-800 /home/cris/Frameworks/Gpu-Midas-Journal-800/build /home/cris/Frameworks/Gpu-Midas-Journal-800/build /home/cris/Frameworks/Gpu-Midas-Journal-800/build/CMakeFiles/ImageCompare.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ImageCompare.dir/depend

