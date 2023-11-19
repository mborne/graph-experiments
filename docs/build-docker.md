
# CMake - build in a docker image

## Build an image

```bash
docker build -t graph-experiments .
# if a proxy is required :
#docker build --build-arg http_proxy --build-arg https_proxy -t graph-experiments .
```

## Run tests

```bash
docker run --rm -ti graph-experiments build/tests/egraph-test
```

