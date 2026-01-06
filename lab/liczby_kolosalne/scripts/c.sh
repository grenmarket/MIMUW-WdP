#!/bin/bash

echo $1 | sed 's:1:(:g; s:0:):g; s:():(0):g; s:)(:)+(:g; s:(:2^(:g; s:)$:-0:g' | bc