RDEPENDS_${PN} += "xkeyboard-config"
RRECOMMENDS_${PN} = "liberation-fonts"

RDEPENDS_${PN}_remove = "weston-startup"

SRC_URI += "file://make-lcms-explicitly-configurable.patch"
SRC_URI += "file://make-libwebp-explicitly-configurable.patch"

PACKAGECONFIG ?= ""

#TODO: separate commit
# The current experimental vc4 drivers for RPI2 don't like the glesv2 backend
#	so, only enable it for archs where this is known to work
# PACKAGECONFIG += "${@bb.utils.contains('SOC_FAMILY', 'rpi', '', 'egl', d)}"
# PACKAGECONFIG += "${@bb.utils.contains('SOC_FAMILY', 'rpi', '', 'cairo-glesv2', d)}"


#PACKAGECONFIG += "egl"

CFLAGS_append_raspberrypi +="-I${STAGING_INCDIR}/interface/vcos/pthreads/ -I${STAGING_INCDIR}/interface/vmcs_host/linux/"

PKG_CONFIG_PATH += "/opt/vc/lib/pkgconfig/"

PACKAGECONFIG += "wayland-egl"


PACKAGECONFIG[egl] += " \
  --enable-drm-compositor --enable-wayland-compositor, \
 --disable-drm-compositor --disable-wayland-compositor, \
 virtual/egl"

PACKAGECONFIG[cairo-glesv2] += "--with-cairo=glesv2, , virtual/libgles2"

PACKAGECONFIG[wayland-egl] += "--enable-egl --enable-simple-egl-clients, --disable-egl --disable-simple-egl-clients,mesa-gl"

EXTRA_OECONF += "   \
                    --disable-vaapi-recorder \
                    --enable-weston-launch \
                    --enable-sys-uid \
                    --enable-fbdev-compositor \
                    --disable-headless-compositor \
                    --enable-setuid-install \
                    --enable-demo-clients-install \
                    --disable-lcms \
                    --disable-webp \
                    "

EXTRA_OECONF += "--disable-rdp-compositor"
EXTRA_OECONF += "--disable-dbus"
EXTRA_OECONF += "--enable-simple-clients --enable-clients"
EXTRA_OECONF += " --disable-static --disable-setuid-install --disable-libunwind"
EXTRA_OECONF += " --disable-xwayland --disable-xwayland-test --disable-x11-compositor"
EXTRA_OECONF += " --disable-rpi-compositor"


do_configure_prepend() {
    sed -i 's/PKG_CHECK_MODULES(WAYLAND_SCANNER, wayland-scanner)//' configure.ac
}

pkg_preinst_${PN}() {
}

export libexecdir="${prefix}/libexec"

FILES_${PN} += "${prefix}/lib/weston/cms-static.so"

FILES_${PN} += "${prefix}/bin/weston-scaler"
FILES_${PN} += "${prefix}/bin/weston-stacking"
FILES_${PN} += "${prefix}/bin/weston-multi-resource"