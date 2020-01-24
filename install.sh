#!/bin/bash

mkdir build && cd build && cmake .. && make && mkdir lib && mv ./libft.a ./lib