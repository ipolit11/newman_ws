#!/bin/bash

check_lsb() {

    echo "Checking your current ubuntu version..."
    VERSION=$(lsb_release  -rs)

    if [[ $VERSION == "18.04" ]]
    then
        echo "->Ubuntu Version $VERSION"
    elif [[ $VERSION == "20.04" ]]
    then
        echo "-> Ubuntu Version $VERSION"
    else
        echo "-> Non-compatible version for installing ROS"
        exit 1
    fi
}

add_sourcelist() {   

    echo "New source list that will be added into this directory </etc/apt/source.list.d>"
    echo "deb http://packages.ros.org/ros/ubuntu focal main" | sudo tee /etc/apt/sources.list.d/ros-focal.list
    
}

key_added() {

    sudo apt install curl
    KEY=$(curl -sSL "http://keyserver.ubuntu.com/pks/lookup?op=get&search=0xC1CF6E31E6BADE8868B172B4F42ED6FBAB17C654" | sudo apt-key add -)
    if [[ $KEY == "OK" ]]
    then 
        echo "-> Key is successfully added"
    else
        echo "-> Failed for key add"
        exit 1
    fi
}

get_repo() {

    sudo apt-get update && sudo apt-get upgrade
}

choice_packages() {

    read -n 1 -p "Would you like to install 
                1. ros-noetic-desktop-full (Recommend)
                2. ros-noetic-desktop
                3. ros-noetic-ros-base
                4. ros-noetic-ros-core 
                
                Please select (1/2/3/4) " ans;

    case $ans in
        1)
            echo "ros-noetic-desktop-full will be installed"
            sudo apt install ros-noetic-desktop-full;;
        2)
            echo "ros-noetic-desktop will be installed"
            sudo apt install ros-noetic-desktop;;
        3) 
            echo "ros-noetic-ros-base will be installed"
            sudo apt instsall ros-noetic-ros-base;;
        4)
            echo "ros-noetic-ros-core will be installed"
            sudo apt install ros-noetic-ros-core;;
        *)
            echo "Unknown"
            exit;;
    esac
}

setup_env() {

    echo "ROS environment set up now.."
    echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
    source ~/.bashrc
}

verify_installation() {
    
    roscd
    DIR=$(/usr/bin/pwd)
    if [[ $DIR == "/opt/ros/noetic" ]]
    then
        echo "-> Installation Completed Succesfully"
    else
        echo "-> Installation failed"
    fi
}

check_lsb
add_sourcelist
key_added
get_repo
choice_packages
setup_env
verify_installation
# user pkgs
#password 116
sudo apt-get update
sudo apt-get install terminator
sudo apt-get install git
git clone ssh://Dima@192.168.1.101:/volume1/git-server/newman_ws.git #dowmload newman ws. pass 123456789
sudo snap install code --classic
# in vs-code install ROS (microsoft) and CMake(twxs)
sudo apt-get install net-tools
#install cuda external pkg
sudo apt-get install libglfw3
sudo apt-get install libglfw3-dev
# install nvidia drivers
sudo apt install nvidia-utils-535 
sudo apt install nvidia-driver-535
# how install cuda https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=deb_local
wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
sudo mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600
wget https://developer.download.nvidia.com/compute/cuda/12.2.2/local_installers/cuda-repo-ubuntu2004-12-2-local_12.2.2-535.104.05-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu2004-12-2-local_12.2.2-535.104.05-1_amd64.deb
sudo cp /var/cuda-repo-ubuntu2004-12-2-local/cuda-*-keyring.gpg /usr/share/keyrings/
sudo apt-get update
sudo apt-get -y install cuda
sudo prime-select nvidia #end enable max performens on notebook
sudo apt-get install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio #add GStreamer
# speech to text
sudo apt-get install bison swig
sudo apt-get install alsa-utils libasound2-dev
sudo apt-get install pocketsphinx
sudo apt-get install python3-pocketsphinx
sudo apt-get install pocketsphinx-en-us
# ros audio suport
sudo apt-get install ros-noetic-audio-common