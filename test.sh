current_dir=$(cd $(dirname $0); pwd)
cd $current_dir/build
cmake ..
make
if [ $1 = "time" ];
then
    time ./layout_design
else
    ./layout_design
fi
cd $current_dir