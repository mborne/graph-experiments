FROM debian:10

#--------------------------------------------
# install build dependencies
#--------------------------------------------
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    clang \
    make \
    libboost-graph-dev \
    libgdal-dev \
 && rm -rf /var/lib/apt/lists/*

#--------------------------------------------
# copy source
#--------------------------------------------
COPY . /usr/local/src/graph-experiments
WORKDIR /usr/local/src/graph-experiments

#--------------------------------------------
# build
#--------------------------------------------
ARG build_type=Release
RUN make build BUILD_TYPE=${build_type}
