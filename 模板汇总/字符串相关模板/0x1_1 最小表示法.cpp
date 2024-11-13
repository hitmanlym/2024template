void get_min() {
	int n; 
	std::cin >> n;
	for (int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		a[i + n] = a[i];
	}
	int i = 1, j = 2, k = 0;
	while (i <= n && j <= n && k < n) {
		if (a[i + k] == a[j + k]) k ++;
		else {
			a[i + k] > a[j + k] ? (i = i + k + 1) : (j = j + k + 1);
			if (i == j) j++; 
			k=0;
		}
	}
	k = std::min(i, j);
	for (int i = k; i < k + n; i ++) {
		std::cout << a[i] << " ";
	}
}