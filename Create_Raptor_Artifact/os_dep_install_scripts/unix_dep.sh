ostype=`egrep '^(NAME)=' /etc/os-release  | grep -o -e Ubuntu -e CentOS`
dep_list_redhat="gtk3 "
dep_list_debian="libgtk-3-0 build-essential"
#echo "[INFO]    Installing Raptor on $ostype"
if [ "$ostype" == "CentOS" ]
then
    [ `which yum` ] && echo "Package manager is yum" || { echo "Fail to find package manager. Manually install below dependencies"; echo $dep_list_redhat; exit 1; }
    for dep in $dep_list_redhat
    do
        echo "$dep"
        sudo yum install -y $dep
    done
    sudo yum group install -y 'Development Tools'
elif [ "$ostype" == "Ubuntu" ]
then
    [ `which apt` ] && echo "Package manager is apt" || { echo "Fail to find package manager. Manually install below dependencies"; echo "$dep_list_debian Development Tools"; exit 1; }
    for dep in $dep_list_debian
    do
        echo "$dep"
        sudo apt install -y $dep
    done 
else
    echo "Unkown OS. Manually install below dependencies."
    echo $dep_list_redhat
    echo "Make sure to find equivalent name of above packages for your OS or contact at support@rapidsilicon.com"
    exit 1
fi