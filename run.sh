set -o xtrace

make PROJECT_NAME=main 'OBJS=*.cpp src/*.cpp' BUILD_MODE=DEBUG  && ./main
