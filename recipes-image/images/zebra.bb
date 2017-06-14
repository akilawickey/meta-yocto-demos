#
# This file was derived from the 'Hello World!' example recipe in the
# Yocto Project Development Manual.
#

DESCRIPTION = "zebra package install recipe"
SECTION = "examples"
DEPENDS = ""
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

SRCREV = "4ec84957442182f36351f94c0626560ec3ffd487"
SRC_URI = "npm://registry.npmjs.org;name=zebkit;version=${PV}"


# this SRCREV determines the branch or tag to be used
SRCREV = "master"

# this is a revision number that should be updated every time you alter this recipe
PR = "r0" 

S = "${WORKDIR}/git"
