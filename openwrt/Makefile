#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=fft2json
PKG_REV:=master
PKG_VERSION:=0.12
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://github.com/aquila/ath9k-spectral-scan.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_REV)

include $(INCLUDE_DIR)/package.mk

define Package/fft2json
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Spectral scan results to json
  DEPENDS:=+libc +@CONFIG_BUSYBOX_CONFIG_NC_SERVER
  URL:=https://github.com/aquila/ath9k-spectral-scan
endef

define Package/fft2json/description
 This package contains fft2json which translates the binary fft output from the ath9k spectral scan to json format.
endef

define Build/Compile
	$(MAKE)  -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) -Wall" \
		LDFLAGS="$(TARGET_LDFLAGS)" \
	fft2json
endef

define Package/fft2json/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fft2json $(1)/usr/bin/fft2json
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fftserver $(1)/usr/bin/fftserver
endef

$(eval $(call BuildPackage,fft2json))
