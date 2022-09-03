git clone git@github.com:arzeo68/CommitVisualizer.git
cd CommitVisualizer
mkdir build
cd build
cmake ..
make
sudo cp repositoryStat /usr/local/bin
cd ../../
rm -rf CommitVisualizer
rm -rf commitVisualizer.sh
echo "----------- END ------------"
