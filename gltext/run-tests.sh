SHARED=`pwd`/src
if test $LD_LIBRARY_PATH; then
    export LD_LIBRARY_PATH=$SHARED:$LD_LIBRARY_PATH
else
    export LD_LIBRARY_PATH=$SHARED
fi

cd test && ./runtests
