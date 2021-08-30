#!/bin/bash

PATH="/usr/bin:/bin"

# ensure that curl is installed
if ! which curl > /dev/null
then
    echo "curl not found on your system"
    echo "to install curl, read -"
    echo "  https://help.ubidots.com/en/articles/2165289-learn-how-to-install-run-curl-on-windows-macosx-linux"
    exit 1
fi

COOLCURL="https://secure.csse.uwa.edu.au/run/coolc"

function usage {
    echo "Usage: $0 program.cool"
    exit 1
}

# ensure that we were given 1 argument
if [ "$#" == 0 ]; then
    usage
fi

# ensure that filename is readable
if [ ! -r $1 ]; then
    echo "cannot read $1"
    usage
fi

# ensure that filename has correct extension
case "$1" in
    *.cool)	;;
    *)		usage
        	;;
esac

B=`basename $1 .cool`
rm -f $B.errs $B.coolexe

#set -x

# send the file to the coolc webpage
curl --silent -F "upload=y" -F "file1=@$1;filename=$1" -O -J $COOLCURL

# see which file coolc sent back
if [ -r $B.coolexe ]; then
    ls -l $B.coolexe
    exit 0
elif [ -r $B.errs ]; then
    cat < $B.errs
    rm -f $B.errs
else
    echo "oops, something went wrong :-("
    echo "did not receive $B.errs or $B.coolexe"
fi

exit 1
