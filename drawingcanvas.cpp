#include "drawingcanvas.h"

DrawingCanvas::DrawingCanvas(QWidget *parent)
{
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");

    initializePattern();
}

void DrawingCanvas::initializePattern() {
    m_segmentPatterns.clear();

    // // === 1. Horizontal Line (center row) ===
    // bool horizontal[5][5] = {
    //     {0,0,0,0,0},
    //     {0,0,0,0,0},
    //     {1,1,1,1,1},
    //     {0,0,0,0,0},
    //     {0,0,0,0,0},
    //     };
    // CustomMatrix h; h.fillMatrix(horizontal);
    // m_segmentPatterns.push_back(h);

    // // === 2. Vertical Line (center column) ===
    // bool vertical[5][5] = {
    //     {0,0,1,0,0},
    //     {0,0,1,0,0},
    //     {0,0,1,0,0},
    //     {0,0,1,0,0},
    //     {0,0,1,0,0},
    //     };
    // CustomMatrix v; v.fillMatrix(vertical);
    // m_segmentPatterns.push_back(v);

    // // === 3. Diagonal (top-left → bottom-right) ===
    // bool diagonal1[5][5] = {
    //     {1,0,0,0,0},
    //     {0,1,0,0,0},
    //     {0,0,1,0,0},
    //     {0,0,0,1,0},
    //     {0,0,0,0,1},
    //     };
    // CustomMatrix d1; d1.fillMatrix(diagonal1);
    // m_segmentPatterns.push_back(d1);

    // // === 4. Diagonal (top-right → bottom-left) ===
    // bool diagonal2[5][5] = {
    //     {0,0,0,0,1},
    //     {0,0,0,1,0},
    //     {0,0,1,0,0},
    //     {0,1,0,0,0},
    //     {1,0,0,0,0},
    //     };
    // CustomMatrix d2; d2.fillMatrix(diagonal2);
    // m_segmentPatterns.push_back(d2);

    // === 5. Cross (+ intersection) ===
    bool cross[5][5] = {
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0},
        {0,0,1,0,0},
        };
    CustomMatrix crossP;
    crossP.fillMatrix(cross);
    m_segmentPatterns.push_back(crossP);

    bool crossD[5][5] = {
        {1,0,0,0,1},
        {0,1,0,1,0},
        {0,0,1,0,0},
        {0,1,0,1,0},
        {1,0,0,0,1},
        };
    CustomMatrix crossPD;
    crossPD.fillMatrix(cross);
    m_segmentPatterns.push_back(crossP);

    // === 6. T-junction: top T ===
    bool t_top[5][5] = {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0},
        };
    CustomMatrix tTop;
    tTop.fillMatrix(t_top);
    m_segmentPatterns.push_back(tTop);

    bool t_topD[5][5] = {
        {1,0,0,0,0},
        {0,1,0,1,0},
        {0,0,1,0,0},
        {0,0,0,1,0},
        {0,0,0,0,1},
        };
    CustomMatrix tTopD;
    tTop.fillMatrix(t_topD);
    m_segmentPatterns.push_back(tTopD);

    bool t_topDR[5][5] = {
        {1,0,0,0,0},
        {0,1,0,0,0},
        {0,0,1,0,0},
        {0,1,0,1,0},
        {0,0,0,0,1},
        };
    CustomMatrix tTopDR;
    tTop.fillMatrix(t_topDR);
    m_segmentPatterns.push_back(tTopDR);

    bool t_topT[5][5] = {
        {1,0,0,0,1},
        {0,1,0,1,0},
        {0,0,1,0,0},
        {0,1,0,0,0},
        {1,0,0,0,0},
        };
    CustomMatrix tTopT;
    tTop.fillMatrix(t_topT);
    m_segmentPatterns.push_back(tTopT);

    bool t_topTR[5][5] = {
        {0,0,0,0,1},
        {0,0,0,1,0},
        {0,0,1,0,0},
        {0,1,0,1,0},
        {1,0,0,0,1},
        };
    CustomMatrix tTopTR;
    tTop.fillMatrix(t_topTR);
    m_segmentPatterns.push_back(tTopTR);

    // === 7. T-junction: bottom T ===
    bool t_bottom[5][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0},
        {0,0,1,0,0},
        };
    CustomMatrix tBottom;
    tBottom.fillMatrix(t_bottom);
    m_segmentPatterns.push_back(tBottom);

    // === 8. T-junction: left T ===
    bool t_left[5][5] = {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,1,1,1},
        {0,0,1,0,0},
        {0,0,0,0,0},
        };
    CustomMatrix tLeft;
    tLeft.fillMatrix(t_left);
    m_segmentPatterns.push_back(tLeft);

    // === 9. T-junction: right T ===
    bool t_right[5][5] = {
        {0,0,0,0,0},
        {0,0,1,0,0},
        {1,1,1,1,0},
        {0,0,1,0,0},
        {0,0,0,0,0},
        };
    CustomMatrix tRight;
    tRight.fillMatrix(t_right);
    m_segmentPatterns.push_back(tRight);

    cout << "Initialized " << m_segmentPatterns.size() << " patterns." << endl;
}


