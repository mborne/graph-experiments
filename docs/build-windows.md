# CMake - Building on windows with Microsoft Visual Studio and miniconda

## Install requirements

* [miniconda](https://docs.conda.io/en/latest/miniconda.html)
* [Microsoft Visual Studio - Community 2022](https://visualstudio.microsoft.com/fr/vs/)

## Build with cmake

```bat
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
"%userprofile%\miniconda3\condabin\activate.bat"

conda install gdal
conda install boost

mkdir build
cd build
cmake -G "NMake Makefiles" -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE="Release" ..
nmake
```
