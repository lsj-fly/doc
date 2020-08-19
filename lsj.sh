#!/bin/sh
echo 254 > /sys/class/gpio/export     #gpio8 from 248,gpio8_A6=248_6=254
echo out > /sys/class/gpio/gpio254/direction  #设置输出方向（out/in）
echo 0 > /sys/class/gpio/gpio254/value
sleep 1
echo 1 > /sys/class/gpio/gpio254/value
sleep 1
echo 0 > /sys/class/gpio/gpio254/value
sleep 1
echo 1 > /sys/class/gpio/gpio254/value
sleep 1
















































