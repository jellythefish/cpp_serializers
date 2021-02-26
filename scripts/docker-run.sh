#!/bin/sh

# dev method to run container with shell and sources located at source
docker run --name cpp_serialization_methods --rm -v "C:\Users\Slava\Desktop\serialization":/usr/src/app/dev -it jellythefish/cpp_serializers /bin/bash

# basic run (default - small 10)
docker run --rm jellythefish/cpp_serializers

# with arguments
docker run --rm jellythefish/cpp_serializers medium 50

# Getting final results command from 0 to 100 real slow bruh...
docker build . --no-cache -t jellythefish/cpp_serializers && ^
docker run --rm jellythefish/cpp_serializers small 1000 && ^
docker run --rm jellythefish/cpp_serializers medium 500 && ^
docker run --rm jellythefish/cpp_serializers large 100
