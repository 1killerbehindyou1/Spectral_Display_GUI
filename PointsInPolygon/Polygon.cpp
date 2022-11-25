#include "Polygon.h"

T_Polygon::T_Polygon(QQuickItem* parent) : QQuickPaintedItem(parent) {}

QPoint T_Polygon::A_point() const { return m_A; }
void T_Polygon::setA_Point(QPoint A) { m_A = A; }

QPoint T_Polygon::B_point() const { return m_B; }
void T_Polygon::setB_Point(QPoint B) { m_B = B; }

QPoint T_Polygon::C_point() const { return m_C; }
void T_Polygon::setC_Point(QPoint C) { m_C = C; }

QPoint T_Polygon::D_point() const { return m_D; }
void T_Polygon::setD_Point(QPoint D) { m_D = D; }

bool T_Polygon::setPixMap(const QUrl& path)
{

    if (!path.isLocalFile())
    {

        emit fileErrLoad(
            "Loaded file failed",
            "Ouch! This is remote file. We don't have handling for that "
            "right now");
        return false;
    }

    QString qstr =
        path.toLocalFile(); // zamiana ścieżki na sciezke do pliku lokanego
    QImage img{};

    if (!img.load(qstr))
    {
        emit fileErrLoad("Loaded file failed",
                         "File is corrupted or isn't graphic file");
        return false;
    }

    m_map = QPixmap::fromImage(std::move(img));

    if (m_map.isNull())
    {
        emit fileErrLoad("Loaded file failed", "Loaded file is null");
        return false;
    }
    // polygonUpdate();
    return true;
}

void T_Polygon::paint(QPainter* painter)
{
    QColor color("red");
    painter->drawPixmap(0, 0, m_map);
    painter->setBrush(color);

    painter->drawPolygon(translate(m_angle, m_top_left, m_side));
}

void T_Polygon::polygonUpdate(int angle, QPoint top_left, int side)
{

    m_angle = angle;
    m_top_left = top_left;
    m_side = side;
    update();
}

QPolygon T_Polygon::translate(int angle, QPoint top_left, int side)
{
    QPoint A, B, C, D;

    int c_side = side * cos(angle);
    int b_side = side * sin(angle);

    A.setX(top_left.x());
    A.setY(top_left.y());

    int x = A.x();
    int y = A.y();

    B.setX(x + c_side);
    B.setY(y + b_side);

    x = B.x();
    y = B.y();

    C.setX(x - b_side);
    C.setY(y + c_side);

    x = C.x();
    y = C.y();

    D.setX(x - c_side);
    D.setY(y - b_side);

    QVector<QPoint> vect;
    vect.push_back(A);
    vect.push_back(B);
    vect.push_back(C);
    vect.push_back(D);

    QPolygon poly(vect);
    return poly;
}