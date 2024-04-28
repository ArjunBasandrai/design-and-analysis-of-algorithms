#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y;
} point;

point p0;

void swap (point* p1, point* p2) {
	point temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int dist_sq(point p1, point p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(point p, point q, point r) {
	int val = (q.y - p.y) * (r.x - q.x) -
			(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; 
	return (val > 0) ? 1 : 2; 
}


int compare(const void* _p1, const void* _p2) {

	point* p1 = (point*) _p1;
	point* p2 = (point*) _p2;

	int o = orientation(p0, *p1, *p2);
	if (o == 0)
		return (dist_sq(p0, *p2) >= dist_sq(p0, *p1)) ? -1 : 1;
	return (o == 2) ? -1 : 1;

}

void convex_hull(point points[], int n) {

	int y_min = points[0].y, min_idx = 0;
	for (int i = 1; i < n; i++) {
		int y = points[i].y;
		if ((y < y_min) || (y == y_min && points[i].x < points[min_idx].x)) {
			y_min = y; min_idx = i;
		}
	}

	swap(&points[0], &points[min_idx]);
	p0 = points[0];
	qsort(&points[1], n-1, sizeof(point), compare);

	int m = 1;
	for (int i = 1; i < n; i++) {
		while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0)
			i++;
		points[m] = points[i];
		m++;
	}

	// If less than 3 points, convex hull is not possible because it is a line
	if (m < 3) return;

	point *stack = (point*) malloc(m * sizeof(point));
	int top = 0;
	stack[top++] = points[0];
	stack[top++] = points[1];

	for (int i = top; i < m; i++) {
		while (top > 1 && orientation(stack[top-2], stack[top-1], points[i]) != 2)
			top--;
		stack[top++] = points[i];
	}

	while (top > 0) {
		point p = stack[--top];
		printf("(%d, %d)\n", p.x, p.y);
	}

	free(stack);
}

int main() {
	point points[] = { {0, 3}, {1, 1}, {2, 2}, {4, 4},
					   {0, 0}, {1, 2}, {3, 1}, {3, 3} };
	int n = sizeof(points) / sizeof(points[0]);
	printf("The Boundary Coordinates are\n");
	convex_hull(points, n);
	return 0;
}
