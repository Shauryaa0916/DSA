class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {
        
        // Find the closest point of the rectangle to the circle's center
        int closestX = max(x1, min(xCenter, x2));
        int closestY = max(y1, min(yCenter, y2));

        // Distance between circle center and closest rectangle point
        long long dx = xCenter - closestX;
        long long dy = yCenter - closestY;

        // If distance <= radius, they overlap
        return dx * dx + dy * dy <= 1LL * radius * radius;
    }
};