#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y;
} point;

int orientation(point a, point b, point c) {
	int val = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);

	if (!val) return 0;
	return (val > 0) ? 1 : 2;
}

void convex_hull(point points[], int n) {
	if (n < 3) return;

	point *hull = (point *)malloc(n * sizeof(point));
	int size = 0;

	int l = 0;
	for (int i = 1; i < n; i++) { if (points[i].x < points[l].x) l = i; }

	int p = l, q;
	do {
		hull[size++] = points[p];
		q = (p + 1) % n;

		for (int i = 0; i < n; i++) {
			if (orientation(points[p], points[i], points[q]) == 2) q = i;
		}

		p = q;
	} while (p != l);

	for (int i = 0; i < size; i++) {
		printf("(%d, %d)\n", hull[i].x, hull[i].y);
	}

	free(hull);
}

int main() {
	point points[] = { {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3} };
    
    int n = sizeof(points) / sizeof(points[0]);
    printf("The Boundary Coordinates are\n");
    convex_hull(points, n);
	return 0;
}
