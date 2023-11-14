set -o xtrace

make PROJECT_NAME=main OBJS=*.cpp BUILD_MODE=DEBUG  && ./main