void DrawingCanvas::clearPoints(){
    m_points.clear();
    m_lines.clear();
    m_detectedSegments.clear();

    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::segmentDetection()
{
    m_detectedSegments.clear();

    QPixmap pixmap(this->contentsRect().size());
    pixmap.fill(Qt::white);
    this->render(&pixmap, QPoint(), this->contentsRect());

    QImage image = pixmap.toImage();

    cout << "image width " << image.width() << endl;
    cout << "image height " << image.height() << endl;

    // To not crash we set initial size of the matrix
    // vector<CustomMatrix> windows(image.width()*image.height());

    // Create binary representation of the image
    vector<vector<bool>> binaryImage(image.height(), vector<bool>(image.width(), false));

    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QRgb pixelColor = image.pixel(x, y);

            // Check if pixel is NOT white (white = 0xffffffff)
            // Also check if it's not the border (gray)
            if (pixelColor != 0xffffffff && pixelColor != 0xffc0c0c0) {
                binaryImage[y][x] = true;
            }
        }
    }

    // Scan image with 3x3 sliding window
    int detectionCount = 0;
    int windowCount = 0;

    // Get the pixel value as an ARGB integer (QRgb is a typedef for unsigned int)
    for(int i = 2; i < image.width() - 2; i++){
        for(int j = 2; j < image.height() - 2; j++){
            bool local_window[5][5] = {false};

            for(int m = -2; m <= 2; m++){
                for(int n = -2; n <= 2; n++){
                    QRgb rgbValue = image.pixel(i + m, j + n);
                    local_window[m + 2][n + 2] = (rgbValue != 0xffffffff);
                }
            }

            // Create CustomMatrix from the window
            CustomMatrix currentWindow;
            currentWindow.fillMatrix(local_window);

            // Skip empty window
            if (currentWindow.isEmpty()) {
                continue;
            }

            windowCount++;

            // Pattern Matching - Compare against reference patterns
            bool matchFound = false;
            for (size_t p = 0; p < m_segmentPatterns.size(); p++) {
                if (currentWindow.matches(m_segmentPatterns[p])) {
                    matchFound = true;
                    detectionCount++;

                    // Store the center point of detected segment
                    m_detectedSegments.push_back(QPoint(i, j));

                    // Debug output (optional - remove for production)
                    cout << "Match found at (" << i << ", " << j << ") with pattern " << p << endl;

                    // break; // No need to check other patterns
                }
            }

            // Dump non-empty windows for analysis
            if (!currentWindow.isEmpty() && windowCount <= 100) { // Limit output
                cout << "Window at (" << i << ", " << j << "):" << endl;
                currentWindow.print();
                cout << "Match: " << (matchFound ? "YES" : "NO") << endl;
                cout << "---" << endl;
            }

        }
    }

    cout << "=== Detection Complete ===" << endl;
    cout << "Non-empty windows: " << windowCount << endl;
    cout << "Detected segments: " << detectionCount << endl;

    // Trigger repaint to visualize detections
    update();
    return;
}

void DrawingCanvas::paintLines()
{
    if (m_points.size() < 2) return;

    // Connect points in pairs as lines and store them permanently
    for (int i = 0; i < m_points.size() - 1; i += 2) {
        QLine newLine(m_points[i], m_points[i + 1]);
        m_lines.append(newLine);
    }

    // Clear points after converting them to lines
    m_points.clear();

    update(); // trigger repaint
}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    pen.setColor(Qt::red);
    pen.setWidth(1); // 4-pixel wide line
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    for (const QLine &ln : std::as_const(m_lines))
        painter.drawLine(ln);

    // return painter pen to blue
    pen.setColor(Qt::blue);
    painter.setPen(pen);

    if (!m_detectedSegments.isEmpty()) {
        pen.setColor(QColor(128, 0, 128));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        for (const QPoint& segmentCenter : m_detectedSegments) {
            painter.drawRect(segmentCenter.x() - 4, segmentCenter.y() - 4, 8, 8);
        };
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


