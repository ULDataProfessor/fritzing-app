# Copyright (c) 2021,2024 Fritzing GmbH

message("Using Fritzing quazip detect script.")

# Try Homebrew-installed quazip first
HOMEBREW_QUAZIP = /opt/homebrew/include
HOMEBREW_QUAZIP_LIB = /opt/homebrew/lib

exists($$HOMEBREW_QUAZIP/QuaZip) {
	message("found Homebrew quazip in $$HOMEBREW_QUAZIP")
	INCLUDEPATH += $$HOMEBREW_QUAZIP
	LIBS += -L$$HOMEBREW_QUAZIP_LIB -lquazip1-qt6
	macx {
		LIBS += -lz
	}
} else {
	# Fallback to local build
	# We are currently using a quazip version from this PR:
	# https://github.com/stachenov/quazip/pull/199
	QUAZIP_VERSION=1.4
	QUAZIP_PATH=$$absolute_path($$PWD/../../quazip-$$QT_VERSION-$$QUAZIP_VERSION)intuisphere
	QUAZIP_INCLUDE_PATH=$$QUAZIP_PATH/include/QuaZip-Qt6-$$QUAZIP_VERSION
	QUAZIP_LIB_PATH=$$QUAZIP_PATH/lib

	SOURCES += \
		src/zlibdummy.c \

	exists($$QUAZIP_PATH) {
			message("found quazip in $${QUAZIP_PATH}")
		} else {
			message("quazip not found, disabling zip features")
			DEFINES += DISABLE_QUAZIP
		}

	INCLUDEPATH += $$QUAZIP_INCLUDE_PATH
	LIBS += -L$$QUAZIP_LIB_PATH -lquazip1-qt$$QT_MAJOR_VERSION

	unix {
		message("set rpath for quazip")
		QMAKE_RPATHDIR += $$QUAZIP_LIB_PATH
	}

	macx {
		LIBS += -lz
	}
}
