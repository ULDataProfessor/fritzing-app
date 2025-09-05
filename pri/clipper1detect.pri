# Copyright (c) 2023 Fritzing GmbH

message("Using fritzing Clipper 1 detect script.")

# Clipper library not available, disabling clipper features
message("Clipper library not found, disabling clipper features")
DEFINES += DISABLE_CLIPPER
DEFINES += DISABLE_SVGPP
