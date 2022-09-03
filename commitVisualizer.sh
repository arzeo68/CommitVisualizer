git clone git@github.com:arzeo68/CommitVisualizer.git
cd CommitVisualizer
sh ./install.sh
mkdir build
cd build
cmake ..
make
cp repositoryStat /usr/local/bin
echo "----------- END A ------------"