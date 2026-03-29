docker run -it --rm \
    --privileged \
    --device=/dev/ttyUSB* \
    --device=/dev/ttyACM* \
    -e DISPLAY=$DISPLAY \
    -e QT_X11_NO_MITSHM=1 \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    -v /home/ethan-reynolds/github/robot-rover-2025/code/system/ros2:/root \
    vehicle_development_environment_ros2:foxy
    bash