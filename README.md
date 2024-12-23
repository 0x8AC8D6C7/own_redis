# own_redis
A porject to complete a simplified Redis, for teaching/learning.

Reference from: [build your own redis](https://build-your-own.org/redis/03_hello_cs)

# build
``` bash
# cd to current directory
cmake -B build
cmake --build build -j$(nproc)
```
# run
``` bash
# cd to current directory
./build/server

# then open a new tab or terminal window
./build/client
```