#!/bin/bash
echo 1; echo 50000; for i in {1..49999}; do echo $i $(($i + 1)); done; echo 50000 1
