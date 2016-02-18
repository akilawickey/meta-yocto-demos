RDEPENDS_${PN} += "xkeyboard-config"
RRECOMMENDS_${PN} = "liberation-fonts"

RDEPENDS_${PN}_remove = "weston-startup"

SRC_URI += "file://make-lcms-explicitly-configurable.patch"
SRC_URI += "file://make-libwebp-explicitly-configurable.patch"

PACKAGECONFIG ?= ""
PACKAGECONFIG += "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'wayland', '', d)}"
PACKAGECONFIG += "cairo-glesv2"
PACKAGECONFIG += "egl"


#EDEPENDS_WAYLAND_EGL ?= "virtual/wayland-egl"
#EDEPENDS_WAYLAND_EGL_append_x86 ?= "virtual/mesa"

PACKAGECONFIG += "wayland-egl"

PACKAGECONFIG[egl] += " \
 --enable-egl --enable-simple-egl-clients, \
 --disable-egl --disable-simple-egl-clients, \
 virtual/egl \
"

PACKAGECONFIG[wayland-egl] += "--enable-egl-backend, ,virtual/wayland-egl"
PACKAGECONFIG[wayland] = "--enable-wayland-compositor, --disable-wayland-compositor, wayland"
PACKAGECONFIG[drm] = "--enable-drm-compositor, --disable-drm-compositor, libdrm"
PACKAGECONFIG[cairo-glesv2] += "--with-cairo=glesv2, , virtual/libgles2"


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
EXTRA_OECONF += "--disable-static --disable-setuid-install --disable-libunwind"
EXTRA_OECONF += "--disable-xwayland --disable-xwayland-test --disable-x11-compositor"


do_configure_prepend() {
    sed -i 's/PKG_CHECK_MODULES(WAYLAND_SCANNER, wayland-scanner)//' configure.ac
}

pkg_preinst_${PN}() {
}

export libexecdir="${prefix}/libexec"

FILES_${PN} += "${prefix}/lib/${PN}/*.so"

FILES_${PN} += "${prefix}/bin/weston-scaler"
FILES_${PN} += "${prefix}/bin/weston-stacking"
FILES_${PN} += "${prefix}/bin/weston-multi-resource"