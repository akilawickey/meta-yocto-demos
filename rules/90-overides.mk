#! /usr/bin/make -f
# Author: Philippe Coval <philippe.coval@osg.samsung.com>
# ex: set tabstop=4 noexpandtab:

rule/overide/rule/configure-conf: rule/configure-conf
	ls -l ${conf_file}

rule/overide/rule/all: rule/all rule/bitbake/task/iotivity rule/bitbake/task/iotivity-simple-client rule/bitbake/task/linux-yocto
	@echo "TODO: rule/bitbake/task/iotivity-sensorboard"