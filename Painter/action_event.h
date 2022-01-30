#pragma once
#include <QtWidgets/QMainWindow>
#include <memory>
#include <functional>
#include "shapemanager.h"
#include "qtalgorithm.h"
#include "line.h"

class ActionEvent {
protected:

    static std::shared_ptr<BaseShape> Draw(std::shared_ptr<BaseShape> obj, QImage& canvas);

    static std::shared_ptr<BaseShape> Draw(const QPoint& start, const QPoint& end, BaseShape::HashType currentID, QImage& canvas);

    static std::shared_ptr<BaseShape> TryDraw(const QPoint& pos1, const QPoint& pos2, BaseShape::HashType currentID, QImage& canvas);

public:
    virtual void mousePressEvent(QMouseEvent* event) = 0;

    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event) = 0;
};