#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include "config.hpp"

#define center SDL_WINDOWPOS_CENTERED
#define width	 1000
#define height 700

SDL_Window * window = nullptr;
SDL_Renderer * renderer = nullptr;
SDL_Event event;

bool isrunning = true;
int n, a, b;
void plot(int arr[]);

void quit() { 
	isrunning = false;
}

void bubble_sort(int arr[]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (input() == 1) return;
			if (arr[j] > arr[j + 1]) {
				swap_pos(arr, arr[j], arr[j + 1]);
			}
		}
	}
}

void interchange_sort(int arr[]) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (input() == 1) return;
			if (arr[i] > arr[j]) {
				swap_pos(arr, arr[i], arr[j]);
			}
		}
	}
}

void select_sort(int arr[]) {
	for (int i = 0; i < n - 1; i++) {
		if (input() == 1) return;
		int &min = arr[i];
		int k = min_element(arr + i + 1, arr + n) - arr;
		if (min > arr[k]) {
			swap_pos(arr, min, arr[k]);
		}
	}
}

void insert_sort(int arr[]) {
	for (int i = 1; i < n; i++) {
		if (input() == 1) return;
		start(arr);
		int j = i - 1;
		while (j >= 0 && arr[i] < arr[j]) j--;
		int k = arr[i];
		for (int m = i; m >= j + 1; m--) {
			arr[m] = arr[m - 1];
		}
		arr[j + 1] = k;
	}
}

void merge_sort(int arr_t[], int arr[], int left, int right) {
	if (left == right) {
		return;
	}
	int mid = left + (right - left) / 2;
	merge_sort(arr_t, arr, left,    mid);
	merge_sort(arr_t, arr, mid + 1, right);
	int i = left, j = mid + 1, cur = 0;
	while (i <= mid || j <= right) {
		if (i > mid) {
			arr_t[cur++] = arr[j++];
		} else if (j > right) {
			arr_t[cur++] = arr[i++];
		} else if (arr[i] > arr[j]) {
			arr_t[cur++] = arr[j++];
		} else {
			arr_t[cur++] = arr[i++];
		}
	}
	for (int k = 0; k < cur; k++) {
		arr[left + k] = arr_t[k];
		start(arr);
	}
}

void quick_sort(int arr[], int left, int right) {
	if (!is_sorted(arr, arr + n)) {
		int pivot = arr[left + (right - left) / 2];
		int i = left, j = right;
		while (i < j) {
			while (arr[i] < pivot) i++;
			while (arr[j] > pivot) j--;
			if (i <= j) swap_pos(arr, arr[i++], arr[j--]);
		}
		if (left < j)  quick_sort(arr, left, j);
		if (i < right) quick_sort(arr, i, right);
	}
}

void count_sort(int arr[], int n, int exp = 1) {
	int arr_t[10], arr_t2[n];
	memset(arr_t, 0, sizeof arr_t);
	for (int i = 0; i < n; i++) {
		arr_t[ (arr[i] / exp) % 10]++;
	}
	for (int i = 1; i < 10; i++) {
		arr_t[i] += arr_t[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		arr_t2[ --arr_t[ (arr[i] / exp) % 10] ] = arr[i];
	}
	for (int i = 0; i < n; i++) {
		start(arr);
		arr[i] = arr_t2[i];
	}
}

void radix_sort(int arr[]) {
	int max = *max_element(arr, arr + n);
	for (int exp = 1; max / exp > 0; exp *= 10) {
		count_sort(arr, n, exp);
	}
}

int binary_search(int arr[], int x, int left, int right) {
	if(is_sorted(arr, arr + right + 1)) {
		int mid;
		do {
			mid = left + (right - left) / 2;
			if(x < arr[mid]) right = mid - 1;
			else if(x > arr[mid]) left = mid + 1;
			else return mid;
		}
		while (left != right);
	}
	return -1;
}

int f() {
	return rand() % (b - a + 1) + a;
}

void init(int arr[]) {
	srand(time(nullptr));
	generate(arr, arr + n, f);
}

void plot(int arr[]) {
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	for (int i = 0; i < n; i++) {
		SDL_RenderDrawLine(renderer, i, height, i, height - arr[i]);
	}
}

int main() {
	window = SDL_CreateWindow("SDL2", center, center, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	scanf("%d %d %d", &n, &a, &b);
	int arr[n], arr_t[n];
	init(arr);
	radix_sort(arr);
	SDL_Delay(1000);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
