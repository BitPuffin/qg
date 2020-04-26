#!/bin/bash

cp -r template $1
cat $1/main.c | sed s/"puffin game"/$1/g

