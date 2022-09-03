if [ $EUID != 0 ]; then
    sudo "$0" "$@"
    exit $?
fi


git clone
mkdir build
cd build
cmake ..
make
cp repositoryStat /usr/local/bin