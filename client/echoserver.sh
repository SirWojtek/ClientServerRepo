#!/bin/bash

ncat -l 1234 -c 'xargs -n1 echo'
