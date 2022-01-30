#pragma once
#include <fstream>
#include <memory>
#include <string_view>
#include <QtGui>
#include "qpoint.h"
#include "qsize.h"


int Distance(const QPoint& lhs, const QPoint& rhs);

QPoint LoadQPoint(std::ifstream& loader);

void SaveQPoint(std::ofstream& saver, const QPoint& obj);

QSize GetSize(const QPoint& _start, const QPoint& _end);

void ClearCanvas(QImage& canvas, int width, int height);

bool PointInRectangle(const QPoint& start, const QPoint& end, const QPoint& point);
