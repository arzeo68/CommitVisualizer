if [ $EUID != 0 ]; then
    sudo "$0" "$@"
    exit $?
fi

git clone git@github.com:arzeo68/CommitVisualizer.git
cd CommitVisualizer
mkdir build
cd build
cmake ..
make
cp repositoryStat /usr/local/bin
echo "----------- END A ------------"