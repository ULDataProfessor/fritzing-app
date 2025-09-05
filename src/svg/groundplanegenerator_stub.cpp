/*******************************************************************

Part of the Fritzing project - http://fritzing.org
Copyright (c) 2007-2024 Fritzing

Fritzing is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Fritzing is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Fritzing.  If not, see <http://www.gnu.org/licenses/>.

********************************************************************/

#include "groundplanegenerator.h"
#include <QString>
#include <QSizeF>
#include <QGraphicsItem>
#include <QPointF>

// Stub implementation when Clipper is disabled
const QString GroundPlaneGenerator::KeepoutSettingName("GPG_Keepout");
const double GroundPlaneGenerator::KeepoutDefaultMils = 10;
QString GroundPlaneGenerator::ConnectorName("connector");

GroundPlaneGenerator::GroundPlaneGenerator() {
    // Stub constructor
}

GroundPlaneGenerator::~GroundPlaneGenerator() {
    // Stub destructor
}

bool GroundPlaneGenerator::generateGroundPlane(const QString & boardSvg, QSizeF boardImageSize, const QString & svg, QSizeF copperImageSize, QStringList & exceptions,
                                               QGraphicsItem * board, double res, const QString & color, double keepoutMils, QList<GroundFillSeed> seeds) {
    Q_UNUSED(boardSvg);
    Q_UNUSED(boardImageSize);
    Q_UNUSED(svg);
    Q_UNUSED(copperImageSize);
    Q_UNUSED(exceptions);
    Q_UNUSED(board);
    Q_UNUSED(res);
    Q_UNUSED(color);
    Q_UNUSED(keepoutMils);
    Q_UNUSED(seeds);
    // Ground plane generation disabled when Clipper is not available
    return false;
}

bool GroundPlaneGenerator::generateGroundPlaneFn(const GPGParams &params) {
    Q_UNUSED(params);
    // Ground plane generation disabled when Clipper is not available
    return false;
}

#ifndef DISABLE_CLIPPER
void GroundPlaneGenerator::makeCopperFillFromPolygons(QList<void*> &sortedPolygons, double res, const QString &colorString, bool makeConnectorFlag, QSizeF minAreaInches, double minDimensionInches) {
    Q_UNUSED(sortedPolygons);
    Q_UNUSED(res);
    Q_UNUSED(colorString);
    Q_UNUSED(makeConnectorFlag);
    Q_UNUSED(minAreaInches);
    Q_UNUSED(minDimensionInches);
    // Stub implementation
}
#endif

bool GroundPlaneGenerator::generateGroundPlaneUnit(const QString & boardSvg, QSizeF boardImageSize, const QString & svg, QSizeF copperImageSize, QStringList & exceptions,
                                                  QGraphicsItem * board, double res, const QString & color, QPointF whereToStart, double keepoutMils) {
    Q_UNUSED(boardSvg);
    Q_UNUSED(boardImageSize);
    Q_UNUSED(svg);
    Q_UNUSED(copperImageSize);
    Q_UNUSED(exceptions);
    Q_UNUSED(board);
    Q_UNUSED(res);
    Q_UNUSED(color);
    Q_UNUSED(whereToStart);
    Q_UNUSED(keepoutMils);
    // Ground plane generation disabled when Clipper is not available
    return false;
}

const QStringList & GroundPlaneGenerator::newSVGs() {
    return m_newSVGs;
}

const QList<QPointF> & GroundPlaneGenerator::newOffsets() {
    return m_newOffsets;
}

void GroundPlaneGenerator::setStrokeWidthIncrement(double increment) {
    Q_UNUSED(increment);
    // Stub implementation
}

void GroundPlaneGenerator::setLayerName(const QString & layerName) {
    Q_UNUSED(layerName);
    // Stub implementation
}

const QString & GroundPlaneGenerator::layerName() {
    static QString empty;
    return empty;
}

void GroundPlaneGenerator::setMinRunSize(int minRunSize, int minRiseSize) {
    Q_UNUSED(minRunSize);
    Q_UNUSED(minRiseSize);
    // Stub implementation
}

QString GroundPlaneGenerator::mergeSVGs(const QString & initialSVG, const QString & layerName) {
    Q_UNUSED(initialSVG);
    Q_UNUSED(layerName);
    return QString();
}

void GroundPlaneGenerator::createGroundThermalPads(GPGParams &params, double clipperDPI, std::vector<void*> &groundConnectorsZone, std::vector<void*> &groundThermalConnectors) {
    Q_UNUSED(params);
    Q_UNUSED(clipperDPI);
    Q_UNUSED(groundConnectorsZone);
    Q_UNUSED(groundThermalConnectors);
    // Stub implementation
}
