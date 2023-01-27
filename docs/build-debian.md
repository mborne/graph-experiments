
# CMake - Building on debian or ubuntu

* Install dependencies :

```bash
sudo apt-get update
sudo apt-get install -y --no-install-recommends \
    cmake \
    clang \
    make \
    libboost-graph-dev \
    libgdal-dev
```

* Build with cmake

```bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make test
```
