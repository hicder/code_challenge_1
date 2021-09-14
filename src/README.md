* Clone
```
git clone https://github.com/hicder/code_challenge_1.git mongo_interview
cd mongo_interview
```
* Build the docker image
```
docker build -t mongo_interview .
```
* Build the code
```
docker run -v $(pwd)/src:/opt/src -w /opt/src -it mongo_interview:latest sh -c "rm -rf _build && mkdir _build && cd _build && cmake .. &&  make -j9"
```
* Run unit test
```
docker run -v $(pwd)/src:/opt/src -w /opt/src -it mongo_interview:latest sh -c "./_build/test/util_test"
```
* Run with a input json file
```
docker run -v $(pwd)/src:/opt/src -w /opt/src -it mongo_interview:latest sh -c "cat input.json | ./_build/flat_json"
```
