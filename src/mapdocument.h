/*
 * Tiled Map Editor (Qt)
 * Copyright 2008 Tiled (Qt) developers (see AUTHORS file)
 *
 * This file is part of Tiled (Qt).
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef MAPDOCUMENT_H
#define MAPDOCUMENT_H

#include <QObject>

class QUndoStack;

namespace Tiled {

class Map;

namespace Internal {

class LayerTableModel;
class TileSelectionModel;

/**
 * Represents an editable map. The purpose of this class is to make sure that
 * any editing operations will cause the appropriate signals to be emitted, in
 * order to allow the GUI to update accordingly.
 *
 * At the moment the map document provides the layer model and keeps track of
 * the currently selected layer. It also owns the QUndoStack.
 */
class MapDocument : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructs a map document around the given map. The map document takes
     * ownership of the map.
     */
    MapDocument(Map *map);

    /**
     * Destructor.
     */
    ~MapDocument();

    /**
     * Returns the map instance. Be aware that directly modifying the map will
     * not allow the GUI to update itself appropriately.
     */
    Map *map() const { return mMap; }

    /**
     * Sets the current layer to the given index.
     */
    void setCurrentLayer(int index);

    /**
     * Returns the index of the currently selected layer.
     */
    int currentLayer() const;

    /**
     * Moves the given layer up. Does nothing when no valid layer index is
     * given.
     */
    void moveLayerUp(int index);

    /**
     * Moves the given layer down. Does nothing when no valid layer index is
     * given.
     */
    void moveLayerDown(int index);

    /**
     * Returns the layer model. Can be used to modify the layer stack of the
     * map, and to display the layer stack in a view.
     */
    LayerTableModel *layerModel() const { return mLayerModel; }

    /**
     * Returns the selection model.
     */
    TileSelectionModel *selectionModel() const { return mSelectionModel; }

    /**
     * Returns the undo stack of this map document. Should be used to push any
     * commands on that modify the map.
     */
    QUndoStack *undoStack() const { return mUndoStack; }

signals:
    /**
     * Emitted when the current layer changes.
     */
    void currentLayerChanged(int index);

private:
    Map *mMap;
    LayerTableModel *mLayerModel;
    TileSelectionModel *mSelectionModel;
    int mCurrentLayer;
    QUndoStack *mUndoStack;
};

} // namespace Internal
} // namespace Tiled

#endif // MAPDOCUMENT_H
