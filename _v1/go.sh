#!/bin/bash

for var in "$@"
do
    if [ "$var" == "--run-tests" ] || [ "$var" == "-t" ]; then
        run_flags="--test"
    elif [ "$var" == "--make-all" -o "$var" == "-b" ]; then
        make_flags="-B -j 2"
    fi
done

echo ${run_flags};

make linux64 ${make_flags}
if [ "$?" -eq "0" ]; then
    cd ./bin/
    ./randar ${run_flags}
fi
